
#include"mylib.h"
#include"Open.h"
#include"output.h"
#include"State_trans.h"
#include"Control.h"
#include"vip.h"
#include<windows.h>

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

 
HEGG noregg[100],String,eggVip[100],eggwin[9],hnorlist,hVIPlist;

LISTNODEPTR headp,headpVIP;
RESTLISTNODEPTR headpWinRest;

struct WINDOW windows[9];
struct CHAIR chair[14];  //判断座位的状态 

RESTLISTNODEPTR lastrp;
LISTNODEPTR lastp,lastpVIP;

int graphical()
{
	
	double X,Y,eggX,eggY; 
	HEGG hEggs,hEggs1,hgou;
	EVENT_TYPE ev;
	int flag=1,flag1=1,i;
	FILE *outPtr=NULL,*output=NULL;
	output=fopen("ins_output.txt","w");
	fclose(output);
	outPtr=fopen("output3.txt","w");
	Open();//读取配置文件 
    Initialization();//初始化银行状态
    option(); 
	EggStart(900,500);//创立盘子 
	PlaySound(TEXT("欢迎来到北京锤雷银行.wav"),NULL,SND_FILENAME|SND_ASYNC);

	hEggs=LayEgg();
	DrawBitmap("背景.bmp");//将背景图贴到屏幕上 
	hgou=LayEgg();
	MovePen(176,485);
	DrawBitmap("对号.bmp");
	for(i=1;i<=8;i++)
	    eggwin[i]=LayEgg();
	hnorlist=LayEgg();
	hVIPlist=LayEgg();
	SetActiveEgg(hEggs);
	StartTimer(1000); 
	while((ev=WaitForEvent())!=EXIT)
	{
		switch(ev)
		{
			case TIMER:
				controllist();//把等待队列中的客户分配到窗口 
                state_trans();//改变各个窗口的状态
                addwinpic(); //显示窗口的状态 
                moveguest(); //移动客户 
                printfnorlist();//打印普通客户等待链表中的总人数 
                printfVIPlist();//打印VIP客户等待链表中的总人数 
                print_message(outPtr);//每过一秒，将窗口信息储存下来 
                print_screen();//每过一秒，将窗口信息打印到屏幕上 
                Time++;//一定时间执行一次TIMER时间 
				break;
			case KEYDOWN:
				if(isquit!=0&&Time<=dropquit)//当没有接受到下班指令以及没到下班时间时 
				{
					if(GetStruckKey() == VK_LBUTTON)
			        {
			        	X = GetMouseX();
			            Y = GetMouseY();  //获取鼠标点击的坐标 
		        	    if(Y<=492&&Y>=462&&X>=1&&X<=175) //点击IP定向服务策略图标 
		        		{
		          			SetActiveEgg(hgou);
	        				EatEgg();
	        				hgou=LayEgg();
	        				MovePen(176,485);
	                        DrawBitmap("对号.bmp");
	                        Strategy_Judge=1; 
	                        SetActiveEgg(String);
	                        EatEgg();
	                        String=LayEgg();
	                        MovePen(0,130);
	                        DrawString("   已将策略改为VIP定向服务");
	                        output=fopen("ins_output.txt","a");
                            fprintf(output,"T=%d,将策略改成VIP定向服务。\n",Time);
                            fclose(output);
							PlaySound(TEXT("亲您已选择了VIP定向服务策略.wav"),NULL,SND_FILENAME|SND_ASYNC);
                            SetActiveEgg(hEggs);
	        			}
	    	    	    else if(Y>=420&&Y<=450&&X>=1&&X<=175) //点击VIP顺便服务策略图标 
	    	    	    {
	    	    	    	SetActiveEgg(hgou);
	    	    			EatEgg();
	    	    			hgou=LayEgg();
	    	    			MovePen(176,445);
	                        DrawBitmap("对号.bmp");
	                        Strategy_Judge=2; 
	                        SetActiveEgg(String);
	                        EatEgg();
	                        String=LayEgg();
	                        MovePen(0,130);
	                        DrawString("   已将策略改为VIP顺便服务");
	                        output=fopen("ins_output.txt","a");
                            fprintf(output,"T=%d,将策略改成VIP顺便服务。\n",Time);
                            fclose(output);
                            PlaySound(TEXT("亲您已选择了VIP顺便服务策略.wav"),NULL,SND_FILENAME|SND_ASYNC);
                            SetActiveEgg(hEggs);
	    		        }
	    		        else if(X>=69&&X<=131&&Y>=149&&Y<=209)//VIP客户到来
						{
							PlaySound(TEXT("欢迎光临.wav"),NULL,SND_FILENAME|SND_SYNC);
							input_VIP();
						}
						else if(Y<=209&&Y>=149&&X>=2&&X<=64) //普通客户到来 
						{ 
						    PlaySound(TEXT("欢迎光临.wav"),NULL,SND_FILENAME|SND_ASYNC);
					        buttonG();
						} 
						else if(X>=2&&X<=64&&Y>=344&&Y<=404) //点击窗口休息请求图标 R1-R8 
	    	    	    {
	    	    	    	getrest(1);
	    	    	    	PlaySound(TEXT("窗口1.wav"),NULL,SND_FILENAME|SND_ASYNC);
	    	    	    }
						else if(X>=68&&X<=130&&Y>=344&&Y<=404)
						{
							getrest(2);
	     	    	    	PlaySound(TEXT("窗口2.wav"),NULL,SND_FILENAME|SND_ASYNC);
						}
	     	    	    else if(X>=134&&X<=196&&Y>=344&&Y<=404)
	     	    	    {
	     	    	    	getrest(3);
							PlaySound(TEXT("窗口3.wav"),NULL,SND_FILENAME|SND_ASYNC);
	     	    	    }
	    	    	    else if(X>=2&&X<=64&&Y>=277&&Y<=337)
	    	    	    {
	    	    	    	getrest(4);
	    	    	    	PlaySound(TEXT("窗口4.wav"),NULL,SND_FILENAME|SND_ASYNC);
	    	    	    }
   	    	    	    else if(X>=68&&X<=130&&Y>=277&&Y<=337)
   	    	    	    {
   	    	    	    	getrest(5);
   	    	    	    	PlaySound(TEXT("窗口5.wav"),NULL,SND_FILENAME|SND_ASYNC);
   	    	    	    }
    		    	    else if(X>=134&&X<=196&&Y>=277&&Y<=337)
    		    	    {
    		    	    	getrest(6);
    		    	    	PlaySound(TEXT("窗口6.wav"),NULL,SND_FILENAME|SND_ASYNC);
    		    	    }
    		      	    else if(X>=2&&X<=64&&Y>=211&&Y<=271)
    		      	    {
    		      	    	getrest(7);
    		      	    	PlaySound(TEXT("窗口7.wav"),NULL,SND_FILENAME|SND_ASYNC);
    		      	    }
    		    	    else if(X>=68&&X<=130&&Y>=211&&Y<=271)
    		    	    {
    		    	    	getrest(8);
    		    	    	PlaySound(TEXT("窗口8.wav"),NULL,SND_FILENAME|SND_ASYNC);
    		    	    }
    		    	    	//窗口1-8的休息请求提出 
    		      	    else if(X>=134&&X<=196&&Y>=149&&Y<=209) //点击下班图标Q 
    		      	    {
					        isquit=0;
    		      	    	SetActiveEgg(String);
	                        EatEgg();
	                        String=LayEgg();
	                        MovePen(0,140);
	                        DrawString("        下班指令已发出");
	                        MovePen(0,120);
							DrawString("      无法进行叫号等操作");
	                        output=fopen("ins_output.txt","a");
                            fprintf(output,"T=%d,发出下班指令。\n",Time);
                            fclose(output);
    		      	    }//下班请求指令的提出 
	    			}
		    	}
				break;
	   	} 
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
        if(flag==0)
            break;
	}
	StopTimer();
	PlaySound(NULL,NULL,SND_FILENAME); //背景音乐停止 
	print_satisfy();
	fclose(outPtr);
	PlaySound(TEXT("下班成功再见.wav"),NULL,SND_FILENAME|SND_SYNC); //播放下班音乐 
	PlaySound(TEXT("下课喽.wav"),NULL,SND_FILENAME|SND_ASYNC);
}

