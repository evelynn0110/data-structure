#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

#define MAXS 1000


typedef struct Lnode{//多项式单个结点
    double coe;
    double exp;
}Lnode;

typedef struct poL{//多项式线性表
    Lnode *list;
    int plen;
    int psize;
}poL;

typedef struct sqL{//串线性表
    char *co;
    int len;
    int size;
}sNode;


void Strnum(double x,int n );//十进制二进制串表示
void InitsqL(sNode *L);//初始化结构体
void Conv(char *s,int len);//逆转数组（用于处理进制转换的整数部分
void Minus(char *s,int *len);//
void CaculateN(double x ,int n);//N进制加减乘
char * SoNConv(double x,int n ,int *len,int N,int pr);//
void polyC(int n);//多项式处理
void Capoly(poL p,int n,double x);//多项式计算



int main(){

    int se;//用户键入选项
    int n;//精度
    double x;//实数

    printf("---------------menu---------------\n");
        printf("\n");
        printf("1.用十进制或二进制串表示数字\n");
        printf("2.进制转换\n");
        printf("3.单变量多项式求值\n");
        printf("\n");
        printf("------------------------------\n");

    printf("请输入功能序号，输入0结束程序\n");
    scanf("%d",&se);


    while(se!=0){//显示菜单
        printf("---------------menu---------------\n");
        printf("\n");
        printf("1.用十进制或二进制串表示数字\n");
        printf("2.进制转换\n");
        printf("3.单变量多项式求值\n");
        printf("\n");
        printf("------------------------------\n");
        
        printf("请输入精度n\n");
        scanf("%d",&n);
        printf("请输入操作的实数\n");
        scanf("%lf",&x);



        switch(se){//选择

            case 1:Strnum(x,n);break;
            case 2:CaculateN(x,n); break;
            case 3:polyC(n);break;
            default:break;

        }
        printf("请输入功能序号，输入0结束程序\n");
        scanf("%d",&se);

    }
    return 0;

}


void Strnum(double x,int n ){//用十进制或二进制串表示数字
    if(x>=1024||x<=-1024) return;//非法输入
    int flag=0;

    if(x<0){//
        flag=1;
        x=-x;
    }

    if((((int)(x*pow(10,n+1)))%10)>=5)//四舍五入处理
        x+=pow(10,-n);

    sNode de,bi;
    InitsqL(&de);
    InitsqL(&bi);//初始化串
    int dec=(int)x;
    int t=dec;
    while(t>0){//整数部分十进制变换
        de.co[de.len++]=t%10+48;
        t/=10;
    }

    t=dec;
    while(t>0){//整数部分二进制变换
        bi.co[bi.len++]=t%2+48;
        t/=2;
    }

    Conv(de.co,de.len);
    Conv(bi.co,bi.len);//由于计算时为逆序，逆转为正序

    de.co[de.len++]='.';
    bi.co[bi.len++]='.';//加小数点
    double fl=x-dec;
    double fd=fl,fb=fl;

    for(int i=0;i<n;i++){//小数位变换
        de.co[de.len++]=(int)(fd*10)+48;//读位
        fd=fd*10-(int)(fd*10);//读下一位

        bi.co[bi.len++]=(int)(fb*2)+48;
        fb=fb*2-(int)(fb*2);
    }

    if(flag){//若x为负数则在表前加负号
       Minus(de.co,&de.len);
       Minus(bi.co,&bi.len);
    }

    de.co[de.len]='\0';
    bi.co[bi.len]='\0';//保证结尾为\0
    printf("十进制串表示为\n");
    puts(de.co);
    printf("\n");
    printf("二进制串表示为\n");
    puts(bi.co);//打印串

}


void InitsqL(sNode *L){//初始化串
    (*L).co=(char *)malloc(sizeof(char)*MAXS);//分配空间
    if(!(*L).co) exit(0);//分配失败则退出
    (*L).len=0;
    (*L).size=MAXS;
}


void Conv(char *s,int len){//整数部分顺序逆转
    for(int i=0;i<len/2;i++){
        char t;
        t=s[i];
        s[i]=s[len-1-i];
        s[len-1-i]=t;
    }
}


void Minus(char *s,int *len){//负数处理
    for(int i=(*len)-1;i>=0;i--)
        s[i+1]=s[i];
    s[0]='-';
    (*len)++;
}

