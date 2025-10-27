#include <iostream>
#include <cstring>
#include <cctype>
#include <cmath>
#include <string>
using namespace std;

#define MAX_SIZE 1024
#define OK 1
#define ERROR 0

//栈定义
struct charStack { int top; char data[MAX_SIZE]; };
struct numStack  { int top; double data[MAX_SIZE]; };
//栈初始化
void InitCharStack(charStack *s){ s->top = -1; }
void InitNumStack (numStack  *s){ s->top = -1; }
//栈判空
bool IsCharStackEmpty(charStack *s){ return s->top == -1; }
bool IsNumStackEmpty (numStack  *s){ return s->top == -1; }
//压栈
bool PushCharStack(charStack *s, char x){
    if(s->top == MAX_SIZE - 1) return false;
    s->data[++(s->top)] = x;
    return true;
}
bool PushNumStack(numStack *s, double x){
    if(s->top == MAX_SIZE - 1) return false;
    s->data[++(s->top)] = x;
    return true;
}
//弹栈
bool PopCharStack(charStack *s, char &x){
    if(s->top == -1) return false;
    x = s->data[(s->top)--];
    return true;
}
bool PopNumStack(numStack *s, double &x){
    if(s->top == -1) return false;
    x = s->data[(s->top)--];
    return true;
}
//获取栈顶
char   GetCharStackTop(charStack *s){ return s->top == -1 ? '\0' : s->data[s->top]; }
double GetNumStackTop (numStack  *s){ return s->top == -1 ? 0.0  : s->data[s->top]; }

//运算符优先级 
char Precede(char op1, char op2) {
    const char prec[8][8] = {
    //       +    -    *    /    ^    (    )    #
    /*+*/   '>', '>', '<', '<', '<', '<', '>', '>',
    /*-*/   '>', '>', '<', '<', '<', '<', '>', '>',
    /***/   '>', '>', '>', '>', '<', '<', '>', '>',
    /*/*/   '>', '>', '>', '>', '<', '<', '>', '>',
    /*^*/   '>', '>', '>', '>', '<', '<', '>', '>',   // ^右结合
    /*(*/   '<', '<', '<', '<', '<', '<', '=', 'e',
    /*)*/   '>', '>', '>', '>', '>', 'e', '>', '>',
    /*#*/   '<', '<', '<', '<', '<', '<', 'e', '='
    };

    int i, j;
    switch(op1){
        case '+': i=0; break; case '-': i=1; break;
        case '*': i=2; break; case '/': i=3; break;
        case '^': i=4; break; case '(': i=5; break;
        case ')': i=6; break; case '#': i=7; break;
        default: return 'e';
    }
    switch(op2){
        case '+': j=0; break; case '-': j=1; break;
        case '*': j=2; break; case '/': j=3; break;
        case '^': j=4; break; case '(': j=5; break;
        case ')': j=6; break; case '#': j=7; break;
        default: return 'e';
    }
    return prec[i][j];
}

//计算函数
double Operate(double a, char theta, double b) {
    switch (theta) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0) {
                cout << "错误：除数为零！" << endl;
                exit(ERROR);
            }
            return a / b;
        case '^': return pow(a, b);
    }
    return 0;
}

//输出状态
void PrintStates(charStack* optr, numStack* opnd, char c, const char* op_str) {
    cout << "| ";
    for (int i = 0; i <= optr->top; i++) cout << optr->data[i];
    cout << "\t\t| ";
    for (int i = 0; i <= opnd->top; i++) cout << opnd->data[i] << " ";
    cout << "\t\t| " << c << "\t\t| " << op_str << endl;
}