int getrest(int num)
{
	int flag=1;
	char c[2];
	RESTLISTNODEPTR crp,newrp;
	FILE *fp=NULL;
	fp=fopen("ins_output.txt","a"); 
	crp=headpWinRest;
	while(crp!=NULL&&flag==1)
	{
	    if(crp->WinNo==num)
	   	    flag=0;
	    crp=crp->nextPtr;
	}//如果窗口休息等待链表中有请求，则无法通过 
	if(flag==1)
	{
	    newrp=(RESTLISTNODEPTR)malloc(sizeof(RESTLISTNODE));
    	if(newrp!=NULL)
    	{
    		newrp->WinNo=num;
    		newrp->nextPtr=NULL;
    		if(headpWinRest==NULL)
    		{
    		    headpWinRest=newrp;
    	    	lastrp=newrp;
    	    }
    		else
    	    {
    		    lastrp->nextPtr=newrp;
    		    lastrp=newrp;
    	    }
    	}//将请求存入等待链表 
    	fprintf(fp,"T=%d,窗口%d发出休息请求。\n",Time,num);
    	SetActiveEgg(String);
    	EatEgg();
    	String=LayEgg();
    	MovePen(0,130);
	    DrawString("      窗口");
	    sprintf(c,"%d",num);
	    DrawString(c);
     	DrawString("发出休息请求。");
     	
    	printf("T=%d,窗口%d发出休息请求。\n",Time,num);
	}
    flag=1;
    fclose(fp);
}
int buttonG()
{
	LISTNODEPTR currentp;       //普通用户链表节点 
	int i,restnum=0;            //restnum是被占座位个数 
	char c[2];                  //存储普通用户号码的字符形式 
	FILE *fptr=NULL;
	fptr=fopen("ins_output.txt","a");
	SerId=SerId+1;
	currentp=(LISTNODEPTR)malloc(sizeof(LISTNODE));    //普通用户队列加一 
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
	fprintf(fptr,"T=%d,来了一位普通用户。\n",Time);
	printf("亲爱的普通用户，您的号码为%d\n",SerId);
	SetActiveEgg(String);
	EatEgg();
	String=LayEgg();       //下蛋并显示提示信息 
	MovePen(0,140);
	DrawString("       亲爱的普通用户,您好！               ");
	MovePen(0,120);
	DrawString("       您的号码为:");
	sprintf(c,"%d",SerId);
	DrawString(c);
	DrawString("号               "); 
	restnum=0;
	for(i=0;i<=13;i++)               //判断被占座位个数
	{
		if(chair[i].Judge==1)
		restnum++;
	}
	if(restnum<14)
	{
		for(i=0;i<=13;i++)        //找到最近的座位 
		{
			if(chair[i].Judge==0)
			    break;
		}
		noregg[SerId]=LayEgg();         //修改座位属性信息 
		chair[i].Judge=1;
		chair[i].Value=0;
		chair[i].Num=SerId;
		if(i<=6)                            //动画显示普通客户到来等待 
		{
			MovePen(230+(i*85),173);
			DrawBitmap("普通用户.bmp");
		}
		else
		{
			MovePen(230+((i-7)*85),80);
			DrawBitmap("普通用户.bmp");
		}
	}
	else
	    noregg[SerId]=LayEgg();
	fclose(fptr);
}


