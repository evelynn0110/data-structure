#include<stdio.h>
#include<stdlib.h>
#define ElemType int//用宏定义将ElemType设成int,代码中所有ElemType可用int代替
#define _DEBUG_ 1//定义_DEBUG_为1


typedef struct Lnode{//定义结点Lnode
    ElemType data;//结点中储存的数据
    struct Lnode *next;//指向下一个结点的指针
}LinkNode,*LinkList;//定义结点类型LinkNode，结点指针类型LinkList

LinkNode *first;//定义头结点指针

LinkNode *initList(){//创建新结点
    LinkNode *p;
    p=(LinkNode*)malloc(sizeof(LinkNode));//申请空间
    if(!p){
        printf("初始化失败！");
        exit(0);//结束程序
    }
    p->next=NULL;//next指针置空值
    return p;//返回指针
}

#ifdef _DEBUG_//条件编译

LinkNode head;//定义头结点

void initList1(LinkNode *p){//错误的创建新结点方法
    p=(LinkNode*)malloc(sizeof(LinkNode));//申请空间
    if(!p){
        printf("初始化失败！");
        exit(0);//结束程序
    }
    p->next=NULL;//next指针置空值
}

void initList2(LinkNode head){
    first=&head;//给头结点的指针赋值
    first->next=NULL;//next指针置空
}

#endif
int ListLength(LinkList p){//计算链表长度
    int count=0;
    while(p->next!=NULL){//若该结点的后继不为空，则继续循环计数（链表的头结点不存值，往后一个结点才参与长度计算
        count++;
        p=p->next;
    }
    return count;//返回链表长度
}


int ListEmpty(LinkList p){//判断是否是空链表
    if(p->next!=NULL)
      return 1;//若不是空链表则返回1
    return 0;
}

void ClearList(LinkList p){//删除p结点后的所有结点（应该是用于清空链表，最后只保留头结点
    LinkNode *q;
    if(p->next!=NULL){//若p后存在结点
        q=p->next;//用q指后一个结点
        p->next=q->next;//p的next指针指向删除的结点的后方（结点或NULL
        free(q);//释放删除结点的空间
    }
}


void DestroyList(LinkList p){//销毁链表
    ClearList(p);
    free(p);//清除头结点
}


int GetElem(LinkList p,int i,ElemType *e){//将链表第i个数据元素的值置给e
    int k=0;
    while((p=p->next)){
        k++;
        if(k==i){
            *e=p->data;
            return k;//返回位置，表明赋值成功
        }
    }
    return 0;//i大于了链表长度，赋值失败
}


LinkNode *LocateElem(LinkList p,ElemType e){//查找链表中数据元素值等于e的第1个结点，并返回指向该结点的指针
    while((p=p->next)){
        if(p->data==e)
          return p;//查找成功，返回p
    }
    return NULL;//未查到，所有结点的元素值均不等于e
}

LinkNode *PriorElem(LinkList p,LinkNode *cur_e){//返回cur_e结点的前驱结点
    for(;p->next;p=p->next){//若p是最后一个结点则跳出for循环
        if(p->next==cur_e)
           return p;//已找到，返回前驱指针
    }
    return NULL;//未找到（cur_e不是链表里的结点
}

LinkNode *NextElem(LinkList p,LinkNode *cur_e){//返回cur_e结点的后继结点
    return cur_e->next;//若cur_e是链表中的结点且不是尾结点，则返回值有效，若不是则会失败
}


LinkNode *LinkInsert(LinkList p,int i,ElemType e){//在第i个结点之前插入新结点，元素值为e/在p结点的后i位插入新结点
    LinkNode *q;
    for(;p;p=p->next){
        if(--i<1){
            q=(LinkNode *)malloc(sizeof(LinkNode));
            if(!q){
                printf("初始化失败！");
                exit(0);
            }
            q->next=p->next;//将新结点与第i个结点相连
            q->data=e;//元素赋值
            p->next=q;//将第i-1个结点与新结点相连
            return q;
        }
    }
    return NULL;//i大于链表长度，插入失败
}


