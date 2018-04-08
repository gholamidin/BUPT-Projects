#include<cstdio>
#include<cstdlib> 
#include<fstream>
#include<sstream>
#include<cstring>

#include "strategy_3.h"

#define CITY_NUM 12  //城市总数 
#define INFINITY 100000 

using namespace std ;

extern graph G ;
extern ifstream in ; 
extern clientlist TR ;
extern clock_t T1, t3 ;

int transfor(string s)  //将字符串转化为整型 
{
    int i ;
	stringstream stream ;
    stream << s ;
    stream >> i ;
    return i ;
}

void write_in(clientlist &p2,clock_t T5) //输入旅客的信息 
{
		routelist N;
		p2->buy_day = (T5/(time_go*1000)) / 24 ;
		p2->buy_hour = (T5/(time_go*1000)) % 24 ;
		p2->city_num = 0 ;
		cout <<
		"*********************************************************\n" 
 		"*      		   城市编号                             *\n"
 		"*  北京 0  上海 1     沈阳 2  郑州 3  武汉 4  长沙 5    *\n"
 		"*  成都 6  乌鲁木齐 7 昆明 8  西安 9  广州 10 重庆 11   *\n"
 		"*********************************************************\n" ;
		cout << "请输入出发城市：" ;
		cin >> p2->city_start ;
		cout << "请输入目的地城市：" ;
		cin >> p2->city_end ;
		cout << "请输入希望途径的城市，按顺序输入，停止请输入-1：" ;
		int i ;
		cin >> i ;
		while ( i != -1 )
		{
			p2->pass_city[p2->city_num] = i ;
			p2->city_num ++ ;
			cin >> i ;
		}
		cout << "请输入您期待出发的天数：" << endl ;
		cout << "0：今天，1：明天，2：后天，依次类推。" << endl ;
		cin >> p2->expected_day ;
		cout << "请输入您期待出发的小时数：" ;
		cin >> p2->expected_hour ;
		cout << "请输入希望选择的策略：" << endl ;
		cout << "最少费用策略，请输入1" << endl ;
		cout << "最少时间策略，请输入2" << endl ;
		cout << "限时最少费用策略，请输入3" << endl ;
		cin >> p2->strategy ;
		p2->R = new route ;
		p2->R->nextptr=NULL ;
		p2->next = NULL;
		switch (p2->strategy)  //选择策略 
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
		//计算路线链表中每条线路的出发天数和出发小时数 
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
	cout << "请输入您的名字：" ;
	cin >> p2->Name ;
	cout << "请输入您的ID号：" ;
	cin >> p2->ID ;
	
	//判断是否有重复ID号但是名字不同的情况 
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
				cout<<"已经输入过此ID，但你的名字不正确，错误输入。"<<endl;
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
	if (flag == 0) //打印旅客的旅行线路至屏幕 
	{
		TR=new Client;
		TR=p2;
		L=p2->R->nextptr;
		cout << "该旅客在第" << TR->buy_day << "天" << TR->buy_hour << "小时购票成功" << endl ;
		cout << "该旅客的旅行计划是：从在第" << L->start_day << "天第" << L->start_hour << "小时开始" << endl ;
		/*cout << G.city_name[L->from] << "->" G.city_name[L->to] << "出发时间：" L->start_hour << "到达时间：" << L->arrive_hour 
		     << " 费用：" << L->price << "元 时间：" << L->time << "小时 交通工具："<< G.transportation_name[L->transportation] << endl ;*/
		while (L)
		{
			cout << G.city_name[L->from] << "->" << G.city_name[L->to] 
			     << " 出发时间：" << L->start_hour << " 到达时间：" << L->arrive_hour 
		         << " 费用：" << L->price << "元  时间：" << L->time << "小时"
				 << " 交通工具："<< G.transportation_name[L->transportation] 
				 << " 车次：" << L->Number << endl ;
			L = L->nextptr;
		}
		system("pause") ; 
	}	

} 








