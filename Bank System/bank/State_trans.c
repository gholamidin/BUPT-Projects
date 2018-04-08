
#include<time.h>
#include"mylib.h"
#include"Control.h"

void state_trans()
{
	
    int i;
	int guestcome;    //�����ģ��ͻ��Ƿ��� 
	int satisfaction; //�����ģ��ͻ�������� 
    int Normalsize=0;   //��ǰ�������е���ͨ������
    int VIPsize=0;      //��ǰ�������е�VIP������
    VIPsize=OpenVIPwindow(); 
    Normalsize=OpenNormalwindow();
    RESTLISTNODEPTR currentrp;
	srand(time(NULL));
	
	for(i=1;i<=Size;i++)
	{
	    switch(windows[i].State)
		{
	        case CLOSE:
			    if((i<=6)&&(controlwin()==1)&&(headp!=NULL))     //���������㣬ת��Ϊ����״̬ 
                {
				    windows[i].State=IDLE;
                } 
                else if((i>=7)&&(controlVIPwin()==1)&&(headpVIP!=NULL))
                {
			        windows[i].State=IDLE;
                }
				break;
			case IDLE:
                if(i>=1&&i<=6)  //����ͨ���ڵĴ��� 
                {
   	                if((i>=4&&i<=6)&&controlwin()==0&&windows[i].ServNo==0)
   	                {
 	   	                windows[i].State=CLOSE;             //��ͨ�ͻ��������٣�ת��Ϊ�ر�״̬
 	   	                break;
                    }
                    controlrest(); 
                    if((Normalsize>3)&&(windows[i].Value_Break==2)&&windows[i].ServNo==0)   
                    {
                        currentrp=headpWinRest; 
        	            headpWinRest=currentrp->nextPtr;
	    	            free(currentrp); 
    		            instantheadpWinRest=headpWinRest;
 	   	                windows[i].State=BREAK;             //����Ϣ����������ͨ����ת��Ϊ��Ϣ״̬
 	   	                break;
  	                }
   	                if(windows[i].ServNo!=0)        //�ӵ�����ת��Ϊ�ȴ�״̬
   	                {
                        windows[i].State=WAITING;
                        windows[i].WaitTime++; //�ȴ���ʱ+1 
                        break;
   	                }
   	                else
   	                {
 	   	                windows[i].State=IDLE;              //��ͨ�û�����Ϊ�������Ϊ����״̬ 
                        break;
					}
   	
                }
                else           //��VIP���ڵĴ��� 
                {
                    if((VIPsize==2)&&(windows[i].VIP_idleTime>VIPSERVLen))
                    {
 	   	                windows[i].State=CLOSE;             //�ͻ��������٣�ת��Ϊ�ر�״̬
 	   	                break; 
                    }
					controlVIPrest();
					if((VIPsize==2)&&(windows[i].Value_Break==2)&&windows[i].ServNo==0)
                    {
                        currentrp=headpWinRest; 
        	            headpWinRest=currentrp->nextPtr;
	    	            free(currentrp); 
    		            instantheadpWinRest=headpWinRest;
  	                    windows[i].State=BREAK;             //����Ϣ����������ͨ����ת��Ϊ��Ϣ״̬
  	                    break;
                    }
					if(windows[i].VIP_idleTime<=VIPSERVLen)
   	                {
                 	   	if(controlVIPwin()==0) //VIP�ͻ���������3����������ʱ��+1 
                 	   	{
 	   	                 	windows[i].VIP_idleTime++;
			            }
			            else
			            {
             				windows[i].VIP_idleTime=0;	           //����VIPSERVLen������һ������3����������ʱ������ 
             			}
            	   	}
   	                if(windows[i].ServNo!=0)
   	                {
   	                 	windows[i].State=WAITING;
   	                 	windows[i].WaitTime++; //�ȴ���ʱ+1 
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
                windows[i].WaitTime++; //�ȴ���ʱ+1 
		        guestcome=rand()%2;    //�ͻ�����ʱΪ1��û����Ϊ0 
		        if(guestcome==0&&windows[i].WaitTime<=WaitingSec) 
		        {
       			    windows[i].State=WAITING;              //�˿�δ�����ҵȴ�δ��ʱ
			    }
			    else if(windows[i].WaitTime>10)
			    {
      				if(windows[i].Value==1)                //��ʱ��Ϊ��ͨ�û� 
      				{
  				        windows[i].CustNormCount--;
  				      	windows[i].ServNo=0;
  				    }
					else                                   //��ʱ����VIP�û� 
					{
  						windows[i].CustVIPCount--;
  						windows[i].ServNo=0;
  					}	
				    windows[i].State=IDLE;                 
      			    windows[i].WaitTime=0;
			    }
			    else if(guestcome==1&&windows[i].WaitTime<=WaitingSec)
			    {
   				    windows[i].State=PROCESSING;           //�˿͵����ҵȴ�ʱ��δ��ʱ
   				    windows[i].WaitTime=0;    
      			}
      			break;
      	    case PROCESSING:
		        if(windows[i].judge_Serv==0)
				{
				    windows[i].PServTime=MinSec+rand()%(MaxSec-MinSec+1);  //��С����ʱ��Ϊ10��������ʱ��Ϊ30
					windows[i].judge_Serv=1;     
					windows[i].ServTotalTime=windows[i].ServTotalTime+windows[i].PServTime; //�ܷ����ʱ���ϸÿͻ���ģ�����ʱ��
				}                         
		        else if(windows[i].ServTime<windows[i].PServTime)
		        {
          			windows[i].ServTime++;          //�ѷ���ʱ���1
          			windows[i].State=PROCESSING;
          		}
          		else
			    {
			      	windows[i].PServTime=0;
  		          	windows[i].ServTime=0;         //��ģ�����ʱ������Ϊ0��ת��Ϊ����״̬
				    windows[i].judge_Serv=0;
				    windows[i].ServNo=0;
					windows[i].State=ENDING;	  
  		        }
		        break;
		    case ENDING:
	            satisfaction=rand()%3;                    //�����ģ��˿͵������
				if(satisfaction==Bad)
				{
  					windows[i].SatisfyBad++;
  				}
		        else if(satisfaction==Normal)
		        {
          			windows[i].SatisfyNorm++;             //������ȼӵ�ͳ����Ϣ��
          		}
		        else if(satisfaction==Good) 
		        {
          			windows[i].SatisfyGood++;
          		}
                if(windows[i].ServNo!=0)
                {
                    windows[i].State=WAITING;     //�ӵ�����ת��Ϊ�ȴ�״̬
                    windows[i].WaitTime++; //�ȴ���ʱ+1 
                }
                else
				{
				    windows[i].State=IDLE;
			    }
		        break;
		    case BREAK: 
                if(windows[i].judge_Break==0)
                {
           			windows[i].PBreakTime=MinRestSec+rand()%(MaxRestSec-MinRestSec+1);    //������Ϣ��Сʱ��Ϊ200�����ʱ��Ϊ1000
					windows[i].judge_Break=1;
					windows[i].BreakTotalTime=windows[i].BreakTotalTime+windows[i].PBreakTime; //����ͣ��ʱ���ϸÿͻ���ģ����ͣʱ��
           		}
           		else if(windows[i].BreakTime<windows[i].PBreakTime)
           		{
  		           	windows[i].BreakTime++;       //����ͣʱ���1
  		           	windows[i].State=BREAK;
	            }
		        else
		        { 
          			windows[i].BreakTime=0;      //ģ����ͣʱ������Ϊ0��ת��Ϊ����״̬ 
          			windows[i].judge_Break=0;
          			windows[i].PBreakTime=0;
          			windows[i].Value_Break=0;
					windows[i].State=IDLE;	  
          		}
		        break;
		}
	}
	
}

