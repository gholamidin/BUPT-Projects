#include "egg.h"
#include "strategy_3.h"
#include<cstdio> 
extern graph G;
extern clientlist TR,TL,C,A;

HEGG String ;
HEGG S_city ;
HEGG TIME ;
HEGG hEggs ;
HEGG guest[10] ;
HEGG word ;

int find_flag ;
int print_num = 0 ;
int tcheck[1000] ;
void ShowTime(clock_t T) ;
int guestcome(clientlist &headp,clientlist &lastp,clock_t T5) ;
int Delete();
void Input(string &s);
void cover() ;
void choose_city(int &city,double,double) ;
void ch_pass_city(clientlist &p,double,double) ;
void choose_strategy(clientlist &p) ;
void check(clientlist clhead,clientlist &tail,clientlist &head) ;
void select(int city,double &x,double &y) ;
void pictureout(clientlist &GS,clock_t T) ;
void file(clientlist HEAD, clock_t T) ;

ofstream outfile("output.txt") ;

int graphical()
{
	double X,Y ;
	int count ;
	int all_flag = 1 ;
	clock_t Tstart,Tend,Tstop=0,T1,T2,T;
	EVENT_TYPE ev;
	EggStart(1500,750);
	hEggs = LayEgg() ;
	DrawBitmap("map.bmp") ;
	StartTimer(time_go*1000) ;
	Tstart=clock();
	while ((ev = WaitForEvent()) != EXIT && all_flag == 1)
	{
		switch (ev)
		{
			case TIMER :
				Tend=clock();
				T=Tend-Tstart-Tstop;
			    ShowTime(T);
			    word = LayEgg() ;
			    file(TR,T) ;
			    pictureout(A,T) ;
				break ;
			
			case KEYDOWN:
				
				if (GetStruckKey() == VK_LBUTTON)
				{
					X = GetMouseX();
			        Y = GetMouseY();  //获取鼠标点击的坐标 
			        cout << X << " " << Y << endl ;
			        Tend = clock();
					T=Tend-Tstart-Tstop; 
			        T1=clock();
			        if (X>=1102&&X<=1208&&Y>=714&&Y<=743)      //添加旅客 
			        {
			        	String = LayEgg() ;
						guestcome(TR,TL,T);
			        }
			        else if (X>=1285&&X<=1390&&Y>=714&&Y<=743) //查询状态
					{
						String = LayEgg() ;
						check(TR,C,A) ;
					}
					if (X>=1440&&X<=1470&&Y>=718&&Y<=745)
					{
						all_flag = 0 ;
					}
					T2=clock();
					Tstop=Tstop+T2-T1;
				}
				break ;
		}
	}
	outfile.close();
	return 0 ;
}

int countInput = 0 ;
double length = 0 ;
int Spacelength = 0 ;
char guest_input[50] ;
char SpaceforClear[50] ;

