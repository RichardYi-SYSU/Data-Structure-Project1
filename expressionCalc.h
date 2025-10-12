#define MAX_SIZE 1000
#include <math.h>
#include <iostream>

//栈的实现
typedef struct {
    char data[MAX_SIZE];
    int top;
}charStack;

typedef struct {
    double data[MAX_SIZE];
    int top;
}numStack;
//初始化
void InitCharStack(charStack *s);

void InitNumStack(numStack *s);
//判空
bool IsCharStackEmpty(charStack *s);

bool IsNumStackEmpty(numStack *s);
//压栈
bool PushCharStack(charStack *s,char x);

bool PushNumStack(numStack *s,double x);
//弹出
bool PopCharStack(charStack *s,char &x);

bool PopNumStack(numStack *s,double &x);
//取栈顶
char GetCharStackTop(charStack *s);

double GetNumStackTop(numStack *s);



//输入的函数

char* Input();//返回一个字符数组

//仅用于程序调试中使用，用于输出当前字符串
void Print(char *s);



//得到整数的长度


//将字符形式的整数转为int型整数
int charToInt(char *s,int begin,int len);

double expressionCalc(char *str,charStack *cs,numStack *ns);