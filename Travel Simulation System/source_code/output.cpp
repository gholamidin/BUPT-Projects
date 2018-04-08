#include<fstream>
#include<sstream>
#include<cstring>
#include "output.h"

using namespace std;

extern int closeflag;
extern clientlist TR;
extern graph G;
extern clock_t T1,t3;
int t[1000];
extern HANDLE hEvent;
extern CRITICAL_SECTION cs;

void cinit(clientlist &B)//�ڵ��ʼ��
{
	int i;
	routelist A;
	B->Name='0' ;   
    B->ID='0' ;     
    B->city_start=13 ;    
    B->city_end=13 ;     
	B->city_num=0;
	B->sco=0;
	B->limit_time=0;
    B->expected_day=0;
    B->expected_hour=0 ;
	B->strategy=0;
	B->buy_day=0;
    B->buy_hour=0;
    B->next=NULL; 
    for (i=0;i<=11;i++)
    {
		B->pass_city[i]=13;	
		B->scp[i]=0;
	}
	B->R=new route ;
	B->R->from=13;
	B->R->to=13;
    B->R->arrive_hour=0 ;
    B->R->price=0;
    B->R->start_day=0;
    B->R->start_hour=0;
    B->R->time=0;
    B->R->transportation=3;
    B->R->nextptr=NULL;
}

void copy1(clientlist A,clientlist &B)//�ڵ㸴�� 
{
	int i;
	routelist C,D,E;
	D=new route;
	C=new route;
	if (B->R->nextptr&&A->R->nextptr)
	{
		D=B->R->nextptr;
		C=A->R->nextptr;
	}
	else
	{
		D=B->R;
		C=A->R;
	}
	B->limit_time=A->limit_time;
	B->Name=A->Name ;   
	B->ID=A->ID ;     
	B->sco=A->sco;
	B->city_start=A->city_start ;    
	B->city_end=A->city_end ;     
	B->city_num=A->city_num;
	B->expected_day=A->expected_day;
	B->expected_hour=A->expected_hour ;
	B->strategy=A->strategy;
	B->buy_day=A->buy_day;
	B->buy_hour=A->buy_hour;
	for (i=0;i<=11;i++)
	{
	   	B->pass_city[i]=A->pass_city[i];
	   	B->scp[i]=A->scp[i];
	}
	while (D&&C)//��route�ڵ�ȫ������ 
	{
		D->from=C->from;
		D->to=C->to;
		D->arrive_hour=C->arrive_hour;
		strcpy(D->Number,C->Number) ;
		D->price=C->price;
		D->start_day=C->start_day;
		D->start_hour=C->start_hour;
		D->time=C->time;
		D->transportation=C->transportation;
		if (C->nextptr)
		{
		    E=new route;
		    D->nextptr=E;
		    D=D->nextptr;
		    C=C->nextptr;
		}
		else
		{
			D->nextptr=NULL;
			C->nextptr=NULL;
			break;
		}
	}
}

