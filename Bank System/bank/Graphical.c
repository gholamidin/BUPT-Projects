
#include"mylib.h"
#include"Open.h"
#include"output.h"
#include"State_trans.h"
#include"Control.h"
#include"vip.h"
#include<windows.h>

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

 
HEGG noregg[100],String,eggVip[100],eggwin[9],hnorlist,hVIPlist;

LISTNODEPTR headp,headpVIP;
RESTLISTNODEPTR headpWinRest;

struct WINDOW windows[9];
struct CHAIR chair[14];  //�ж���λ��״̬ 

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
	Open();//��ȡ�����ļ� 
    Initialization();//��ʼ������״̬
    option(); 
	EggStart(900,500);//�������� 
	PlaySound(TEXT("��ӭ����������������.wav"),NULL,SND_FILENAME|SND_ASYNC);

	hEggs=LayEgg();
	DrawBitmap("����.bmp");//������ͼ������Ļ�� 
	hgou=LayEgg();
	MovePen(176,485);
	DrawBitmap("�Ժ�.bmp");
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
				controllist();//�ѵȴ������еĿͻ����䵽���� 
                state_trans();//�ı�������ڵ�״̬
                addwinpic(); //��ʾ���ڵ�״̬ 
                moveguest(); //�ƶ��ͻ� 
                printfnorlist();//��ӡ��ͨ�ͻ��ȴ������е������� 
                printfVIPlist();//��ӡVIP�ͻ��ȴ������е������� 
                print_message(outPtr);//ÿ��һ�룬��������Ϣ�������� 
                print_screen();//ÿ��һ�룬��������Ϣ��ӡ����Ļ�� 
                Time++;//һ��ʱ��ִ��һ��TIMERʱ�� 
				break;
			case KEYDOWN:
				if(isquit!=0&&Time<=dropquit)//��û�н��ܵ��°�ָ���Լ�û���°�ʱ��ʱ 
				{
					if(GetStruckKey() == VK_LBUTTON)
			        {
			        	X = GetMouseX();
			            Y = GetMouseY();  //��ȡ����������� 
		        	    if(Y<=492&&Y>=462&&X>=1&&X<=175) //���IP����������ͼ�� 
		        		{
		          			SetActiveEgg(hgou);
	        				EatEgg();
	        				hgou=LayEgg();
	        				MovePen(176,485);
	                        DrawBitmap("�Ժ�.bmp");
	                        Strategy_Judge=1; 
	                        SetActiveEgg(String);
	                        EatEgg();
	                        String=LayEgg();
	                        MovePen(0,130);
	                        DrawString("   �ѽ����Ը�ΪVIP�������");
	                        output=fopen("ins_output.txt","a");
                            fprintf(output,"T=%d,�����Ըĳ�VIP�������\n",Time);
                            fclose(output);
							PlaySound(TEXT("������ѡ����VIP����������.wav"),NULL,SND_FILENAME|SND_ASYNC);
                            SetActiveEgg(hEggs);
	        			}
	    	    	    else if(Y>=420&&Y<=450&&X>=1&&X<=175) //���VIP˳��������ͼ�� 
	    	    	    {
	    	    	    	SetActiveEgg(hgou);
	    	    			EatEgg();
	    	    			hgou=LayEgg();
	    	    			MovePen(176,445);
	                        DrawBitmap("�Ժ�.bmp");
	                        Strategy_Judge=2; 
	                        SetActiveEgg(String);
	                        EatEgg();
	                        String=LayEgg();
	                        MovePen(0,130);
	                        DrawString("   �ѽ����Ը�ΪVIP˳�����");
	                        output=fopen("ins_output.txt","a");
                            fprintf(output,"T=%d,�����Ըĳ�VIP˳�����\n",Time);
                            fclose(output);
                            PlaySound(TEXT("������ѡ����VIP˳��������.wav"),NULL,SND_FILENAME|SND_ASYNC);
                            SetActiveEgg(hEggs);
	    		        }
	    		        else if(X>=69&&X<=131&&Y>=149&&Y<=209)//VIP�ͻ�����
						{
							PlaySound(TEXT("��ӭ����.wav"),NULL,SND_FILENAME|SND_SYNC);
							input_VIP();
						}
						else if(Y<=209&&Y>=149&&X>=2&&X<=64) //��ͨ�ͻ����� 
						{ 
						    PlaySound(TEXT("��ӭ����.wav"),NULL,SND_FILENAME|SND_ASYNC);
					        buttonG();
						} 
						else if(X>=2&&X<=64&&Y>=344&&Y<=404) //���������Ϣ����ͼ�� R1-R8 
	    	    	    {
	    	    	    	getrest(1);
	    	    	    	PlaySound(TEXT("����1.wav"),NULL,SND_FILENAME|SND_ASYNC);
	    	    	    }
						else if(X>=68&&X<=130&&Y>=344&&Y<=404)
						{
							getrest(2);
	     	    	    	PlaySound(TEXT("����2.wav"),NULL,SND_FILENAME|SND_ASYNC);
						}
	     	    	    else if(X>=134&&X<=196&&Y>=344&&Y<=404)
	     	    	    {
	     	    	    	getrest(3);
							PlaySound(TEXT("����3.wav"),NULL,SND_FILENAME|SND_ASYNC);
	     	    	    }
	    	    	    else if(X>=2&&X<=64&&Y>=277&&Y<=337)
	    	    	    {
	    	    	    	getrest(4);
	    	    	    	PlaySound(TEXT("����4.wav"),NULL,SND_FILENAME|SND_ASYNC);
	    	    	    }
   	    	    	    else if(X>=68&&X<=130&&Y>=277&&Y<=337)
   	    	    	    {
   	    	    	    	getrest(5);
   	    	    	    	PlaySound(TEXT("����5.wav"),NULL,SND_FILENAME|SND_ASYNC);
   	    	    	    }
    		    	    else if(X>=134&&X<=196&&Y>=277&&Y<=337)
    		    	    {
    		    	    	getrest(6);
    		    	    	PlaySound(TEXT("����6.wav"),NULL,SND_FILENAME|SND_ASYNC);
    		    	    }
    		      	    else if(X>=2&&X<=64&&Y>=211&&Y<=271)
    		      	    {
    		      	    	getrest(7);
    		      	    	PlaySound(TEXT("����7.wav"),NULL,SND_FILENAME|SND_ASYNC);
    		      	    }
    		    	    else if(X>=68&&X<=130&&Y>=211&&Y<=271)
    		    	    {
    		    	    	getrest(8);
    		    	    	PlaySound(TEXT("����8.wav"),NULL,SND_FILENAME|SND_ASYNC);
    		    	    }
    		    	    	//����1-8����Ϣ������� 
    		      	    else if(X>=134&&X<=196&&Y>=149&&Y<=209) //����°�ͼ��Q 
    		      	    {
					        isquit=0;
    		      	    	SetActiveEgg(String);
	                        EatEgg();
	                        String=LayEgg();
	                        MovePen(0,140);
	                        DrawString("        �°�ָ���ѷ���");
	                        MovePen(0,120);
							DrawString("      �޷����нкŵȲ���");
	                        output=fopen("ins_output.txt","a");
                            fprintf(output,"T=%d,�����°�ָ�\n",Time);
                            fclose(output);
    		      	    }//�°�����ָ������ 
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
        if(flag==0)
            break;
	}
	StopTimer();
	PlaySound(NULL,NULL,SND_FILENAME); //��������ֹͣ 
	print_satisfy();
	fclose(outPtr);
	PlaySound(TEXT("�°�ɹ��ټ�.wav"),NULL,SND_FILENAME|SND_SYNC); //�����°����� 
	PlaySound(TEXT("�¿��.wav"),NULL,SND_FILENAME|SND_ASYNC);
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
	}//���������Ϣ�ȴ����������������޷�ͨ�� 
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
    	}//���������ȴ����� 
    	fprintf(fp,"T=%d,����%d������Ϣ����\n",Time,num);
    	SetActiveEgg(String);
    	EatEgg();
    	String=LayEgg();
    	MovePen(0,130);
	    DrawString("      ����");
	    sprintf(c,"%d",num);
	    DrawString(c);
     	DrawString("������Ϣ����");
     	
    	printf("T=%d,����%d������Ϣ����\n",Time,num);
	}
    flag=1;
    fclose(fp);
}
int buttonG()
{
	LISTNODEPTR currentp;       //��ͨ�û�����ڵ� 
	int i,restnum=0;            //restnum�Ǳ�ռ��λ���� 
	char c[2];                  //�洢��ͨ�û�������ַ���ʽ 
	FILE *fptr=NULL;
	fptr=fopen("ins_output.txt","a");
	SerId=SerId+1;
	currentp=(LISTNODEPTR)malloc(sizeof(LISTNODE));    //��ͨ�û����м�һ 
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
	fprintf(fptr,"T=%d,����һλ��ͨ�û���\n",Time);
	printf("�װ�����ͨ�û������ĺ���Ϊ%d\n",SerId);
	SetActiveEgg(String);
	EatEgg();
	String=LayEgg();       //�µ�����ʾ��ʾ��Ϣ 
	MovePen(0,140);
	DrawString("       �װ�����ͨ�û�,���ã�               ");
	MovePen(0,120);
	DrawString("       ���ĺ���Ϊ:");
	sprintf(c,"%d",SerId);
	DrawString(c);
	DrawString("��               "); 
	restnum=0;
	for(i=0;i<=13;i++)               //�жϱ�ռ��λ����
	{
		if(chair[i].Judge==1)
		restnum++;
	}
	if(restnum<14)
	{
		for(i=0;i<=13;i++)        //�ҵ��������λ 
		{
			if(chair[i].Judge==0)
			    break;
		}
		noregg[SerId]=LayEgg();         //�޸���λ������Ϣ 
		chair[i].Judge=1;
		chair[i].Value=0;
		chair[i].Num=SerId;
		if(i<=6)                            //������ʾ��ͨ�ͻ������ȴ� 
		{
			MovePen(230+(i*85),173);
			DrawBitmap("��ͨ�û�.bmp");
		}
		else
		{
			MovePen(230+((i-7)*85),80);
			DrawBitmap("��ͨ�û�.bmp");
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
				DrawBitmap("�ر�.bmp");
				break;
			case IDLE:
				DrawBitmap("����.bmp");
				break;
			case WAITING:
				DrawBitmap("�к���.bmp"); 
				break;
			case ENDING:
				DrawBitmap("������.bmp");
				break;
			case BREAK:
				DrawBitmap("��Ϣ��.bmp"); 
				break;
			case PROCESSING:
			    DrawBitmap("������.bmp"); 
				break;
		}//��ͼƬ��������������ʾ���ڵ�ǰ״̬ 
	}
	return 0;
}//��ʾ��ǰ���ڵķ���״̬ 

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
					DrawBitmap("��ͨ�û�.bmp");
					for(j=0;j<=13;j++)
					{
						if(chair[j].Num==num)
						    chair[j].Judge=0;
					}
					//��ͼ������ͨ�û�������������
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
					//��ͼ����VIP�û�������������
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
				}//���������ϣ����˿��ƶ����ſڣ���ʧ 
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
}//��ӡ��ͨ�ȴ������еĵȴ��˿������� 

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
}//�ȴ�VIP�ȴ������еĵȴ��˿������� 
























