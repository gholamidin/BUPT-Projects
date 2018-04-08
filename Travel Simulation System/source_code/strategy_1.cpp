#include<cstdio>
#include<cstdlib> 
#include<fstream>
#include<sstream>
#include<cstring>

#include "strategy_1.h"
#define INFINITY 100000

using namespace std;

//给用户链表节点赋值 
void assignment(routelist &p1, routelist &p2, int start, int arrive, struct temp D[][12])
{
	p2->from = start ;
	p2->to = arrive ;
	p2->price = 0 ;
	p2->start_hour = D[start][arrive].start_hour ;
	p2->arrive_hour =  D[start][arrive].arrive_hour ;
	p2->transportation = D[start][arrive].tran ;
	strcpy(p2->Number,D[start][arrive].Number) ;
	p2->time = D[start][arrive].time ;
	p2->price = p2->price + D[start][arrive].price ;
	p2->nextptr = NULL ;
	p1->nextptr = p2 ;
	p1 = p2 ;
}

void floyd( graph G , clientlist &p)
{
	int i,j,k,v,u,w ;
	struct temp cost[12][12] ; 
	int path[12][12] ;
	translist tou ; 
	for (v = 0 ; v < G.city_num ; v ++)
	{
		//给矩阵赋值 
		for (w = 0 ; w < G.city_num ; w ++)
		{
			if (v == w)
			{
				cost[v][w].price= 0 ;
				cost[v][w].tran = -1 ;
			} 
			else
			{
				cost[v][w].price = INFINITY ;
				for (k = 0 ; k < 3 ; k ++)
				{
					tou = G.cs[v][w].trans[k]->nextptr ;
					while (tou)
					{
						if (tou->price < cost[v][w].price)
						{
							cost[v][w].price = tou->price ;
							cost[v][w].start_hour = tou->start_hour ;
							cost[v][w].arrive_hour = tou->arrive_hour ;
							strcpy(cost[v][w].Number,tou->Number) ;
							cost[v][w].time = tou->time ; 
							cost[v][w].tran = k ;
						}
						tou = tou->nextptr ;
					}
				}
			}
			path[v][w] = -1 ;	
		}
	}
	//三层循环 
	for (k = 0 ; k < G.city_num ; k ++)
	{
		for (i = 0 ; i < G.city_num ; i ++)
		{
			for (j = 0 ; j < G.city_num ; j ++)
			{
				if (cost[i][j].price > cost[i][k].price + cost[k][j].price)
				{
					cost[i][j].price = cost[i][k].price + cost[k][j].price ;
					path[i][j] = k ;
				}
			}
		}
	}
	
	//有沿途城市的操作 
	routelist p1,p2 ;
	p1 = p->R ;
	int m = p->city_start ;
	for (i = 0 ; i < p->city_num ; i ++)
	{
		int w = p->pass_city[i] ;
		while (path[m][w] != -1)
		{
			int temp = path[m][w] ;
			p2 = new route ;
			assignment(p1,p2,m,temp,cost) ;
			m = temp ;
		}
		p2 = new route ;
		assignment(p1,p2,m,w,cost) ;
		m = w ;
	}
	p2 = new route ;
	assignment(p1,p2,m,p->city_end,cost) ;	
}

