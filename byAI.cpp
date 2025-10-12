#include <iostream>
#include <iomanip>
using namespace std;

#define MAX_SIZE 1000

struct charStack { int top; char data[MAX_SIZE]; };
struct numStack  { int top; double data[MAX_SIZE]; };

// ===== 栈操作 =====
void InitCharStack(charStack *s){ s->top=-1; memset(s->data,0,sizeof(s->data)); }
void InitNumStack (numStack  *s){ s->top=-1; memset(s->data,0,sizeof(s->data)); }

bool IsCharStackEmpty(charStack *s){ return s->top==-1; }
bool IsNumStackEmpty (numStack  *s){ return s->top==-1; }

bool PushCharStack(charStack *s,char x){ if(s->top==MAX_SIZE-1) return false; s->data[++s->top]=x; return true; }
bool PushNumStack (numStack  *s,double x){ if(s->top==MAX_SIZE-1) return false; s->data[++s->top]=x; return true; }

bool PopCharStack(charStack *s,char &x){ if(s->top==-1) return false; x=s->data[s->top--]; return true; }
bool PopNumStack (numStack  *s,double &x){ if(s->top==-1) return false; x=s->data[s->top--]; return true; }

char GetCharStackTop(charStack *s){ return (s->top==-1)? '\0' : s->data[s->top]; }
double GetNumStackTop(numStack *s){ return (s->top==-1)? NAN : s->data[s->top]; }

// ===== 运算 =====
double Operate(double b, char op, double a){
    switch(op){
        case '+': return b + a;
        case '-': return b - a;
        case '*': return b * a;
        case '/': return (a==0.0)? NAN : b / a;
        default:  return NAN;
    }
}

// ===== 输入/输出辅助 =====
char* Input(){
    char *str = new char[MAX_SIZE];
    cin.getline(str, MAX_SIZE);
    return str;
}

void Print(char* s){
    for(int i=0; s[i]!='\0'; ++i) cout<<s[i];
    cout << "\nPrintSuccess\n";
}

// 将 [begin, begin+len) 的数字串转为整数
int charToInt(char *s, int begin, int len){
    int num=0;
    for(int i=0;i<len;++i) num = num*10 + (s[begin+i]-'0');
    return num;
}

bool isOp(char c){
    return c=='+'||c=='-'||c=='*'||c=='/'||c=='('||c==')'||c=='#';
}

// 按题目给的优先级表：返回关系 '<' 进栈, '>' 规约, '=' 匹配(括号或##), '?' 非法
char Precede(char top, char cur){
    // 完整覆盖 7x7 的组合
    switch(top){
        case '+':
        case '-':
            switch(cur){
                case '+': case '-': case ')': case '#': return '>';
                case '*': case '/': case '(':          return '<';
                default: return '?';
            }
        case '*':
        case '/':
            switch(cur){
                case '(':                 return '<';
                case '+': case '-':
                case '*': case '/':
                case ')': case '#':       return '>';
                default: return '?';
            }
        case '(':
            switch(cur){
                case ')': return '=';
                case '#': return '?'; // 不应直接遇到 # 
                default:  return '<'; // 对除 ')' 外的所有符号都先入栈
            }
        case ')':
            // 栈顶不应为 ')'（规约过程中不会保留它）
            return '?';
        case '#':
            switch(cur){
                case '#': return '=';
                case ')': return '?';
                default:  return '<'; // 对 + - * / ( 皆为 <
            }
        default:
            return '?';
    }
}

double expressionCalc(char *str, charStack *cs, numStack *ns){
    // 确保输入以 # 结束：如果用户没打，就补一个
    {
        size_t L = strlen(str);
        if(L==0 || str[L-1] != '#'){
            if(L+1 < MAX_SIZE){ str[L]='#'; str[L+1]='\0'; }
        }
    }

    int i=0;
    while(str[i]!='\0'){
        char cur = str[i];

        // 忽略空白
        if(isspace(static_cast<unsigned char>(cur))){ ++i; continue; }

        if(isdigit(static_cast<unsigned char>(cur))){
            // 读取整数
            int j=i;
            while(isdigit(static_cast<unsigned char>(str[j]))) ++j;
            int val = charToInt(str,i,j-i);
            PushNumStack(ns, static_cast<double>(val));
            i = j;
            continue;
        }

        if(!isOp(cur)){
            // 非法字符：直接跳过或可报错
            ++i;
            continue;
        }

        // 运算符处理（含括号和 #）
        char topOp = GetCharStackTop(cs);
        char rel   = Precede(topOp, cur);

        if(rel=='<'){
            PushCharStack(cs, cur);
            ++i;
        }else if(rel=='='){
            char tmp; PopCharStack(cs, tmp); // 弹出 '(' 或与 '#' 匹配
            ++i;
        }else if(rel=='>'){
            // 连续规约直到不能规约
            while(true){
                char Op;  double a,b;
                PopCharStack(cs, Op);
                PopNumStack(ns, a);
                PopNumStack(ns, b);
                PushNumStack(ns, Operate(b, Op, a));
                topOp = GetCharStackTop(cs);
                rel   = Precede(topOp, cur);
                if(rel!='>') break;
            }
            // 规约完后根据关系处理当前符号
            if(rel=='<'){
                PushCharStack(cs, cur);
                ++i;
            }else if(rel=='='){
                char tmp; PopCharStack(cs, tmp); // 正确做法：弹出 '('，不应该 Push
                ++i;
            }else if(rel=='?'){
                // 非法：跳过
                ++i;
            }
        }else{ // '?'
            ++i;
        }
    }

    // 此时应已处理到字符串末尾（保证以 # 结束），数栈剩一个结果
    double ans;
    PopNumStack(ns, ans);
    return ans;
}

// ========== 示例 main ==========
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    charStack cStack; numStack nStack;
    InitCharStack(&cStack); InitNumStack(&nStack);
    PushCharStack(&cStack, '#');

    char* s = Input();
    Print(s);

    double ans = expressionCalc(s, &cStack, &nStack);
    if(std::isnan(ans)) cout << "Error\n";
    else cout << fixed << setprecision(0) << ans << "\n";

    delete [] s;
    return 0;
}
