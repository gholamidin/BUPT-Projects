
#include"State_trans.h"
#include"mylib.h"

void controllist()
{
    int i;
	LISTNODEPTR currentptr,currentptrVIP;
    RESTLISTNODEPTR currentrp;
    winrestsort();
    for(i=1;i<=6;i++) 
    {
	    if((windows[i].State==IDLE)||(windows[i].State==ENDING))    //当窗口状态为空闲或结束时 
	    {    
		    controlrest();
	        if(i>=1&&i<4)
	        {
	            if(headp!=NULL&&windows[i].Value_Break!=2) //如果普通队列不为空 
                {
    		        windows[i].ServNo=headp->Num;
   		            windows[i].Value=1;           //该窗口正在服务普通用户 
    		        windows[i].CustNormCount++;   //该窗口服务的普通用户记数加一 
    		        currentptr=headp; 
    		        headp=currentptr->nextPtr;
			        free(currentptr);       //删除普通用户等待队列头节点 
			        instantheadp=headp;
                }
	        }
	        else
	        {
				if(controlwin()==0)
	            {
	            	if(windows[i].Value_Break==2)
	            	{
	            	    currentrp=headpWinRest; 
        	            headpWinRest=currentrp->nextPtr;
	    	            free(currentrp); 
    		            instantheadpWinRest=headpWinRest;
    		            windows[i].Value_Break==0;
	            	}
	            }
	            else if(headp!=NULL&&windows[i].Value_Break!=2)
	            {
	            	windows[i].ServNo=headp->Num;
   		            windows[i].Value=1;           //该窗口正在服务普通用户 
    		        windows[i].CustNormCount++;   //该窗口服务的普通用户记数加一 
    		        currentptr=headp; 
    		        headp=currentptr->nextPtr;
			        free(currentptr);       //删除普通用户等待队列头节点 
			        instantheadp=headp;
	            }
	        }
	    }
	}
    for(i>=7;i<=8;i++)
	{
	    if((windows[i].State==IDLE)||(windows[i].State==ENDING)) 
	    {
	    	controlVIPrest();
	        if(headpVIP!=NULL&&windows[i].Value_Break!=2&&!((i==8)&&(windows[i].VIP_idleTime>VIPSERVLen)))//当VIP用户等待队列不为空 
		    {
			    windows[i].ServNo=headpVIP->Num;
		        windows[i].Value=2;         //说明该VIP窗口正在为VIP用户服务 
			    windows[i].CustVIPCount++;  //该窗口服务的VIP用户记数加一
	            currentptrVIP=headpVIP; 
    	        headpVIP=currentptrVIP->nextPtr;
		        free(currentptrVIP); 
		        instantheadpVIP=headpVIP;
		    }
		    else
		    {
     		    if(Strategy_Judge==1)   //如果为先来先服务策略 
     		    {
                    windows[i].State==IDLE;	 
		        }
		        else                    //如果为VIP顺便服务策略 
		        {
        		    if(headp!=NULL)
				    {
					    windows[i].ServNo=headp->Num;
				        windows[i].Value=1;  //明该VIP窗口正在为普通用户服务
        		    	windows[i].CustNormCount++; //窗口服务的普通用户记数加一
    		            currentptr=headp; 
    		            headp=currentptr->nextPtr;
			        	free(currentptr);       //删除普通用户等待队列头节点 
			        	instantheadp=headp;
					}
        	    }
     	    }
	    }
		     
    }
}

int controlwin()
{
    int i,Normalsize;
	LISTNODEPTR currentptr=headp;
	Normalsize=OpenNormalwindow();
	for(i=0;currentptr!=NULL;i++)
	{
	    currentptr=currentptr->nextPtr;  //计算当前普通用户队列的长度 
	}
	if(i<=2*Normalsize) 
	{
	    return 0;
	} //如果普通用户队列长度小于普通窗口数的两倍，则返回0 
	else if(i>=3*Normalsize) 
	{
		return 1;
	}//如果普通用户队列长度大于普通窗口数的三倍，则返回1
}
//普通窗口动态开、关的操作 

