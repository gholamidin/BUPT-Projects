#include"mylib.h"
#include<math.h>


 
void print_message(FILE *fPtr)
{
	LISTNODEPTR currentp=NULL,currentpVIP=NULL;
	char ch;
	int i;
	fprintf(fPtr,"T=%3d\n",Time);
	for(i=1;i<=8;i=i+1)
	{
		fprintf(fPtr,"WIN%d:State=",i);
		switch(windows[i].State)
		{
			case CLOSE:
				fprintf(fPtr,"      CLOSE,ServNo=");
				break;
			case IDLE:
				fprintf(fPtr,"       IDLE,ServNo=");
				break;
			case WAITING:
				fprintf(fPtr,"    WAITING,ServNo=");
				break;
			case PROCESSING:
				fprintf(fPtr," PROCESSING,ServNo=");
				break;
			case ENDING:
				fprintf(fPtr,"     ENDING,ServNo=");
				break;
			case BREAK:
				fprintf(fPtr,"      BREAK,ServNo=");
				break;
		}
		if(windows[i].Value==2)
		    fprintf(fPtr,"V%3d",windows[i].ServNo);
		else
		    fprintf(fPtr," %3d",windows[i].ServNo);
		fprintf(fPtr,",ServLen=%3d/%3d,",windows[i].ServTime,windows[i].PServTime);
		fprintf(fPtr,"RestLen=%3d/%3d\n",windows[i].BreakTime,windows[i].PBreakTime);
	}
	fprintf(fPtr,"NormList=");
	currentp=headp;
	while(currentp!=NULL)
	{
		fprintf(fPtr,"%3d",currentp->Num);
		currentp=currentp->nextPtr;
		if(currentp!=NULL)
		fprintf(fPtr,"->");
	}
	fprintf(fPtr,"\nVIPList=");
	currentpVIP=headpVIP;
	while(currentpVIP!=NULL)
	{
		fprintf(fPtr,"%3d",currentpVIP->Num);
		currentpVIP=currentpVIP->nextPtr;
		if(currentpVIP!=NULL)
		fprintf(fPtr,"->");
	}
	fprintf(fPtr,"\n");
}
//过一段时间打印一次窗口信息 

void print_satisfy()
{
	FILE *fptr=NULL;
	int i,j=0,total_good=0,total_normal=0,total_bad=0,total_CustNormCount=0,total_CustVIPCount=0;
	int NotSWin[8];
	int average=0;
	float judge_good,judge_bad;
	if((fptr=fopen("print_satisfy.txt","w"))==NULL)
	    printf("File could not be opened\n");
	else
	{
		for(i=1;i<=6;i++)
	    {
	    	if(windows[i].CustNormCount>0)
	    	    average=windows[i].ServTotalTime/windows[i].CustNormCount;
	    	total_good=total_good+windows[i].SatisfyGood;
		    total_normal=total_normal+windows[i].SatisfyNorm;
    		total_bad=total_bad+windows[i].SatisfyBad;
    		total_CustNormCount=total_CustNormCount+windows[i].CustNormCount;
    		judge_good=(float)windows[i].SatisfyGood/windows[i].CustNormCount;
    		judge_bad=(float)windows[i].SatisfyBad/windows[i].CustNormCount;
    		if((fabs(judge_good)<0.7||fabs(judge_bad)>0.1)&&windows[i].CustNormCount>0)
    		{
    		    j++;
				NotSWin[j]=i;
    		}
    		fprintf(fptr,"WIN%d:CustCount=%3d  ServLen=%5d PerServLen=%2d ",i,windows[i].CustNormCount,windows[i].ServTotalTime,average);
    		fprintf(fptr,"CustSatisfyGood=%3d CustSatisfyNormal=%3d CustSatisfyBad=%3d \n",windows[i].SatisfyGood,windows[i].SatisfyNorm,windows[i].SatisfyBad);
    		average=0;
    	}
    	for(i=7;i<=Size;i++)
    	{
    		if((windows[i].CustNormCount+windows[i].CustVIPCount)>0)
    	        average=windows[i].ServTotalTime/(windows[i].CustNormCount+windows[i].CustVIPCount);
	    	total_good=total_good+windows[i].SatisfyGood;
    		total_normal=total_normal+windows[i].SatisfyNorm;
    		total_bad=total_bad+windows[i].SatisfyBad;
    		total_CustNormCount=total_CustNormCount+windows[i].CustNormCount;
    		total_CustVIPCount=total_CustVIPCount+windows[i].CustVIPCount;
    		judge_good=(float)windows[i].SatisfyGood/(windows[i].CustNormCount+windows[i].CustVIPCount);
    		judge_bad=(float)windows[i].SatisfyBad/(windows[i].CustNormCount+windows[i].CustVIPCount);
    		if((fabs(judge_good)<0.7||fabs(judge_bad)>0.1)&&(windows[i].CustNormCount+windows[i].CustVIPCount)>0)
			{
    		    j++;
				NotSWin[j]=i;
    		}
    		fprintf(fptr,"WIN%d:CustCount=%3d  ServLen=%5d PerServLen=%2d ",i,windows[i].CustNormCount+windows[i].CustVIPCount,windows[i].ServTotalTime,average);
    		fprintf(fptr,"CustSatisfyGood=%3d CustSatisfyNormal=%3d CustSatisfyBad=%3d \n",windows[i].SatisfyGood,windows[i].SatisfyNorm,windows[i].SatisfyBad);
    		average=0;
    	}
    	fprintf(fptr,"TotalCustNormCount=%3d\n",total_CustNormCount);
    	fprintf(fptr,"TotalCustVIPCount=%3d\n",total_CustVIPCount);
    	fprintf(fptr,"SatisfyNotGoodWin=");
    	if(j>0)
    	{
    		for(i=1;i<j;i++)
    	    {
    	    	fprintf(fptr,"Win%d, ",NotSWin[i]);
        	}
        	fprintf(fptr,"Win%d\n",NotSWin[j]);
    	}
    	
    }
    fclose(fptr);
}
    



