#include<cstdio>
#include<iostream> 
#include<cstdlib>
#include "init.h"
#include "graphical.h"

int closeflag ;
ifstream in("time_table.txt") ;
graph G ;
clientlist TR, TL, C, A ;  //用户的头，尾，查询队列的尾，头。 
clock_t t1=0, t2=0, t3=0 ; //t3表示当G或者P暂停查询时所暂停的时间  t3=t3+t2-t1; 
int choice ;
HANDLE hEvent, hEvent1 ;
CRITICAL_SECTION cs ;

void xiancheng(void)//线程函数 
{		
	HANDLE hTheard1,hTheard2;
	hTheard1=CreateThread(NULL,0,h1,NULL,0,NULL);
	hTheard2=CreateThread(NULL,0,h2,NULL,0,NULL);
	hEvent=CreateEvent(NULL,TRUE,TRUE,NULL);
	while (closeflag==0) {}
}

DWORD WINAPI h2(LPVOID pPararneter)//线程2 查找线程 
{
	clock_t T1 ;
 	T1 = clock() ;//总程序开始计时 
	while (closeflag == 0)
	{			
		screenout(A,T1) ;
	}
}


DWORD WINAPI h1(LPVOID pPararneter)//线程1 选项线程-主线程 
{
	choose() ;
} 

		
void init()//总初始化
{
    Creategraph(G) ;
    TR = new Client ;
	cinit(TR) ;
	TL = TR ;
    A = new Client ;
    cinit(A) ;
	C = new Client ;
	C = A ;
	hEvent1 = CreateEvent(NULL,TRUE,TRUE,NULL) ;	
} 

void choose() //选择 
{
	char option ;
	int b = 0 ;
	clock_t T,T1,T2 ;
	T1 = clock() ; //总程序开始计时 
	while (closeflag == 0)
	{		
		cin >> option ;
		switch (option)
		{
			case 'G' ://客户到来	
				ResetEvent(hEvent);
				ResetEvent(hEvent1);
				t1=clock();
				input(TR,TL,T1) ; 
				t2=clock();
				t3=t3+t2-t1; 
				SetEvent(hEvent); 
				SetEvent(hEvent1);
				break ;
			case 'P' ://查询 
				ResetEvent(hEvent);
				ResetEvent(hEvent1);
				t1=clock();
				find(TR,C,A);
				cout << endl << endl ;
				t2=clock();
				t3=t3+t2-t1;
				SetEvent(hEvent);
				SetEvent(hEvent1);
				break ;
			case 'Q' : //关闭系统 
				cout << "退出系统！" << endl ;
				closeflag=1;
				break ;
			default :	;
				cout <<"输入错误。"<<endl;
		}
	}
}
	
int main()
{
	init();
	cout << "进入命令行界面请输入 1" << endl ;
	cout << "进入图形化界面请输入 2" << endl ;
	cin >> choice ;
	switch (choice)
	{
		case 1 :
			Fileout() ;
			xiancheng() ;
			break ;
		case 2 :
			graphical() ;
			break ;
	} 
	return 0 ;
}
