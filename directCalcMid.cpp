#include <iostream>
#include <cstring>
#include <cctype>
#include <cmath>
#include <string>
using namespace std;

#define MAX_SIZE 1024

// ------------- 自定义栈（可与您现有接口对齐） -------------
struct charStack { int top; char  data[MAX_SIZE]; };
struct numStack  { int top; double data[MAX_SIZE]; };

void InitCharStack(charStack *s){ s->top = -1; memset(s->data, 0, sizeof(s->data)); }
void InitNumStack (numStack  *s){ s->top = -1; memset(s->data, 0, sizeof(s->data)); }

bool IsCharStackEmpty(charStack *s){ return s->top==-1; }
bool IsNumStackEmpty (numStack  *s){ return s->top==-1; }

bool PushCharStack(charStack *s, char x){ if(s->top==MAX_SIZE-1) return false; s->data[++s->top]=x; return true; }
bool PushNumStack (numStack  *s, double x){ if(s->top==MAX_SIZE-1) return false; s->data[++s->top]=x; return true; }

bool PopCharStack(charStack *s, char *x){ if(IsCharStackEmpty(s)) return false; *x=s->data[s->top--]; return true; }
bool PopNumStack (numStack  *s, double *x){ if(IsNumStackEmpty(s)) return false; *x=s->data[s->top--]; return true; }

char  GetCharStackTop(charStack *s){ return s->data[s->top]; }
double GetNumStackTop (numStack  *s){ return s->data[s->top]; }

// ------------- 调试打印（不显示 #） -------------
static void printStacks(charStack *ops, numStack *nums, char cur, const char* action){
    cout << "OpStack: [";
    for(int i=0;i<=ops->top;i++){
        if(ops->data[i]!='#'){
            cout << ops->data[i];
            if(i<ops->top) cout << ' ';
        }else{
            if(i<ops->top && ops->data[i+1]!='#') cout << ' ';
        }
    }
    cout << "]  ";

    cout << "NumStack: [";
    for(int i=0;i<=nums->top;i++){
        // 只为观感按整数输出
        cout << (long long)llround(nums->data[i]);
        if(i<nums->top) cout << ' ';
    }
    cout << "]  ";

    if(cur=='\0') cout << "ch: <END>  ";
    else          cout << "ch: " << cur << "  ";

    cout << "action: " << action << "\n";
}

// ------------- 算符优先级比较（switch–case 明示） -------------
// 返回：'<' 进栈； '>' 规约； '=' 括号配对； '?' 非法
char compare(char topOp, char curOp){
    switch(topOp){
        case '+':
            switch(curOp){
                case '+': case '-': return '>';
                case '*': case '/': return '<';
                case '(': return '<';
                case ')': return '>';
                case '#': return '>';
            } break;
        case '-':
            switch(curOp){
                case '+': case '-': return '>';
                case '*': case '/': return '<';
                case '(': return '<';
                case ')': return '>';
                case '#': return '>';
            } break;
        case '*':
            switch(curOp){
                case '+': case '-': case '*': case '/': return '>';
                case '(': return '<';
                case ')': return '>';
                case '#': return '>';
            } break;
        case '/':
            switch(curOp){
                case '+': case '-': case '*': case '/': return '>';
                case '(': return '<';
                case ')': return '>';
                case '#': return '>';
            } break;
        case '(':
            switch(curOp){
                case '+': case '-': case '*': case '/': case '(': return '<';
                case ')': return '=';
                case '#': return '?';
            } break;
        case ')':
            switch(curOp){
                case '+': case '-': case '*': case '/': case ')': case '#': return '>';
                case '(': return '?';
            } break;
        case '#':
            switch(curOp){
                case '+': case '-': case '*': case '/': case '(': return '<';
                case ')': return '?';
                case '#': return '=';
            } break;
        default: return '?';
    }
    return '?';
}