void find(clientlist B,clientlist &C,clientlist &R)//���Һ����������û�����ͷ�ʹ�ӡ����ͷβ 
{
		int bz = 0 ;
		string id ;
		clientlist GS, D, GX ;
		routelist A, xx ;
		GS = B ; //GSΪ�û�����ͷ 
		GX = R ; //GXΪ��ӡ����ͷ 
		cout << "��������ÿ͵�ID���룺" << endl ;
		cin >> id ;
		if (GX)//�����ӡ�����Ƿ��Ѿ��иýڵ� 
		{
			while (GX&&GX->ID!=id)
			{
				GX=GX->next;
			}	
			if (GX&&GX->ID==id)
			{
				bz=1;
			}
		}
		if (GS)
		{
			if (bz==0)//����ӡ������û�иýڵ� ����û���Ѱ�� �����ҵ����ڴ�ӡ����β��ֵ�� 
			{
				while (GS && GS->ID != id)
				{
					GS = GS->next ;
				}	
				if (GS && GS->ID == id)
				{
					cout << "�ÿ� " << GS->Name ;
					cout << "  �ڵ�" << GS->buy_day << "��" << GS->buy_hour << "Сʱ��Ʊ" << endl ;
					if (C->city_start == 13)
					{
						A = new route ;
						C->R->nextptr = A ;
						copy1(GS,C) ;
					}
					else 
					{
						D = new Client ;
						cinit(D) ;
						xx = new route ;
						D->R->nextptr = xx ;		
						C->next = D ;
						C = C->next ;
						copy1(GS,C) ;
					}
					C->next = NULL ;
				}	
				else
					cout << "�޴��ÿ͵���Ϣ��" ;
			} 
			if (bz == 1)//����ӡ�����иýڵ㣬���û��еĸýڵ㸲�ǵ���ӡ������ 
			{
				while (GS && GS->ID != id)
				{
					GS = GS->next ;
				}
				if (GS && GS->ID == id)
				{
					cout << "�ÿ� " << GS->Name ;
					cout << "  �ڵ�" << GS->buy_day << "��" << GS->buy_hour << "Сʱ��Ʊ" << endl ;
					copy1(GS,GX) ;
				}
			}	
		}
		else 
			cout << "�޴��ÿ͵���Ϣ��" ;
		
}
void screenout(clientlist &GS,clock_t T1)//��Ļ����������ӡ����ͷ��ϵͳ������ʼʱ�� 
{
	int city1,trans,city2;//1�������У�2������� 
	string id;
	char ch;
	int xx=0;
	routelist TX;
	clientlist TR;
	TR=new Client;
	clock_t T3,T;
	
	while (closeflag==0)
	{
		TR=GS;//TRΪ��ӡ����ͷ 
		T3=clock();//clock��ǰʱ�� 
		T=T3-T1-t3;//ȥ����ͣʱ���ĵ�ǰʱ�� 
		if (T/(time_go*1000)>=0&&(T%(time_go*1000)<500)&&t[T/(time_go*1000)]==0)//ÿ��һСʱ�� ����ӡһ�� 
		{	
			t[T/(time_go*1000)]=1;
			system("cls");
			cout<<"��ǰʱ��Ϊ����"<<T/1000/time_go/24<<"��,��"<<(T/1000/time_go)%24<<"Сʱ��"<<endl<<endl;
			cout<<"������ѡ�G�����빺Ʊѡ�P�������ѯѡ�Q���˳�ϵͳ����"<<endl ;
			while (TR&&TR->city_start!=13)
			{
				TX=new route;//TXΪ��ǰ�û��еĵ�һ�����нڵ㣬route�ڵ� 
				TX=TR->R;	
				TX=TX->nextptr;
				if (TX) //��һ������ 
				{
					if ((TX->start_day*24+TX->start_hour)*time_go*1000>T)// δ������xx=0 
					{
						xx=0;
					}	
					if ((TX->start_day*24+TX->start_hour)*time_go*1000<=T)// �ѳ�����xx=1 
					{
						xx=1;
						city1=TX->from;
						trans=TX->transportation;
						if((TX->start_day*24+TX->start_hour+TX->time)*time_go*1000>T&&!TX->nextptr) //�ѵ����һ����Ϊ�� xx=3 
							xx=3;
						if((TX->start_day*24+TX->start_hour+TX->time)*time_go*1000<=T&&TX->nextptr)//�ѵ����һ���в�Ϊ�� xx=4 
						{
							xx=4;
							city2=TX->nextptr->from;
						}
					}
					TX=TX->nextptr; 
				}
						
				while (TX) //�����Ժ���� 
				{
					if ((TX->start_day*24+TX->start_hour)*time_go*1000<=T)// �ѳ�����xx=1 
					{
						xx=1;
						city1=TX->from;
						trans=TX->transportation;
						if ((TX->start_day*24+TX->start_hour+TX->time)*time_go*1000>T&&!(TX->nextptr)) //�ѵ����һ����Ϊ�� xx=3 
							xx=3;
						if ((TX->start_day*24+TX->start_hour+TX->time)*time_go*1000<=T&&(TX->nextptr)) //�ѵ����һ���в�Ϊ�� xx=4 
						{
							xx=4;
							city2=TX->nextptr->from;
						}
					}
					if ((TX->start_day*24+TX->start_hour)*time_go*1000>T&&xx==1) //��һ�������ѵ���ó��У����ó��л�δ������ 
					{
						xx=2;
						city2=TX->from;
					}
					TX=TX->nextptr; 	
				}
				switch (xx)
				{
					case 0 :
						cout<<"�ÿ� "<<TR->Name<< "(ID��:"<< TR->ID <<") �� "<<G.city_name[TR->city_start]<<" ��δ������"<<endl; 
						TR=TR->next;
						break;
					case 1 :
						if (TR->sco==0)
						{
							cout<<"�ÿ� "<<TR->Name << "(ID��:" << TR->ID <<") �ѵ���Ŀ�ĵ�"<<G.city_name[TR->city_end]<<endl;
							TR->sco=1;
						}
						TR=TR->next;
						break;
					case 2 :
						cout<<"�ÿ� "<<TR->Name<< "(ID��:"<< TR->ID << ") ���ڴ�"<<G.city_name[city1]; 
						cout<<"����"<<G.transportation_name[trans];
						cout<<"��"<<G.city_name[city2]<<endl;
						TR=TR->next;
						break;
					case 3 :
						cout<<"�ÿ� "<<TR->Name << "(ID��:" << TR->ID <<") ���ڴ�"<<G.city_name[city1]; 
						cout<<"����"<<G.transportation_name[trans];
						cout<<"��"<<G.city_name[TR->city_end]<<endl; 
						TR=TR->next;
						break;
					case 4 :
						if(TR->scp[city2]==0)
						{
							cout<<"�ÿ� "<<TR->Name << "(ID��:" << TR->ID <<") �Ѿ�����"<<G.city_name[city2]<<",����ԭ�صȴ���һ��"<<endl; 
							TR->scp[city2]=0;
						}
						TR=TR->next;
						break;
					default:
						break;
			
				}
			}
					
		}
		WaitForSingleObject(hEvent,INFINITE);
	}
}


