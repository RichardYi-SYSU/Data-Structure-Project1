#include <iostream>
#include <cstring>
#include <cctype>
#include <cmath>
#include <string>
using namespace std;

#define MAX_SIZE 1024
#define OK 1
#define ERROR 0

//栈定义与操作 

struct charStack { int top; char data[MAX_SIZE]; };
struct numStack  { int top; double data[MAX_SIZE]; };

void InitCharStack(charStack *s){ s->top = -1; }
void InitNumStack (numStack  *s){ s->top = -1; }

bool IsCharStackEmpty(charStack *s){ return s->top == -1; }
bool IsNumStackEmpty (numStack  *s){ return s->top == -1; }

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

char   GetCharStackTop(charStack *s){ return s->top == -1 ? '\0' : s->data[s->top]; }
double GetNumStackTop (numStack  *s){ return s->top == -1 ? 0.0  : s->data[s->top]; }

//运算符优先级 
// 保持 ^ 为右结合（第5行第5列 '^' 对 '^' 为 '<'）
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
        if (b == 0) return NAN;  // 返回 NAN 表示错误
        return a / b;
    case '^':
        if (a==0.0 && b<0.0) return NAN; // 同样错误
        return pow(a, b);
    default: return NAN;
    }
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
double EvaluateExpression(string expr) {
    charStack OPTR;
    numStack  OPND;
    InitCharStack(&OPTR);
    InitNumStack(&OPND);
    PushCharStack(&OPTR, '#');

    bool negFlag[MAX_SIZE];
    int flagTop = -1;

    if (expr.back() != '#') expr += '#';  // 自动补上结束符  
    int i = 0;
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
                //PrintStates(&OPTR, &OPND, expr[i], "单目负号 + '(' → 标记为取反括号");
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
                //PrintStates(&OPTR, &OPND, expr[i], ("检测到单目负号 → 压入 " + to_string(num)).c_str());
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
            //PrintStates(&OPTR, &OPND, expr[i], ("操作数 " + num_str + " 入栈").c_str());
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
                //PrintStates(&OPTR, &OPND, c, "栈顶运算符优先级低, 当前运算符入栈");
                i++;
                break;
            }

            case '=': {
                char op;
                PopCharStack(&OPTR, op); // 弹出 '('
                //PrintStates(&OPTR, &OPND, c, "脱括号");
                i++;

                // 若该括号为取反括号，则取反
                if (flagTop >= 0 && negFlag[flagTop--]) {
                    double val;
                    PopNumStack(&OPND, val);
                    PushNumStack(&OPND, -val);
                    //PrintStates(&OPTR, &OPND, c, "取反括号生效：结果变号");
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
                //传出除零错误
                double result = Operate(a, theta, b);
                if (std::isnan(result)) {
                    return NAN;  // 传错
                }

                PushNumStack(&OPND, result);

                char op_buf[60];
                //snprintf(op_buf, sizeof(op_buf), "归约: %.4f %c %.4f = %.4f", a, theta, b, result);
                //PrintStates(&OPTR, &OPND, c, op_buf);
                last = OPERAND;
                break;
            }

            case 'e':
                //cout << "语法错误！" << endl;
                return NAN;
        }
    }

    double final_result;
    PopNumStack(&OPND, final_result);
    //cout << "------------------------------------------------------------------\n";
    return final_result;
}


//作为接入GUI的表达式求值版本，传入string，返回NAN或者表达式的值

