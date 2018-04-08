#include<iostream> 
#include "strategy_2.h"
#define INFINITY 100000

using namespace std;

//初始化，并判断期待出发小时后有没有线路 
void second_initial(graph G, int start, int &expected_hour, int fl[], struct temp D[][12], int P[], int &flag)
{
	int count = 0 ;
	int i, k, hour_diff ;
	translist p ;
	for (i = 0 ; i < G.city_num ; i ++)
	{
		for (k = 0 ; k < 3 ; k ++)
		{
			p = G.cs[start][i].trans[k]->nextptr ;
			while (p) 
			{
			    hour_diff = p->start_hour - expected_hour ;
			    //线路出发时间在用户期待之后 
				if (hour_diff >= 0)
				{
					fl[i] = 1 ;
				}
				p = p->nextptr ;
			}
		}
		P[i] = start ;
	}
	
	for (i = 0 ; i < G.city_num ; i ++)
	{
		if (fl[i] == 0)
		count ++ ;
	} 
	if (count == 12)
	cout <<  "今天在期待时间后没有线路 " << endl ;
	else flag = 1 ;
	
}

void initial(graph G, clientlist &p, int final[], struct temp D[][12], int P[])
{
	int flag = 0 ;
	int i, j ;
	int citystart = p->city_start ;
	int fl[G.city_num] ;
	int hour_diff ;
	for (i = 0 ; i < G.city_num ; i ++)
    {
    	for (j = 0 ; j < G.city_num ; j ++)
    	{
    		D[i][j].time = INFINITY ;
    	}
    	
    	final[i] = 0 ;
    	fl[i] = 0 ;
    }
    
    second_initial(G,citystart,p->expected_hour,final,D,P,flag) ;
	while (flag == 0)
	{
		cout << "是否重新输入期待出发时间？" << " 是：Y 不是：N " ;
		char choice ;
		cin >> choice ;
		if (choice == 'Y')
		{
			cout << "输入出发时间：" ; 
			cin >> p->expected_hour ;
		}
		else if (choice == 'N')
		{
			cout << "系统自动帮您设计明天出发的线路" ;
			p->expected_hour = -1 ;
		}
		second_initial(G,citystart,p->expected_hour,final,D,P,flag) ;
	} 
	D[citystart][citystart].time = 0 ;
	final[citystart] = 1 ;
	P[citystart] = -1 ;
	
}

void shortest_time(graph G, int start, int arrive, int &expected_hour, int final[], struct temp D[][12], int P[], routelist &m)
{

	int i , j , k, w , min , pre , current ;
    translist p ;
    int hour_diff ;
    int flag ;
	for (i = 0 ; i < G.city_num ; i ++)
	{
		for (k = 0 ; k < 3 ; k ++)
		{
			p = G.cs[start][i].trans[k]->nextptr ;
			while (p) 
			{
			    hour_diff = p->start_hour - expected_hour ;
			   	//跨天情况判断 
			    if (hour_diff >= 0) 
			    {
			    	if (D[start][i].time > p->time + hour_diff)
					{
						D[start][i].time = p->time ;
						D[start][i].start_hour = p->start_hour ;
						D[start][i].arrive_hour = p->arrive_hour ;
						strcpy(D[start][i].Number,p->Number) ;
						D[start][i].price = p->price ;
						D[start][i].tran = k ;
					}
			    }
			    else
			    {
			    	if (D[start][i].time > p->time + 24 + hour_diff)
					{
						D[start][i].time = p->time + 24 + hour_diff ;
						D[start][i].start_hour = p->start_hour ;
						D[start][i].arrive_hour = p->arrive_hour ;
						strcpy(D[start][i].Number,p->Number) ;
						D[start][i].price = p->price ;
						D[start][i].tran = k ;
					}
			    }
				
				p = p->nextptr ;
			}
		}
		P[i] = start ;
	}
	//Dijstra算法主体 
	for (i = 0 ; i < G.city_num && !final[arrive] ; i ++)
	{
		min = INFINITY + 1 ;
		for (w = 0 ; w < G.city_num ; w ++)
		{
			if (!final[w] && D[start][w].time < min)
			{
				j = w ;
				min = D[start][w].time ;
			}
		} 
		
		final[j] = 1;
		for (w = 0 ; w < G.city_num ; w ++)
		{
			for (k = 0 ; k < 3 ; k ++)
			{
				p = G.cs[j][w].trans[k]->nextptr ;
				while (p)
				{
					if (!final[w]) 
					{
						hour_diff = p->start_hour - D[start][j].arrive_hour ;
						if (hour_diff < 0)
						{
							if (D[start][j].time + 24 + hour_diff + p->time < D[start][w].time)
							{
								D[start][w].time = D[start][j].time + 24 + hour_diff + p->time ;
								P[w] = j;
								D[j][w].time =  24 + hour_diff + p->time ;
								D[j][w].start_hour = p->start_hour ;
								D[j][w].arrive_hour = p->arrive_hour ;
								D[j][w].price = p->price ;
								strcpy(D[j][w].Number,p->Number) ;
								D[j][w].tran = k ;
							}
						}
						else
						{
							if (D[start][j].time + hour_diff + p->time < D[start][w].time)
							{
								D[start][w].time = D[start][j].time + hour_diff + p->time ;
								P[w] = j;
								D[j][w].time = hour_diff + p->time ;
								D[j][w].start_hour = p->start_hour ;
								D[j][w].arrive_hour = p->arrive_hour ;
								D[j][w].price = p->price ;
								strcpy(D[j][w].Number,p->Number) ;
								D[j][w].tran = k ;
							}
						}	
						
					}
					
					p = p->nextptr ;
				}
			}
		
		}
	}
	routelist p1,p2 ;
	pre = arrive ;
	//对用户的路线链表进行赋值 
	while ( pre != start )
	{
		current = pre ;
		pre = P[current] ;
		p2 = new route ;
		p2->from = pre ;
		p2->to = current ;
		p2->start_hour = D[pre][current].start_hour ;
		p2->arrive_hour = D[pre][current].arrive_hour ;
		p2->transportation = D[pre][current].tran ;
		p2->time = D[pre][current].time ;
		p2->price = D[pre][current].price ;
		strcpy(p2->Number,D[pre][current].Number) ;
		p2->nextptr = m->nextptr ;
		m->nextptr = p2 ;
	}
	expected_hour = D[P[arrive]][arrive].arrive_hour ;
    while (m->nextptr)
	{
		m = m->nextptr ;
	} 
}

void Shortest_Time(graph G,clientlist &p)
{
	routelist p1 ;
	p1 = p->R ;
	
	int final[G.city_num], P[G.city_num] ;
	struct temp D[12][12] ; 
	initial(G,p,final,D,P) ;
	
	int i , m , w ; 
	int exp = p->expected_hour ;
	//有途径城市的操作 
	if (p->city_num > 0)
	{
		shortest_time(G,p->city_start,p->pass_city[0],exp,final,D,P,p1) ;
		for (i = 0 ; i < p->city_num - 1 ; i ++)
		{
	    	m = p->pass_city[i] ;
			w = p->pass_city[i+1] ;
			shortest_time(G,m,w,exp,final,D,P,p1) ;
		}
		shortest_time(G,p->pass_city[p->city_num-1],p->city_end,exp,final,D,P,p1) ;
	}
	else
	{
		shortest_time(G,p->city_start,p->city_end,exp,final,D,P,p1) ;
	} 
} 
