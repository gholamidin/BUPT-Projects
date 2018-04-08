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

void cinit(clientlist &B)//节点初始化
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

void copy1(clientlist A,clientlist &B)//节点复制 
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
	while (D&&C)//将route节点全部复制 
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

void find(clientlist B,clientlist &C,clientlist &R)//查找函数，传入用户链表头和打印链表头尾 
{
		int bz = 0 ;
		string id ;
		clientlist GS, D, GX ;
		routelist A, xx ;
		GS = B ; //GS为用户链表头 
		GX = R ; //GX为打印链表头 
		cout << "请输入该旅客的ID号码：" << endl ;
		cin >> id ;
		if (GX)//如果打印队列是否已经有该节点 
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
			if (bz==0)//若打印队列中没有该节点 则从用户中寻找 ，若找到则在打印队列尾赋值。 
			{
				while (GS && GS->ID != id)
				{
					GS = GS->next ;
				}	
				if (GS && GS->ID == id)
				{
					cout << "旅客 " << GS->Name ;
					cout << "  在第" << GS->buy_day << "天" << GS->buy_hour << "小时购票" << endl ;
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
					cout << "无此旅客的信息！" ;
			} 
			if (bz == 1)//若打印队列有该节点，则将用户中的该节点覆盖到打印队列中 
			{
				while (GS && GS->ID != id)
				{
					GS = GS->next ;
				}
				if (GS && GS->ID == id)
				{
					cout << "旅客 " << GS->Name ;
					cout << "  在第" << GS->buy_day << "天" << GS->buy_hour << "小时购票" << endl ;
					copy1(GS,GX) ;
				}
			}	
		}
		else 
			cout << "无此旅客的信息！" ;
		
}
void screenout(clientlist &GS,clock_t T1)//屏幕输出，传入打印队列头和系统启动初始时间 
{
	int city1,trans,city2;//1出发城市，2到达城市 
	string id;
	char ch;
	int xx=0;
	routelist TX;
	clientlist TR;
	TR=new Client;
	clock_t T3,T;
	
	while (closeflag==0)
	{
		TR=GS;//TR为打印队列头 
		T3=clock();//clock当前时间 
		T=T3-T1-t3;//去除暂停时间后的当前时间 
		if (T/(time_go*1000)>=0&&(T%(time_go*1000)<500)&&t[T/(time_go*1000)]==0)//每过一小时后 ，打印一次 
		{	
			t[T/(time_go*1000)]=1;
			system("cls");
			cout<<"当前时间为：第"<<T/1000/time_go/24<<"天,第"<<(T/1000/time_go)%24<<"小时。"<<endl<<endl;
			cout<<"请输入选项（G：进入购票选项，P：进入查询选项，Q：退出系统）："<<endl ;
			while (TR&&TR->city_start!=13)
			{
				TX=new route;//TX为当前用户中的第一个城市节点，route节点 
				TX=TR->R;	
				TX=TX->nextptr;
				if (TX) //第一个城市 
				{
					if ((TX->start_day*24+TX->start_hour)*time_go*1000>T)// 未出发，xx=0 
					{
						xx=0;
					}	
					if ((TX->start_day*24+TX->start_hour)*time_go*1000<=T)// 已出发，xx=1 
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
						
				while (TX) //遍历以后城市 
				{
					if ((TX->start_day*24+TX->start_hour)*time_go*1000<=T)// 已出发，xx=1 
					{
						xx=1;
						city1=TX->from;
						trans=TX->transportation;
						if ((TX->start_day*24+TX->start_hour+TX->time)*time_go*1000>T&&!(TX->nextptr)) //已到达，下一城市为空 xx=3 
							xx=3;
						if ((TX->start_day*24+TX->start_hour+TX->time)*time_go*1000<=T&&(TX->nextptr)) //已到达，下一城市不为空 xx=4 
						{
							xx=4;
							city2=TX->nextptr->from;
						}
					}
					if ((TX->start_day*24+TX->start_hour)*time_go*1000>T&&xx==1) //上一个城市已到达该城市，但该城市还未出发。 
					{
						xx=2;
						city2=TX->from;
					}
					TX=TX->nextptr; 	
				}
				switch (xx)
				{
					case 0 :
						cout<<"旅客 "<<TR->Name<< "(ID号:"<< TR->ID <<") 在 "<<G.city_name[TR->city_start]<<" 还未出发。"<<endl; 
						TR=TR->next;
						break;
					case 1 :
						if (TR->sco==0)
						{
							cout<<"旅客 "<<TR->Name << "(ID号:" << TR->ID <<") 已到达目的地"<<G.city_name[TR->city_end]<<endl;
							TR->sco=1;
						}
						TR=TR->next;
						break;
					case 2 :
						cout<<"旅客 "<<TR->Name<< "(ID号:"<< TR->ID << ") 正在从"<<G.city_name[city1]; 
						cout<<"乘坐"<<G.transportation_name[trans];
						cout<<"到"<<G.city_name[city2]<<endl;
						TR=TR->next;
						break;
					case 3 :
						cout<<"旅客 "<<TR->Name << "(ID号:" << TR->ID <<") 正在从"<<G.city_name[city1]; 
						cout<<"乘坐"<<G.transportation_name[trans];
						cout<<"到"<<G.city_name[TR->city_end]<<endl; 
						TR=TR->next;
						break;
					case 4 :
						if(TR->scp[city2]==0)
						{
							cout<<"旅客 "<<TR->Name << "(ID号:" << TR->ID <<") 已经到达"<<G.city_name[city2]<<",正在原地等待下一趟"<<endl; 
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