char *SoNConv(double x,int n,int *len,int N,int pr){//N进制转换

    
    if(N<=0){//输入异常判断
        printf("输入异常！\n");
        return;
    }

    sNode sn;
    InitsqL(&sn);

    
    int flag=0;
    if(x<0){//负数处理
        flag=1;
        x=-x;
    }

    if((((int)(x*pow(10,n+1)))%10)>=5)//四舍五入处理
        x+=pow(10,-n);

    int dec=(int)x,t=dec;
    double fl=x-dec,ft=fl;

    if(t==0)
        sn.co[sn.len++]=48;

    while(t>0){//整数部分转换
        int nbit=t%N;
        if(nbit<10)
           sn.co[sn.len++]=nbit+48;
        else 
           sn.co[sn.len++]='a'+(nbit-10);
        t=t/N;
    }
 
    Conv(sn.co,sn.len);


    sn.co[sn.len++]='.';

    for(int i=0;i<n;i++){//浮点部分转换
        double fbit=ft*N;
        if(fbit>=10)
           sn.co[sn.len++]='a'+(int)fbit-10;
        else
           sn.co[sn.len++]=fbit+48;
        ft=ft*N-(int)(ft*N);
    }

    if(flag&&sn.co[0]!='0')
        Minus(sn.co,&sn.len);
    sn.co[sn.len]='\0';

    if(pr){
        printf("转化后的%d进制数为\n",N);
        puts(sn.co);
        printf("\n");
    }
    
    *len=sn.len;
    return sn.co;

}


void CaculateN(double x ,int n){//进制转换及基本操作
    sNode sn,sm;
    InitsqL(&sn);//初始化字符串
    InitsqL(&sm);
    int N;//进制
    double y;

    printf("请输入转换的进制\n");
    scanf("%d",&N);
    if(N<=0)
       return;


    sn.co=SoNConv(x,n,&sn.len,N,1);

    printf("请输入另一个实数y\n");
    scanf("%lf",&y);

    sm.co=SoNConv(y,n,&sm.len,N,1);

    if(x<=-1024||x>=1024||y<=-1024||y>=1024)//处理非法输入
       return ;


    int suml;
    printf("x+y=%s",SoNConv(x+y,n,&suml,N,0));
    printf("\n");
    printf("x-y=%s",SoNConv(x-y,n,&suml,N,0));
    printf("\n");
    printf("y-x=%s",SoNConv(y-x,n,&suml,N,0));
    printf("\n");
    printf("x*y=%s",SoNConv(x*y,n,&suml,N,0));
    printf("\n");


}


void InitPoly(poL *L){//多项式初始化
    (*L).list=(Lnode *)malloc(sizeof(Lnode)*MAXS);
    if(!(*L).list)   exit(0);//申请失败输入
    (*L).plen=0;
    (*L).psize=MAXS;

    for(int i=0;i<MAXS;i++)
       (*L).list[i].coe=0;
}



void MinusToP(char *s,int *len){
    for(int i=1;i<(*len)-1;i++){
        s[i-1]=s[i];
    }
    (*len)--;
}


void polyC(int n){

    poL pol;
    InitPoly(&pol);//多项式初始化


    int addp=0;
    char p[MAXS],num[MAXS];
    printf("请输入多项式\n");
    getchar();
    gets(p);

    int flag=0;//flag表明系数是否为分数
    int ju=0,jd=0;
    char up[MAXS],down[MAXS];//分子和分母

    for(int i=0;p[i]!='\0';i++){//解析多项式字符串
        if(p[i]=='+'||p[i]=='*'||p[i]=='x'||p[i]=='^')//字符不解析
            continue;

        if(i-1>=0&&p[i-1]=='^'){//解析指数
            char ex[MAXS];
            int a=0;
            for(a=0;p[i]!='+'&&p[i]!='-'&&p[i]!='\0';i++)
                ex[a++]=p[i];//连续读入指数
            ex[a]='\0';
            pol.list[addp++].exp=atof(ex);
        }

        if(p[i]=='/'){//系数是分数
            flag=1;
            continue;
        }

        if(flag==0){
            up[ju++]=p[i];
            up[ju]='\0';
        }
        else{
            down[jd++]=p[i];
            down[jd]='\0';
        }

        if(p[i+1]=='*'){
            if(flag==0)//解析系数
                pol.list[addp].coe=atof(up);
        
            else
                pol.list[addp].coe=atof(up)/atof(down);//处理分数
            ju=0;//分子计数器
            jd=0;//分母计数器
            flag=0;//重置flag
        }
    }


    for(int s=0;s<2;s++)
       printf("%lf,%lf   ",pol.list[s].coe,pol.list[s].exp);

    double x;

        printf("请输入变量的值\n");
        scanf("%lf",&x);

        Capoly(pol,n,x);

}

void Capoly(poL p,int n,double x){//计算多项式
    double sum=0;
    int len;
    for(int i=0;p.list[i].coe!=0;i++)
       sum+=p.list[i].coe*pow(x,p.list[i].exp);
    SoNConv(sum,n,&len,10,1);

}