#include"mylib.h"
#include"Graphical.h"
#include<windows.h>

int countInput;
double length;
int Spacelength;
char VIPinput[200];
char SpaceforClear[200];
int time;
int flag;
int input_flag;
double a,b;
struct vipdata indata[50],cvip;
FILE * fvip;
char c[2];

LISTNODEPTR lastpVIP;

void input_VIP()
{
	int i;
	time=3;
	PlaySound(TEXT("亲请输入您的ID账号.wav"),NULL,SND_FILENAME|SND_ASYNC);
	
	for(i=0;i<=199;i++)   //将输入字符数组和用于清空的字符数组初始化 
    {
    	VIPinput[i]='\0';
    	SpaceforClear[i]='\0';
    }
	SetActiveEgg(String); 
	EatEgg();
	String=LayEgg();      //下蛋 
	MovePen(0,140);       //显示输入提示 
    SetPenColor(BLACK);
	DrawString("     请输入您的VIP号码：     ");
	MovePen(0,120);
	DrawString("    （剩余次数:      ");
	sprintf(c,"%d",time);
	DrawString(c);
	DrawString("次）");
	input_flag=1;
	while(input_flag==1)
    {
	    while(!(WaitForEvent()==KEYDOWN)) {}
	    if(GetStruckKey()==VK_BACK)  //键盘输入Backspace 
	    {
			Delete();                
	    }
	    else if(GetStruckKey()==VK_RETURN||GetStruckKey()==VK_SEPARATOR) //键盘输入回车键（包括小键盘） 
	    {
	    	Correct();             
	    }
	    else if(GetStruckKey()==VK_LBUTTON)  //获取鼠标点击的坐标 
	    {
	        a=GetMouseX();
	        b=GetMouseY();
	        if( a>=26 && a<=86 && b>=0 && b<=60 ) //点击界面上的确定键 
	        {
	            Correct();
            }
            else if(a>=105 && a<=165 && b>=0 && b<=60) //点击界面上的删除键 
    	    {
    	        Delete();
    	    }
        }
        else   //键盘输入字符 
	    {
				MovePen(45,92);
	            if(GetStruckKey()>=96 && GetStruckKey()<=105)  //将输入的字符存入输入字符数组 
	            {
	            	VIPinput[countInput]=GetStruckKey()-48;
	            }
				else
				{
					VIPinput[countInput]=GetStruckKey();
				}
				countInput++;
	            length=GetStringWidth(VIPinput);  
	            if(length<112)
	            {
				    DrawString(VIPinput);   //如果总共输入的字符长度不超过输入框则显示输入的字符 
	            }
	            MovePen(45,92);
	    }
   }  
            
}
            
int Delete(void)
{
    int j;
	length=GetStringWidth(VIPinput);
	OffsetPen(length-GetStringWidth(&VIPinput[countInput-1]),0);
	Spacelength=(int) GetStringWidth(&VIPinput[countInput-1])/GetStringWidth(" ");
    for(j=0;j<=Spacelength;j++)
	{
		SpaceforClear[j]=' ';
	}	
	if(countInput>=1)
	{
		VIPinput[countInput-1]='\0';
	    countInput--;
	}
    
    DrawString(SpaceforClear);
	MovePen(45,92);
}	 //删除输入的最后一个字符  

int MoveVIP(int SerVIPId)
{
	 int i;
	 int flag1=0;
	 eggVip[SerVIPId]=LayEgg();
	 for(i=0;i<=13&&flag1==0;i++)
    	{
		    if(chair[i].Judge==0)
	    	{
			    if(i<=6)
		    	{
			    	SetActiveEgg(eggVip[SerVIPId]);
			    	MoveEgg(222+85*i,180);
			    	DrawBitmap("VIP.bmp");
			    	chair[i].Judge=1;
			    	chair[i].Value=1;
			    	chair[i].Num=SerVIPId;
		    	}
		    	else
		    	{
		     		SetActiveEgg(eggVip[SerVIPId]);
		    		MoveEgg(222+85*(i-7),90);
		    		DrawBitmap("VIP.bmp");
		    		chair[i].Judge=1;
		    		chair[i].Value=1;
		    		chair[i].Num=SerVIPId;
		    	}
		    	flag1=1;
			
	    	}
    	}
}	 //将VIP用户移动到空着的椅子上  
	   
