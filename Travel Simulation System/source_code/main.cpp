#include<cstdio>
#include<iostream> 
#include<cstdlib>
#include "init.h"
#include "graphical.h"

int closeflag ;
ifstream in("time_table.txt") ;
graph G ;
clientlist TR, TL, C, A ;  //�û���ͷ��β����ѯ���е�β��ͷ�� 
clock_t t1=0, t2=0, t3=0 ; //t3��ʾ��G����P��ͣ��ѯʱ����ͣ��ʱ��  t3=t3+t2-t1; 
int choice ;
HANDLE hEvent, hEvent1 ;
CRITICAL_SECTION cs ;

void xiancheng(void)//�̺߳��� 
{		
	HANDLE hTheard1,hTheard2;
	hTheard1=CreateThread(NULL,0,h1,NULL,0,NULL);
	hTheard2=CreateThread(NULL,0,h2,NULL,0,NULL);
	hEvent=CreateEvent(NULL,TRUE,TRUE,NULL);
	while (closeflag==0) {}
}

DWORD WINAPI h2(LPVOID pPararneter)//�߳�2 �����߳� 
{
	clock_t T1 ;
 	T1 = clock() ;//�ܳ���ʼ��ʱ 
	while (closeflag == 0)
	{			
		screenout(A,T1) ;
	}
}


DWORD WINAPI h1(LPVOID pPararneter)//�߳�1 ѡ���߳�-���߳� 
{
	choose() ;
} 

		
void init()//�ܳ�ʼ��
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

void choose() //ѡ�� 
{
	char option ;
	int b = 0 ;
	clock_t T,T1,T2 ;
	T1 = clock() ; //�ܳ���ʼ��ʱ 
	while (closeflag == 0)
	{		
		cin >> option ;
		switch (option)
		{
			case 'G' ://�ͻ�����	
				ResetEvent(hEvent);
				ResetEvent(hEvent1);
				t1=clock();
				input(TR,TL,T1) ; 
				t2=clock();
				t3=t3+t2-t1; 
				SetEvent(hEvent); 
				SetEvent(hEvent1);
				break ;
			case 'P' ://��ѯ 
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
			case 'Q' : //�ر�ϵͳ 
				cout << "�˳�ϵͳ��" << endl ;
				closeflag=1;
				break ;
			default :	;
				cout <<"�������"<<endl;
		}
	}
}
	
int main()
{
	init();
	cout << "���������н��������� 1" << endl ;
	cout << "����ͼ�λ����������� 2" << endl ;
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
