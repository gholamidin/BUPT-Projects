#include"egg.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

    
#define Size 8     //�ܴ�������������ͨ��VIP���ڣ� 
#define Good 2 //���� 
#define Normal 1 //��ͨ���� 
#define Bad 0 //���� 

	

enum STATE{CLOSE,IDLE,WAITING,PROCESSING,ENDING,BREAK};
enum EVENTTYPE{G,V,R1,R2,R3,R4,R5,R6,R7,R8,Q};

struct WINDOW 
{
    int State ;  //���ڵ�״̬
    int WaitTime ;  //�ȴ��ͻ�����ʱ��
    int ServNo ;    //���ڷ���Ŀͻ��ĺ���
    int ServTime ;  //ĳ�ͻ��Ѿ�����ҵ��ʱ��
	int PServTime ; //�ͻ�����ҵ���ģ�����ʱ�� 
	int judge_Serv; //�жϿͻ��Ƿ�յ���(0:û����յ�;1:���Ǹյ�)
    int BreakTime ; //����ͣ����ʱ�� 
    int PBreakTime ; //��ͣ����ģ��ʱ�� 
    int judge_Break; //�жϸô����Ƿ�տ�ʼ��ͣ����(0:û��ʼ��տ�ʼ;1:���Ǹտ�ʼ)
    int BreakTotalTime ; //��ͣ������ʱ��
    int ServTotalTime ;  //�ô��ڷ�����ʱ��
    int CustVIPCount ;     //�ô��ڷ����VIP�ܿͻ���
    int CustNormCount ;     //�ô��ڷ������ͨ�ܿͻ���
    int SatisfyGood ;     //�ô��ڱ�����ΪGood�Ĵ���
    int SatisfyNorm ;     //�ô��ڱ�����ΪNormal�Ĵ���
    int SatisfyBad ;      //�ô��ڱ�����ΪBad�Ĵ���
    int VIP_idleTime;    //VIP������������ʱ�� 
    int Value;          //�����жϸô��ڷ��������ͨ�ͻ�����VIP�ͻ� 
    int Value_Break;//�����жϸô����Ƿ�����Ϣ���� 0������,1������δ������Ϣ,2�Ѱ�����Ϣ 
};

struct listNode
{
    int Num ;    //�ͻ��ĺ���
    struct listNode * nextPtr ;
};//�ͻ��������������������ڽ��

struct winToRest
{
    int WinNo ;    //���ں�
    struct winToRest * nextPtr ;
};//������Ϣ������н��

struct vipdata
{
	char VIPID[20];//VIP��ID�� 
    char name[30];//����
	float balance;//���
};

struct CHAIR
{
	int Judge;//�ж��Ƿ��й˿�����λ�� 
	int Num;//������λ�ϵ��û��ĺ��� 
	int Value;//�ж���λ�ϵ���VIP�û�������ͨ�û� 
}; 

typedef struct listNode LISTNODE;
typedef struct listNode * LISTNODEPTR;
typedef struct winToRest RESTLISTNODE;
typedef struct winToRest * RESTLISTNODEPTR;

extern int SerId;// ��ͨ�ͻ��ĺ��� 
extern int SerVIPId;// VIP�û��ĺ��� 
extern int T; //����ĳ���¼���ʱ��
extern int Time;// ϵͳʱ��
extern int Strategy_Judge;// �����жϲ��� ��1Ϊ�����ȷ���2ΪVIP˳����� 
extern int isquit;  // �����ж��Ƿ��°� 
extern LISTNODEPTR headp,headpVIP;
extern RESTLISTNODEPTR headpWinRest;
extern LISTNODEPTR instantheadp,instantheadpVIP;//������ʱ������� 
extern RESTLISTNODEPTR instantheadpWinRest;//��ʱ������� 
extern int instantquit;//��ʱ���� 
extern struct WINDOW windows[9];
    
extern int WaitingSec; //Ԥ�Ƶȴ��ͻ����ﴰ�ڵ�ʱ��
extern int MaxSeqLen; //��ͨ�û����������������ȴ�����
extern int VIPMaxSeqLen; //VIP�û����������������ȴ�����
extern int MinSec; //��С����ʱ��
extern int MaxSec; //������ʱ��
extern int MinRestSec; //������С��Ϣʱ��
extern int MaxRestSec; //���������Ϣʱ��
extern int VIPSERVLen; //VIP���ڶ�̬�ر�ʱ��
extern int dropquit; //�°�ʱ�� 

extern HEGG noregg[100],String,eggVip[100];
extern struct CHAIR chair[14];  //�ж���λ��״̬ 
