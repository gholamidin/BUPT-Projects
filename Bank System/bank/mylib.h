#include"egg.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

    
#define Size 8     //总窗口数（包括普通和VIP窗口） 
#define Good 2 //好评 
#define Normal 1 //普通评价 
#define Bad 0 //差评 

	

enum STATE{CLOSE,IDLE,WAITING,PROCESSING,ENDING,BREAK};
enum EVENTTYPE{G,V,R1,R2,R3,R4,R5,R6,R7,R8,Q};

struct WINDOW 
{
    int State ;  //窗口的状态
    int WaitTime ;  //等待客户到来时间
    int ServNo ;    //正在服务的客户的号码
    int ServTime ;  //某客户已经办理业务时间
	int PServTime ; //客户办理业务的模拟服务时间 
	int judge_Serv; //判断客户是否刚到来(0:没到或刚到;1:不是刚到)
    int BreakTime ; //已暂停服务时间 
    int PBreakTime ; //暂停服务模拟时间 
    int judge_Break; //判断该窗口是否刚开始暂停服务(0:没开始或刚开始;1:不是刚开始)
    int BreakTotalTime ; //暂停服务总时间
    int ServTotalTime ;  //该窗口服务总时间
    int CustVIPCount ;     //该窗口服务的VIP总客户数
    int CustNormCount ;     //该窗口服务的普通总客户数
    int SatisfyGood ;     //该窗口被评价为Good的次数
    int SatisfyNorm ;     //该窗口被评价为Normal的次数
    int SatisfyBad ;      //该窗口被评价为Bad的次数
    int VIP_idleTime;    //VIP窗口连续空闲时间 
    int Value;          //用于判断该窗口服务的是普通客户还是VIP客户 
    int Value_Break;//用于判断该窗口是否有休息请求 0无请求,1有请求但未安排休息,2已安排休息 
};

struct listNode
{
    int Num ;    //客户的号码
    struct listNode * nextPtr ;
};//客户到来队列请求队列链表节结点

struct winToRest
{
    int WinNo ;    //窗口号
    struct winToRest * nextPtr ;
};//窗口休息请求队列结点

struct vipdata
{
	char VIPID[20];//VIP的ID号 
    char name[30];//姓名
	float balance;//余额
};

struct CHAIR
{
	int Judge;//判断是否有顾客在座位上 
	int Num;//坐在座位上的用户的号码 
	int Value;//判断座位上的是VIP用户还是普通用户 
}; 

typedef struct listNode LISTNODE;
typedef struct listNode * LISTNODEPTR;
typedef struct winToRest RESTLISTNODE;
typedef struct winToRest * RESTLISTNODEPTR;

extern int SerId;// 普通客户的号码 
extern int SerVIPId;// VIP用户的号码 
extern int T; //发生某个事件的时间
extern int Time;// 系统时间
extern int Strategy_Judge;// 用于判断策略 （1为先来先服务，2为VIP顺便服务） 
extern int isquit;  // 用于判断是否下班 
extern LISTNODEPTR headp,headpVIP;
extern RESTLISTNODEPTR headpWinRest;
extern LISTNODEPTR instantheadp,instantheadpVIP;//用于暂时储存队列 
extern RESTLISTNODEPTR instantheadpWinRest;//暂时储存队列 
extern int instantquit;//暂时储存 
extern struct WINDOW windows[9];
    
extern int WaitingSec; //预计等待客户到达窗口的时间
extern int MaxSeqLen; //普通用户单条队列最大允许等待长度
extern int VIPMaxSeqLen; //VIP用户单条队列最大允许等待长度
extern int MinSec; //最小服务时长
extern int MaxSec; //最大服务时长
extern int MinRestSec; //窗口最小休息时间
extern int MaxRestSec; //窗口最大休息时间
extern int VIPSERVLen; //VIP窗口动态关闭时间
extern int dropquit; //下班时间 

extern HEGG noregg[100],String,eggVip[100];
extern struct CHAIR chair[14];  //判断座位的状态 
