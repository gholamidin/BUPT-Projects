
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
	    if((windows[i].State==IDLE)||(windows[i].State==ENDING))    //������״̬Ϊ���л����ʱ 
	    {    
		    controlrest();
	        if(i>=1&&i<4)
	        {
	            if(headp!=NULL&&windows[i].Value_Break!=2) //�����ͨ���в�Ϊ�� 
                {
    		        windows[i].ServNo=headp->Num;
   		            windows[i].Value=1;           //�ô������ڷ�����ͨ�û� 
    		        windows[i].CustNormCount++;   //�ô��ڷ������ͨ�û�������һ 
    		        currentptr=headp; 
    		        headp=currentptr->nextPtr;
			        free(currentptr);       //ɾ����ͨ�û��ȴ�����ͷ�ڵ� 
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
   		            windows[i].Value=1;           //�ô������ڷ�����ͨ�û� 
    		        windows[i].CustNormCount++;   //�ô��ڷ������ͨ�û�������һ 
    		        currentptr=headp; 
    		        headp=currentptr->nextPtr;
			        free(currentptr);       //ɾ����ͨ�û��ȴ�����ͷ�ڵ� 
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
	        if(headpVIP!=NULL&&windows[i].Value_Break!=2&&!((i==8)&&(windows[i].VIP_idleTime>VIPSERVLen)))//��VIP�û��ȴ����в�Ϊ�� 
		    {
			    windows[i].ServNo=headpVIP->Num;
		        windows[i].Value=2;         //˵����VIP��������ΪVIP�û����� 
			    windows[i].CustVIPCount++;  //�ô��ڷ����VIP�û�������һ
	            currentptrVIP=headpVIP; 
    	        headpVIP=currentptrVIP->nextPtr;
		        free(currentptrVIP); 
		        instantheadpVIP=headpVIP;
		    }
		    else
		    {
     		    if(Strategy_Judge==1)   //���Ϊ�����ȷ������ 
     		    {
                    windows[i].State==IDLE;	 
		        }
		        else                    //���ΪVIP˳�������� 
		        {
        		    if(headp!=NULL)
				    {
					    windows[i].ServNo=headp->Num;
				        windows[i].Value=1;  //����VIP��������Ϊ��ͨ�û�����
        		    	windows[i].CustNormCount++; //���ڷ������ͨ�û�������һ
    		            currentptr=headp; 
    		            headp=currentptr->nextPtr;
			        	free(currentptr);       //ɾ����ͨ�û��ȴ�����ͷ�ڵ� 
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
	    currentptr=currentptr->nextPtr;  //���㵱ǰ��ͨ�û����еĳ��� 
	}
	if(i<=2*Normalsize) 
	{
	    return 0;
	} //�����ͨ�û����г���С����ͨ���������������򷵻�0 
	else if(i>=3*Normalsize) 
	{
		return 1;
	}//�����ͨ�û����г��ȴ�����ͨ���������������򷵻�1
}
//��ͨ���ڶ�̬�����صĲ��� 

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
	}//��VIP�û����г��ȴ���3��ʱ�򣬷���1�����򷵻�0 
	return 0; 
}
//VIP���ڶ�̬�����ز��� 

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
    	}//������������׼��ô�����Ϣ������1������ɾ����Ϣ�ȴ����еĵ�һ���ڵ� 
    	windows[num].Value_Break=1;
	}
	return 0;//����������������׼��Ϣ������0 
}
//����ͨ������Ϣ�Ĵ��� 

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
		}//������������׼��ô�����Ϣ������1������ɾ����Ϣ�ȴ����еĵ�һ���ڵ�
	}
	
	return 0;//����������������׼��Ϣ������0 
}
//��VIP������Ϣ�Ĵ���

int OpenNormalwindow()      //���㵱ʱ��������״̬����ͨ������ 
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

int OpenVIPwindow()         //���㵱ʱ��������״̬��VIP������ 
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
	    }//��ð���������� 
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
}//����Ҫ�󣬽�������Ϣ�������� 
