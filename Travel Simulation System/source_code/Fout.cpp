#include<iostream> 
#include<fstream>
#include<sstream>
#include<cstring>
#include "Fout.h"
using namespace std;

extern int closeflag;
extern clock_t t3;
extern clientlist TR,TL;
extern graph G;
extern HANDLE hEvent1,hEvent2;
void Fileout()
{
	HANDLE hTheard;
	hTheard=CreateThread(NULL,0,h,NULL,0,NULL);

}
DWORD WINAPI h(LPVOID pPararneter)//�߳� �ļ���� 
{
	fileout(TR);
} 

void fileout(clientlist HEAD)
{		
		int city1,city2,trans,xx,t[1000];
		clock_t Ts,Te,T;//��ʼ ��ǰ
		clientlist p;
		routelist TX;
		p=new Client;
		TX=new route;
		Ts=clock();
		ofstream outfile("output.txt");
		while(closeflag==0)
		{	
			
			Te=clock();
			p=HEAD;
			T=Te-Ts-t3;
			
			if(T/(time_go*1000)>=0&&(T%(time_go*1000)<500)&&t[T/(time_go*1000)]==0)//ÿ��һСʱ�� ����ӡһ�� 
			{
					
				t[T/(time_go*1000)]=1;
				outfile<<endl<< "��ǰʱ��Ϊ����"<<T/1000/time_go/24<<"��,��"<<(T/1000/time_go)%24<<"Сʱ��"<<endl;
				while(p&&p->city_start!=13)
						{
							TX=new route;//TXΪ��ǰ�û��еĵ�һ�����нڵ㣬route�ڵ� 
							TX=p->R;	
							TX=TX->nextptr;								
						
							if(TX) //��һ������ 
							{

								if((TX->start_day*24+TX->start_hour)*time_go*1000>T)// δ������xx=0 
									{
										xx=0;
									}	
								if((TX->start_day*24+TX->start_hour)*time_go*1000<=T)// �ѳ�����xx=1 
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
							
							while(TX) //�����Ժ���� 
							{
								if((TX->start_day*24+TX->start_hour)*time_go*1000<=T)// �ѳ�����xx=1 
								{
									xx=1;
									city1=TX->from;
									trans=TX->transportation;
									if((TX->start_day*24+TX->start_hour+TX->time)*time_go*1000>T&&!(TX->nextptr)) //�ѵ����һ����Ϊ�� xx=3 
										xx=3;
									if((TX->start_day*24+TX->start_hour+TX->time)*time_go*1000<=T&&(TX->nextptr)) //�ѵ����һ���в�Ϊ�� xx=4 
									{
										xx=4;
										city2=TX->nextptr->from;
									}
									
								}
								if((TX->start_day*24+TX->start_hour)*time_go*1000>T&&xx==1) //��һ�������ѵ���ó��У����ó��л�δ������ 
								{
									xx=2;
									city2=TX->from;
								}
								TX=TX->nextptr; 	
							}
							switch(xx)
							{
								case 0:
									outfile<<"�ÿ� "<<p->Name<<" ID "<<p->ID<<" ��δ������"<<endl; 
									p=p->next;
									break;
								case 1:
								
									if(p->sco==0)
									{
										outfile<<"�ÿ� "<<p->Name<<" ID "<<p->ID<<" �ѵ���Ŀ�ĵ� "<<G.city_name[p->city_end]<<endl; 
										p->sco=1;
									}
									p=p->next;
									break;
											
								case 2:
									outfile<<"�ÿ� "<<p->Name<<" ID "<<p->ID<<" ���ڴ�"<<G.city_name[city1]; 
									outfile<<"����"<<G.transportation_name[trans];
									outfile<<"��"<<G.city_name[city2]<<endl;
									p=p->next;
									break;
								case 3:
									outfile<<"�ÿ� "<<p->Name<<" ID "<<p->ID<<" ���ڴ�"<<G.city_name[city1]; 
									outfile<<"����"<<G.transportation_name[trans];
									outfile<<"��"<<G.city_name[p->city_end]<<endl; 
									p=p->next;
									break;
								case 4:
									if(p->scp[city2]==0)
									{
									
										outfile<<"�ÿ� "<<p->Name<<" ID "<<p->ID<<" �Ѿ�����"<<G.city_name[city2]<<",����ԭ�صȴ���һ��"<<endl; 
										TR->scp[city2]=0;
									}
									p=p->next;
									break;
								default:break;
				
							}
						}
			}
			WaitForSingleObject(hEvent1,INFINITE);			
		}
		outfile.close();
}