int Correct() //判断是否为VIP客户 
{
	int i,j,n=0;
	LISTNODEPTR currentpVIP;
	fvip=fopen("vip.dat","rb+");
	fread(&cvip,sizeof(struct vipdata),1,fvip);
  	while(!feof(fvip))
    {
	  	indata[n]=cvip;
    	fread(&cvip,sizeof(struct vipdata),1,fvip);
    	n++;
    } //将文件中已有的信息储存到结构体数组中
    fclose(fvip);
   
         i=0;
		 while(i<n-1&&strcmp(VIPinput,indata[i].VIPID)!=0)
         {
             i++;
         }
         if(strcmp(VIPinput,indata[i].VIPID)==0)   //通过验证则添加队列 
	     {
									
			SerVIPId=SerVIPId+1;
			printf("尊贵的VIP用户，您的号码为V%d\n",SerVIPId);
			MovePen(0,140);
			DrawString("       尊贵的VIP用户,您好！               ");
			MovePen(0,120);
			DrawString("       您的号码为:");
			sprintf(c,"V%d",SerVIPId);
			DrawString(c);
			DrawString("号               "); 
			MoveVIP(SerVIPId);
			SetActiveEgg(String);
			MovePen(45,92);             //清空输入框 
			Spacelength=(int) 112/GetStringWidth(" ");
            for(j=0;j<=Spacelength;j++)
            {
	            SpaceforClear[j]=' ';
            }	
            DrawString(SpaceforClear);
            for(i=0;i<=199;i++)         //将输入字符数组和用于清空的字符数组清空 
            {
                VIPinput[i]='\0';
                SpaceforClear[i]='\0';
            }
            countInput=0;
			currentpVIP=(LISTNODEPTR)malloc(sizeof(LISTNODE));  //将VIP用户加入到链表中 
			if(currentpVIP!=NULL)
			{
			    currentpVIP->Num=SerVIPId;
			    if(headpVIP==NULL)
			    {
					headpVIP=currentpVIP;
			    	lastpVIP=currentpVIP;
			    }
				else
				{
			    	lastpVIP->nextPtr=currentpVIP;
		    		lastpVIP=currentpVIP;	
			    }
			}
	        lastpVIP->nextPtr=NULL;
			time=3;
			input_flag=0;
	     
	     }            
	    else 
	    {
			if(time>1)      //在三次之内输入错误 
		    {
					time--;
				    MovePen(0,140);
		            DrawString("您输入的VIP号有误,请重新输入:");
	                MovePen(0,120);
			        DrawString("(剩余次数；");
			        sprintf(c,"%d",time);
			        DrawString(c);
			        DrawString("次)            "); 
			                        	
			        MovePen(45,92);    //清空输入框 
			        Spacelength=(int) 112/GetStringWidth(" ");
                    for(j=0;j<=Spacelength;j++)      //将输入字符数组和用于清空的字符数组清空 
                    {
	                    SpaceforClear[j]=' ';
                    }	
                    DrawString(SpaceforClear);
                    for(i=0;i<=199;i++)
                    {
                        VIPinput[i]='\0';
                        SpaceforClear[i]='\0';
                    }
                    countInput=0;
                   
		   }
		   else   //输错三次直接变为普通用户 
		   {
			    	MovePen(0,140);
     	            SetPenColor(BLACK);
				    DrawString("    很遗憾你已经输错三次             ");
				    MovePen(0,120);
				    DrawString("    现在给您安排普通号");
				    MovePen(45,92);     //清空输入框 
			        Spacelength=(int) 112/GetStringWidth(" ");
                    for(j=0;j<=Spacelength;j++)
                    {
	                    SpaceforClear[j]=' ';
                    }	
                    DrawString(SpaceforClear);
                    Sleep(500); 
				    buttonG();
				    for(i=0;i<=199;i++)   //将输入字符数组和用于清空的字符数组清空
                    {
                        VIPinput[i]='\0';
                        SpaceforClear[i]='\0';
                    }
                    countInput=0;
			    	time=3;
			    	input_flag=0;
		   }
       }
}	   
	   
            
            