int controlVIPwin()
{
	int i;
	LISTNODEPTR currentptr=headpVIP;
	for(i=0;currentptr!=NULL;i++)
	{
		currentptr=currentptr->nextPtr;
	}
	if(i>3)
	{
		return 1;
	}//当VIP用户队列长度大于3的时候，返回1，否则返回0 
	return 0; 
}
//VIP窗口动态开、关操作 

int controlrest()
{
	int i,Normalsize,num;
	LISTNODEPTR currentptr;
	currentptr=headp;
	Normalsize=OpenNormalwindow();
	if(headpWinRest!=NULL) 
	{
		for(i=0;currentptr!=NULL;i++)
	    {
		    currentptr=currentptr->nextPtr;
    	}
		num=headpWinRest->WinNo;
	    if(i<MaxSeqLen*Normalsize&&Normalsize>3)
    	{
    		windows[num].Value_Break=2;
    		return 0;
    	}//当符合条件，准许该窗口休息，返回1，并且删除休息等待队列的第一个节点 
    	windows[num].Value_Break=1;
	}
	return 0;//若不符合条件，不准休息，返回0 
}
//对普通窗口休息的处理 

int controlVIPrest()
{
	int i,VIPsize,num;
	LISTNODEPTR currentptr=headpVIP;
	VIPsize=OpenVIPwindow(); 
	if(headpWinRest!=NULL)
	{
		for(i=0;currentptr!=NULL;i++)
	    {
		    currentptr=currentptr->nextPtr;
	    }
	    if(i<=VIPMaxSeqLen*VIPsize&&VIPsize==2)
	    {
		    num=headpWinRest->WinNo;
        	windows[num].Value_Break=2;
		}//当符合条件，准许该窗口休息，返回1，并且删除休息等待队列的第一个节点
	}
	
	return 0;//若不符合条件，不准休息，返回0 
}
//对VIP窗口休息的处理

int OpenNormalwindow()      //计算当时处于运行状态的普通窗口数 
{ 
	int i,size=0;
	for(i=1;i<=6;i++)
	{
		if(windows[i].State!=CLOSE&&windows[i].State!=BREAK)
		{
			size++;
		}
	}
	return size;
} 

int OpenVIPwindow()         //计算当时处于运行状态的VIP窗口数 
{
	int i,size=0;
	for(i=7;i<=8;i++)
	{
		if(windows[i].State!=CLOSE&&windows[i].State!=BREAK)
		{
			size++;
		}
	}
	return size;
}

int winrestsort()
{
	int restnum=0,x[9],i,j,temp;
	static RESTLISTNODEPTR currentpWinRest,PheadpWinRest;
	if(headpWinRest!=NULL)
	{
	    currentpWinRest=headpWinRest;
	    while(currentpWinRest!=NULL)
	    {
	    	restnum++;
	    	x[restnum]=currentpWinRest->WinNo;
	    	currentpWinRest=currentpWinRest->nextPtr;
	    }
	    for(i=1;i<=restnum;i++)
	    {
	    	for(j=1;j<=restnum-i;j++)
	    	{
	    		if(windows[x[j]].BreakTotalTime>windows[x[j+1]].BreakTotalTime)
	    		{
	    			temp=x[j];
	    			x[j]=x[j+1];
	    			x[j+1]=temp;
	    		}
	    	}
	    }//用冒泡排序法排序 
	    PheadpWinRest=headpWinRest;
	    for(i=1;i<=restnum;i++)
	    {
	    	if(i==1)
	    	{
	    		PheadpWinRest->WinNo=x[i];
	    		currentpWinRest=PheadpWinRest->nextPtr;
	    	}
	    	else
	    	{
	    		currentpWinRest->WinNo=x[i];
	    	    currentpWinRest=currentpWinRest->nextPtr;
	    	}
	    }
	    headpWinRest=PheadpWinRest;
		instantheadpWinRest=headpWinRest;
	}
	return 0;
}//根据要求，将窗口休息队列排序 
