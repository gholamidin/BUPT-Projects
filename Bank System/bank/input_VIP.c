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
	PlaySound(TEXT("������������ID�˺�.wav"),NULL,SND_FILENAME|SND_ASYNC);
	
	for(i=0;i<=199;i++)   //�������ַ������������յ��ַ������ʼ�� 
    {
    	VIPinput[i]='\0';
    	SpaceforClear[i]='\0';
    }
	SetActiveEgg(String); 
	EatEgg();
	String=LayEgg();      //�µ� 
	MovePen(0,140);       //��ʾ������ʾ 
    SetPenColor(BLACK);
	DrawString("     ����������VIP���룺     ");
	MovePen(0,120);
	DrawString("    ��ʣ�����:      ");
	sprintf(c,"%d",time);
	DrawString(c);
	DrawString("�Σ�");
	input_flag=1;
	while(input_flag==1)
    {
	    while(!(WaitForEvent()==KEYDOWN)) {}
	    if(GetStruckKey()==VK_BACK)  //��������Backspace 
	    {
			Delete();                
	    }
	    else if(GetStruckKey()==VK_RETURN||GetStruckKey()==VK_SEPARATOR) //��������س���������С���̣� 
	    {
	    	Correct();             
	    }
	    else if(GetStruckKey()==VK_LBUTTON)  //��ȡ����������� 
	    {
	        a=GetMouseX();
	        b=GetMouseY();
	        if( a>=26 && a<=86 && b>=0 && b<=60 ) //��������ϵ�ȷ���� 
	        {
	            Correct();
            }
            else if(a>=105 && a<=165 && b>=0 && b<=60) //��������ϵ�ɾ���� 
    	    {
    	        Delete();
    	    }
        }
        else   //���������ַ� 
	    {
				MovePen(45,92);
	            if(GetStruckKey()>=96 && GetStruckKey()<=105)  //��������ַ����������ַ����� 
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
				    DrawString(VIPinput);   //����ܹ�������ַ����Ȳ��������������ʾ������ַ� 
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
}	 //ɾ����������һ���ַ�  

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
}	 //��VIP�û��ƶ������ŵ�������  
	   
int Correct() //�ж��Ƿ�ΪVIP�ͻ� 
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
    } //���ļ������е���Ϣ���浽�ṹ��������
    fclose(fvip);
   
         i=0;
		 while(i<n-1&&strcmp(VIPinput,indata[i].VIPID)!=0)
         {
             i++;
         }
         if(strcmp(VIPinput,indata[i].VIPID)==0)   //ͨ����֤����Ӷ��� 
	     {
									
			SerVIPId=SerVIPId+1;
			printf("����VIP�û������ĺ���ΪV%d\n",SerVIPId);
			MovePen(0,140);
			DrawString("       ����VIP�û�,���ã�               ");
			MovePen(0,120);
			DrawString("       ���ĺ���Ϊ:");
			sprintf(c,"V%d",SerVIPId);
			DrawString(c);
			DrawString("��               "); 
			MoveVIP(SerVIPId);
			SetActiveEgg(String);
			MovePen(45,92);             //�������� 
			Spacelength=(int) 112/GetStringWidth(" ");
            for(j=0;j<=Spacelength;j++)
            {
	            SpaceforClear[j]=' ';
            }	
            DrawString(SpaceforClear);
            for(i=0;i<=199;i++)         //�������ַ������������յ��ַ�������� 
            {
                VIPinput[i]='\0';
                SpaceforClear[i]='\0';
            }
            countInput=0;
			currentpVIP=(LISTNODEPTR)malloc(sizeof(LISTNODE));  //��VIP�û����뵽������ 
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
			if(time>1)      //������֮��������� 
		    {
					time--;
				    MovePen(0,140);
		            DrawString("�������VIP������,����������:");
	                MovePen(0,120);
			        DrawString("(ʣ�������");
			        sprintf(c,"%d",time);
			        DrawString(c);
			        DrawString("��)            "); 
			                        	
			        MovePen(45,92);    //�������� 
			        Spacelength=(int) 112/GetStringWidth(" ");
                    for(j=0;j<=Spacelength;j++)      //�������ַ������������յ��ַ�������� 
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
		   else   //�������ֱ�ӱ�Ϊ��ͨ�û� 
		   {
			    	MovePen(0,140);
     	            SetPenColor(BLACK);
				    DrawString("    ���ź����Ѿ��������             ");
				    MovePen(0,120);
				    DrawString("    ���ڸ���������ͨ��");
				    MovePen(45,92);     //�������� 
			        Spacelength=(int) 112/GetStringWidth(" ");
                    for(j=0;j<=Spacelength;j++)
                    {
	                    SpaceforClear[j]=' ';
                    }	
                    DrawString(SpaceforClear);
                    Sleep(500); 
				    buttonG();
				    for(i=0;i<=199;i++)   //�������ַ������������յ��ַ��������
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
	   
            
            