int guestcome(clientlist &headp,clientlist &lastp,clock_t T5)
{
	int flag=0;
	clientlist temp,phead,p2 ;
	p2 = new Client ;
	cinit(p2);
	clientlist p1,TR;
	routelist N,L;
	phead=headp;
	int n ;
	for(n=0;n<=49;n++)   //将输入字符数组和用于清空的字符数组初始化 
    {
    	guest_input[n]='\0';
    	SpaceforClear[n]='\0';
    }
    cover() ;
	SetPenColor(BLACK);
	DrawString("  请输入您的名字：");
	Input(p2->Name);
	cover() ;
	DrawString("  请输入您的ID号：");
	Input(p2->ID);
	cout << p2->ID << endl ;
	p2->city_num = 0 ;
	S_city = LayEgg();
	cover() ;
	DrawString("  请选择出发城市：");
	choose_city(p2->city_start,849,459) ;
	cout << p2->city_start << endl ;
	cover() ;
	DrawString("  请选择目的地城市：");
	choose_city(p2->city_end,985,459) ;
	cout << p2->city_end << endl ;
	cover() ;
	DrawString("  请选择希望途径的城市，按顺序输入：") ;
	ch_pass_city(p2,1165,459);
    for (n = 0 ; n < p2->city_num ; n++)
    {
    	cout << G.city_name[p2->pass_city[n]] << ' ' ;
    }
    cout << endl ;
	cover() ;
	DrawString("  请输入期待出发的天数：") ;
	string temp_string ;
	Input(temp_string) ;
	p2->expected_day = transfor(temp_string) ;
	cout << p2->expected_day << endl ;
	cover() ;
	DrawString("  请输入期待出发的小时数：") ;
	Input(temp_string) ;
	p2->expected_hour = transfor(temp_string) ;
	cout << p2->expected_hour << endl ;
	
	p2->buy_day = (T5/(time_go*1000))/24 ;
	p2->buy_hour = (T5/(time_go*1000))%24 ;
	
	cover() ;
	DrawString("  请选择希望选择的策略：");
	choose_strategy(p2) ;
	cout << p2->strategy << endl ;
	p2->R = new route ;
	p2->R->nextptr=NULL ;
	p2->next = NULL;
	switch(p2->strategy)
	{
		case 1:
				floyd(G,p2) ;
				break;
		case 2:
				Shortest_Time(G,p2) ;
				break;
		case 3:
				strategy_3(G,p2) ;
				break;
	}
	
	if(p2->R->nextptr->start_hour<(T5/time_go/1000)%24&&p2->expected_day==0)
	{
		p2->R->nextptr->start_day=(T5/time_go/1000/24)+1;
		N=p2->R->nextptr;
	}
	else 
	{
		if(p2->R->nextptr->start_hour>=(T5/time_go/1000)%24&&p2->R->nextptr->start_hour<p2->expected_hour&&p2->expected_day==0)
		{
			p2->R->nextptr->start_day=(T5/time_go/1000/24)+1;
			N=p2->R->nextptr;
		}
		else
		{
			p2->R->nextptr->start_day=(T5/time_go/1000/24)+p2->expected_day;
			N=p2->R->nextptr;
		}
	} 
	while(N->nextptr)
	{
		if((N->start_hour+N->time)%24>N->nextptr->start_hour)
		{
			N->nextptr->start_day=N->start_day+(N->start_hour+N->time)/24+1;
		}
		else if((N->start_hour+N->time)%24<=N->nextptr->start_hour)
		{
			N->nextptr->start_day=N->start_day+(N->start_hour+N->time)/24;
		}
		N=N->nextptr;
	}
	
	while(phead&&p2->ID!=phead->ID)
	{	
		phead=phead->next;
	}
	if(phead)
	{
		if(phead->ID==p2->ID)
		{
			if(phead->Name==p2->Name)
			{
				phead->R->nextptr=new route;
				copy1(p2,phead);
			}
			else
			{
				cout<<"已经输入过此ID，但你的名字不正确，错误输入。"<<endl;
				Sleep(2000) ;
				flag=1;
			}
		}
	}
	else
	{
		if(lastp->city_start!=13)
		{
			lastp->next=new Client;
			cinit(lastp->next);
			lastp->next->R->nextptr=new route;
			lastp=lastp->next;
			copy1(p2,lastp);
		}
		else
		{
			lastp->R->nextptr=new route;
			copy1(p2,lastp);
		} 
	}
	if(flag == 0)
	{
		cover() ;
		TR=new Client;
		TR=p2;
		L=p2->R->nextptr;
		SetActiveEgg(S_city) ;
		MovePen(796,368) ;
		char c[20] ;
		strcpy(c,TR->Name.c_str()) ;
		DrawString(c) ;
		DrawString("（ID号：") ;
		strcpy(c,TR->ID.c_str()) ;
		DrawString(c) ; 
		DrawString("）在第");
		sprintf(c,"%d",TR->buy_day) ;
		DrawString(c);
		DrawString("天");
		sprintf(c,"%d",TR->buy_hour) ;
		DrawString(c);
		DrawString("小时购票成功") ;
		MovePen(796,350) ;
		DrawString("该旅客的旅行计划是：从第") ;
		sprintf(c,"%d",L->start_day) ;
		DrawString(c);
		DrawString("天开始") ;
		int d = 0 ;
		int totalprice = 0 ;
		int totaltime = 0 ;
		while(L)
		{
			MovePen(796,330-d) ;
			switch (L->transportation)
			{
				case 0 :
					DrawBitmap("bus.bmp") ;
					break ;
				case 1 :
					DrawBitmap("plane.bmp") ;
					break ;
				case 2 :
					DrawBitmap("train.bmp") ;
					break ;
			}
			OffsetPen(5,-13) ;
			DrawString("车次：") ;
			DrawString(L->Number) ;
			DrawString(" ") ;
			strcpy(c,G.city_name[L->from].c_str()) ;
			DrawString(c) ;
			DrawString(" -> ") ;
			strcpy(c,G.city_name[L->to].c_str()) ;
			DrawString(c) ;
			DrawString(" 出发时间：") ;
			sprintf(c,"%d",L->start_hour) ;
			DrawString(c);
			DrawString(" 到达时间：") ;
			sprintf(c,"%d",L->arrive_hour) ;
			DrawString(c);
			DrawString(" 费用：") ;
			sprintf(c,"%d",L->price) ;
			DrawString(c);
			DrawString(" 时间：") ;
			sprintf(c,"%d",L->time) ;
			DrawString(c);
			totalprice += L->price ;
			totaltime += L->time ;
			d += 50 ;
			L=L->nextptr;
		}
		MovePen(1141,410) ;
		sprintf(c,"%d",totalprice) ;
		DrawString(c) ;
		MovePen(1344,410) ;
		sprintf(c,"%d",totaltime) ;
		DrawString(c) ;
		Sleep(8000) ; 
	}
	SetActiveEgg(S_city) ;
	EatEgg() ;
} 

