#include<iostream> 
#include "strategy_3.h"
#include "graphical.h"
#define INFINITY 100000
using namespace std;

//Dijstra算法求最少费用 
void lowest_price(graph G, clientlist &c)
{
	int i, j, k, w ,min ;
	int visited[12] ;
	struct temp L[12][12] ;
	translist p ;
	int start = c->city_start ;
	int arrive = c->city_end ;
	
	for (i = 0 ; i < G.city_num ; i ++)
    {
    	d[i] = INFINITY ;
    	time1[i] = INFINITY ;
    	visited[i] = 0 ;
    }
    
	for (i = 0 ; i < G.city_num ; i ++)
	{
		for (k = 0 ; k < 3 ; k ++)
		{
			p = G.cs[start][i].trans[k]->nextptr ;
			while (p) 
			{
				if (d[i] > p->price)
				{
					d[i] = p->price ;
					time1[i] = p->time ;
					L[start][i].price = p->price ;
					L[start][i].start_hour = p->start_hour ;
					L[start][i].arrive_hour = p->arrive_hour ;
					L[start][i].time = p->time ;
					strcpy(L[start][i].Number,p->Number) ;
					L[start][i].tran = k ;
				}
				p = p->nextptr ;
			}
		}
		note[i] = start ;
	}
	
    visited[start] = 1 ;
	d[start] = 0 ;
	time1[start] = 0 ;
	note[start] = -1 ;
	
	for (i = 0 ; i < G.city_num ; i ++)
	{
		min = INFINITY + 1 ;
		for (w = 0 ; w < G.city_num ; w ++)
		{
			if (!visited[w] && d[w] < min)
			{
				j = w ;
				min = d[w] ;
			}
		} 
		
		visited[j] = 1;
		for (w = 0 ; w < G.city_num ; w ++)
		{
			for (k = 0 ; k < 3 ; k ++)
			{
				p = G.cs[j][w].trans[k]->nextptr ;
				while (p)
				{
					if (!visited[w]) 
					{
						if (d[j] + p->price < d[w])
						{
							d[w] = d[j] + p->price ;
							time1[w] = time1[j] + p->time + (p->start_hour-(c->expected_hour+time1[j]) % 24 + 24) % 24 ;
							note[w] = j;
							L[j][w].price = p->price ;
							L[j][w].start_hour = p->start_hour ;
							L[j][w].arrive_hour = p->arrive_hour ;
							L[j][w].time = p->time ;
							strcpy(L[j][w].Number,p->Number) ;
							L[j][w].tran = k ;
						}
						
					}
					
					p = p->nextptr ;
				}
			}
		}
	} 
	
	num = 0 ;
	//对用户的路线链表进行赋值 
	int pre = arrive ;
	int current ;
	while (pre != start)
	{
		current = pre ;
		pre = note[current] ;
		num ++ ;
	}
	pre = arrive ;
	int number = num ;
	while (pre != start)
	{
		current = pre ;
		pre = note[current] ;
		Route[number-1].pre = pre ;
		Route[number-1].cur = current ;
		Route[number-1].start_hour = L[pre][current].start_hour ;
		Route[number-1].arrive_hour = L[pre][current].arrive_hour ;
		Route[number-1].time = L[pre][current].time ;
		Route[number-1].price = L[pre][current].price ;
		strcpy(Route[number-1].Number,L[pre][current].Number) ;
		Route[number-1].tran = L[pre][current].tran ;
		number -- ;
	}
	
}

