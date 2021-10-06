#include<stdio.h>
#include<stdlib.h>
#include <inttypes.h>


#define STACK_INIT_SIZE 100//存储空间初始分配量
#define STACKINCREMENT 10//分配增量


unsigned  int_stacksize;//栈的空间大小
int *int_stacktop_ptr;//栈顶指针
int *int_stackbase_ptr;//栈底指针


/*初始化栈：先申请空间确定栈底指针，再将其赋值给栈顶指针（两者此时都指向栈底
若申请失败则结束程序
*/
#define initStack(stack) stack ## _stackbase_ptr=malloc(sizeof(stack)*STACK_INIT_SIZE);\
        if(stack ## _stackbase_ptr){\
        stack ## _stacktop_ptr=stack ## _stackbase_ptr;\
        stack ##_stacksize=STACK_INIT_SIZE; \
        }\
        else exit(0)

#define stackEmpty(stack) stack ##_stackbase_ptr==stack ## _stacktop_ptr?1:0//判断栈是否为空，若为空返回1，反之返回0

/*得到栈顶元素的值*/
#define getTop(stack,e) stack ## _stackbase_ptr==stack ## _stacktop_ptr?0:(e=*(stack ## _stacktop_ptr-1),1)

/*清空栈*/
#define clearStack(stack) stack ## _stacktop_ptr=stack ## _stackbase_ptr

/*销毁栈*/
#define destroyStack(stack) free(stack ## _stackbase_ptr)

/*求栈的大小*/
#define stackLength(stack) stack ## _stacktop_ptr-stack ## _stackbase_ptr

/*删除栈顶元素，用e返回其值，否则返回0*/
#define pop(stack,e) stack ## _stackbase_ptr==stack ## _stacktop_ptr?0:(e=*(--stack ## _stacktop_ptr),1)

/*插入元素e为新的栈顶元素，若空间已满则申请新空间，并改变栈空间size值*/
#define push(stack,e) if(stack ## _stacktop_ptr-stack ## _stackbase_ptr>=STACK_INIT_SIZE){\
    stack ## _stackbase_ptr=(stack *)realloc(stack ## _stackbase_ptr,sizeof(stack)*(stack ##_stacksize+STACKINCREMENT));\
    if(!stack ## _stackbase_ptr) exit(0);\
    stack ##_stacksize+=STACKINCREMENT;\
    stack ## _stacktop_ptr=stack ## _stackbase_ptr+stack ##_stacksize;\
    }\
    *(stack ## _stacktop_ptr++)=e


/*定义其他类型的基本栈*/

/*字符型栈*/
unsigned  char_stacksize;//栈的空间大小
char *char_stacktop_ptr;//栈顶指针
char *char_stackbase_ptr;//栈底指针

/*结构体型栈*/
typedef struct node{
    int data[10];
    float x,y;
}tnode;

unsigned  tnode_stacksize;//栈的空间大小
tnode *tnode_stacktop_ptr;//栈顶指针
tnode *tnode_stackbase_ptr;//栈底指针

int main(){

    initStack(int);//建立整数栈
    initStack(char);//建立字符栈
    initStack(tnode);//建立结构体栈

//测试整数栈
    int x;
    if((pop(int,x)))//让栈顶元素出栈
      printf("出栈成功 %d\n",x);
    else
      printf("栈空，不能出栈\n");
    printf("栈中有 %ld 个元素",stackLength(int));//打印栈元素总值

    
    if(stackEmpty(int))
      printf("栈空，无法取栈顶");
    else if(getTop(int,x))
      printf("栈顶元素是 %d \n",x);//若栈非空，打印栈顶元素

    push(int,3);//插入新的栈顶元素，值为3
    printf("栈中有 %ld 个元素\n",stackLength(int));//打印栈元素总值


    push(int,4);//插入新的栈顶元素，值为4
    push(int,5);//插入新的栈顶元素，值为5

    printf("栈中有 %ld 个元素\n",stackLength(int));//打印栈元素总值

    if(stackEmpty(int))
      printf("栈空，无法取栈顶\n");
    else if(getTop(int,x))
      printf("栈顶元素是 %d \n",x);//若栈非空，打印栈顶元素
 

    clearStack(int);//清空栈
}