#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

const int MAX_SIZE = 10000;

// ---------------- 栈定义（保持你的风格） ----------------
typedef struct {
    int top;
    char data[MAX_SIZE];
} charStack;

typedef struct {
    int top;
    double data[MAX_SIZE];
} numStack;

void InitCharStack(charStack *s) { s->top = -1; memset(s->data, 0, sizeof(s->data)); }
void InitNumStack(numStack *s)   { s->top = -1; memset(s->data, 0, sizeof(s->data)); }

bool IsCharStackEmpty(charStack *s) { return s->top == -1; }
bool IsNumStackEmpty(numStack *s)   { return s->top == -1; }

bool PushCharStack(charStack *s, char x) {
    if (s->top == MAX_SIZE - 1) return false;
    s->data[++(s->top)] = x;
    return true;
}
bool PushNumStack(numStack *s, double x) {
    if (s->top == MAX_SIZE - 1) return false;
    s->data[++(s->top)] = x;
    return true;
}

char GetCharStackTop(charStack *s) {
    if (IsCharStackEmpty(s)) return '\0';
    return s->data[s->top];
}
double GetNumStackTop(numStack *s) {
    if (IsNumStackEmpty(s)) return 0.0;
    return s->data[s->top];
}

bool PopCharStack(charStack *s, char &x) {
    if (IsCharStackEmpty(s)) return false;
    x = s->data[(s->top)--];
    return true;
}
bool PopNumStack(numStack *s, double &x) {
    if (IsNumStackEmpty(s)) return false;
    x = s->data[(s->top)--];
    return true;
}

// ---------------- 工具函数 ----------------

// 判断 i 位置的 '-' 是否为单目减
bool isUnaryMinus(char *str, int i)
{
    int p = i - 1;
    while (p >= 0 && str[p] == ' ') p--; // 跳过空格
    if (p < 0) return true;              // 表达式开头
    if (str[p] == '(') return true;      // 左括号后
    if (str[p] == '+' || str[p] == '-' || str[p] == '*' || str[p] == '/' || str[p] == '^')
        return true;                     // 另一个运算符后
    return false;                        // 其它情况为二目减
}

// 比较当前运算符 a 与“栈顶运算符” b 的优先级关系
// 约定：返回 '<' 表示 a 的优先级低（需要先弹出 b）
//      返回 '>' 表示 a 的优先级高或等价但右结合（不弹出 b，直接压栈 a）
// 规则（从高到低）： ^  >  ~(单目减)  >  * /  >  + -
// 结合性： ^ 与 ~ 均按右结合处理（a==b 时返回 '>'）
char compare(char a, char b)
{
    switch (a)
    {
        case '+': {
            switch (b) {
                case '+':
                case '-':
                case '*':
                case '/':
                case '^': return '<';
                case '~': return '<';
            }
        } break;

        case '-': {
            switch (b) {
                case '+':
                case '-':
                case '*':
                case '/':
                case '^': return '<';
                case '~': return '<';
            }
        } break;

        case '*': {
            switch (b) {
                case '+':
                case '-': return '>';
                case '*':
                case '/': return '<';
                case '^': return '<'; // ^ 更高
                case '~': return '<'; // ~ 更高
            }
        } break;

        case '/': {
            switch (b) {
                case '+':
                case '-': return '>';
                case '*':
                case '/': return '<';
                case '^': return '<';
                case '~': return '<';
            }
        } break;

        case '^': { // 最高，右结合
            switch (b) {
                case '^': return '>'; // 右结合：不弹
                case '~':
                case '*':
                case '/':
                case '+':
                case '-': return '>'; // 当前 ^ 更高
            }
        } break;

        case '~': { // 单目减，次高，右结合
            switch (b) {
                case '^': return '<'; // ^ 比 ~ 高，先弹 ^
                case '~': return '>'; // 右结合：不弹
                case '*':
                case '/':
                case '+':
                case '-': return '>'; // ~ 比这些都高
            }
        } break;
    }
    // 保守处理：未知组合按“当前更低”
    return '<';
}

// 将从 str[i] 开始的 numLen 位十进制数转为整数
int charToInt(char* str, int i, int numLen)
{
    int v = 0;
    for (int k = 0; k < numLen; ++k) {
        v = v * 10 + (str[i + k] - '0');
    }
    return v;
}

// 二目运算
double Operate(double x, char op, double y)
{
    switch (op)
    {
        case '+': return x + y;
        case '-': return x - y;
        case '*': return x * y;
        case '/': return x / y;       // 可按需加除零检查
        case '^': return pow(x, y);   // 乘方
    }
    return 0.0;
}

