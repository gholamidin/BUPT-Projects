#include<windows.h>
#include<time.h>
#include"mylib.h"
#include"Open.h"
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

HANDLE hMutex;
DWORD WINAPI Fun1(LPVOID lpParameter);
DWORD WINAPI Fun2(LPVOID lpParameter);


int keyboard()
{
    FILE *outPtr=NULL;
	outPtr=fopen("output2.txt","w");
	int flag1=1,flag=1,i;
	HANDLE hThread1,hThread2;
	hMutex=CreateMutex(NULL,FALSE,NULL);
	LISTNODEPTR currentp,currentpVIP;
    Time=1; //系统时间初始化为1 
    headp=NULL;
    headpVIP=NULL;
    headpWinRest=NULL;
    Open();//读取配置文件 
    Initialization();//初始化银行状态 
    option();
    hThread1=CreateThread(NULL,0,Fun1,NULL,0,NULL);
    hThread2=CreateThread(NULL,0,Fun2,NULL,0,NULL);
    CloseHandle(hThread1);
    CloseHandle(hThread2);
    while(flag!=0) 
    {
        controllist();//把等待队列中的客户分配到窗口 
        state_trans();//改变各个窗口的状态
        print_message(outPtr);
        Time++;
        if(Time%5==0&&Time>=5)
        {
        	print_screen();
	        printf("普通用户叫号请输入  G\n");
        	printf("VIP用户叫号请输入   V\n");
        	printf("窗口申请休息请输入  R\n");
            printf("下班申请请输入      Q\n");
            printf("VIP信息维护请输入   X\n"); 
            printf("进入策略选择请输入  S\n");
            printf("您想输入的指令为：\n");
        }
            
        Sleep(1000);
    	if(isquit==0||Time>dropquit)
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
    	if(headp==NULL&&headpVIP==NULL&&flag1==0&&(isquit==0||Time>dropquit))
    	{
    	    flag=0;//用户等待为空 ，窗口均结束服务并且满意度评价完毕，下班，退出系统 
            for(i=1;i<=Size;i++)
                windows[i].State=CLOSE;
            print_message(outPtr);
        }
    }
    print_satisfy();
    int value,judge,value_flag=1;
    system("cls");
    printf("*******************************************************************************\n" 
 		   "                         欢迎来到北京锤雷银行                                  \n"
 	       "                                                    编写人员：黄锐 周尧棋 朱魁 \n"
 		   "*******************************************************************************\n");
	printf("进入配置文件修改,请输入 1 \n"
           "进入VIP信息维护状态,请输入 2 \n"
		   "进入VIP窗口的服务策略选择,请输入 3 \n" 
	       "完全退出程序,请输入 4 \n");
	fflush(stdin);
	scanf("%d",&value);
	while(value!=4)
	{
		switch(value)
		{
			case 1:
				printf("下面进入修改配置文件状态\n");
	            ChangeOpenfile(); //修改配置文件上的数据(但是并不改变源文件)
	            break;
	        case 2:
	        	printf("下面进入VIP信息维护状态：\n");
                VIPdata();//VIP信息维护
                break;
            case 3:
            	printf("请选择VIP窗口的服务策略：\n");
	            printf("1 - VIP定向服务.\n"); 
	            printf("2 - VIP顺便服务.\n");
	            scanf("%d",&judge);
	            while(value_flag==1)
	            {
	            	if(judge==1)
	            	{
	            		Strategy_Judge=1;
	            		value_flag=0;
	            	}
	                else if(judge==2)
	                {
	                	Strategy_Judge=2;
	                	value_flag=0;
	                }
	                else
	                {
	                	printf("亲,您的输入有误,请根据提示信息重新输入:\n");
	        	        printf("VIP定向服务策略请输入 1 \n");
				        printf("VIP顺便服务策略请输入 2 \n");
				        scanf("%d",&judge);
	                }
	            }
	            break;
	        default:
	        {
	        	printf("亲，您的输入有误，请根据提示信息重新输入\n");
	        	printf("进入配置文件修改,请输入 1 \n"
                       "进入VIP信息维护状态,请输入 2 \n"
		               "进入VIP窗口的服务策略选择,请输入 3 \n" 
	                   "完全退出程序,请输入 4 \n");
	        	scanf("%d",&value);
	        	break;
	        }
	    }
	    system("cls");
        printf("*******************************************************************************\n" 
 		       "                         欢迎来到北京锤雷银行                                  \n"
 	           "                                                    编写人员：黄锐 周尧棋 朱魁 \n"
 		       "*******************************************************************************\n");
		printf("进入配置文件修改,请输入 1 \n"
               "进入VIP信息维护状态,请输入 2 \n"
		       "进入VIP窗口的服务策略选择,请输入 3 \n" 
	           "完全退出程序,请输入 4 \n");
	    scanf("%d",&value);
	 
	}
	fflush(stdin);
	fclose(outPtr);
	return 0;
}

