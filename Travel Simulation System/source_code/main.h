#ifndef DSAD
#define DSAD

#include<iostream> 
#include<fstream>
#include<sstream>
#include<cstring>
#include<time.h>
#include<windows.h> 
#define time_go 3 //时间轴一小时等于几秒 
#define CITY_NUM 12  //城市总数 
#define INFINITY 100000 
using namespace std;

void choose();
void init();
void xiancheng();
DWORD WINAPI h1(LPVOID pPararneter);
DWORD WINAPI h2(LPVOID pPararneter);
extern int choice ;

#endif

typedef struct transportation
{
	int start_hour ;       //每种路线的出发时间
    int arrive_hour ;      //每种路线的到达时间
    char Number[20] ;       //交通工具的编号 
    int price ;           //价格
    int time ;            //历经时间
    struct transportation *nextptr ;
} transportation,*translist;     //每种交通工具的路线链表

struct chengshi
{
	translist trans[6];  //三种交通工具的链表 
};

typedef struct 
{
    int city_num;                 //城市数量
	struct chengshi cs[12][12] ;  //城市邻接矩阵
	string city_name[12] ;        //城市名数组
	string transportation_name[3]; //交通工具名数组
} graph;     //城市路线信息图

typedef struct route
{
	int from ;            //出发城市
    int to ;              //到达城市 
    int transportation ;   //使用交通工具
	int start_day ;       //出发天数
    int start_hour ;      //出发小时数 
    int arrive_hour ;     //到达小时数 
    char Number[20] ;          //交通工具的编号 
    int time ;           //经历时间
   	int price ;           //票价
	struct route *nextptr ;
} route, *routelist;      //策略路线存储结构

typedef struct Client
{
	string Name ;   //用户的姓名
    string ID ;      //用户的ID号
    int city_start ;    //输入出发城市代号0-11
    int city_end ;     //输入目的城市代号0-11
    int pass_city[12] ;  //输入希望途径的城市
	int city_num ;       //经过城市总数 
    int expected_day ;     //输入希望第几天出发
    int expected_hour ;    //输入希望第几小时出发，
	int strategy ;       //用户希望的策略 
	int buy_day ;      //订票时第几天
    int buy_hour ;     //订票时的小时数 
    int limit_time ;    //策略3限定的时间 
   	int sco;          //打印的flag 
   	int scp[12];
	routelist R ;     //用户路线链表头结点 
    struct Client *next ;
} Client, *clientlist; 

    
struct temp
{
	int tran ;         //交通工具 
	int start_hour ;    //每种路线的出发时间
    int arrive_hour ;      //每种路线的到达时间
    char Number[20] ;           //交通工具的编号 
    int time  ;            //总时间 
    int price ;           //价格
};