// ------------- 执行一次二目运算 -------------
static bool apply(char op, numStack *nums, double &out, const char* &err){
    double b, a;
    if(!PopNumStack(nums, &b) || !PopNumStack(nums, &a)){
        err = "表达式错误：二目运算缺少操作数";
        return false;
    }
    switch(op){
        case '+': out = a + b; return true;
        case '-': out = a - b; return true;
        case '*': out = a * b; return true;
        case '/':
            if(fabs(b)==0.0){ err="错误：除以 0"; return false; }
            out = a / b; return true;
        default:
            err = "表达式错误：未知运算符";
            return false;
    }
}

// ------------- 核心：直接解析中缀 -------------
bool evaluateInfix(const char* input, double &result){
    char expr[MAX_SIZE+2];
    strncpy(expr, input, MAX_SIZE);
    expr[MAX_SIZE] = '\0';

    charStack ops; numStack nums;
    InitCharStack(&ops); InitNumStack(&nums);
    PushCharStack(&ops, '#');

    auto isUnaryCtx = [](char prev)->bool{
        return (prev==0 || prev=='(' || prev=='+' || prev=='-' || prev=='*' || prev=='/' || prev=='#');
    };

    int i=0, n=(int)strlen(expr);
    char prevTok = 0; // 'n' 表数字，其它为运算符/括号/#

    while(true){
        while(expr[i] && isspace((unsigned char)expr[i])) i++;
        char ch = (expr[i] ? expr[i] : '#');

        // 数字（含一元负号）
        if( isdigit((unsigned char)ch) ||
           (ch=='-' && isUnaryCtx(prevTok) && isdigit((unsigned char)expr[i+1])) ){
            int sign = 1;
            if(ch=='-'){ sign=-1; i++; ch=expr[i]; }
            long long v=0;
            while(isdigit((unsigned char)expr[i])){ v = v*10 + (expr[i]-'0'); i++; }
            PushNumStack(&nums, sign*(double)v);
            printStacks(&ops, &nums, expr[i] ? expr[i] : '\0', "push number");
            prevTok = 'n';
            continue;
        }

        // 运算符/括号/结束
        if(ch=='+'||ch=='-'||ch=='*'||ch=='/'||ch=='('||ch==')'||ch=='#'){
            char rel = compare(GetCharStackTop(&ops), ch);
            if(rel=='<'){ // 进栈
                PushCharStack(&ops, ch);
                printStacks(&ops, &nums, ch, "push operator");
                if(ch!='#') i = (expr[i] ? i+1 : i);
                else        i = n; // 触发收尾
                prevTok = ch;
            }else if(rel=='='){ // 括号配对
                char dummy; PopCharStack(&ops, &dummy);
                printStacks(&ops, &nums, ch, "match () and pop");
                i++; prevTok = ')';
            }else if(rel=='>'){ // 规约
                char op; PopCharStack(&ops, &op);
                const char* err=nullptr; double r=0.0;
                if(!apply(op, &nums, r, err)){ cout << err << "\n"; return false; }
                PushNumStack(&nums, r);
                printStacks(&ops, &nums, ch, "reduce");
                // 不前进 i，让当前 ch 继续与新栈顶比较
            }else{ // '?'
                cout << "表达式错误：非法的符号或次序\n";
                return false;
            }

            if(ch=='#' && GetCharStackTop(&ops)=='#'){ char d; PopCharStack(&ops,&d); break; }
            continue;
        }

        // 其他字符
        cout << "表达式错误：出现非法字符\n";
        return false;
    }

    if(nums.top!=0){
        cout << "表达式错误：多余的数字或缺少运算符\n";
        return false;
    }
    result = GetNumStackTop(&nums);
    return true;
}

// ------------- 简单主程序（iostream 读写） -------------
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    while (true){
        cout << "\n请输入中缀表达式（回车计算，Ctrl+D 结束）：\n> ";
        if(!getline(cin, line)) break;

        double ans=0.0;
        if(evaluateInfix(line.c_str(), ans)){
            cout << "= " << (long long)llround(ans) << "\n";
        }
    }
    return 0;
}
