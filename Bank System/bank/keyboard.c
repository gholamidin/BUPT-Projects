#include<windows.h>
#include<time.h>
#include"mylib.h"
#include"Open.h"
#include"output.h"
#include"State_trans.h"
#include"Control.h"
#include"vip.h"


int SerId;// ��ͨ�ͻ��ĺ��� 
int SerVIPId;// VIP�û��ĺ��� 
int T; //����ĳ���¼���ʱ��
int Time;// ϵͳʱ��
int Strategy_Judge;// �����жϲ��� ��1ΪVIP�������2ΪVIP˳����� 
int isquit;  // �����ж��Ƿ��°� 

int WaitingSec; //Ԥ�Ƶȴ��ͻ����ﴰ�ڵ�ʱ��
int MaxSeqLen; //��ͨ�û����������������ȴ�����
int VIPMaxSeqLen; //VIP�û����������������ȴ�����
int MinSec; //��С����ʱ��
int MaxSec; //������ʱ��
int MinRestSec; //������С��Ϣʱ��
int MaxRestSec; //���������Ϣʱ��
int VIPSERVLen; //VIP���ڶ�̬�ر�ʱ��
int dropquit; //�°�ʱ�� 
LISTNODEPTR headp,headpVIP;
RESTLISTNODEPTR headpWinRest;
LISTNODEPTR instantheadp,instantheadpVIP;
RESTLISTNODEPTR instantheadpWinRest;
int instantquit;//��ʱ�����°෢��ָ�� 

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
    Time=1; //ϵͳʱ���ʼ��Ϊ1 
    headp=NULL;
    headpVIP=NULL;
    headpWinRest=NULL;
    Open();//��ȡ�����ļ� 
    Initialization();//��ʼ������״̬ 
    option();
    hThread1=CreateThread(NULL,0,Fun1,NULL,0,NULL);
    hThread2=CreateThread(NULL,0,Fun2,NULL,0,NULL);
    CloseHandle(hThread1);
    CloseHandle(hThread2);
    while(flag!=0) 
    {
        controllist();//�ѵȴ������еĿͻ����䵽���� 
        state_trans();//�ı�������ڵ�״̬
        print_message(outPtr);
        Time++;
        if(Time%5==0&&Time>=5)
        {
        	print_screen();
	        printf("��ͨ�û��к�������  G\n");
        	printf("VIP�û��к�������   V\n");
        	printf("����������Ϣ������  R\n");
            printf("�°�����������      Q\n");
            printf("VIP��Ϣά��������   X\n"); 
            printf("�������ѡ��������  S\n");
            printf("���������ָ��Ϊ��\n");
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
    		    }//����д��ڻ��ڷ���ͻ����������������״̬�������°� 
   		    }
    	}
    	if(headp==NULL&&headpVIP==NULL&&flag1==0&&(isquit==0||Time>dropquit))
    	{
    	    flag=0;//�û��ȴ�Ϊ�� �����ھ����������������������ϣ��°࣬�˳�ϵͳ 
            for(i=1;i<=Size;i++)
                windows[i].State=CLOSE;
            print_message(outPtr);
        }
    }
    print_satisfy();
    int value,judge,value_flag=1;
    system("cls");
    printf("*******************************************************************************\n" 
 		   "                         ��ӭ����������������                                  \n"
 	       "                                                    ��д��Ա������ ��Ң�� ��� \n"
 		   "*******************************************************************************\n");
	printf("���������ļ��޸�,������ 1 \n"
           "����VIP��Ϣά��״̬,������ 2 \n"
		   "����VIP���ڵķ������ѡ��,������ 3 \n" 
	       "��ȫ�˳�����,������ 4 \n");
	fflush(stdin);
	scanf("%d",&value);
	while(value!=4)
	{
		switch(value)
		{
			case 1:
				printf("��������޸������ļ�״̬\n");
	            ChangeOpenfile(); //�޸������ļ��ϵ�����(���ǲ����ı�Դ�ļ�)
	            break;
	        case 2:
	        	printf("�������VIP��Ϣά��״̬��\n");
                VIPdata();//VIP��Ϣά��
                break;
            case 3:
            	printf("��ѡ��VIP���ڵķ�����ԣ�\n");
	            printf("1 - VIP�������.\n"); 
	            printf("2 - VIP˳�����.\n");
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
	                	printf("��,������������,�������ʾ��Ϣ��������:\n");
	        	        printf("VIP���������������� 1 \n");
				        printf("VIP˳�������������� 2 \n");
				        scanf("%d",&judge);
	                }
	            }
	            break;
	        default:
	        {
	        	printf("�ף��������������������ʾ��Ϣ��������\n");
	        	printf("���������ļ��޸�,������ 1 \n"
                       "����VIP��Ϣά��״̬,������ 2 \n"
		               "����VIP���ڵķ������ѡ��,������ 3 \n" 
	                   "��ȫ�˳�����,������ 4 \n");
	        	scanf("%d",&value);
	        	break;
	        }
	    }
	    system("cls");
        printf("*******************************************************************************\n" 
 		       "                         ��ӭ����������������                                  \n"
 	           "                                                    ��д��Ա������ ��Ң�� ��� \n"
 		       "*******************************************************************************\n");
		printf("���������ļ��޸�,������ 1 \n"
               "����VIP��Ϣά��״̬,������ 2 \n"
		       "����VIP���ڵķ������ѡ��,������ 3 \n" 
	           "��ȫ�˳�����,������ 4 \n");
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
	    int restwindow;        //restwindowΪ������Ϣ�Ĵ���  vipxΪ0��ʾVIPͨ����֤ ����δͨ����֤ 
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
    	}//���ļ������е���Ϣ���浽�ṹ��������
    	fclose(fvip);
    	fflush(stdin);
	    printf("��ͨ�û��к�������  G\n");
	    printf("VIP�û��к�������   V\n");
	    printf("����������Ϣ������  R\n");
        printf("�°�����������      Q\n");
        printf("VIP��Ϣά��������   X\n"); 
        printf("�������ѡ��������  S\n");
        printf("���������ָ��Ϊ��\n");
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
		        	printf("����������VIP����:\n");
		        	scanf("%s",&id);
		        	fflush(stdin);
             		while(flag==1)
             		{
             			i=0;
					    while(i<=n&&strcmp(id,indata[i].VIPID)!=0)
             		        i++;
             			if(strcmp(id,indata[i].VIPID)==0)   //ͨ����֤����Ӷ��� 
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
			                printf("�װ���VIP�û������ĺ���Ϊ%d��\n",SerVIPId);
		    	            break;
	                	}            //δͨ����֤ ֱ�ӽ�����ͨ���� 
	                 	else if(time>=1)
	                	{
						    if(time>1)
				            {
							    time--;
	                		    printf("�������VIP����������������VIP�ţ�ʣ���������%d�Σ�:\n",time);
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
	                if(type=='G')      //�ж�ֱ������ͨ�ͻ�����VIPΪͨ���ͻ� 
	    		        printf("�װ�����ͨ�û������ĺ���Ϊ%d\n",SerId);
	    		    else
	    		        printf("���ź����Ѿ�������Σ����ڸ���������ͨ��%d����������Ϣ���ȴ��кţ�лл����\n",SerId);
	    		    break;
	            case 'R':
	            	printf("��������Ҫ��Ϣ�Ĵ��ںţ�\n");
					scanf("%d",&restwindow);
	            	fflush(stdin);
    	        	while(restwindow!=1&&restwindow!=2&&restwindow!=3&&restwindow!=4&&restwindow!=5&&restwindow!=6&&restwindow!=7&&restwindow!=8)
    	            {
    	            	printf("������������,�������ʾ��Ϣ��ȷ����\n"); 
    	            	printf("��������Ҫ��Ϣ�Ĵ��ںţ�\n");
						scanf("%d",&restwindow);
	            	    fflush(stdin);
    	            }
					printf("����%d�����Ϣ����\n\n",restwindow);
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
    	        	printf("���յ��°��������ڵȴ��°ࡣ\n\n"); 
    	        	break;
    	        case 'X':
    	        	VIPdata();
    	        	break;
    	        case 'S':
    	        	printf("VIP���������������� 1 \n");
    				printf("VIP˳�������������� 2 \n"); 
    				fflush(stdin);
    	        	scanf("%d",&num);
    	        	while(flag1==1)
	            	{
	            		if(num==1)
    	        	    {
    	        	    	Strategy_Judge=1;
    	        	    	flag1=0;
    	        	    	printf("��ѡ��VIP����������\n\n"); 
    	            	}
    	            	else if(num==2)
	                	{
    	            		Strategy_Judge=2;
	                		flag1=0;
	                		printf("��ѡ��VIP˳��������\n\n"); 
	                	}
	            	    else
	            	    {
	            	    	printf("��,������������,�������ʾ��Ϣ��������:\n");
	            	    	printf("VIP���������������� 1 \n");
	    			        printf("VIP˳�������������� 2 \n");
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

