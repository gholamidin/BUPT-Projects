#include<windows.h>
#include<time.h>
#include"mylib.h"
#include"Open.h"
#include"file_input.h"
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


int file()
{
	int flag1=1,flag=1,i;
	FILE *fPtr=NULL,*outPtr=NULL;
	LISTNODEPTR currentp,currentpVIP;
	Time=1; //ϵͳʱ���ʼ��Ϊ1 
	headp=NULL;
	headpVIP=NULL;
	headpWinRest=NULL;
	fPtr=fopen("input.txt","r");
	outPtr=fopen("output1.txt","w");
	Open();//��ȡ�����ļ� 
    Initialization();//��ʼ������״̬ 
	ChangeOpenfile(); //�޸������ļ��ϵ�����(���ǲ����ı�Դ�ļ�) 
    VIPdata();//VIP��Ϣά�� 
    system("cls");
    printf( "*******************************************************************************\n" 
 		    "                         ��ӭ����������������                                  \n"
 		    "                                                    ��д��Ա������ ��Ң�� ��� \n"
 		    "*******************************************************************************\n");
    printf("��ѡ��VIP���ڵķ�����ԣ�\n");
	printf("1 - VIP�������.\n"); 
	printf("2 - VIP˳�����.\n");
	scanf("%d",&Strategy_Judge);
	while(Strategy_Judge!=1&&Strategy_Judge!=2)
	{
		printf("�ף��������������������ʾ��Ϣ��������\n");
		printf("��ѡ��VIP���ڵķ�����ԣ�\n");
	    printf("1 - VIP�������.\n"); 
	    printf("2 - VIP˳�����.\n");
	    scanf("%d",&Strategy_Judge);
	}
    input(fPtr);
    
    while(flag!=0) 
    {
	    if(Time==T)
	    {
	    	AddServList();//����ȡ���¼���ӵ����������� 
	    }
		controllist();//�ѵȴ������еĿͻ����䵽���� 
		state_trans();//�ı�������ڵ�״̬ 
		 
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
			    }//����д��ڻ��ڷ���ͻ����������������״̬�������°� 
		    }
		}
		if(headp==NULL&&headpVIP==NULL&&flag1==0)
		{
			flag=0;//�û��ȴ�Ϊ�� �����ھ����������������������ϣ��°࣬�˳�ϵͳ 
			for(i=1;i<=Size;i++)
			{
                windows[i].State=CLOSE;
            }
			print_message(outPtr);
		    fclose(outPtr);
		}  
    } 
    
    print_satisfy();
	printf("�°�ɹ�\n");
    //system("pause");
    return 0;
}