void ShowTime(clock_t T)
{
	SetActiveEgg(TIME) ;
	EatEgg();
	TIME = LayEgg() ; 
	MovePen(923,736) ;
	char Ttime[100] ;
	DrawString("Day：");
	sprintf(Ttime,"%d",(T/(time_go*1000))/24) ;
	DrawString(Ttime);
	DrawString("  Hour：") ;
	sprintf(Ttime,"%d",(T/(time_go*1000))%24) ;
	DrawString(Ttime);
	system("cls");
	cout << "Day：" << (T/(time_go*1000))/24 << "  Hour：" << (T/(time_go*1000))%24 << endl ;
}

void cover() 
{
	SetActiveEgg(String); 
	EatEgg();
	String=LayEgg();      //下蛋 
	MovePen(802,678);
}

int Delete(void) //删除输入的最后一个字符
{
    int j;
	length=GetStringWidth(guest_input);
	OffsetPen(length-GetStringWidth(&guest_input[countInput-1]),0);
	Spacelength=(int) GetStringWidth(&guest_input[countInput-1])/GetStringWidth(" ");
    for(j=0;j<=Spacelength;j++)
	{
		SpaceforClear[j]=' ';
	}	
	if(countInput>=1)
	{
		guest_input[countInput-1]='\0';
	    countInput--;
	}
    
    DrawString(SpaceforClear);
	MovePen(797,644);
}	  

void Input(string &s)
{
	SetActiveEgg(String);
	int input_flag = 1 ;
	while(input_flag)
	{
		while(!(WaitForEvent()==KEYDOWN)) {}
		if(GetStruckKey()==VK_BACK)  //键盘输入Backspace 
		{
			Delete();                
		}
		else if (GetStruckKey() == VK_LBUTTON) //点击确认键 
		{
			double inX,inY;
			inX = GetMouseX() ;
			inY = GetMouseY() ;
			if (inX>=969&&inX<=1019&&inY>=588&&inY<=611)
			{
				input_flag = 0 ;
			}
		}
		else if(GetStruckKey()==VK_RETURN||GetStruckKey()==VK_SEPARATOR) //键盘输入回车键（包括小键盘） 
		{
	    	input_flag = 0 ;
			//Correct();             
		}
		else   //键盘输入字符 
		{ 
			MovePen(797,644);
	    	if(GetStruckKey()>=96 && GetStruckKey()<=105)  //将输入的字符存入输入字符数组 
	    	{
	        	guest_input[countInput]=GetStruckKey()-48;
	    	}
			else
			{
				guest_input[countInput]=GetStruckKey();
			}
			countInput++;
	    	length=GetStringWidth(guest_input);  
	    	if(length<213)
	    	{
				DrawString(guest_input);   //如果总共输入的字符长度不超过输入框则显示输入的字符 
	    	}
	    	MovePen(797,644);
		}
	}
	s = guest_input ;
	SetActiveEgg(String);
	MovePen(797,644);             //清空输入框 
	Spacelength=(int) 213/GetStringWidth(" ");
    for(int j=0;j<=Spacelength;j++)
    {
	    SpaceforClear[j]=' ';
    }	
    DrawString(SpaceforClear);
    for(int i=0;i<=49;i++)         //将输入字符数组和用于清空的字符数组清空 
    {
        guest_input[i]='\0';
        SpaceforClear[i]='\0';
    }
    countInput = 0 ;
} 

