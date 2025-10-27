#include "polynomialCalc.h"
#include <string>
#include <sstream>
#include <iomanip>
#include <cctype>
#include <cstdlib>
#include <cmath>

//用于连接GUI与多项式计算器的适配器
// 实现将GUI中输入的字符串进行解析转为链表，传递至多项式求值相关函数后返回链表
//还实现了链表形式的多项式向可阅读的多项式字符串的转换


//去掉字符串里的所有空白
static std::string removeSpaces(const std::string& s) {
    std::string r; r.reserve(s.size());
    for (char ch : s) if (!std::isspace(static_cast<unsigned char>(ch))) r.push_back(ch);
    return r;
}



//把 double 变成紧凑字符串（去掉多余的0与小数点）
static std::string fmtDouble(double v) {
    std::ostringstream oss;
    oss << std::setprecision(12) << std::noshowpoint << std::defaultfloat << v;
    std::string s = oss.str();
    // 如果是科学计数或已无小数，直接返回
    if (s.find('.') == std::string::npos) return s;

    // 标准浮点：去掉尾随0和可能的点
    while (!s.empty() && s.back()=='0') s.pop_back();
    if (!s.empty() && s.back()=='.') s.pop_back();
    if (s.empty()) s = "0";
    return s;
}

// 解析一个可能带符号的小数：返回是否解析到了数字，并把光标前进
static bool parseSignedDouble(const std::string& s, size_t& i, double& out) {
    const char* start = s.c_str() + i;
    char* end = nullptr;
    // 允许直接以 + 或 - 开头；但 fromString 外层已经处理了项的总符号
    // 仅解析纯数字部分（不读 + -），所以要避免把项级符号吃掉
    // 手动检测数字开头
    if (!(std::isdigit(static_cast<unsigned char>(s[i])) || s[i]=='.')) return false;
    out = std::strtod(start, &end);
    size_t consumed = static_cast<size_t>(end - start);
    if (consumed == 0) return false;
    i += consumed;
    return true;
}

// 解析一个可能带符号的整数指数：支持可选的 + / - 号
static bool parseSignedInt(const std::string& s, size_t& i, int& out) {
    const char* start = s.c_str() + i;
    char* end = nullptr;
    long v = std::strtol(start, &end, 10);
    size_t consumed = static_cast<size_t>(end - start);
    if (consumed == 0) return false;
    i += consumed;
    out = static_cast<int>(v);
    return true;
}

// fromString：支持形如  -2.5x^3 + 7x - 1 、 x^2-1 、 -x 、 3  等，将多项式字符串解析为链表后返回其头指针
PolyNode* fromString(const std::string& src) {
    PolyNode* head = nullptr;
    const std::string s = removeSpaces(src);
    const double EPS = 1e-12;
    if (s.empty()) return head; // 视为空多项式
    size_t i = 0, n = s.size();
    while (i < n) {
        // 1) 读取项的符号
        int sign = +1;
        if (s[i] == '+') { sign = +1; ++i; }
        else if (s[i] == '-') { sign = -1; ++i; }
        // 注意：第一个项若没写符号，默认正
        // 2) 读取系数（可省略；若后面紧跟 x 则系数默认 1）
        double coef = 0.0;
        bool hasCoef = false;
        if (i < n && (std::isdigit(static_cast<unsigned char>(s[i])) || s[i]=='.')) {
            if (parseSignedDouble(s, i, coef)) hasCoef = true;
        }
        // 3) 看是否有 x / X
        bool hasX = false;
        int exp = 0;
        if (i < n && (s[i]=='x' || s[i]=='X')) {
            hasX = true;
            ++i;
            exp = 1; // 默认 x^1
            // 3.1) 看是否有 ^ 指数
            if (i < n && s[i] == '^') {
                ++i;
                // 指数允许写 +/- 号（如 x^-2），否则默认正
                int eSign = +1;
                if (i < n && (s[i]=='+' || s[i]=='-')) {
                    eSign = (s[i]=='-') ? -1 : +1;
                    ++i;
                }
                int e = 0;
                if (!parseSignedInt(s, i, e)) {
                    // 没有合法整数指数，回退为 1
                    e = 1;
                }
                exp = eSign * e;
            }
            // 若未显式给系数，则系数为 1
            if (!hasCoef) coef = 1.0;
        } else {
            // 没有 x：这就是常数项；如果也没读到数字，且不是末尾，视为输入异常——此处直接跳过该字符以避免死循环
            if (!hasCoef) {
                // 容错：跳过一个字符（避免无限循环），也可选择直接返回当前已解析内容
                ++i;
                continue;
            }
            exp = 0;
        }
        coef *= sign;
        if (std::fabs(coef) > EPS) {
            // 传给多项式计算器中的插入链表的函数，实现指数降序排列
            InsertTerm(head, coef, exp);
        }
        // 4) 下一项必须从 + 或 - 继续；如果遇到其他字符，就让循环继续处理（上面的容错会推进 i）
        if (i < n && s[i] != '+' && s[i] != '-' && s[i] != 'x' && s[i] != 'X' && !std::isdigit(static_cast<unsigned char>(s[i])) && s[i] != '.') {
            ++i; // 容错推进，防止卡死
        }
    }
    return head;
}

// toString：把链表变回如 3x^2 - 5x + 1 的形式
std::string toString(PolyNode* head) {
    if (!head) return "0";
    //创建一个输出流对象，后续将往里输入内容
    std::ostringstream out;
    const double EPS = 1e-12;
    bool first = true;
    //遍历多项式链表中的每个节点
    for (PolyNode* p = head; p; p = p->next) {
        double c = p->coef;
        int e = p->exp;
        if (std::fabs(c) <= EPS) continue;

        // 确定符号
        if (first) {
            if (c < 0) out << "-";
        } else {
            out << (c >= 0 ? " + " : " - ");
        }

        double a = std::fabs(c);

        if (e == 0) {
            // 常数项
            out << fmtDouble(a);
        } else {
            // 非常数项：系数为1时省略“1”
            if (std::fabs(a - 1.0) > 1e-12) out << fmtDouble(a);
            out << "x";
            if (e != 1) out << "^" << e;
        }

        first = false;
    }

    std::string s = out.str();
    if (s.empty()) return "0";
    return s;
}


// evaluatePolynomial：计算多项式在x处的值
double evaluatePolynomial(PolyNode* head, double x) {
    return Evaluate(head, x);  // 直接调用多项式计算器里的Evaluate函数
}