void dfs(int now,clientlist &c, graph G)
{
	int i, j, k ;
	translist p ;
	
	if (time1[now] > c->limit_time)  //超过限定时间，回溯 
		return ;
	if (d[now] > totalmin && success) //成功的方案，但是比之前存储的方案费用多，回溯 
		return ;
	if (now == c->city_end && pass_num == c->city_num) //到达目的城市且经过了所有沿途城市 
	{
		success = 1 ;
		size = sizet ;
		totalmin = d[now] ;
		totaltime = time1[now] ;
		for (i = 0 ; i < size ; i ++)
		{
			Route[i].pre = line[i].pre ;
			Route[i].cur = line[i].cur ;
			Route[i].start_hour = line[i].start_hour ;
			Route[i].arrive_hour = line[i].arrive_hour ;
			Route[i].time = line[i].time ;
			Route[i].price = line[i].price ;
			strcpy(Route[i].Number,line[i].Number) ;
			Route[i].tran = line[i].tran ;
		}
		return ;
	}
	//判断是否经过了所有必经城市 
	for (i = 0 ; i < c->city_num ; i ++)
	{
		if (now == c->pass_city[i])
		{
			if (passed[now] == 0)
			{
				pass_num ++ ;
			}	
			passed[now] ++ ;
			if (passed[now] == 1)
			{
				for (int j = 0 ; j < i ; j ++)
				{
					if (!passed[c->pass_city[j]])
					{
						pass_num -- ;
						passed[now] -- ; 
						return ;
					} 
				}	
			}	
		}
	}
	
	int pricetemp, timetemp, passed_marktemp ;
	for (i = 0 ; i < G.city_num ; i ++)
	{
		for (k = 0 ; k < 3 ; k ++)
		{
			p = G.cs[now][i].trans[k]->nextptr ;
			
			while (p)
			{
				int T ;
				T = time1[now]+ p->time + (p->start_hour-(c->expected_hour + time1[now]) % 24 + 24) % 24 ;
				if (pass_num > pass_marked[i] || d[now] + p->price < d[i]
			              || T < time1[i])
				{
			 		pass_marked[i] = pass_num ;
			 		pricetemp = d[now] ;
			 		timetemp = time1[now] ;
			 		passed_marktemp = pass_marked[now] ;
			 		d[i] = d[now] + p->price ;
			 		time1[i] = T  ;
			 		line[sizet].pre = now ;
			 		line[sizet].cur = i ;
			 		line[sizet].start_hour = p->start_hour ;
			 		line[sizet].arrive_hour = p->arrive_hour ;
			 		line[sizet].time = p->time ;
			 		line[sizet].price = p->price ;
			 		strcpy(line[sizet].Number,p->Number) ;
			 		line[sizet].tran = k ;
			 		sizet ++ ;
			 		dfs(i,c,G) ;
			 		d[now] = pricetemp ;
			 		time1[now]= timetemp ;
			 		pass_marked[now] = passed_marktemp ;
			 		sizet -- ;
				}
				p = p->nextptr ;
			}
			
		}	
	}
	if (passed[now] && --passed[now] == 0)
	{
		pass_num -- ;
	} 
	
} 
	
void strategy_3(graph G,clientlist &c)
{
	if (choice == 1)
	{
		cout << "请输入限定时间：" << endl ;
		cin >> c->limit_time ;
	}
	else if (choice == 2)
	{
		cover() ;
		DrawString("请输入限定时间：") ;
		string temp_limit ;
		Input(temp_limit) ;
		c->limit_time = transfor(temp_limit) ;
		cout << c->limit_time << endl ;
	}
	size = 0 ;	 
	int i , j ,temp ;
    lowest_price(G,c);
    i = c->city_num - 1 ;
    temp = c->city_end ;
    int count = 0 ;
    while (temp != c->city_start && i >= 0)
    {
    	if (temp == c->pass_city[i])
    	{
    		count ++ ;
    		i -- ;
    	}
    	temp = note[temp] ;
    }
    //如果Dijstra算法计算的路线满足限定时间且经过了所有必经城市 
    if (count == c->city_num && time1[c->city_end] <= c->limit_time)
    {
    	success = 1 ;
		size = num ; 
    }
    else //没有成功则进行深度优先搜索加上回溯法 
    {
    	pass_num = 0 ; 
    	dfs(c->city_start,c,G) ;
    }
    while (!success) //没有线路则重新输入限定时间 
    {
    	if (choice == 1)
    	{
    		cout << "在限定时间内无线路可满足您的要求！" << endl ;
			cout << "重新输入" ;
    	}
		else if (choice == 2)
		{
			cover() ;
			DrawString("在限定时间内无线路可满足您的要求，请重新输入限定时间") ; 
			Sleep(1500) ;
		}
		strategy_3(G,c) ; 
    }
	
	routelist p1,p2 ;
	p1 = c->R ;
	for (i = 0 ; i < size ; i ++)
	{
		p2 = new route ;
		p2->nextptr = NULL ;
		p2->from = Route[i].pre ;
		p2->to = Route[i].cur ;
		p2->start_hour = Route[i].start_hour ;
		p2->arrive_hour = Route[i].arrive_hour ;
		p2->time = Route[i].time ;
		p2->price = Route[i].price ;
		strcpy(p2->Number,Route[i].Number) ;
		p2->transportation = Route[i].tran ;
		p1->nextptr = p2 ;
		p1 = p2 ;
	} 
}
