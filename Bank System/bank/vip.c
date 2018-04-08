#include"mylib.h"

void VIPdata()
{
	int judge;
    system("cls"); 
    printf( "*******************************************************************************\n" 
 		    "                         欢迎来到北京锤雷银行                                  \n"
 		    "                                                    编写人员：黄锐 周尧棋 朱魁 \n"
 		    "*******************************************************************************\n");
    printf("下面进入VIP信息维护状态：\n");
    printf("1 - 增加一个VIP客户.\n"); 
	printf("2 - 删除一个VIP客户.\n");
	printf("3 - 更新一个VIP客户的信息.\n");
	printf("4 - 查看已有的VIP信息.\n");
	printf("5 - 退出.\n");
	scanf("%d",&judge);
	while(judge!=5)
	{
		if(judge!=1&&judge!=2&&judge!=3&&judge!=4)
		{
			printf("亲，您的输入有误，请根据提示信息重新输入\n"); 
		}
		switch(judge)
		{
		    case 1:
			    AddVIP();
			    break;
		   	case 2:
			    DeleteVip();
		    	break;
		   	case 3:
		    	UpdataVIP();
		    	break;
	    	case 4:
			    system("cls");
                ReadVIP();
                break;
	    }
	    printf("1 - 增加一个VIP客户.\n"); 
		printf("2 - 删除一个VIP客户.\n");
		printf("3 - 更新一个VIP客户的信息.\n");
	    printf("4 - 查看已有的VIP信息.\n");
	    printf("5 - 退出.\n");
	    scanf("%d",&judge);
	} 
}
//以上为VIP信息更新 

int AddVIP()
{
	FILE * fPtr;
    int flag=1,i=0,n=0;
    struct vipdata svip={"","",0},vip[99];
    struct vipdata cvip={"","",0};
    printf("请输入VIP的ID号（5位）:\n");
    scanf("%s",svip.VIPID);
    fPtr=fopen("vip.dat","rb+");
    fread(&cvip,sizeof(struct vipdata),1,fPtr);
	while(!feof(fPtr))
	{
		vip[n]=cvip;
		fread(&cvip,sizeof(struct vipdata),1,fPtr);
		n++;
	}//将文件中已有的信息储存到结构体数组中
	while(i<=n) 
    {
        if(strcmp(vip[i].VIPID,svip.VIPID)==0)
        {
            flag=0;
            break;
        } 
        i++;   
    }
    system("cls");
    printf( "*******************************************************************************\n" 
 		    "                         欢迎来到北京锤雷银行                                  \n"
 		    "                                                    编写人员：黄锐 周尧棋 朱魁 \n"
 		    "*******************************************************************************\n");
    if(flag==0)
    {
        printf("您输入的VIP号已存在\n");
    }
    else if(flag==1)
    {
        printf("请输入您要添加的VIP的名字、余额:\n");
        scanf("%s%f",svip.name,&svip.balance);
        fwrite(&svip,sizeof(struct vipdata),1,fPtr);//将信息储存到数组并输入到文件中
    } 
    fclose(fPtr);
	return 0; 
}
//增加VIP信息 


int DeleteVip()
{
	struct vipdata vip[50],cvip={"","",0};
	char delid[50];
	int i=0,n=0,flag=1;
	FILE * fPtr;
	fPtr=fopen("vip.dat","rb+");
	fread(&cvip,sizeof(struct vipdata),1,fPtr);
	while(!feof(fPtr))
	{
		vip[n]=cvip;
		fread(&cvip,sizeof(struct vipdata),1,fPtr);
		n++;
	}//将文件中已有的信息储存到结构体数组中
	printf("请输入你想要删除的VIP的ID号码:\n");
	scanf("%s",delid);//输入要删除信息的VIP的id 
	system("cls");
    printf("*******************************************************************************\n" 
 		   "                         欢迎来到北京锤雷银行                                  \n"
 	       "                                                    编写人员：黄锐 周尧棋 朱魁 \n"
 		   "*******************************************************************************\n");
	while(i<=n)
	{
		if(strcmp(delid,vip[i].VIPID)==0)
		{
			flag=0;
			break;
		}
		    
		i++;//查找待删除的VIP的id 
	}
	if(flag==1)
	{
		printf("您输入的VIP号不存在\n");
		fclose(fPtr);
	}
	else
	{
		if(strcmp(delid,vip[i].VIPID)==0)
	        while(i<n-1)
	        {
	        	vip[i]=vip[i+1];
	        	i++;
	        } //将该VIP的信息删除
		fPtr=fopen("vip.dat","wb+");//定位文件指针 
	    for(i=0;i<n-1;i++)
		    fwrite(&vip[i],sizeof(struct vipdata),1,fPtr);//将更改后的信息重新输入到文件中 
	    fclose(fPtr);
	}
    return 0;
}
//删除VIP信息 

