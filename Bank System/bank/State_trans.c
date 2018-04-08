
#include<time.h>
#include"mylib.h"
#include"Control.h"

void state_trans()
{
	
    int i;
	int guestcome;    //随机数模拟客户是否到来 
	int satisfaction; //随机数模拟客户的满意度 
    int Normalsize=0;   //当前正在运行的普通窗口数
    int VIPsize=0;      //当前正在运行的VIP窗口数
    VIPsize=OpenVIPwindow(); 
    Normalsize=OpenNormalwindow();
    RESTLISTNODEPTR currentrp;
	srand(time(NULL));
	
	for(i=1;i<=Size;i++)
	{
	    switch(windows[i].State)
		{
	        case CLOSE:
			    if((i<=6)&&(controlwin()==1)&&(headp!=NULL))     //窗口数不足，转化为空闲状态 
                {
				    windows[i].State=IDLE;
                } 
                else if((i>=7)&&(controlVIPwin()==1)&&(headpVIP!=NULL))
                {
			        windows[i].State=IDLE;
                }
				break;
			case IDLE:
                if(i>=1&&i<=6)  //对普通窗口的处理 
                {
   	                if((i>=4&&i<=6)&&controlwin()==0&&windows[i].ServNo==0)
   	                {
 	   	                windows[i].State=CLOSE;             //普通客户人数过少，转化为关闭状态
 	   	                break;
                    }
                    controlrest(); 
                    if((Normalsize>3)&&(windows[i].Value_Break==2)&&windows[i].ServNo==0)   
                    {
                        currentrp=headpWinRest; 
        	            headpWinRest=currentrp->nextPtr;
	    	            free(currentrp); 
    		            instantheadpWinRest=headpWinRest;
 	   	                windows[i].State=BREAK;             //有休息请求，且请求被通过，转化为休息状态
 	   	                break;
  	                }
   	                if(windows[i].ServNo!=0)        //接到任务，转化为等待状态
   	                {
                        windows[i].State=WAITING;
                        windows[i].WaitTime++; //等待计时+1 
                        break;
   	                }
   	                else
   	                {
 	   	                windows[i].State=IDLE;              //普通用户队列为空则继续为空闲状态 
                        break;
					}
   	
                }
                else           //对VIP窗口的处理 
                {
                    if((VIPsize==2)&&(windows[i].VIP_idleTime>VIPSERVLen))
                    {
 	   	                windows[i].State=CLOSE;             //客户人数过少，转化为关闭状态
 	   	                break; 
                    }
					controlVIPrest();
					if((VIPsize==2)&&(windows[i].Value_Break==2)&&windows[i].ServNo==0)
                    {
                        currentrp=headpWinRest; 
        	            headpWinRest=currentrp->nextPtr;
	    	            free(currentrp); 
    		            instantheadpWinRest=headpWinRest;
  	                    windows[i].State=BREAK;             //有休息请求，且请求被通过，转化为休息状态
  	                    break;
                    }
					if(windows[i].VIP_idleTime<=VIPSERVLen)
   	                {
                 	   	if(controlVIPwin()==0) //VIP客户人数少于3，连续空闲时间+1 
                 	   	{
 	   	                 	windows[i].VIP_idleTime++;
			            }
			            else
			            {
             				windows[i].VIP_idleTime=0;	           //当在VIPSERVLen内人数一但超过3，连续空闲时间置零 
             			}
            	   	}
   	                if(windows[i].ServNo!=0)
   	                {
   	                 	windows[i].State=WAITING;
   	                 	windows[i].WaitTime++; //等待计时+1 
   	                 	break;
   	                }
   	                else
   	                {
                 	   	windows[i].State=IDLE;
                 	   	break;
              	    }
                }
   	            break;
		    case WAITING:
                windows[i].WaitTime++; //等待计时+1 
		        guestcome=rand()%2;    //客户到来时为1，没有来为0 
		        if(guestcome==0&&windows[i].WaitTime<=WaitingSec) 
		        {
       			    windows[i].State=WAITING;              //顾客未到达且等待未超时
			    }
			    else if(windows[i].WaitTime>10)
			    {
      				if(windows[i].Value==1)                //超时的为普通用户 
      				{
  				        windows[i].CustNormCount--;
  				      	windows[i].ServNo=0;
  				    }
					else                                   //超时的是VIP用户 
					{
  						windows[i].CustVIPCount--;
  						windows[i].ServNo=0;
  					}	
				    windows[i].State=IDLE;                 
      			    windows[i].WaitTime=0;
			    }
			    else if(guestcome==1&&windows[i].WaitTime<=WaitingSec)
			    {
   				    windows[i].State=PROCESSING;           //顾客到达且等待时间未超时
   				    windows[i].WaitTime=0;    
      			}
      			break;
      	    case PROCESSING:
		        if(windows[i].judge_Serv==0)
				{
				    windows[i].PServTime=MinSec+rand()%(MaxSec-MinSec+1);  //最小服务时长为10，最大服务时长为30
					windows[i].judge_Serv=1;     
					windows[i].ServTotalTime=windows[i].ServTotalTime+windows[i].PServTime; //总服务计时加上该客户的模拟服务时间
				}                         
		        else if(windows[i].ServTime<windows[i].PServTime)
		        {
          			windows[i].ServTime++;          //已服务时间加1
          			windows[i].State=PROCESSING;
          		}
          		else
			    {
			      	windows[i].PServTime=0;
  		          	windows[i].ServTime=0;         //将模拟服务时间设置为0，转化为结束状态
				    windows[i].judge_Serv=0;
				    windows[i].ServNo=0;
					windows[i].State=ENDING;	  
  		        }
		        break;
		    case ENDING:
	            satisfaction=rand()%3;                    //随机数模拟顾客的满意度
				if(satisfaction==Bad)
				{
  					windows[i].SatisfyBad++;
  				}
		        else if(satisfaction==Normal)
		        {
          			windows[i].SatisfyNorm++;             //将满意度加到统计信息中
          		}
		        else if(satisfaction==Good) 
		        {
          			windows[i].SatisfyGood++;
          		}
                if(windows[i].ServNo!=0)
                {
                    windows[i].State=WAITING;     //接到任务，转化为等待状态
                    windows[i].WaitTime++; //等待计时+1 
                }
                else
				{
				    windows[i].State=IDLE;
			    }
		        break;
		    case BREAK: 
                if(windows[i].judge_Break==0)
                {
           			windows[i].PBreakTime=MinRestSec+rand()%(MaxRestSec-MinRestSec+1);    //窗口休息最小时间为200，最大时间为1000
					windows[i].judge_Break=1;
					windows[i].BreakTotalTime=windows[i].BreakTotalTime+windows[i].PBreakTime; //总暂停计时加上该客户的模拟暂停时间
           		}
           		else if(windows[i].BreakTime<windows[i].PBreakTime)
           		{
  		           	windows[i].BreakTime++;       //已暂停时间加1
  		           	windows[i].State=BREAK;
	            }
		        else
		        { 
          			windows[i].BreakTime=0;      //模拟暂停时间设置为0，转化为空闲状态 
          			windows[i].judge_Break=0;
          			windows[i].PBreakTime=0;
          			windows[i].Value_Break=0;
					windows[i].State=IDLE;	  
          		}
		        break;
		}
	}
	
}

