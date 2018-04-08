#ifndef QBBB
#define QBBB
#include "strategy_2.h"
void lowest_price(graph G, clientlist &c);
void dfs(int now,clientlist &c, graph G);
void strategy_3 (graph G,clientlist &c);
#endif

typedef struct line
{
	int pre ;
	int cur ;
	int price ;
	int start_hour ;
	int arrive_hour ;
	char Number[20] ;
	int time ;
	int tran ;
}; 

static int totalmin = 0 ;
static int totaltime = 0 ;
static int pass_num ;        //已经过必经城市的数量 
static int passed[12] ;      //是否已经过此必经城市 
static int pass_marked[12] ; //上次到达该城市时，已经过必经城市的数量
static int success = 0 ;
static struct line line[20], Route[20] ;
static int size = 0 ;
static int sizet = 0 ;
static int flag = 0 ;
static int d[12] ;
static int time1[12] ;
static int note[12] ;
static int num ;