DWORD WINAPI Fun1(LPVOID lpParameter)
{
    WaitForSingleObject(hMutex,INFINITE);
	if(Time>=5) 
	    print_screen();
    ReleaseMutex(hMutex);
	Sleep(5000);	
}

DWORD WINAPI Fun2(LPVOID lpParameter)
{	
	while(isquit!=0&&Time<=dropquit)
	{
	    LISTNODEPTR currentp,currentpVIP,lastp,lastpVIP;
        RESTLISTNODEPTR currentpW,lastpW;
	    char type,id[20];
	    int restwindow;        //restwindow为申请休息的窗口  vipx为0表示VIP通过验证 否则未通过验证 
        int num,flag1=1,time,flag=1,n=0,i=0;
        struct vipdata indata[50],cvip;
        FILE * fvip;
        fvip=fopen("vip.dat","rb+");
        fread(&cvip,sizeof(struct vipdata),1,fvip);
     	while(!feof(fvip))
    	{
	    	indata[n]=cvip;
    		fread(&cvip,sizeof(struct vipdata),1,fvip);
    		n++;
    	}//将文件中已有的信息储存到结构体数组中
    	fclose(fvip);
    	fflush(stdin);
	    printf("普通用户叫号请输入  G\n");
	    printf("VIP用户叫号请输入   V\n");
	    printf("窗口申请休息请输入  R\n");
        printf("下班申请请输入      Q\n");
        printf("VIP信息维护请输入   X\n"); 
        printf("进入策略选择请输入  S\n");
        printf("您想输入的指令为：\n");
	    while(isquit!=0&&Time<=dropquit)
	    {
	    	time=3;
	    	fflush(stdin);
			WaitForSingleObject(hMutex,INFINITE);
            fflush(stdin);
            scanf("%c",&type);
	    	switch(type) 
    		{
		        case 'V':
		        	printf("请输入您的VIP号码:\n");
		        	scanf("%s",&id);
		        	fflush(stdin);
             		while(flag==1)
             		{
             			i=0;
					    while(i<=n&&strcmp(id,indata[i].VIPID)!=0)
             		        i++;
             			if(strcmp(id,indata[i].VIPID)==0)   //通过验证则添加队列 
	            	    {
	        	    	    SerVIPId=SerVIPId+1;
			                currentpVIP=(LISTNODEPTR)malloc(sizeof(LISTNODE));
			                if(currentpVIP!=NULL)
			                {
			                    currentpVIP->Num=SerVIPId;
			                    if(headpVIP==NULL)
			                    {
					        	    headpVIP=currentpVIP;
			    		    	    lastpVIP=currentpVIP;
			                    }
				    	        else
				    	        {
			    		            lastpVIP->nextPtr=currentpVIP;
		    			    	    lastpVIP=currentpVIP;	
			    		        }
			                }
	                        lastpVIP->nextPtr=NULL;
			                printf("亲爱的VIP用户，您的号码为%d。\n",SerVIPId);
		    	            break;
	                	}            //未通过验证 直接进入普通队列 
	                 	else if(time>=1)
	                	{
						    if(time>1)
				            {
							    time--;
	                		    printf("您输入的VIP号有误，请重新输入VIP号（剩余输入此数%d次）:\n",time);
				                scanf("%s",&id);
				            	fflush(stdin);
				            }
			    		    else
			    		    {
			    		    	flag=0; 
			    		    }
	                	}
             	    }
             	    if(flag!=0)
             	        break;
					flag=1;
	    		case 'G':
		    	    SerId=SerId+1;
		    	    currentp=(LISTNODEPTR)malloc(sizeof(LISTNODE));
		    	    if(currentp!=NULL)
			        {
	    		        currentp->Num=SerId;
	    		        if(headp==NULL)
	    		        {
	    					headp=currentp;
	    					lastp=currentp;
	    		        }
	    				else
	    				{
	    				    lastp->nextPtr=currentp;
	    					lastp=currentp;	
	    				}
	    		    }
	                lastp->nextPtr=NULL;
	                if(type=='G')      //判断直接是普通客户还是VIP为通过客户 
	    		        printf("亲爱的普通用户，您的号码为%d\n",SerId);
	    		    else
	    		        printf("很遗憾你已经输错三次，现在给您安排普通号%d，请您到休息区等待叫号，谢谢合作\n",SerId);
	    		    break;
	            case 'R':
	            	printf("请输入想要休息的窗口号：\n");
					scanf("%d",&restwindow);
	            	fflush(stdin);
    	        	while(restwindow!=1&&restwindow!=2&&restwindow!=3&&restwindow!=4&&restwindow!=5&&restwindow!=6&&restwindow!=7&&restwindow!=8)
    	            {
    	            	printf("您的输入有误,请根据提示信息正确输入\n"); 
    	            	printf("请输入想要休息的窗口号：\n");
						scanf("%d",&restwindow);
	            	    fflush(stdin);
    	            }
					printf("窗口%d提出休息请求\n\n",restwindow);
    	        	currentpW=(RESTLISTNODEPTR)malloc(sizeof(RESTLISTNODE));
    			    if(currentpW!=NULL)
    			    {
    			        currentpW->WinNo=restwindow;
    			        if(headpWinRest==NULL)
    			        {
    						headpWinRest=currentpW;
    						lastpW=currentpW;
    			        }
	    				else
    					{
    					    lastpW->nextPtr=currentpW;
    						lastpW=currentpW;	
    					}
    			    }
    	            lastpW->nextPtr=NULL;
    	            break;
    	        case 'Q':
    	        	isquit=0;
    	        	printf("已收到下班请求，正在等待下班。\n\n"); 
    	        	break;
    	        case 'X':
    	        	VIPdata();
    	        	break;
    	        case 'S':
    	        	printf("VIP定向服务策略请输入 1 \n");
    				printf("VIP顺便服务策略请输入 2 \n"); 
    				fflush(stdin);
    	        	scanf("%d",&num);
    	        	while(flag1==1)
	            	{
	            		if(num==1)
    	        	    {
    	        	    	Strategy_Judge=1;
    	        	    	flag1=0;
    	        	    	printf("已选择VIP定向服务策略\n\n"); 
    	            	}
    	            	else if(num==2)
	                	{
    	            		Strategy_Judge=2;
	                		flag1=0;
	                		printf("已选择VIP顺便服务策略\n\n"); 
	                	}
	            	    else
	            	    {
	            	    	printf("亲,您的输入有误,请根据提示信息重新输入:\n");
	            	    	printf("VIP定向服务策略请输入 1 \n");
	    			        printf("VIP顺便服务策略请输入 2 \n");
	    			        fflush(stdin);
	    			        scanf("%d",&num);
	            	    }
    	        	}
    	        	flag1=1; 
    	        	break;
     		}
    	}
	}
	ReleaseMutex(hMutex);
	return 0;
}