void choose_city(int &city,double input_x,double input_y)
{
	SetActiveEgg(S_city) ;
	char ch[10];
	int city_X,city_Y ;
    int flag = 1 ;
    while (flag)
    {
    	while(!(WaitForEvent()==KEYDOWN)) {}
		if(GetStruckKey()==VK_RETURN||GetStruckKey()==VK_SEPARATOR) //键盘输入回车键（包括小键盘） 
		{
	    	flag = 0 ;             
		}
		else if (GetStruckKey() == VK_LBUTTON)
		{
			MovePen(input_x,input_y);
			city_X = GetMouseX() ;
			city_Y = GetMouseY() ;
			if (city_X>=1063&&city_X<=1085&&city_Y>=615&&city_Y<=639) //北京
				city = 0 ;	
			else if (city_X>=1156&&city_X<=1180&&city_Y>=615&&city_Y<=639) //上海
				city = 1 ;
			else if (city_X>=1250&&city_X<=1272&&city_Y>=615&&city_Y<=639) //沈阳
				city = 2 ;
			else if (city_X>=1343&&city_X<=1365&&city_Y>=615&&city_Y<=639) //郑州
				city = 3 ; 
			else if (city_X>=1063&&city_X<=1085&&city_Y>=566&&city_Y<=591) //武汉
				city = 4 ; 
			else if (city_X>=1156&&city_X<=1180&&city_Y>=566&&city_Y<=591) //长沙
				city = 5 ;
			else if (city_X>=1250&&city_X<=1272&&city_Y>=566&&city_Y<=591) //成都	
				city = 6 ;
			else if (city_X>=1343&&city_X<=1365&&city_Y>=566&&city_Y<=591) //乌鲁木齐
				city = 7 ;
			else if (city_X>=1063&&city_X<=1085&&city_Y>=517&&city_Y<=540) //昆明
				city = 8 ;
			else if (city_X>=1156&&city_X<=1180&&city_Y>=517&&city_Y<=540) //西安
				city = 9 ;
			else if (city_X>=1250&&city_X<=1272&&city_Y>=517&&city_Y<=540) //广州
				city = 10 ;
			else if (city_X>=1343&&city_X<=1365&&city_Y>=517&&city_Y<=540) //重庆
				city = 11 ;
			else if (city_X>=969&&city_X<=1019&&city_Y>=588&&city_Y<=611) //点击确认键 
				return ;
			strcpy(ch,G.city_name[city].c_str()) ;
			DrawString(ch);
		}
    }	
}

void ch_pass_city(clientlist &p,double input_x,double input_y)
{
	SetActiveEgg(S_city) ;
	MovePen(input_x,input_y);
	char ch[20];
	int city_X,city_Y ;
    int flag = 1 ;
    int city ;
    while (flag)
    {
    	while(!(WaitForEvent()==KEYDOWN)) {}
		if(GetStruckKey()==VK_RETURN||GetStruckKey()==VK_SEPARATOR) //键盘输入回车键（包括小键盘） 
		{
	    	flag = 0 ;             
		}
		else if (GetStruckKey() == VK_LBUTTON)
		{
			city_X = GetMouseX() ;
			city_Y = GetMouseY() ;
			if (city_X>=1063&&city_X<=1085&&city_Y>=615&&city_Y<=639) //北京
				city = 0 ;	
			else if (city_X>=1156&&city_X<=1180&&city_Y>=615&&city_Y<=639) //上海
				city = 1 ;
			else if (city_X>=1250&&city_X<=1272&&city_Y>=615&&city_Y<=639) //沈阳
				city = 2 ;
			else if (city_X>=1343&&city_X<=1365&&city_Y>=615&&city_Y<=639) //郑州
				city = 3 ; 
			else if (city_X>=1063&&city_X<=1085&&city_Y>=566&&city_Y<=591) //武汉
				city = 4 ; 
			else if (city_X>=1156&&city_X<=1180&&city_Y>=566&&city_Y<=591) //长沙
				city = 5 ;
			else if (city_X>=1250&&city_X<=1272&&city_Y>=566&&city_Y<=591) //成都	
				city = 6 ;
			else if (city_X>=1343&&city_X<=1365&&city_Y>=566&&city_Y<=591) //乌鲁木齐
				city = 7 ;
			else if (city_X>=1063&&city_X<=1085&&city_Y>=517&&city_Y<=540) //昆明
				city = 8 ;
			else if (city_X>=1156&&city_X<=1180&&city_Y>=517&&city_Y<=540) //西安
				city = 9 ;
			else if (city_X>=1250&&city_X<=1272&&city_Y>=517&&city_Y<=540) //广州
				city = 10 ;
			else if (city_X>=1343&&city_X<=1365&&city_Y>=517&&city_Y<=540) //重庆
				city = 11 ;
			else if (city_X>=969&&city_X<=1019&&city_Y>=588&&city_Y<=611)
				return ;
			p->pass_city[p->city_num] = city ;
			p->city_num ++ ;	
			strcpy(ch,G.city_name[city].c_str()) ;
			DrawString(ch) ;
			DrawString("  ") ;
		}
    }	
}

