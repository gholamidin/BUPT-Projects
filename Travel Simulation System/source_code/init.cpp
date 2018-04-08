#include "init.h"
extern graph G ;
extern ifstream in ;
extern clientlist TR;

int LocateVex(graph G,string s) //查找城市 
{
	int i ;
	for (i = 0 ; i < G.city_num ; i ++)
	{
		if (s == G.city_name[i])
		{
			return i ;
		}
	}
	return -1 ;
}

void store(graph &G, int i, int j, int k)  //读入每条线路的信息 
{
    translist p2 ;
	string str2 ;
	getline(in,str2,'\t') ;
	if(str2.length() != 0)
	{
		p2 = (translist)malloc(sizeof(transportation)) ;
		p2->start_hour = transfor(str2) ;
    	getline(in,str2,'\t') ;
    	p2->arrive_hour = transfor(str2) ;
    	getline(in,str2,'\t') ;
    	p2->time = transfor(str2) ;
    	getline(in,str2,'\t') ;
    	p2->price = transfor(str2) ;
    	getline(in,str2,'\n') ;
    	strcpy(p2->Number,str2.c_str()) ;
    	p2->nextptr = NULL ;
    	G.cs[i][j].trans[k+3]->nextptr = p2 ;
    	G.cs[i][j].trans[k+3] = p2 ;
    	G.cs[j][i].trans[k+3]->nextptr = p2 ;
    	G.cs[j][i].trans[k+3] = p2 ;
	}
}

void Creategraph(graph &G)  //创建城市图 
{
    int i = 0, j, k ;
	G.city_num = CITY_NUM ;
	ifstream city("city.txt") ;
	string s ;
    int n = 0 ;
    G.transportation_name[0] = "汽车" ;
    G.transportation_name[1] = "飞机" ;
    G.transportation_name[2] = "火车" ;
    while (getline(city,s))
    {
    	G.city_name[n] = s ;
    	n ++ ;
    }
    city.close() ;
    for (i = 0 ; i < CITY_NUM ; i ++)
    {
    	for (j = 0 ; j < CITY_NUM ; j ++)
    	{
    		for (k = 0 ; k < 3 ; k ++)
    		{
    			G.cs[i][j].trans[k] = (translist)malloc(sizeof(transportation)) ;
                G.cs[i][j].trans[k]->nextptr = NULL ;
                if (i == j)
                {
                	G.cs[i][j].trans[k]->arrive_hour = -1 ;
                	G.cs[i][j].trans[k]->start_hour = -1 ;
                	G.cs[i][j].trans[k]->time = 0 ;
                	G.cs[i][j].trans[k]->price = 0 ;
                }
                G.cs[i][j].trans[k+3] = G.cs[i][j].trans[k] ;
    		}
    	}
    }
    if ( !in )
    {
    	cout << "error" << endl ;
    }
    string str1, str2 ;
    while ( getline(in,str1,'\t') )
    {
    	getline(in,str2,'\t') ;
    	i = LocateVex(G,str1) ;
    	j = LocateVex(G,str2) ;
    	getline(in,str1,'\t') ;
    	if (str1 == "汽车")
    	{ 
			store(G,i,j,0);	
    	}
    	else if (str1 == "飞机")
    	{
    		
			store(G,i,j,1);
    	}
    	else if (str1 == "火车")
    	{
    		store(G,i,j,2);
    	}
    }
    in.close() ;
}


