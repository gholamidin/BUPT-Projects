#include"mylib.h"

void VIPdata()
{
	int judge;
    system("cls"); 
    printf( "*******************************************************************************\n" 
 		    "                         ��ӭ����������������                                  \n"
 		    "                                                    ��д��Ա������ ��Ң�� ��� \n"
 		    "*******************************************************************************\n");
    printf("�������VIP��Ϣά��״̬��\n");
    printf("1 - ����һ��VIP�ͻ�.\n"); 
	printf("2 - ɾ��һ��VIP�ͻ�.\n");
	printf("3 - ����һ��VIP�ͻ�����Ϣ.\n");
	printf("4 - �鿴���е�VIP��Ϣ.\n");
	printf("5 - �˳�.\n");
	scanf("%d",&judge);
	while(judge!=5)
	{
		if(judge!=1&&judge!=2&&judge!=3&&judge!=4)
		{
			printf("�ף��������������������ʾ��Ϣ��������\n"); 
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
	    printf("1 - ����һ��VIP�ͻ�.\n"); 
		printf("2 - ɾ��һ��VIP�ͻ�.\n");
		printf("3 - ����һ��VIP�ͻ�����Ϣ.\n");
	    printf("4 - �鿴���е�VIP��Ϣ.\n");
	    printf("5 - �˳�.\n");
	    scanf("%d",&judge);
	} 
}
//����ΪVIP��Ϣ���� 

int AddVIP()
{
	FILE * fPtr;
    int flag=1,i=0,n=0;
    struct vipdata svip={"","",0},vip[99];
    struct vipdata cvip={"","",0};
    printf("������VIP��ID�ţ�5λ��:\n");
    scanf("%s",svip.VIPID);
    fPtr=fopen("vip.dat","rb+");
    fread(&cvip,sizeof(struct vipdata),1,fPtr);
	while(!feof(fPtr))
	{
		vip[n]=cvip;
		fread(&cvip,sizeof(struct vipdata),1,fPtr);
		n++;
	}//���ļ������е���Ϣ���浽�ṹ��������
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
 		    "                         ��ӭ����������������                                  \n"
 		    "                                                    ��д��Ա������ ��Ң�� ��� \n"
 		    "*******************************************************************************\n");
    if(flag==0)
    {
        printf("�������VIP���Ѵ���\n");
    }
    else if(flag==1)
    {
        printf("��������Ҫ��ӵ�VIP�����֡����:\n");
        scanf("%s%f",svip.name,&svip.balance);
        fwrite(&svip,sizeof(struct vipdata),1,fPtr);//����Ϣ���浽���鲢���뵽�ļ���
    } 
    fclose(fPtr);
	return 0; 
}
//����VIP��Ϣ 


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
	}//���ļ������е���Ϣ���浽�ṹ��������
	printf("����������Ҫɾ����VIP��ID����:\n");
	scanf("%s",delid);//����Ҫɾ����Ϣ��VIP��id 
	system("cls");
    printf("*******************************************************************************\n" 
 		   "                         ��ӭ����������������                                  \n"
 	       "                                                    ��д��Ա������ ��Ң�� ��� \n"
 		   "*******************************************************************************\n");
	while(i<=n)
	{
		if(strcmp(delid,vip[i].VIPID)==0)
		{
			flag=0;
			break;
		}
		    
		i++;//���Ҵ�ɾ����VIP��id 
	}
	if(flag==1)
	{
		printf("�������VIP�Ų�����\n");
		fclose(fPtr);
	}
	else
	{
		if(strcmp(delid,vip[i].VIPID)==0)
	        while(i<n-1)
	        {
	        	vip[i]=vip[i+1];
	        	i++;
	        } //����VIP����Ϣɾ��
		fPtr=fopen("vip.dat","wb+");//��λ�ļ�ָ�� 
	    for(i=0;i<n-1;i++)
		    fwrite(&vip[i],sizeof(struct vipdata),1,fPtr);//�����ĺ����Ϣ�������뵽�ļ��� 
	    fclose(fPtr);
	}
    return 0;
}
//ɾ��VIP��Ϣ 

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
	}//���ļ������е���Ϣ���浽�ṹ��������
	printf("����������Ҫ������Ϣ��VIP�ͻ���ID��:\n");
	scanf("%s",delid);//��ȡ��Ҫ�޸���Ϣ��VIP��id 
	while(i<n)
	{
		if(strcmp(delid,vip[i].VIPID)==0)
		{
			flag=0;
			break;
		}
		i++;//���Ҵ��޸���Ϣ��ѧ����id 
	}
    if(flag==1)
    {
    	system("cls");
        printf( "*******************************************************************************\n" 
 		        "                         ��ӭ����������������                                  \n"
 		        "                                                    ��д��Ա������ ��Ң�� ��� \n"
 		        "*******************************************************************************\n");
    	printf("�������VIP�Ų�����\n");
    }
    else
	if(strcmp(delid,vip[i].VIPID)==0)
	{
		fflush(stdin);
		printf("�޸����������� 1 \n");
		printf("�޸���������� 2 \n");
		scanf("%d",&value);
		while(value!=1&&value!=2)
		{
			printf("��,������������,�������ʾ��Ϣ��������\n");
			printf("�޸����������� 1 \n");
		    printf("�޸���������� 2 \n");
		    scanf("%d",&value);
		}
		switch(value)
		{
			case 1:
				printf("��������������:\n");
				scanf("%s",&vip[i].name);
				break;
			case 2: 
				printf("�������������:\n");
				scanf("%f",&vip[i].balance);
				break;
		}
		system("cls");
        printf("*******************************************************************************\n" 
 		       "                         ��ӭ����������������                                  \n"
 		       "                                                    ��д��Ա������ ��Ң�� ��� \n"
 		       "*******************************************************************************\n");
	}//���ĸ�VIP��Ϣ 
	fclose(fPtr);
    fPtr=fopen("vip.dat","wb+");
	//��λ�ļ�ָ�� 
	for(i=0;i<n;i++)
		fwrite(&vip[i],sizeof(struct vipdata),1,fPtr);//�����ĺ����Ϣ�������뵽�ļ��� 
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
	}//���ļ������е���Ϣ���浽�ṹ��������	
	for(i=1;i<n;i++)
	{
		printf("%-10d%-16s%-26s%-11f\n",i,vip[i].VIPID,vip[i].name,vip[i].balance);
	}
    printf("*******************************************************************************\n" 
 		   "                         ��ӭ����������������                                  \n"
 	       "                                                    ��д��Ա������ ��Ң�� ��� \n"
 		   "*******************************************************************************\n");
   	fclose(fPtr);
}
