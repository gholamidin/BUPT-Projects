#include"mylib.h" 

void Open()
{
	
    FILE *fp;
    fp=fopen("Config.ini","r");
	fscanf(fp,"[WaitSec]%d\n",&WaitingSec);
    fscanf(fp,"[MaxSeqLen]%d\n",&MaxSeqLen);
    fscanf(fp,"[VIPMaxSeqLen]%d\n",&VIPMaxSeqLen);
    fscanf(fp,"[MinSec]%d\n",&MinSec);
    fscanf(fp,"[MaxSec]%d\n",&MaxSec);
    fscanf(fp,"[MinRestSec]%d\n",&MinRestSec);
    fscanf(fp,"[MaxRestSec]%d\n",&MaxRestSec);
    fscanf(fp,"[VIPSERVLen]%d\n",&VIPSERVLen);
    fscanf(fp,"[dropquit]%d\n",&dropquit);
}//读取配置文件 

void Initialization()
{
	int i;
	for(i=1;i<=8;i++)
	{
		windows[i].ServNo=0;
		windows[i].State=CLOSE;
		windows[i].ServTime=0;
		windows[i].BreakTime=0;
		windows[i].PServTime=0;
		windows[i].PBreakTime=0;
		windows[i].judge_Break=0;
		windows[i].judge_Serv=0; 
		windows[i].BreakTotalTime=0;
		windows[i].ServTotalTime=0;
		windows[i].SatisfyGood=0;
		windows[i].SatisfyNorm=0;
		windows[i].SatisfyBad=0;
		windows[i].CustNormCount=0;
		windows[i].CustVIPCount=0;
		windows[i].VIP_idleTime=0;
		windows[i].Value=-1; 
		windows[i].Value_Break=0;
	}//将八个窗口的信息初始化 
	for(i=0;i<=13;i++)
	{
		chair[i].Judge=0;
		chair[i].Num=0;
		chair[i].Value=-1;
	}
	for(i=1;i<=3;i++)
	    windows[i].State=IDLE;//打开三个普通窗口 
	windows[7].State=IDLE;//打开第一个VIP窗口 
	SerId=0;
	SerVIPId=0;//初始化号码 
	Strategy_Judge=1;//将策略默认输入为先来先服务策略 
	isquit=1;//用于判断是否下班，1为上班时，0为下班
	instantquit=1; 
}
//初始化银行状态 

void ChangeOpenfile()
{
	int value;
	prompt(); 
	scanf("%d",&value);
	while(value!=0)
	{
		if(value<0||value>9)
		{
			printf("亲，您的输入有误，请根据提示信息重新输入\n");
		}
		else
		{
			switch(value)
			{
			    case 1:
					printf("请输入窗口等待客户到来的最大时间.\n"); 
					scanf("%d",&WaitingSec);
					break;
				case 2:
					printf("请输入普通用户单条队列最大允许等待长度.\n");
					scanf("%d",&MaxSeqLen);
					break;
				case 3:
					printf("请输入VIP用户单条队列最大允许等待长度.\n");
					scanf("%d",&VIPMaxSeqLen);
					break;
				case 4:
					printf("请输入最小服务时长.\n");
					scanf("%d",&MinSec);
					break;
				case 5:
					printf("请输入最大服务时长.\n");
					scanf("%d",&MaxSec);
					break;
				case 6:
					printf("请输入窗口最小休息时间.\n");
					scanf("%d",&MinRestSec);
					break;
				case 7:
					printf("请输入普窗口最大休息时间.\n");
					scanf("%d",&MaxRestSec);
					break;
				case 8:
					printf("请输入VIP窗口动态关闭时间.\n");
					scanf("%d",&VIPSERVLen);
					break;
				case 9:
					printf("请输入下班时间.\n");
					scanf("%d",&dropquit);
					break;
			}
		}
		prompt();
		scanf("%d",&value);
		FILE *fp;
        fp=fopen("Config.ini","w");
        fprintf(fp,"[WaitSec]%d\n",WaitingSec);
        fprintf(fp,"[MaxSeqLen]%d\n",MaxSeqLen);
        fprintf(fp,"[VIPMaxSeqLen]%d\n",VIPMaxSeqLen);
        fprintf(fp,"[MinSec]%d\n",MinSec);
        fprintf(fp,"[MaxSec]%d\n",MaxSec);
        fprintf(fp,"[MinRestSec]%d\n",MinRestSec);
        fprintf(fp,"[MaxRestSec]%d\n",MaxRestSec);
        fprintf(fp,"[VIPSERVLen]%d\n",VIPSERVLen);
        fprintf(fp,"[dropquit]%d\n",dropquit);
        fclose(fp);
	}
}

