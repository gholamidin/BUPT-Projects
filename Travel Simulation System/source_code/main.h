#ifndef DSAD
#define DSAD

#include<iostream> 
#include<fstream>
#include<sstream>
#include<cstring>
#include<time.h>
#include<windows.h> 
#define time_go 3 //ʱ����һСʱ���ڼ��� 
#define CITY_NUM 12  //�������� 
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
	int start_hour ;       //ÿ��·�ߵĳ���ʱ��
    int arrive_hour ;      //ÿ��·�ߵĵ���ʱ��
    char Number[20] ;       //��ͨ���ߵı�� 
    int price ;           //�۸�
    int time ;            //����ʱ��
    struct transportation *nextptr ;
} transportation,*translist;     //ÿ�ֽ�ͨ���ߵ�·������

struct chengshi
{
	translist trans[6];  //���ֽ�ͨ���ߵ����� 
};

typedef struct 
{
    int city_num;                 //��������
	struct chengshi cs[12][12] ;  //�����ڽӾ���
	string city_name[12] ;        //����������
	string transportation_name[3]; //��ͨ����������
} graph;     //����·����Ϣͼ

typedef struct route
{
	int from ;            //��������
    int to ;              //������� 
    int transportation ;   //ʹ�ý�ͨ����
	int start_day ;       //��������
    int start_hour ;      //����Сʱ�� 
    int arrive_hour ;     //����Сʱ�� 
    char Number[20] ;          //��ͨ���ߵı�� 
    int time ;           //����ʱ��
   	int price ;           //Ʊ��
	struct route *nextptr ;
} route, *routelist;      //����·�ߴ洢�ṹ

typedef struct Client
{
	string Name ;   //�û�������
    string ID ;      //�û���ID��
    int city_start ;    //����������д���0-11
    int city_end ;     //����Ŀ�ĳ��д���0-11
    int pass_city[12] ;  //����ϣ��;���ĳ���
	int city_num ;       //������������ 
    int expected_day ;     //����ϣ���ڼ������
    int expected_hour ;    //����ϣ���ڼ�Сʱ������
	int strategy ;       //�û�ϣ���Ĳ��� 
	int buy_day ;      //��Ʊʱ�ڼ���
    int buy_hour ;     //��Ʊʱ��Сʱ�� 
    int limit_time ;    //����3�޶���ʱ�� 
   	int sco;          //��ӡ��flag 
   	int scp[12];
	routelist R ;     //�û�·������ͷ��� 
    struct Client *next ;
} Client, *clientlist; 

    
struct temp
{
	int tran ;         //��ͨ���� 
	int start_hour ;    //ÿ��·�ߵĳ���ʱ��
    int arrive_hour ;      //ÿ��·�ߵĵ���ʱ��
    char Number[20] ;           //��ͨ���ߵı�� 
    int time  ;            //��ʱ�� 
    int price ;           //�۸�
};