int addwinpic()
{
	int i;
	for(i=1;i<=8;i++)
	{
		SetActiveEgg(eggwin[i]);
		EatEgg();
		eggwin[i]=LayEgg();
		MovePen(110+89*i,500);
		switch(windows[i].State)
		{
			case CLOSE:
				DrawBitmap("关闭.bmp");
				break;
			case IDLE:
				DrawBitmap("空闲.bmp");
				break;
			case WAITING:
				DrawBitmap("叫号中.bmp"); 
				break;
			case ENDING:
				DrawBitmap("评估中.bmp");
				break;
			case BREAK:
				DrawBitmap("休息中.bmp"); 
				break;
			case PROCESSING:
			    DrawBitmap("服务中.bmp"); 
				break;
		}//将图片贴到窗口上以显示窗口当前状态 
	}
	return 0;
}//显示当前窗口的服务状态 

int moveguest()
{
	int num,i,j,k;
	for(i=1;i<=Size;i++)
	{
		if(windows[i].State==PROCESSING)
		{
			if(windows[i].ServTime==0)
			{
			    num=windows[i].ServNo;
				if(windows[i].Value==1)
				{
					SetActiveEgg(noregg[num]);
					EatEgg();
					noregg[num]=LayEgg();
					MovePen(141+85*i,400);
					DrawBitmap("普通用户.bmp");
					for(j=0;j<=13;j++)
					{
						if(chair[j].Num==num)
						    chair[j].Judge=0;
					}
					//贴图，把普通用户贴到窗口下面
				}
				else if(windows[i].Value==2)
				{
					SetActiveEgg(eggVip[num]);
					EatEgg();
					eggVip[num]=LayEgg();
					MovePen(141+85*i,400);
					DrawBitmap("VIP.bmp");
					for(j=0;j<=13;j++)
					{
						if(chair[j].Num==num)
						    chair[j].Judge=0;
					}
					//贴图，把VIP用户贴到窗口下面
				}
			}
			else if(windows[i].ServTime==windows[i].PServTime)
			{
				num=windows[i].ServNo;
				if(windows[i].Value==1)
				{
			    	SetActiveEgg(noregg[num]);
				}
				else if(windows[i].Value==2)
				{
					SetActiveEgg(eggVip[num]);
				}
				for(k=1;k<=10;k++)
				{
					OffsetEgg((745-141-85*i)/10,(281-400)/10);
					Sleep(50);
				}//如果服务完毕，将顾客移动到门口，消失 
				EatEgg();
			}
		}
	}
	return 0;
}

int printfnorlist()
{
	char c[2];
	int i=0;
	LISTNODEPTR currentp;
	currentp=headp; 
	SetActiveEgg(hnorlist);
	EatEgg();
	hnorlist=LayEgg();
	while(currentp!=NULL)
	{
		i++;
		currentp=currentp->nextPtr;
	}
	MovePen(840,117);
	sprintf(c,"%d",i);
	DrawString(c);
}//打印普通等待链表中的等待顾客总人数 

int printfVIPlist()
{
	char c[2];
	int i=0;
	LISTNODEPTR currentp;
	currentp=headpVIP; 
	SetActiveEgg(hVIPlist);
	EatEgg();
	hVIPlist=LayEgg();
	while(currentp!=NULL)
	{
		i++;
		currentp=currentp->nextPtr;
	}
	MovePen(840,87);
	sprintf(c,"%d",i);
	DrawString(c);
}//等待VIP等待链表中的等待顾客总人数 
























