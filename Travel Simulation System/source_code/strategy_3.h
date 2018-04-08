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
static int pass_num ;        //�Ѿ����ؾ����е����� 
static int passed[12] ;      //�Ƿ��Ѿ����˱ؾ����� 
static int pass_marked[12] ; //�ϴε���ó���ʱ���Ѿ����ؾ����е�����
static int success = 0 ;
static struct line line[20], Route[20] ;
static int size = 0 ;
static int sizet = 0 ;
static int flag = 0 ;
static int d[12] ;
static int time1[12] ;
static int note[12] ;
static int num ;