int UpdataVIP()
{
	char delid[20];
	struct vipdata vip[50],cvip;
	int i=0,n=0,value,flag=1;
	FILE * fPtr;
	fPtr=fopen("vip.dat","rb+");
	fread(&cvip,sizeof(struct vipdata),1,fPtr);
	while(!feof(fPtr))
	{
		vip[n]=cvip;
		fread(&cvip,sizeof(struct vipdata),1,fPtr);
		n++;
	}//将文件中已有的信息储存到结构体数组中
	printf("请输入你想要更新信息的VIP客户的ID号:\n");
	scanf("%s",delid);//读取需要修改信息的VIP的id 
	while(i<n)
	{
		if(strcmp(delid,vip[i].VIPID)==0)
		{
			flag=0;
			break;
		}
		i++;//查找待修改信息的学生的id 
	}
    if(flag==1)
    {
    	system("cls");
        printf( "*******************************************************************************\n" 
 		        "                         欢迎来到北京锤雷银行                                  \n"
 		        "                                                    编写人员：黄锐 周尧棋 朱魁 \n"
 		        "*******************************************************************************\n");
    	printf("您输入的VIP号不存在\n");
    }
    else
	if(strcmp(delid,vip[i].VIPID)==0)
	{
		fflush(stdin);
		printf("修改名字请输入 1 \n");
		printf("修改余额请输入 2 \n");
		scanf("%d",&value);
		while(value!=1&&value!=2)
		{
			printf("亲,您的输入有误,请根据提示信息重新输入\n");
			printf("修改名字请输入 1 \n");
		    printf("修改余额请输入 2 \n");
		    scanf("%d",&value);
		}
		switch(value)
		{
			case 1:
				printf("请输入您的名字:\n");
				scanf("%s",&vip[i].name);
				break;
			case 2: 
				printf("请输入您的余额:\n");
				scanf("%f",&vip[i].balance);
				break;
		}
		system("cls");
        printf("*******************************************************************************\n" 
 		       "                         欢迎来到北京锤雷银行                                  \n"
 		       "                                                    编写人员：黄锐 周尧棋 朱魁 \n"
 		       "*******************************************************************************\n");
	}//更改该VIP信息 
	fclose(fPtr);
    fPtr=fopen("vip.dat","wb+");
	//定位文件指针 
	for(i=0;i<n;i++)
		fwrite(&vip[i],sizeof(struct vipdata),1,fPtr);//将更改后的信息重新输入到文件中 
	fclose(fPtr);
	return 0;
}

int ReadVIP()
{
    struct vipdata vip[50],cvip={"","",0};
    int i=1,n=1;
    FILE * fPtr;
	fPtr=fopen("vip.dat","rb+");
    printf("%-10s%-16s%-26s%-11s\n","Number","VIPID","name","balance");
	fread(&cvip,sizeof(struct vipdata),1,fPtr);
	while(!feof(fPtr))
	{
		vip[n]=cvip;
		fread(&cvip,sizeof(struct vipdata),1,fPtr);
		n++;
	}//将文件中已有的信息储存到结构体数组中	
	for(i=1;i<n;i++)
	{
		printf("%-10d%-16s%-26s%-11f\n",i,vip[i].VIPID,vip[i].name,vip[i].balance);
	}
    printf("*******************************************************************************\n" 
 		   "                         欢迎来到北京锤雷银行                                  \n"
 	       "                                                    编写人员：黄锐 周尧棋 朱魁 \n"
 		   "*******************************************************************************\n");
   	fclose(fPtr);
}
