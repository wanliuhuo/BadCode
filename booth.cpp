#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//��ע�⣬�����Ǵ�Ӣ�����룬���������ĵ�','

int main()
{
    int i,j,k;
    int cha;
    int jw=0;//��λ��Ƿ���
    int cd;//�ַ�������
    int biaoji;
    char bcs[21],cs[21],jg[41];//��ֵΪ0
    memset(bcs,0,sizeof(bcs));
    memset(cs,0,sizeof(cs));
    memset(jg,0,sizeof(jg));
    char *bufen,ji[41];
    memset(ji,0,sizeof(ji));
    char tmp[200];
    scanf("%s",&tmp);
    int pos;
    for(int i=0;i<strlen(tmp);i++){
        if(tmp[i]==','){pos=i;break;}
        bcs[i]=tmp[i];
    }
    int tt=0;
    for(int i=pos+1;i<strlen(tmp);i++){
        cs[tt]=tmp[i];
        tt++;
    }
    for(i=0;i<strlen(bcs);i++)
    {
        jg[i]=bcs[i];
    }
    //��С����ȫ���������  ������λ����λ
    if(bcs[0]=='+')bcs[2]='0';//��bcs�е�ԭ��䲹�� jg��¼-x�Ĳ���
    if(bcs[0]=='-')//�������
    {
        bcs[1]=bcs[2]='1';//����λΪ11
        for(i=strlen(bcs)-1;i>2;i--)//��β����ʼ
        {
            if(bcs[i]=='1')
            {
                for(i=i-1;i>2;i--)
                {
                    if(bcs[i]=='0')
                        bcs[i]='1';//ȡ��
                    else
                        bcs[i]='0';
                }
                break;
            }

        }
    }
    if(jg[0]=='-')
        jg[2]='0';//-x�Ĳ���
    if(jg[0]=='+')
    {
        jg[1]=jg[2]='1';
        for(i=strlen(jg)-1;i>2;i--)
        {
            if(jg[i]=='1')
            {
                for(i=i-1;i>2;i--)//ȡ������
                {
                    if(jg[i]=='0')
                        jg[i]='1';
                    else
                        jg[i]='0';
                }
                break;
            }
        }
    }
    cs[strlen(cs)]='0';//��b�е�ԭ��䲹�� β����0 ��Ϊy(n+1)
    if(cs[0]=='+')//��ֵ������ֵ���ֲ���
        cs[2]='0';
    if(cs[0]=='-')//��ֵ����
    {
        cs[1]=cs[2]='1';//����λ��Ϊ1 1
        for(i=strlen(cs)-1;i>2;i--)
        {
            if(cs[i]=='1')
            {
                for(i=i-1;i>2;i--)//ȡ������
                {
                    if(cs[i]=='0')
                        cs[i]='1';
                    else
                        cs[i]='0';
                }
                break;
            }
        }
    }
    bufen=(char*)malloc(strlen(bcs));//�����¿ռ�
    for(i=0;i<strlen(bcs);i++)//��ֵ0
        bufen[i]='0';
    for(i=strlen(cs)-1;i>2;i--)
    {
        cha=cs[strlen(cs)-1]-cs[strlen(cs)-2];// y(n+1)-y(n)
        if(cha==1)//���ֻ���[x]����  ����һλ
        {
            for(j=strlen(bcs)-1;j>0;j--)
            {
                if(bcs[j]-'0'+bufen[j]-'0'+jw==3)//1+1 ��λΪ1
                {
                    bufen[j]='1';
                    jw=1;
                }
                else if(bcs[j]-'0'+bufen[j]-'0'+jw==2)//1+0��λΪ1 ���� 0+1��λΪ1 ���� 1+1 ��λΪ0
                {
                    bufen[j]='0';
                    jw=1;
                }
                else if(bcs[j]-'0'+bufen[j]-'0'+jw==1)//0+0��λΪ1 ���� 1+0��λΪ0 ���� 0+1��λΪ0
                {
                    bufen[j]='1';
                    jw=0;
                }
                else//����λ
                {
                    bufen[j]='0';
                    jw=0;
                }
            }
            jw=0;//���ý�λ���
        }
        else if(cha==-1)//���ֻ���[-x]���� ����һλ
        {
            for(j=strlen(jg)-1;j>0;j--)
            {
                if(jg[j]-'0'+bufen[j]-'0'+jw==3)
                {
                    bufen[j]='1';
                    jw=1;
                }
                else if(jg[j]-'0'+bufen[j]-'0'+jw==2)
                {
                    bufen[j]='0';
                    jw=1;
                }
                else if(jg[j]-'0'+bufen[j]-'0'+jw==1)
                {
                    bufen[j]='1';
                    jw=0;
                }
                else //����λ
                {
                    bufen[j]='0';
                    jw=0;
                }
            }
            jw=0;//���ý�λ��Ƿ���
        }
        //��λ
        if(i==3)break;
        for(k=strlen(cs)-1;k>2;k--)
                cs[k]=cs[k-1];
        cs[2]=bufen[strlen(bcs)-1];
        for(k=strlen(bcs)-1;k>1;k--)
            bufen[k]=bufen[k-1];
    }
    for(i=0;i<strlen(bcs);i++)//���������ֵ
        ji[i]=bufen[i];
    cd=strlen(ji);//�������ֵ�ó���
    for(i=2;i<strlen(cs)-2;i++)
        ji[cd+i-2]=cs[i];//��֮ǰ���ֻ��Ƶ��������ֵ�ֵ���¸��������
    if(ji[1]=='0')//��ӷ���
    {
        ji[0]='+';
        ji[2]='.';//��֮ǰȥ����С���㻹ԭ
    }
    else if(ji[1]=='1')//��ӷ���
    {
        ji[0]='-';
        ji[1]='0';
        ji[2]='.';//��֮ǰȥ����С���㻹ԭ
        for(i=strlen(ji)-1;i>2;i--)
        {
            if(ji[i]=='1')
            {
                for(i=i-1;i>2;i--)//ȡ��
                {
                    if(ji[i]=='0')
                        ji[i]='1';
                    else
                        ji[i]='0';
                }
                break;
            }
        }
    }
    for(i=strlen(ji)-1;i>2;i--)
    {
        if(ji[i]=='1')
        {
            biaoji=i;
            break;
        }
    }
    for(i=0;i<=biaoji;i++)//��������
        printf("%c",ji[i]);
	system("pause");
}