//表达式求值
double EvaluateExpression() {
    charStack OPTR;
    numStack  OPND;
    InitCharStack(&OPTR);
    InitNumStack(&OPND);
    PushCharStack(&OPTR, '#');

    bool negFlag[MAX_SIZE];   // 标记每个括号是否为取反括号
    int flagTop = -1;

    cout << "请输入一个以'#'结尾的整数算术表达式: ";
    string expr;
    getline(cin, expr);
    if (expr.empty()) getline(cin, expr);
    expr += '#';

    cout << "------------------------------------------------------------------\n";
    cout << "| 运算符栈\t| 运算数栈\t| 输入字符\t| 主要操作\n";
    cout << "------------------------------------------------------------------\n";
    PrintStates(&OPTR, &OPND, expr[0], "初始化");

    int i = 0;

    // 用 token 类型来区分单目 / 二元运算符
    enum LastTok { START, OPERAND, OPERATOR, LPAREN, RPAREN };
    LastTok last = START;

    while (expr[i] != '#' || GetCharStackTop(&OPTR) != '#') {
        char c = expr[i];
        if (isspace(c)) { i++; continue; }

        // ========== 单目减号判断 ==========
        if (c == '-' && (last == START || last == OPERATOR || last == LPAREN)) {
            i++;
            // -(...) 情况
            if (expr[i] == '(') {
                PushCharStack(&OPTR, '(');
                negFlag[++flagTop] = true;  // 记录这是取反括号
                PrintStates(&OPTR, &OPND, expr[i], "单目负号 + '(' → 标记为取反括号");
                i++;
                last = LPAREN;
                continue;
            }
            // -数字 情况
            else if (isdigit(expr[i])) {
                double num = 0;
                string num_str;
                while (isdigit(expr[i])) {
                    num = num * 10 + (expr[i] - '0');
                    num_str += expr[i];
                    i++;
                }
                num = -num;
                PushNumStack(&OPND, num);
                PrintStates(&OPTR, &OPND, expr[i], ("检测到单目负号 → 压入 " + to_string(num)).c_str());
                last = OPERAND;
                continue;
            }
        }

        //数字
        if (isdigit(c)) {
            double num = 0;
            string num_str;
            while (isdigit(expr[i])) {
                num = num * 10 + (expr[i] - '0');
                num_str += expr[i];
                i++;
            }
            PushNumStack(&OPND, num);
            PrintStates(&OPTR, &OPND, expr[i], ("操作数 " + num_str + " 入栈").c_str());
            last = OPERAND;
            continue;
        }

        //运算符优先级处理
        char top = GetCharStackTop(&OPTR);
        switch (Precede(top, c)) {
            case '<': {
                PushCharStack(&OPTR, c);
                if (c == '(') {
                    negFlag[++flagTop] = false;  // 普通左括号标记
                    last = LPAREN;
                } else last = OPERATOR;
                PrintStates(&OPTR, &OPND, c, "栈顶运算符优先级低, 当前运算符入栈");
                i++;
                break;
            }

            case '=': {
                char op;
                PopCharStack(&OPTR, op); // 弹出 '('
                PrintStates(&OPTR, &OPND, c, "脱括号");
                i++;

                // 若该括号为取反括号，则取反
                if (flagTop >= 0 && negFlag[flagTop--]) {
                    double val;
                    PopNumStack(&OPND, val);
                    PushNumStack(&OPND, -val);
                    PrintStates(&OPTR, &OPND, c, "取反括号生效：结果变号");
                }
                last = OPERAND;
                break;
            }

            case '>': {
                char theta;
                double a, b;
                PopCharStack(&OPTR, theta);
                PopNumStack(&OPND, b);
                PopNumStack(&OPND, a);
                double result = Operate(a, theta, b);
                PushNumStack(&OPND, result);
                char op_buf[60];
                snprintf(op_buf, sizeof(op_buf), "归约: %.4f %c %.4f = %.4f", a, theta, b, result);
                PrintStates(&OPTR, &OPND, c, op_buf);
                last = OPERAND;
                break;
            }

            case 'e':
                cout << "语法错误！" << endl;
                return ERROR;
        }
    }

    double final_result;
    PopNumStack(&OPND, final_result);
    cout << "------------------------------------------------------------------\n";
    return final_result;
}



void ExpressionEvaluator() {
    cout << "\n--- 算术表达式求值计算器（含乘方、单目减） ---\n";
    double result = EvaluateExpression();
    cout << "表达式的计算结果是: " << result << endl;
}



// int main() {
//     int choice;
//     while (true) {
//         std::cout << "\n========= Project 1: 计算器 =========\n";
//         std::cout << "1. 一元稀疏多项式简单计算器\n";
//         std::cout << "2. 算术表达式求值计算器\n";
//         std::cout << "3. 退出程序\n";
//         std::cout << "=======================================\n";
//         std::cout << "请输入您的选择: ";
//         std::cin >> choice;

//         switch (choice) {
//             case 1:
//                 //PolynomialCalculator();
//                 break;
//             case 2:
//                 while(std::cin.get() != '\n'); 
//                 ExpressionEvaluator();
//                 break;
//             case 3:
//                 std::cout << "程序退出。\n";
//                 return 0;
//             default:
//                 std::cout << "无效选择，请重新输入。\n";
//                 std::cin.clear();
//                 while(std::cin.get() != '\n');
//                 break;
//         }
//     }
//     return 0;
// }