int ListDelete(LinkList p,int i,ElemType *e){//删除第i个结点，并用*e保存删除结点的元素值
    LinkNode *q=p;
    for(p=p->next;p;p=p->next){
        if(--i<1){
            *e=p->data;//元素值赋给e指向的整型数
            q->next=p->next;//第i-1个结点指向第i+1个结点或指向空
            free(p);//释放删除结点的空间
            return 1;//表明删除成功
        }
        q=p;
    }
    return 0;//i的值大于链表长度，删除失败
}


void PrintLinkNode(LinkNode *p){//打印结点的元素值
    printf("%d,",p->data);
}

void Add2(LinkNode *p){//将结点元素值+2并打印表明该操作
    p->data+=2;
    printf("+2,");
}

void DebugLinkNode(LinkNode *p){//打印出结点p的地点值（十六进制）和元素值
    printf("结点-(*addr)=value :");
    printf("(*%lx)=%d\n",p,p->data);
}


void ListTraverse(LinkList p,void (*ptrFunc)(LinkNode *ptr)){//遍历链表，并打印每个结点的地址和元素值
    printf("链表(表长=%d):",ListLength(p));//打印表长
    while((p=p->next)!=NULL){
        (*ptrFunc)(p);//调用Debug函数，打印每个结点的地址和元素值
        printf("\n");
    }
}

int main(){

    void (*ptrFunc)(LinkNode *p)=DebugLinkNode;//设定指向函数DebugLinkNode的指针

    first=initList();//创建头结点

    ListTraverse(first,ptrFunc);//遍历链表，打印每个结点的地址和元素值，下面同理
    LinkInsert(first,1,2);//在头结点的后1位插入新结点，新结点元素值为2，下面同理
    LinkInsert(first,1,3);
    LinkInsert(first,1,4);
    LinkInsert(first,1,5);
    ListTraverse(first,ptrFunc);
    LinkInsert(first,1,6);
    LinkInsert(first,1,7);
    LinkInsert(first,1,8);
    LinkInsert(first,1,9);
    ListTraverse(first,ptrFunc);
    LinkInsert(first,3,666);
    LinkInsert(first,5,777);
    LinkInsert(first,7,888);
    LinkInsert(first,9,999);
    ListTraverse(first,ptrFunc);

    ElemType ei;
    printf("取数据之前 %d --",ei);
    GetElem(first,10,&ei);//读取第10个结点的元素值
    printf("读取的数据为 %d --",ei);//打印元素值

    LinkNode *q=LocateElem(first,888);
    if(!q)
        printf("未找到对应结点");
    else{
        q=PriorElem(first,q);//查找元素值为888结点的前驱
        printf("找到结点的前驱为 %d --",q->data);
        printf("找到的结点为 %d --",q->next->data);
        if(q->next->next!=NULL)//判断后继是否存在
            printf("找到结点的后继为 %d ",NextElem(first,NextElem(first,q))->data);//打印后继元素值
        printf("\n");
    }

    printf("删除前的值 %d --",ei);
    if(ListDelete(first,15,&ei)>0)//删除第15个结点，并用ei返回其元素值，若元素值大于零则进入if语句
        printf("删除的值为 %d\n",ei);//打印删除结点的元素值
    else
        printf("删除失败, %d\n",ei);//删除失败则返回ei的原值



    ListTraverse(first,ptrFunc);//遍历链表，打印每个结点的地址和元素值
    printf("删除前的值 %d --",ei);
    if(ListDelete(first,10,&ei)>0)//删除第10个结点，并用ei返回其元素值，若元素值大于零则进入if语句
        printf("删除的值为 %d\n",ei);//打印删除结点的元素值
    else
        printf("删除失败, %d\n",ei);//删除失败则返回ei的原值


    printf("删除前的值 %d --",ei);
    if(ListDelete(first,6,&ei)>0)//删除第6个结点，并用ei返回其元素值，若元素值大于零则进入if语句
        printf("删除的值为 %d\n",ei);//打印删除结点的元素值
    else
        printf("删除失败, %d\n",ei);//删除失败则返回ei的原值
    ListTraverse(first,ptrFunc);//遍历链表，打印每个结点的地址和元素值

    ptrFunc=Add2;//将ptrFunc指向Add2函数
    printf("每个元素准备+2\n");
    ListTraverse(first,ptrFunc);//每个结点+2
    printf("完成+2后,新的链表:");
    ListTraverse(first,PrintLinkNode);//打印链表


    DestroyList(first);//销毁链表

    return 0;//程序结束
}