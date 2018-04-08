#include<cstdio>
#include<cstdlib> 
#include<fstream>
#include<sstream>
#include<cstring>

#include "strategy_3.h"

#define CITY_NUM 12  //�������� 
#define INFINITY 100000 

using namespace std ;

extern graph G ;
extern ifstream in ; 
extern clientlist TR ;
extern clock_t T1, t3 ;

int transfor(string s)  //���ַ���ת��Ϊ���� 
{
    int i ;
	stringstream stream ;
    stream << s ;
    stream >> i ;
    return i ;
}

void write_in(clientlist &p2,clock_t T5) //�����ÿ͵���Ϣ 
{
		routelist N;
		p2->buy_day = (T5/(time_go*1000)) / 24 ;
		p2->buy_hour = (T5/(time_go*1000)) % 24 ;
		p2->city_num = 0 ;
		cout <<
		"*********************************************************\n" 
 		"*      		   ���б��                             *\n"
 		"*  ���� 0  �Ϻ� 1     ���� 2  ֣�� 3  �人 4  ��ɳ 5    *\n"
 		"*  �ɶ� 6  ��³ľ�� 7 ���� 8  ���� 9  ���� 10 ���� 11   *\n"
 		"*********************************************************\n" ;
		cout << "������������У�" ;
		cin >> p2->city_start ;
		cout << "������Ŀ�ĵس��У�" ;
		cin >> p2->city_end ;
		cout << "������ϣ��;���ĳ��У���˳�����룬ֹͣ������-1��" ;
		int i ;
		cin >> i ;
		while ( i != -1 )
		{
			p2->pass_city[p2->city_num] = i ;
			p2->city_num ++ ;
			cin >> i ;
		}
		cout << "���������ڴ�������������" << endl ;
		cout << "0�����죬1�����죬2�����죬�������ơ�" << endl ;
		cin >> p2->expected_day ;
		cout << "���������ڴ�������Сʱ����" ;
		cin >> p2->expected_hour ;
		cout << "������ϣ��ѡ��Ĳ��ԣ�" << endl ;
		cout << "���ٷ��ò��ԣ�������1" << endl ;
		cout << "����ʱ����ԣ�������2" << endl ;
		cout << "��ʱ���ٷ��ò��ԣ�������3" << endl ;
		cin >> p2->strategy ;
		p2->R = new route ;
		p2->R->nextptr=NULL ;
		p2->next = NULL;
		switch (p2->strategy)  //ѡ����� 
		{
			case 1:
				floyd(G,p2) ;
				break;
			case 2:
				Shortest_Time(G,p2) ;
				break;	
			case 3:
				strategy_3(G,p2) ;
				break;
		}
		//����·��������ÿ����·�ĳ��������ͳ���Сʱ�� 
		if (p2->R->nextptr->start_hour<(T5/time_go/1000)%24&&p2->expected_day==0)
		{
			p2->R->nextptr->start_day=(T5/time_go/1000/24)+1;
			N=p2->R->nextptr;
		}
		else 
		{
			if(p2->R->nextptr->start_hour>=(T5/time_go/1000)%24&&p2->R->nextptr->start_hour<p2->expected_hour&&p2->expected_day==0)
			{
				p2->R->nextptr->start_day=(T5/time_go/1000/24)+1;
				N=p2->R->nextptr;
			}
			else
			{
				p2->R->nextptr->start_day=(T5/time_go/1000/24)+p2->expected_day;
				N=p2->R->nextptr;
			}
		} 
		while (N->nextptr)
		{
			if ((N->start_hour+N->time)%24>N->nextptr->start_hour)
			{
				N->nextptr->start_day=N->start_day+(N->start_hour+N->time)/24+1;
			}
			else if ((N->start_hour+N->time)%24<=N->nextptr->start_hour)
			{
				N->nextptr->start_day=N->start_day+(N->start_hour+N->time)/24;
			}
			N=N->nextptr;
		}
		
}

void input(clientlist &headp, clientlist & lastp, clock_t T1)
{		
	int flag=0;
	clientlist temp,phead,p2 ;
	p2 = new Client ;
	cinit(p2);
	clock_t T4,T5;
	clientlist p1,TR;
	routelist N,L;
	T4=clock();
	T5=T4-T1-t3;
	phead=headp;
	cout << "�������������֣�" ;
	cin >> p2->Name ;
	cout << "����������ID�ţ�" ;
	cin >> p2->ID ;
	
	//�ж��Ƿ����ظ�ID�ŵ������ֲ�ͬ����� 
	while (phead&&p2->ID!=phead->ID)
	{	
		phead=phead->next;
	}
	if (phead)
	{
		if (phead->ID==p2->ID)
		{
			if (phead->Name==p2->Name)
			{
				write_in(p2,T5);
				phead->R->nextptr=new route;
				copy1(p2,phead);
			}
			else
			{
				cout<<"�Ѿ��������ID����������ֲ���ȷ���������롣"<<endl;
				Sleep(2000) ;
				flag = 1 ;	 
			}
		}
	}
	else
	{
		if (lastp->city_start!=13)
		{
			write_in(p2,T5);
			lastp->next=new Client;
			cinit(lastp->next);
			lastp->next->R->nextptr=new route;
			lastp=lastp->next;
			copy1(p2,lastp);
		}
		else
		{	
			write_in(p2,T5);
			lastp->R->nextptr=new route;
			copy1(p2,lastp);	
		} 
	}
	if (flag == 0) //��ӡ�ÿ͵�������·����Ļ 
	{
		TR=new Client;
		TR=p2;
		L=p2->R->nextptr;
		cout << "���ÿ��ڵ�" << TR->buy_day << "��" << TR->buy_hour << "Сʱ��Ʊ�ɹ�" << endl ;
		cout << "���ÿ͵����мƻ��ǣ����ڵ�" << L->start_day << "���" << L->start_hour << "Сʱ��ʼ" << endl ;
		/*cout << G.city_name[L->from] << "->" G.city_name[L->to] << "����ʱ�䣺" L->start_hour << "����ʱ�䣺" << L->arrive_hour 
		     << " ���ã�" << L->price << "Ԫ ʱ�䣺" << L->time << "Сʱ ��ͨ���ߣ�"<< G.transportation_name[L->transportation] << endl ;*/
		while (L)
		{
			cout << G.city_name[L->from] << "->" << G.city_name[L->to] 
			     << " ����ʱ�䣺" << L->start_hour << " ����ʱ�䣺" << L->arrive_hour 
		         << " ���ã�" << L->price << "Ԫ  ʱ�䣺" << L->time << "Сʱ"
				 << " ��ͨ���ߣ�"<< G.transportation_name[L->transportation] 
				 << " ���Σ�" << L->Number << endl ;
			L = L->nextptr;
		}
		system("pause") ; 
	}	

} 








