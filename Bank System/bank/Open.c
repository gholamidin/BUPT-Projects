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
}//��ȡ�����ļ� 

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
	}//���˸����ڵ���Ϣ��ʼ�� 
	for(i=0;i<=13;i++)
	{
		chair[i].Judge=0;
		chair[i].Num=0;
		chair[i].Value=-1;
	}
	for(i=1;i<=3;i++)
	    windows[i].State=IDLE;//��������ͨ���� 
	windows[7].State=IDLE;//�򿪵�һ��VIP���� 
	SerId=0;
	SerVIPId=0;//��ʼ������ 
	Strategy_Judge=1;//������Ĭ������Ϊ�����ȷ������ 
	isquit=1;//�����ж��Ƿ��°࣬1Ϊ�ϰ�ʱ��0Ϊ�°�
	instantquit=1; 
}
//��ʼ������״̬ 

void ChangeOpenfile()
{
	int value;
	prompt(); 
	scanf("%d",&value);
	while(value!=0)
	{
		if(value<0||value>9)
		{
			printf("�ף��������������������ʾ��Ϣ��������\n");
		}
		else
		{
			switch(value)
			{
			    case 1:
					printf("�����봰�ڵȴ��ͻ����������ʱ��.\n"); 
					scanf("%d",&WaitingSec);
					break;
				case 2:
					printf("��������ͨ�û����������������ȴ�����.\n");
					scanf("%d",&MaxSeqLen);
					break;
				case 3:
					printf("������VIP�û����������������ȴ�����.\n");
					scanf("%d",&VIPMaxSeqLen);
					break;
				case 4:
					printf("��������С����ʱ��.\n");
					scanf("%d",&MinSec);
					break;
				case 5:
					printf("������������ʱ��.\n");
					scanf("%d",&MaxSec);
					break;
				case 6:
					printf("�����봰����С��Ϣʱ��.\n");
					scanf("%d",&MinRestSec);
					break;
				case 7:
					printf("�������մ��������Ϣʱ��.\n");
					scanf("%d",&MaxRestSec);
					break;
				case 8:
					printf("������VIP���ڶ�̬�ر�ʱ��.\n");
					scanf("%d",&VIPSERVLen);
					break;
				case 9:
					printf("�������°�ʱ��.\n");
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
 		    "                         ��ӭ����������������                                  \n"
 		    "                                                    ��д��Ա������ ��Ң�� ��� \n"
 		    "*******************************************************************************\n");
    printf("��������޸������ļ�״̬\n");
	printf("1 - �޸Ĵ��ڵȴ��ͻ����������ʱ��.\n");
	printf("2 - �޸���ͨ�û����������������ȴ�����.\n");
	printf("3 - �޸�VIP�û����������������ȴ�����.\n");
	printf("4 - �޸���С����ʱ��.\n");
	printf("5 - �޸�������ʱ��.\n");
	printf("6 - �޸Ĵ�����С��Ϣʱ��.\n");
	printf("7 - �޸Ĵ��������Ϣʱ��.\n");
	printf("8 - �޸�VIP���ڶ�̬�ر�ʱ��.\n");
	printf("9 - �޸��°�ʱ��.\n");
	printf("0 - �˳�.\n"); 
	return 0;
}


void option()
{
	int value,judge,judge_flag=1;
	system("cls");
    printf("*******************************************************************************\n" 
 		   "                         ��ӭ����������������                                  \n"
 	       "                                                    ��д��Ա������ ��Ң�� ��� \n"
 		   "*******************************************************************************\n");
	printf("���������ļ��޸�,������ 1 \n"
           "����VIP��Ϣά��״̬,������ 2 \n"
		   "����VIP���ڵķ������ѡ��,������ 3 \n" 
	       "���빤��״̬,������ 4 \n");
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
            	system("cls");
                printf("*******************************************************************************\n" 
 		               "                         ��ӭ����������������                                  \n"
 	                   "                                                    ��д��Ա������ ��Ң�� ��� \n"
 		               "*******************************************************************************\n");
            	printf("��ѡ��VIP���ڵķ�����ԣ�\n");
	            printf("1 - VIP�������.\n"); 
	            printf("2 - VIP˳�����.\n");
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
	                	printf("��,������������,�������ʾ��Ϣ��������:\n");
	        	        printf("VIP���������������� 1 \n");
				        printf("VIP˳�������������� 2 \n");
				        scanf("%d",&judge);
	                }
	            }
	            break;
	        default:
	        {
	        	system("cls");
                printf("*******************************************************************************\n" 
 		               "                         ��ӭ����������������                                  \n"
 	                   "                                                    ��д��Ա������ ��Ң�� ��� \n"
 		               "*******************************************************************************\n");
	        	printf("�ף��������������������ʾ��Ϣ��������\n");
	        	printf("���������ļ��޸�,������ 1 \n"
                       "����VIP��Ϣά��״̬,������ 2 \n"
		               "����VIP���ڵķ������ѡ��,������ 3 \n" 
	                   "���빤��״̬,������ 4 \n");
	        	scanf("%d",&value);
	        	break;
	        }
	    }
		printf("���������ļ��޸�,������ 1 \n"
               "����VIP��Ϣά��״̬,������ 2 \n"
		       "����VIP���ڵķ������ѡ��,������ 3 \n" 
	           "���빤��״̬,������ 4 \n");
	    scanf("%d",&value);
	}
	fflush(stdin);
}