void choose_strategy(clientlist &p)
{
	char ch[10];
	int str_X,str_Y ;
    int flag = 1 ;
    while (flag)
    {
    	while(!(WaitForEvent()==KEYDOWN)) {}
		if(GetStruckKey()==VK_RETURN||GetStruckKey()==VK_SEPARATOR) //键盘输入回车键（包括小键盘） 
		{
	    	flag = 0 ;             
		}
		else if (GetStruckKey() == VK_LBUTTON)
		{
			str_X = GetMouseX() ;
			str_Y = GetMouseY() ;
			SetActiveEgg(S_city) ;
			MovePen(899,412);
			if (str_X>=789&&str_X<=902&&str_Y>=539&&str_Y<=577)
			{
				p->strategy = 1 ;
				DrawString("最少费用策略") ;
			}
			else if (str_X>=912&&str_X<=1025&&str_Y>=539&&str_Y<=577)
			{
				p->strategy = 2 ;
				DrawString("最少时间策略") ;
			}
			else if (str_X>=831&&str_X<=989&&str_Y>=491&&str_Y<=528)
			{
				p->strategy = 3 ;
				DrawString("限时最少费用策略") ;
			}
			else if (str_X>=969&&str_X<=1019&&str_Y>=588&&str_Y<=611)
			{
				return ;
			}
			
		}
    }
} 

void check(clientlist clhead,clientlist &tail,clientlist &head)//查找是否在用户队列中，传入用户链表头和打印链表头和尾 
{
	find_flag = 0 ;
	int flag = 0 ;
	string id ;
	clientlist D,client_head, print_head ;
	routelist A,xx ;
	client_head = clhead ;  //client_head为用户链表头 
	print_head = head;      //print_head为打印链表头
	int n ; 
	for (n = 0 ; n <= 49 ; n ++)   //将输入字符数组和用于清空的字符数组初始化 
    {
    	guest_input[n] = '\0' ;
    	SpaceforClear[n] = '\0' ;
    }
    cover() ;
	DrawString("  请输入您的ID号：") ;
	Input(id) ;
	if(print_head)//如果打印队列是否已经有该节点 
	{
		while (print_head && print_head->ID != id)
		{
			print_head = print_head->next ;
		}	
		if (print_head && print_head->ID == id)
		{
			flag = 1;
		}
	}
	if(client_head)
	{
		if (flag == 0)   //若打印队列中没有该节点则从用户中寻找，若找到则在打印队列尾赋值。 
		{
			while (client_head && client_head->ID != id)
			{
				client_head = client_head->next ;
			}	
			if (client_head && client_head->ID == id)
			{
				cout<<"旅客 " << client_head->Name ;
				cout<<"  在第"<<client_head->buy_day<<"天"<<client_head->buy_hour<<"小时购票"<<endl;
				if(tail->city_start==13)
				{
					A=new route;
					tail->R->nextptr=A;
					copy1(client_head,tail) ;
				}
				else 
				{
					D=new Client;
					cinit(D);
					xx=new route;
					D->R->nextptr=xx;		
					tail->next=D;
					tail=tail->next;
					copy1(client_head,tail);
				}
				print_num ++ ;
				tail->next=NULL ;
				cover() ;
				DrawString("查询成功！") ;
				Sleep(2000);
			}	
			else
			{
				cover() ;
				DrawString("无此旅客的信息！") ;
				Sleep(2000);
			}
		} 
		else if (flag == 1)   //若打印队列有该节点，则将用户中的该节点覆盖到打印队列中 
		{
			while (client_head && client_head->ID != id)
			{
				client_head = client_head->next ;
			}
			if (client_head && client_head->ID == id)
			{
				cout<<"旅客 " <<client_head->Name ;
				cout<<"  在第"<<client_head->buy_day<<"天"<<client_head->buy_hour<<"小时购票"<<endl;
				copy1(client_head,print_head) ;
				cover() ;
				DrawString("查询成功！") ;
				Sleep(2000);
			}
		}
			
	}
	else 
	{
		cover() ;
		DrawString("无此旅客的信息！") ;
		Sleep(2000);
	}
	SetActiveEgg(String) ;
	EatEgg() ;
}

void select(int city,double &x,double &y)
{
	switch (city)
	{
		case 0 :
			x = 512 ;
			y = 519 ;
			break ;
		case 1 :
			x = 596 ;
			y = 390 ;
			break ;
		case 2 :
			x = 596 ;
			y = 563 ;
			break ;
		case 3 :
			x = 493 ;
			y = 430 ;
			break ;
		case 4 :
			x = 502 ;
			y = 372 ;
			break ;
		case 5 :
			x = 487 ;
			y = 336 ;
			break ;
		case 6 :
			x = 369 ;
			y = 371 ;
			break ;
		case 7 :
			x = 197 ;
			y = 587 ;
			break ;
		case 8 :
			x = 353 ;
			y = 280 ;
			break ;
		case 9 :
			x = 433 ;
			y = 422 ;
			break ;
		case 10 :
			x = 505 ;
			y = 261 ;
			break ;
		case 11 :
			x = 417 ;
			y = 367 ;
			break ;
	}
}