int prompt()
{
	system("cls"); 
	printf( "*******************************************************************************\n" 
 		    "                         欢迎来到北京锤雷银行                                  \n"
 		    "                                                    编写人员：黄锐 周尧棋 朱魁 \n"
 		    "*******************************************************************************\n");
    printf("下面进入修改配置文件状态\n");
	printf("1 - 修改窗口等待客户到来的最大时间.\n");
	printf("2 - 修改普通用户单条队列最大允许等待长度.\n");
	printf("3 - 修改VIP用户单条队列最大允许等待长度.\n");
	printf("4 - 修改最小服务时长.\n");
	printf("5 - 修改最大服务时长.\n");
	printf("6 - 修改窗口最小休息时间.\n");
	printf("7 - 修改窗口最大休息时间.\n");
	printf("8 - 修改VIP窗口动态关闭时间.\n");
	printf("9 - 修改下班时间.\n");
	printf("0 - 退出.\n"); 
	return 0;
}


void option()
{
	int value,judge,judge_flag=1;
	system("cls");
    printf("*******************************************************************************\n" 
 		   "                         欢迎来到北京锤雷银行                                  \n"
 	       "                                                    编写人员：黄锐 周尧棋 朱魁 \n"
 		   "*******************************************************************************\n");
	printf("进入配置文件修改,请输入 1 \n"
           "进入VIP信息维护状态,请输入 2 \n"
		   "进入VIP窗口的服务策略选择,请输入 3 \n" 
	       "进入工作状态,请输入 4 \n");
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
            	system("cls");
                printf("*******************************************************************************\n" 
 		               "                         欢迎来到北京锤雷银行                                  \n"
 	                   "                                                    编写人员：黄锐 周尧棋 朱魁 \n"
 		               "*******************************************************************************\n");
            	printf("请选择VIP窗口的服务策略：\n");
	            printf("1 - VIP定向服务.\n"); 
	            printf("2 - VIP顺便服务.\n");
	            scanf("%d",&judge);
	            while(judge_flag==1)
	            {
	            	if(judge==1)
	            	{
	            		Strategy_Judge=1;
	            		judge_flag=0;
	            	}
	                else if(judge==2)
	                {
	                	Strategy_Judge=2;
	                	judge_flag=0;
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
	        	system("cls");
                printf("*******************************************************************************\n" 
 		               "                         欢迎来到北京锤雷银行                                  \n"
 	                   "                                                    编写人员：黄锐 周尧棋 朱魁 \n"
 		               "*******************************************************************************\n");
	        	printf("亲，您的输入有误，请根据提示信息重新输入\n");
	        	printf("进入配置文件修改,请输入 1 \n"
                       "进入VIP信息维护状态,请输入 2 \n"
		               "进入VIP窗口的服务策略选择,请输入 3 \n" 
	                   "进入工作状态,请输入 4 \n");
	        	scanf("%d",&value);
	        	break;
	        }
	    }
		printf("进入配置文件修改,请输入 1 \n"
               "进入VIP信息维护状态,请输入 2 \n"
		       "进入VIP窗口的服务策略选择,请输入 3 \n" 
	           "进入工作状态,请输入 4 \n");
	    scanf("%d",&value);
	}
	fflush(stdin);
}