// ---------------- 中缀转后缀 ----------------
void midToEnd(char* str, char*& result, charStack* cs)
{
    int i = 0, j = 0, k = 0;
    char tmp;

    while (str[i] != '\0')
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            // 扫一段连续数字
            j = i;
            while (str[j] != '\0' && str[j] != '#'
                && str[j] != '/' && str[j] != '*' && str[j] != '+' && str[j] != '-'
                && str[j] != '(' && str[j] != ')' && str[j] != '^') // 加入 '^'
            {
                result[k++] = str[j];
                j++;
            }
            result[k++] = ' '; // 数字之间用空格分隔
            i = j;
        }
        else
        {
            if (str[i] == ' ')
            {
                i++; // 忽略空格
            }
            else if (str[i] == '(')
            {
                PushCharStack(cs, str[i]);
                i++;
            }
            else if (str[i] == ')')
            {
                while (!IsCharStackEmpty(cs) && GetCharStackTop(cs) != '(')
                {
                    result[k++] = GetCharStackTop(cs);
                    PopCharStack(cs, tmp);
                }
                if (!IsCharStackEmpty(cs) && GetCharStackTop(cs) == '(') {
                    PopCharStack(cs, tmp); // 弹出 '('
                }
                i++;
            }
            else
            {
                // 处理运算符：支持 + - * / ^ 以及单目减（用 '~'）
                char curOp = str[i];

                // 单目减识别：把 '-' 替换为内部一元记号 '~'
                if (curOp == '-' && isUnaryMinus(str, i)) {
                    curOp = '~';
                }

                while (!IsCharStackEmpty(cs)
                       && compare(curOp, GetCharStackTop(cs)) == '<'
                       && GetCharStackTop(cs) != '(')
                {
                    result[k++] = GetCharStackTop(cs);
                    PopCharStack(cs, tmp);
                }
                PushCharStack(cs, curOp);
                i++;
            }
        }
    }

    while (!IsCharStackEmpty(cs))
    {
        result[k++] = GetCharStackTop(cs);
        PopCharStack(cs, tmp);
    }
    result[k] = '\0';
}

// ---------------- 计算后缀表达式 ----------------
double calcRPN(char *str, numStack* ns)
{
    int i = 0;
    while (str[i] != '\0')
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            // 把连续数字转成整数
            int j = i;
            int numLen = 0;
            while (str[j] >= '0' && str[j] <= '9') { j++; numLen++; }
            PushNumStack(ns, charToInt(str, i, numLen));
            i = j;
        }
        else if (str[i] == ' ')
        {
            i++;
        }
        else
        {
            char op = str[i];
            if (op == '~') // 单目减：只弹一个数
            {
                double a;
                if (!PopNumStack(ns, a)) {
                    cerr << "表达式错误：单目减缺少操作数\n";
                    exit(1);
                }
                PushNumStack(ns, -a);
                i++;
            }
            else // 二目运算：^ * / + -
            {
                double a, b;
                if (!PopNumStack(ns, a) || !PopNumStack(ns, b)) {
                    cerr << "表达式错误：二目运算缺少操作数\n";
                    exit(1);
                }
                PushNumStack(ns, Operate(b, op, a)); // 注意顺序：b op a
                i++;
            }
        }
    }
    return GetNumStackTop(ns);
}

// ---------------- 主程序：读入一行表达式，计算 ----------------
int main()
{
    // 读入一行中缀表达式，例如：  -(-3)^2 + 4  或  2^3^2
    // 建议：不以 '#' 结尾，直接回车结束一行即可
    static char inbuf[MAX_SIZE];
    if (!cin.getline(inbuf, MAX_SIZE)) return 0;

    // 准备栈和后缀输出缓冲区
    charStack cs;  InitCharStack(&cs);
    numStack  ns;  InitNumStack(&ns);
    // 后缀表达式缓存，数字之间以空格分隔
    char *post = new char[MAX_SIZE];
    memset(post, 0, MAX_SIZE);

    // 中缀 -> 后缀
    midToEnd(inbuf, post, &cs);

    // 计算后缀
    double ans = calcRPN(post, &ns);

    // 输出：先打印后缀（便于你肉眼核对），再打印结果
    cout << "RPN: " << post << "\n";
    cout << "Ans: " << ans << "\n";

    delete [] post;
    return 0;
}