void pictureout(clientlist &GS,clock_t T)//屏幕输出，传入打印队列头和系统启动初始时间 
{
	int city1,trans,city2;//1出发城市，2到达城市 
	string id;
	char ch;
	int xx=0;
	routelist TX;
	clientlist TR;
	int start_day,start_hour,duetime;
	TR=new Client;
	TR=GS;//TR为打印队列头 
	int i ; 
	int g_num = 0 ;	
	for (i = 0 ; i < print_num ; i ++)
	{
		guest[i] = LayEgg() ;
	}
	
	SetActiveEgg(word) ;
	EatEgg() ;
	word = LayEgg() ;
	MovePen(796,368) ;	
	while(TR&&TR->city_start!=13&&g_num<print_num)
	{
		TX=new route;//TX为当前用户中的第一个城市节点，route节点 
		TX=TR->R;	
		TX=TX->nextptr;
		if(TX) //第一个城市 
		{
			if((TX->start_day*24+TX->start_hour)*time_go*1000>T)// 未出发，xx=0 
			{
				xx=0;
				start_hour = TX->start_hour;
				start_day = TX->start_day;
				duetime = TX->time;
			}	
			if((TX->start_day*24+TX->start_hour)*time_go*1000<=T)// 已出发，xx=1 
			{
				xx=1;
				start_hour=TX->start_hour;
				start_day=TX->start_day;
				duetime=TX->time;
				city1=TX->from;
				trans=TX->transportation;
				if((TX->start_day*24+TX->start_hour+TX->time)*time_go*1000>T&&!TX->nextptr) //已到达，下一城市为空 xx=3 
					xx=3;
				if((TX->start_day*24+TX->start_hour+TX->time)*time_go*1000<=T&&TX->nextptr)//已到达，下一城市不为空 xx=4 
				{
					xx=4;
					city2=TX->nextptr->from;
				}					
			}
			
			TX=TX->nextptr; 
		}
						
		while(TX) //遍历以后城市 
		{
			if((TX->start_day*24+TX->start_hour)*time_go*1000<=T)// 已出发，xx=1 
			{
				xx=1;
				start_hour=TX->start_hour;
				start_day=TX->start_day;
				duetime=TX->time;
				city1=TX->from;
				trans=TX->transportation;
				if((TX->start_day*24+TX->start_hour+TX->time)*time_go*1000>T&&!(TX->nextptr)) //已到达，下一城市为空 xx=3 
					xx=3;
				if((TX->start_day*24+TX->start_hour+TX->time)*time_go*1000<=T&&(TX->nextptr)) //已到达，下一城市不为空 xx=4 
				{
					xx=4;
					city2=TX->nextptr->from;
				}
			}
			if((TX->start_day*24+TX->start_hour)*time_go*1000>T&&xx==1) //上一个城市已到达该城市，但该城市还未出发。 
			{
				xx=2;
				city2=TX->from;
			}
			TX=TX->nextptr; 	
		}
		
		char ch[20] ;
		double move_x,move_y ;	
		double x1,y1,x2,y2 ;
		double proportion ;
		
		switch(xx)
		{
			case 0 :
				
				DrawString("旅客") ;
				strcpy(ch,TR->Name.c_str()) ;
				DrawString(ch) ;
				DrawString("(ID号:") ;
				strcpy(ch,TR->ID.c_str()) ;
				DrawString(ch);
				DrawString(") 在 ") ;
				strcpy(ch,G.city_name[TR->city_start].c_str()) ;
				DrawString(ch);
				DrawString(" 还未出发。") ;
				select(TR->city_start,move_x,move_y) ;
				SetActiveEgg(guest[g_num]) ;
				EatEgg() ;
				guest[g_num] = LayEgg() ;
				MovePen(move_x-10,move_y+10);
				DrawBitmap("坐标.bmp");   
				cout<<"旅客 "<<TR->Name<< "(ID号:"<< TR->ID <<") 在 "<<G.city_name[TR->city_start]<<" 还未出发。"<<endl; 
				//outfile<<" 旅客 "<<TR->Name<<" ID "<<TR->ID<<" 还未出发。"<<endl; 
				TR=TR->next;
				break;
			case 1 :
				
				if(TR->sco==0)
				{
					DrawString("旅客") ;
					strcpy(ch,TR->Name.c_str()) ;
					DrawString(ch) ;
					DrawString("(ID号:") ;
					strcpy(ch,TR->ID.c_str()) ;
					DrawString(ch);
					DrawString(") 已到达目的地") ;
					strcpy(ch,G.city_name[TR->city_end].c_str()) ;
					DrawString(ch);
					select(TR->city_end,move_x,move_y) ;
					SetActiveEgg(guest[g_num]) ;
					EatEgg() ;
					guest[g_num] = LayEgg() ;
					MovePen(move_x-10,move_y+10);
					DrawBitmap("坐标.bmp");  
					cout<<"旅客 "<<TR->Name << "(ID号:" << TR->ID <<") 已到达目的地"<<G.city_name[TR->city_end]<<endl;
					//outfile<<" 旅客 "<<TR->Name<<" ID "<<TR->ID<<TR->ID<<" 还未出发。"<<endl; 
					TR->sco=1;
				}
				TR=TR->next;
				break;
			case 2 :
				
				SetActiveEgg(word) ;
				EatEgg() ;
				word = LayEgg() ;
				MovePen(796,368) ;
				DrawString("旅客") ;
				strcpy(ch,TR->Name.c_str()) ;
				DrawString(ch) ;
				DrawString("(ID号:") ;
				strcpy(ch,TR->ID.c_str()) ;
				DrawString(ch);
				DrawString(") 正在从") ;
				strcpy(ch,G.city_name[city1].c_str()) ;
				DrawString(ch);
				DrawString("乘坐") ;
				strcpy(ch,G.transportation_name[trans].c_str()) ;
				DrawString(ch);
				DrawString("去") ;
				strcpy(ch,G.city_name[city2].c_str()) ;
				DrawString(ch);
				
				proportion = ((double)T/((double)time_go*1000) - ((double)start_day*24+(double)start_hour)) / (double)duetime ;
				cout << proportion << endl ;
				select(city1,x1,y1) ;
				select(city2,x2,y2) ;
				SetActiveEgg(guest[g_num]) ;
				EatEgg() ;
				guest[g_num] = LayEgg() ;
				MoveEgg(x1-10+(x2-x1)*proportion,y1+10+(y2-y1)*proportion) ;
				switch(trans)
				{
					case 0 :
						DrawBitmap("汽车.bmp") ;
						break ;
					case 1 :
						DrawBitmap("飞机.bmp") ;
						break ;
					case 2 :
						DrawBitmap("火车.bmp") ;
						break ;
				}
				
				cout<<"旅客 "<<TR->Name<< "(ID号:"<< TR->ID << ") 正在从"<<G.city_name[city1]; 
				cout<<"乘坐"<<G.transportation_name[trans];
				cout<<"到"<<G.city_name[city2]<<endl;
				/*outfile<<" 旅客 "<<TR->Name<<" ID "<<" 正在从"<<G.city_name[city1]; 
				outfile<<"乘坐"<<G.transportation_name[trans];
				outfilet<<"到"<<G.city_name[city2]<<endl;*/
				TR=TR->next;
				break;
			case 3 :
				
				DrawString("旅客") ;
				strcpy(ch,TR->Name.c_str()) ;
				DrawString(ch) ;
				DrawString("(ID号:") ;
				strcpy(ch,TR->ID.c_str()) ;
				DrawString(ch);
				DrawString(") 正在从") ;
				strcpy(ch,G.city_name[city1].c_str()) ;
				DrawString(ch);
				DrawString("乘坐") ;
				strcpy(ch,G.transportation_name[trans].c_str()) ;
				DrawString(ch);
				DrawString("去") ;
				strcpy(ch,G.city_name[TR->city_end].c_str()) ;
				DrawString(ch);
				
				proportion = ((double)T/((double)time_go*1000) - ((double)start_day*24+(double)start_hour)) / (double)duetime ;
				cout << proportion ;
				select(city1,x1,y1) ;
				select(TR->city_end,x2,y2) ;
				SetActiveEgg(guest[g_num]) ;
				EatEgg() ;
				guest[g_num] = LayEgg() ;
				MoveEgg(x1-10+(x2-x1)*proportion,y1+10+(y2-y1)*proportion) ;
				switch(trans)
				{
					case 0 :
						DrawBitmap("汽车.bmp") ;
						break ;
					case 1 :
						DrawBitmap("飞机.bmp") ;
						break ;
					case 2 :
						DrawBitmap("火车.bmp") ;
						break ;
				}
				
				cout<<"旅客 "<<TR->Name << "(ID号:" << TR->ID <<") 正在从"<<G.city_name[city1]; 
				cout<<"乘坐"<<G.transportation_name[trans];
				cout<<"到"<<G.city_name[TR->city_end]<<endl; 
				TR=TR->next;
				break;
			case 4 :
				
				if(TR->scp[city2]==0)
				{
					DrawString("旅客") ;
					strcpy(ch,TR->Name.c_str()) ;
					DrawString(ch) ;
					DrawString("(ID号:") ;
					strcpy(ch,TR->ID.c_str()) ;
					DrawString(ch);
					DrawString(") 已经到达") ;
					strcpy(ch,G.city_name[city2].c_str()) ;
					DrawString(ch);
					DrawString("，正在原地等待下一趟") ;
					select(city2,move_x,move_y) ;
					SetActiveEgg(guest[g_num]) ;
					EatEgg() ;
					guest[g_num] = LayEgg() ;
					MovePen(move_x-10,move_y+10);
					DrawBitmap("坐标.bmp");  
					
					cout<<"旅客 "<<TR->Name << "(ID号:" << TR->ID <<") 已经到达"<<G.city_name[city2]<<",正在原地等待下一趟"<<endl; 
					TR->scp[city2]=0;
				}
				TR=TR->next;
				break;
			default:
				break;
			
		}
		g_num ++ ;
		SetActiveEgg(word) ;
		MovePen(796,368-g_num*20) ;
	}
	Sleep(1000) ;
	SetActiveEgg(word) ;
	EatEgg() ;
	for (i = 0 ; i < print_num ; i ++)
	{
		SetActiveEgg(guest[i]) ;
		EatEgg() ;
	}
}

