#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//请注意，必须是纯英文输入，不读入中文的','

int main()
{
    int i,j,k;
    int cha;
    int jw=0;//进位标记符号
    int cd;//字符串长度
    int biaoji;
    char bcs[21],cs[21],jg[41];//赋值为0
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
    //将小数点全部变成数字  即有两位符号位
    if(bcs[0]=='+')bcs[2]='0';//将bcs中的原码变补码 jg记录-x的补码
    if(bcs[0]=='-')//负数情况
    {
        bcs[1]=bcs[2]='1';//符号位为11
        for(i=strlen(bcs)-1;i>2;i--)//从尾部开始
        {
            if(bcs[i]=='1')
            {
                for(i=i-1;i>2;i--)
                {
                    if(bcs[i]=='0')
                        bcs[i]='1';//取反
                    else
                        bcs[i]='0';
                }
                break;
            }

        }
    }
    if(jg[0]=='-')
        jg[2]='0';//-x的补码
    if(jg[0]=='+')
    {
        jg[1]=jg[2]='1';
        for(i=strlen(jg)-1;i>2;i--)
        {
            if(jg[i]=='1')
            {
                for(i=i-1;i>2;i--)//取反操作
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
    cs[strlen(cs)]='0';//将b中的原码变补码 尾部填0 即为y(n+1)
    if(cs[0]=='+')//正值补码数值部分不变
        cs[2]='0';
    if(cs[0]=='-')//负值操作
    {
        cs[1]=cs[2]='1';//符号位改为1 1
        for(i=strlen(cs)-1;i>2;i--)
        {
            if(cs[i]=='1')
            {
                for(i=i-1;i>2;i--)//取反操作
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
    bufen=(char*)malloc(strlen(bcs));//开辟新空间
    for(i=0;i<strlen(bcs);i++)//赋值0
        bufen[i]='0';
    for(i=strlen(cs)-1;i>2;i--)
    {
        cha=cs[strlen(cs)-1]-cs[strlen(cs)-2];// y(n+1)-y(n)
        if(cha==1)//部分积加[x]补码  右移一位
        {
            for(j=strlen(bcs)-1;j>0;j--)
            {
                if(bcs[j]-'0'+bufen[j]-'0'+jw==3)//1+1 进位为1
                {
                    bufen[j]='1';
                    jw=1;
                }
                else if(bcs[j]-'0'+bufen[j]-'0'+jw==2)//1+0进位为1 或者 0+1进位为1 或者 1+1 进位为0
                {
                    bufen[j]='0';
                    jw=1;
                }
                else if(bcs[j]-'0'+bufen[j]-'0'+jw==1)//0+0进位为1 或者 1+0进位为0 或者 0+1进位为0
                {
                    bufen[j]='1';
                    jw=0;
                }
                else//不进位
                {
                    bufen[j]='0';
                    jw=0;
                }
            }
            jw=0;//重置进位标记
        }
        else if(cha==-1)//部分积加[-x]补码 右移一位
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
                else //不进位
                {
                    bufen[j]='0';
                    jw=0;
                }
            }
            jw=0;//重置进位标记符号
        }
        //移位
        if(i==3)break;
        for(k=strlen(cs)-1;k>2;k--)
                cs[k]=cs[k-1];
        cs[2]=bufen[strlen(bcs)-1];
        for(k=strlen(bcs)-1;k>1;k--)
            bufen[k]=bufen[k-1];
    }
    for(i=0;i<strlen(bcs);i++)//给最后结果赋值
        ji[i]=bufen[i];
    cd=strlen(ji);//测量最后值得长度
    for(i=2;i<strlen(cs)-2;i++)
        ji[cd+i-2]=cs[i];//将之前部分积移到乘数部分的值重新赋给最后结果
    if(ji[1]=='0')//添加符号
    {
        ji[0]='+';
        ji[2]='.';//将之前去掉的小数点还原
    }
    else if(ji[1]=='1')//添加符号
    {
        ji[0]='-';
        ji[1]='0';
        ji[2]='.';//将之前去掉的小数点还原
        for(i=strlen(ji)-1;i>2;i--)
        {
            if(ji[i]=='1')
            {
                for(i=i-1;i>2;i--)//取反
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
    for(i=0;i<=biaoji;i++)//输出最后结果
        printf("%c",ji[i]);
	system("pause");
}
