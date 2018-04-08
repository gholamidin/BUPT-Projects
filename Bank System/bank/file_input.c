#include"mylib.h"

static LISTNODEPTR lastp,lastpVIP,newp,newpVIP;
static RESTLISTNODEPTR lastrp,newrp;


void input(FILE *fPtr)
{
	char ch,id[20],cid[20]; 
	int flag=1,flag1=1;
	int i=0,n=0,j,num;//id用于判断输入的VIP的id是否正确，num用于读取请求休息的窗口号码 
	struct vipdata indata[50],cvip;
    RESTLISTNODEPTR crp;
    FILE * fvip;
    fvip=fopen("vip.dat","rb+");
    fread(&cvip,sizeof(struct vipdata),1,fvip);
	while(!feof(fvip))
	{
		indata[n]=cvip;
		fread(&cvip,sizeof(struct vipdata),1,fvip);
		n++;
	}//将文件中已有的信息储存到结构体数组中
	fclose(fvip);
	if((ch=fgetc(fPtr))!=EOF)
	{
        fscanf(fPtr,"=%d,EVENT=",&T);
        ch=fgetc(fPtr);
        while(ch!='\n'&&flag==1)
        {
        	switch(ch)
        	{
        		case 'G':
        			SerId++;
    	    		newp=(LISTNODEPTR)malloc(sizeof(LISTNODE));
	                if(newp!=NULL)
	                {
		                newp->Num=SerId;
		                newp->nextPtr=NULL;
	     	            if(instantheadp==NULL)
	            	    {
	              	        instantheadp=newp;
	            	        lastp=newp;
    	        	    }
    	        	    else
	            	    {
	            		    lastp->nextPtr=newp;
	              		    lastp=newp;
	            	    }//创立节点并接上之前的链表节点
         	        }
         	        printf("T=%d,来了一个普通用户，他的服务号码为%d。\n",T,SerId);
             	    ch=fgetc(fPtr);
             	    break;
             	case 'V':
                    j=0;
                    i=0;
                    ch=fgetc(fPtr);
                    ch=fgetc(fPtr);
                    fscanf(fPtr,"%c",&id[j]);
                    while(id[j]!='|'&&id[j]!='\n')
                    {
                        cid[j]=id[j];
                        j++;
                        fscanf(fPtr,"%c",&id[j]);
                    }
                    if(id[j]=='|')
            		    ch='|';
        		    if(id[j]=='\n')
        		        ch='\n';
            		cid[j]='\0';
             		while(i<=n&&strcmp(cid,indata[i].VIPID)!=0)
             		    i++;
             		if(strcmp(cid,indata[i].VIPID)==0)
             		{
             			SerVIPId++;
    	    		    newpVIP=(LISTNODEPTR)malloc(sizeof(LISTNODE));
	                    if(newpVIP!=NULL)
	                    {
		                    newpVIP->Num=SerVIPId;
		                    newpVIP->nextPtr=NULL;
	     	                if(instantheadpVIP==NULL)
	            	        {
	              	            instantheadpVIP=newpVIP;
	            	            lastpVIP=newpVIP;
    	        	        }
    	        	        else
	            	        {
	            		        lastpVIP->nextPtr=newpVIP;
	             		        lastpVIP=newpVIP;
	            	        }//创立节点并接上之前的链表节点
         	            }
         	            printf("T=%d,来了一个VIP用户，他的服务号码为%d。\n",T,SerVIPId);
             		}//如果VIP信息正确，将其添加到VIP客户等待队列中 
             		else
             		{
             			SerId++;
         			    newp=(LISTNODEPTR)malloc(sizeof(LISTNODE));
	                    if(newp!=NULL)
	                    {
		                    newp->Num=SerId;
    		                newp->nextPtr=NULL;
 	         	            if(instantheadp==NULL)
    	        	        {
    	          	            instantheadp=newp;
    	        	            lastp=newp;
        	    	        }
        	    	        else
	            	        {
	            		        lastp->nextPtr=newp;
	              		        lastp=newp;
	            	        }//创立节点并接上之前的链表节点
             	        }
             	        printf("T=%d,来了一个普通用户，他的服务号码为%d。\n",T,SerId);
             		}//如果VIP信息不正确，将其添加到普通客户等待队列中 
             	    break;
             	case '|':
             		ch=fgetc(fPtr);
    			    break;
    			case 'R':
	    		    fscanf(fPtr,"%d",&num);
	    		    crp=instantheadpWinRest;
	    		    while(crp!=NULL&&flag1==1)
	    		    {
	    		    	if(crp->WinNo==num)
	    		    	    flag1=0;
	    		    	crp=crp->nextPtr;
	    		    }
	    		    if(flag1==1)
	    		    {
	    		    	newrp=(RESTLISTNODEPTR)malloc(sizeof(RESTLISTNODE));
    				    if(newrp!=NULL)
    				    {
    					    newrp->WinNo=num;
    				    	newrp->nextPtr=NULL;
    			    		if(instantheadpWinRest==NULL)
    			    		{
    		    				instantheadpWinRest=newrp;
    	    					lastrp=newrp;
    	    				}
    		    			else
    	    				{
    		    				lastrp->nextPtr=newrp;
    		    				lastrp=newrp;
    	    				}
    	    			}
    		    		printf("T=%d,窗口%d发出休息请求。\n",T,num);
	    		    }
    				flag1=1;
    				ch=fgetc(fPtr);
    				break;
    			case 'Q':
    				printf("T=%d,收到下班请求，正在准备下班。\n",T);
    				instantquit=0;
    				flag=0;
    				break;
        	}
        }
    }
    
}

void AddServList()
{
	int NUM;
	headp=instantheadp;
	headpVIP=instantheadpVIP;
	headpWinRest=instantheadpWinRest;
	isquit=instantquit;
	RESTLISTNODEPTR wcp;
	winrestsort();
	wcp=headpWinRest;
	while(wcp!=NULL)
	{
		NUM=wcp->WinNo;
		windows[NUM].Value_Break=1;
		wcp=wcp->nextPtr;
	}
}//将读取的事件添加到服务链表中 