void file(clientlist HEAD, clock_t T)
{
	int city1,city2,trans,xx ;
	clientlist p;
	routelist TX;
	p=new Client;
	TX=new route;
	p=HEAD;
	if(tcheck[T/1000/time_go]==0)
	{
		tcheck[T/1000/time_go]=1;
		outfile << "当前时间为：第"<<T/1000/time_go/24<<"天,第"<<(T/1000/time_go)%24<<"小时。"<<endl;
		while (p&&p->city_start!=13)
		{
			TX=new route;//TX为当前用户中的第一个城市节点，route节点 
			TX=p->R;	
			TX=TX->nextptr;								
							
			if(TX) //第一个城市 
			{
				if((TX->start_day*24+TX->start_hour)*time_go*1000>T)// 未出发，xx=0 
				{
					xx=0;
				}	
				if((TX->start_day*24+TX->start_hour)*time_go*1000<=T)// 已出发，xx=1 
				{
					xx=1;
					city1=TX->from;
					trans=TX->transportation;
					if((TX->start_day*24+TX->start_hour+TX->time)*time_go*1000>T&&!TX->nextptr) //已到达，下一城市为空 xx=3 
						xx=3;
					if((TX->start_day*24+TX->start_hour+TX->time)*time_go*1000<=T&&TX->nextptr)//已到达，下一城市不为空 xx=4 
					{
						xx=4;
						city2=TX->nextptr->from;
					}						
				}
				TX=TX->nextptr; 
			}
								
			while(TX) //遍历以后城市 
			{
				if((TX->start_day*24+TX->start_hour)*time_go*1000<=T)// 已出发，xx=1 
				{
					xx=1;
					city1=TX->from;
					trans=TX->transportation;
					if((TX->start_day*24+TX->start_hour+TX->time)*time_go*1000>T&&!(TX->nextptr)) //已到达，下一城市为空 xx=3 
						xx=3;
					if((TX->start_day*24+TX->start_hour+TX->time)*time_go*1000<=T&&(TX->nextptr)) //已到达，下一城市不为空 xx=4 
					{
						xx=4;
						city2=TX->nextptr->from;
					}
				}
				if((TX->start_day*24+TX->start_hour)*time_go*1000>T&&xx==1) //上一个城市已到达该城市，但该城市还未出发。 
				{
					xx=2;
					city2=TX->from;
				}
				TX=TX->nextptr; 	
			}
			switch(xx)
			{
				case 0:
					outfile<<"旅客 "<<p->Name<<" ID "<<p->ID<<" 还未出发。"<<endl; 
					p=p->next;
					break;
				case 1:
					if (p->sco==0)
					{
						outfile<<"旅客 "<<p->Name<<" ID "<<p->ID<<" 已到达目的地 "<<G.city_name[p->city_end]<<endl; 
						p->sco=1;
					}
					p=p->next;
					break;
				case 2:
					outfile<<"旅客 "<<p->Name<<" ID "<<p->ID<<" 正在从"<<G.city_name[city1]; 
					outfile<<"乘坐"<<G.transportation_name[trans];
					outfile<<"到"<<G.city_name[city2]<<endl;
					p=p->next;
					break;
				case 3:
					outfile<<"旅客 "<<p->Name<<" ID "<<p->ID<<" 正在从"<<G.city_name[city1]; 
					outfile<<"乘坐"<<G.transportation_name[trans];
					outfile<<"到"<<G.city_name[p->city_end]<<endl; 
					p=p->next;
					break;
				case 4:
					if(p->scp[city2]==0)
					{
						outfile<<"旅客 "<<p->Name<<" ID "<<p->ID<<" 已经到达"<<G.city_name[city2]<<",正在原地等待下一趟"<<endl; 
						TR->scp[city2]=0;
					}
					p=p->next;
					break;
				default:
					break;
			}
		}
		outfile << endl ;
	}
}
