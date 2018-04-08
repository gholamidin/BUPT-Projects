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
DWORD WINAPI h(LPVOID pPararneter)//线程 文件输出 
{
	fileout(TR);
} 

void fileout(clientlist HEAD)
{		
		int city1,city2,trans,xx,t[1000];
		clock_t Ts,Te,T;//开始 当前
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
			
			if(T/(time_go*1000)>=0&&(T%(time_go*1000)<500)&&t[T/(time_go*1000)]==0)//每过一小时后 ，打印一次 
			{
					
				t[T/(time_go*1000)]=1;
				outfile<<endl<< "当前时间为：第"<<T/1000/time_go/24<<"天,第"<<(T/1000/time_go)%24<<"小时。"<<endl;
				while(p&&p->city_start!=13)
						{
							TX=new route;//TX为当前用户中的第一个城市节点，route节点 
							TX=p->R;	
							TX=TX->nextptr;								
						
							if(TX) //第一个城市 
							{

								if((TX->start_day*24+TX->start_hour)*time_go*1000>T)// 未出发，xx=0 
									{
										xx=0;
									}	
								if((TX->start_day*24+TX->start_hour)*time_go*1000<=T)// 已出发，xx=1 
									{
										xx=1;
										city1=TX->from;
										trans=TX->transportation;
										if((TX->start_day*24+TX->start_hour+TX->time)*time_go*1000>T&&!TX->nextptr) //已到达，下一城市为空 xx=3 
											xx=3;
										if((TX->start_day*24+TX->start_hour+TX->time)*time_go*1000<=T&&TX->nextptr)//已到达，下一城市不为空 xx=4 
										{
											xx=4;
											city2=TX->nextptr->from;
										}
										
									}
								TX=TX->nextptr; 
							}
							
							while(TX) //遍历以后城市 
							{
								if((TX->start_day*24+TX->start_hour)*time_go*1000<=T)// 已出发，xx=1 
								{
									xx=1;
									city1=TX->from;
									trans=TX->transportation;
									if((TX->start_day*24+TX->start_hour+TX->time)*time_go*1000>T&&!(TX->nextptr)) //已到达，下一城市为空 xx=3 
										xx=3;
									if((TX->start_day*24+TX->start_hour+TX->time)*time_go*1000<=T&&(TX->nextptr)) //已到达，下一城市不为空 xx=4 
									{
										xx=4;
										city2=TX->nextptr->from;
									}
									
								}
								if((TX->start_day*24+TX->start_hour)*time_go*1000>T&&xx==1) //上一个城市已到达该城市，但该城市还未出发。 
								{
									xx=2;
									city2=TX->from;
								}
								TX=TX->nextptr; 	
							}
							switch(xx)
							{
								case 0:
									outfile<<"旅客 "<<p->Name<<" ID "<<p->ID<<" 还未出发。"<<endl; 
									p=p->next;
									break;
								case 1:
								
									if(p->sco==0)
									{
										outfile<<"旅客 "<<p->Name<<" ID "<<p->ID<<" 已到达目的地 "<<G.city_name[p->city_end]<<endl; 
										p->sco=1;
									}
									p=p->next;
									break;
											
								case 2:
									outfile<<"旅客 "<<p->Name<<" ID "<<p->ID<<" 正在从"<<G.city_name[city1]; 
									outfile<<"乘坐"<<G.transportation_name[trans];
									outfile<<"到"<<G.city_name[city2]<<endl;
									p=p->next;
									break;
								case 3:
									outfile<<"旅客 "<<p->Name<<" ID "<<p->ID<<" 正在从"<<G.city_name[city1]; 
									outfile<<"乘坐"<<G.transportation_name[trans];
									outfile<<"到"<<G.city_name[p->city_end]<<endl; 
									p=p->next;
									break;
								case 4:
									if(p->scp[city2]==0)
									{
									
										outfile<<"旅客 "<<p->Name<<" ID "<<p->ID<<" 已经到达"<<G.city_name[city2]<<",正在原地等待下一趟"<<endl; 
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