void print_screen()
{
	LISTNODEPTR currentp=NULL,currentpVIP=NULL;
	char ch;
	int i;
	system("cls");
    printf("*******************************************************************************\n" 
 		   "                         欢迎来到北京锤雷银行                                  \n"
 	       "                                                    编写人员：黄锐 周尧棋 朱魁 \n"
 		   "*******************************************************************************\n");
	printf("T=%3d\n",Time);
	for(i=1;i<=8;i=i+1)
	{
		printf("WIN%d:State=",i);
		switch(windows[i].State)
		{
			case CLOSE:
				printf("      CLOSE,ServNo=");
				break;
			case IDLE:
				printf("       IDLE,ServNo=");
				break;
			case WAITING:
				printf("    WAITING,ServNo=");
				break;
			case PROCESSING:
				printf(" PROCESSING,ServNo=");
				break;
			case ENDING:
				printf("     ENDING,ServNo=");
				break;
			case BREAK:
				printf("      BREAK,ServNo=");
				break;
		}
		if(windows[i].Value==2)
		    printf("V%3d",windows[i].ServNo);
		else 
		    printf(" %3d",windows[i].ServNo);
		printf(",ServLen=%3d/%3d,",windows[i].ServTime,windows[i].PServTime);
	    printf("RestLen=%3d/%3d\n",windows[i].BreakTime,windows[i].PBreakTime);
	}
	printf("NormList:");
	currentp=headp;
	while(currentp!=NULL)
	{
		if(currentp->Num==headp->Num)
		{
			printf("%d",currentp->Num);
		    if(currentp->nextPtr!=NULL)
		        printf("~");
		}
		else if(currentp->nextPtr==NULL)
		    printf("%d",currentp->Num);
		currentp=currentp->nextPtr;
	}
	printf("\n");
	printf("VIPList=");
	currentpVIP=headpVIP;
	while(currentpVIP!=NULL)
	{
		if(currentpVIP->Num==headpVIP->Num)
		{
			printf("%d",currentpVIP->Num);
		    if(currentpVIP->nextPtr!=NULL)
		        printf("~");
		}
		else if(currentpVIP->nextPtr==NULL)
		    printf("%d",currentpVIP->Num);
		currentpVIP=currentpVIP->nextPtr;
	}
	printf("\n");
}

