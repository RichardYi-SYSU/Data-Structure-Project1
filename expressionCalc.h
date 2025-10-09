#define MAX_SIZE 1000
#include <math.h>

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

bool PushNumStack(numStack *s,int x);
//弹出
bool PopCharStack(charStack *s,char &x);

bool PopNumStack(numStack *s,int &x);
//取栈顶
char GetCharStackTop(charStack *s);

int GetNumStackTop(numStack *s);



//输入的函数

void Input();


//得到整数的长度
int getNumLen(int num)
{
    int len=0;
    while(num>0)
    {
        num/=10;
        len++;
    }
    return len;
}


