#ifndef EXPRESSIONCALC_H
#define EXPRESSIONCALC_H



//常量定义
#define MAX_SIZE 1024
#define OK 1
#define ERROR 0
#include <string>
//栈结构定义

//运算符栈
struct charStack {
    int top;
    char data[MAX_SIZE];
};

//运算数栈
struct numStack {
    int top;
    double data[MAX_SIZE];
};

//栈操作函数

// 初始化栈
void InitCharStack(charStack *s);
void InitNumStack(numStack *s);

// 判断栈是否为空
bool IsCharStackEmpty(charStack *s);
bool IsNumStackEmpty(numStack *s);

// 压栈
bool PushCharStack(charStack *s, char x);
bool PushNumStack(numStack *s, double x);

// 出栈
bool PopCharStack(charStack *s, char &x);
bool PopNumStack(numStack *s, double &x);

// 获取栈顶元素
char   GetCharStackTop(charStack *s);
double GetNumStackTop(numStack *s);

//表达式处理函数

// 运算符优先级比较函数
char Precede(char op1, char op2);

// 运算执行函数（a θ b）
double Operate(double a, char theta, double b);

// 输出当前运算状态（调试用）
void PrintStates(charStack* optr, numStack* opnd, char c, const char* op_str);

// 主表达式求值函数（输入表达式字符串并计算结果）
double EvaluateExpression(std::string expr);

// 控制台封装版（用于独立运行测试）
void ExpressionEvaluator();


#endif // EXPRESSIONCALC_H



