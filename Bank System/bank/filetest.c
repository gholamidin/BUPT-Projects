#include<windows.h>
#include<time.h>
#include"mylib.h"
#include"Open.h"
#include"file_input.h"
#include"output.h"
#include"State_trans.h"
#include"Control.h"
#include"vip.h"

int SerId;// 普通客户的号码 
int SerVIPId;// VIP用户的号码 
int T; //发生某个事件的时间
int Time;// 系统时间
int Strategy_Judge;// 用于判断策略 （1为VIP定向服务，2为VIP顺便服务） 
int isquit;  // 用于判断是否下班 

int WaitingSec; //预计等待客户到达窗口的时间
int MaxSeqLen; //普通用户单条队列最大允许等待长度
int VIPMaxSeqLen; //VIP用户单条队列最大允许等待长度
int MinSec; //最小服务时长
int MaxSec; //最大服务时长
int MinRestSec; //窗口最小休息时间
int MaxRestSec; //窗口最大休息时间
int VIPSERVLen; //VIP窗口动态关闭时间
int dropquit; //下班时间 
LISTNODEPTR headp,headpVIP;
RESTLISTNODEPTR headpWinRest;
LISTNODEPTR instantheadp,instantheadpVIP;
RESTLISTNODEPTR instantheadpWinRest;
int instantquit;//暂时储存下班发起指令 
struct WINDOW windows[9];


int file()
{
	int flag1=1,flag=1,i;
	FILE *fPtr=NULL,*outPtr=NULL;
	LISTNODEPTR currentp,currentpVIP;
	Time=1; //系统时间初始化为1 
	headp=NULL;
	headpVIP=NULL;
	headpWinRest=NULL;
	fPtr=fopen("input.txt","r");
	outPtr=fopen("output1.txt","w");
	Open();//读取配置文件 
    Initialization();//初始化银行状态 
	ChangeOpenfile(); //修改配置文件上的数据(但是并不改变源文件) 
    VIPdata();//VIP信息维护 
    system("cls");
    printf( "*******************************************************************************\n" 
 		    "                         欢迎来到北京锤雷银行                                  \n"
 		    "                                                    编写人员：黄锐 周尧棋 朱魁 \n"
 		    "*******************************************************************************\n");
    printf("请选择VIP窗口的服务策略：\n");
	printf("1 - VIP定向服务.\n"); 
	printf("2 - VIP顺便服务.\n");
	scanf("%d",&Strategy_Judge);
	while(Strategy_Judge!=1&&Strategy_Judge!=2)
	{
		printf("亲，您的输入有误，请根据提示信息重新输入\n");
		printf("请选择VIP窗口的服务策略：\n");
	    printf("1 - VIP定向服务.\n"); 
	    printf("2 - VIP顺便服务.\n");
	    scanf("%d",&Strategy_Judge);
	}
    input(fPtr);
    
    while(flag!=0) 
    {
	    if(Time==T)
	    {
	    	AddServList();//将读取的事件添加到服务链表中 
	    }
		controllist();//把等待队列中的客户分配到窗口 
		state_trans();//改变各个窗口的状态 
		 
		if(Time==T&&isquit!=0&&Time<=dropquit)
		{
			input(fPtr);
		}
		if(isquit==0||Time>dropquit)
		    fclose(fPtr);
    	//Sleep(100);
		print_message(outPtr);
		Time++;
		if(isquit==0||Time>=dropquit)
		{
			flag1=0;
			for(i=1;i<=Size;i++)
		    {
			    if(windows[i].ServNo!=0||windows[i].State==ENDING)
			    {
				    flag1=1;
			        break; 
			    }//如果有窗口还在服务客户或者在满意度评价状态，则不能下班 
		    }
		}
		if(headp==NULL&&headpVIP==NULL&&flag1==0)
		{
			flag=0;//用户等待为空 ，窗口均结束服务并且满意度评价完毕，下班，退出系统 
			for(i=1;i<=Size;i++)
			{
                windows[i].State=CLOSE;
            }
			print_message(outPtr);
		    fclose(outPtr);
		}  
    } 
    
    print_satisfy();
	printf("下班成功\n");
    //system("pause");
    return 0;
}

