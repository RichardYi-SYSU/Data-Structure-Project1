// #include "expressionCalc.h"
// #include <cstdio>
// #include <cstring>
// #include <cmath>
// using namespace std;

// // 栈初始化
// void InitCharStack(charStack *s){ s->top=-1; }
// void InitNumStack(numStack *s){ s->top=-1; }

// // 判空 
// bool IsCharStackEmpty(charStack *s){ return s->top==-1; }
// bool IsNumStackEmpty(numStack *s){ return s->top==-1; }

// // 压栈
// bool PushCharStack(charStack *s,char x){
//     if(s->top==MAX_SIZE-1) return false;
//     s->data[++(s->top)] = x;
//     return true;
// }
// bool PushNumStack(numStack *s,double x){
//     if(s->top==MAX_SIZE-1) return false;
//     s->data[++(s->top)] = x;
//     return true;
// }

// // 弹栈
// bool PopCharStack(charStack *s,char &x){
//     if(s->top==-1) return false;
//     x = s->data[(s->top)--];
//     return true;
// }
// bool PopNumStack(numStack *s,double &x){
//     if(s->top==-1) return false;
//     x = s->data[(s->top)--];
//     return true;
// }

// // ========== 取栈顶 ==========
// char   GetCharStackTop(charStack *s){ return s->top==-1? '\0' : s->data[s->top]; }
// double GetNumStackTop (numStack  *s){ return s->top==-1? 0.0  : s->data[s->top]; }

// // ================== 计算 ==================
// double Operate(double b,char op,double a){
//     switch(op){
//         case '+': return b+a;
//         case '-': return b-a;
//         case '*': return b*a;
//         case '/':
//             if(a==0.0){cerr<<"除零错误\n";exit(1); }
//             return b/a;
//         case '^':
//             if(b==0.0 && a<0.0){ cerr<<"除零错误\n";exit(1); }
//             return pow(b,a);
//     }
//     return 0.0;
// }

// // ================== 输入 ==================
// char* Input(){
//     char *str = new char[MAX_SIZE];
//     cin.getline(str,MAX_SIZE);
//     return str;
// }

// // ================== 工具函数 ==================

// // 将 [begin, begin+len) 的十进制数字字符转为 int
// int charToInt(char *s,int begin,int len)
// {
//     int num=0;
//     for(int i=begin;i<begin+len;i++)
//     {
//         num=num*10+(s[i]-'0');
//     }
//     return num;
// }

// // 判断 str[i] 的 '-' 是否为单目减，若为单目减，则将其标记为～，方便后续计算
// bool isUnaryMinus(char* str, int i){
//     int p = i-1;
//     while(p>=0 && str[p]==' ') p--;
//     if(p<0) return true;                 // 开头
//     if(str[p]=='(') return true;         // 左括号后
//     if(str[p]=='+'||str[p]=='-'||str[p]=='*'||str[p]=='/'||str[p]=='^') return true; // 运算符后
//     return false;
// }

// // 比较：返回 '>' 表示 当前运算符优先级高于栈顶
// char compare(char a,char b){
//     switch (a){
//         case '+': case '-':
//             switch(b){
//                 case '+': case '-': case '*': case '/': case '^': case '~': return '<';//加减法优先级最低
//             }
//             break;
//         case '*': case '/':
//             switch(b){
//                 case '+': case '-': return '>';//乘除法优先级比加减法高
//                 case '*': case '/': case '^': case '~': return '<';
//             }
//             break;
//         case '^':
//             switch(b){
//                 case '^': return '>';     // 乘方为左结合，优先级高于加减乘除
//                 case '~':
//                 case '*': case '/': case '+': case '-': return '>';
//             }
//             break;
//         case '~': // 单目减，优先级最高，右结合
//             switch(b){
//                 case '^': return '>';
//                 case '~': return '>';
//                 case '+': case '-': case '*': case '/': return '>';
//             }
//             break;
//     }
//     return '<';
// }

// // ========== 仿真输出相关（新增） ==========

// static const int COLW = 22;
// //用于打印当前的运算符栈
// void printCharStackLine(charStack* cs, const char* title){
//     cout << left << setw(COLW) << title << "| ";
//     if(IsCharStackEmpty(cs)){
        
//     }else{
//         for(int i=0;i<=cs->top;i++){
//             char c = cs->data[i];
//             cout << (c==0? ' ' : c);
//         }
//     }
// }
// //用于打印当前的运算数栈
// void printNumStackLine(numStack* ns, const char* title){
//     cout << left << setw(COLW) << title << "| ";
//     if(IsNumStackEmpty(ns)){
//         // cout << "#";
//     }else{
//         for(int i=0;i<=ns->top;i++){
//             //long long iv = static_cast<long long>(ns->data[i]);
//             cout << ns->data[i];
//             if(i<ns->top) cout << ' ';
//         }
//     }
// }

// // 打印当前已生成的后缀串（前 k 个字符）
// void printRPNPrefix(const char* rpn, int k, const char* title){
//     cout << left << setw(COLW) << title << "| ";
//     if(k<=0) cout << '#';
//     else{
//         for(int i=0;i<k;i++) cout << rpn[i];
//     }
// }

// // 转换阶段的一行：运算符栈 + “输出队列(后缀前缀)” + 当前输入 + 操作
// void log_step_conv(charStack* cs, const char* rpn, int k, char inCh, const char* action){
//     printCharStackLine(cs, "运算符栈");
//     cout << "  " << left << setw(COLW) << "输出(后缀)" << "| ";
//     if(k<=0) cout << '#';
//     else{
//         for(int i=0;i<k;i++) cout << rpn[i];
//     }
//     cout << "  " << left << setw(COLW) << "输入字符" << "| ";
//     if(inCh!='\0')cout<<inCh;
//     cout << "  " << action << endl;
// }


// // 计算阶段的一行：运算数栈 + 当前后缀记号 + 操作
// void log_step_eval(numStack* ns, const char* token, const char* action){
//     printNumStackLine(ns, "运算数栈");
//     cout << "  " << left << setw(COLW) << "读入记号" << "| ";
//     if(token && token[0]) cout << token;
//     cout << "  " << action << endl;
// }


// // result字符串用于存放后缀表达式
// char *result = new char[MAX_SIZE];

// // 中缀表达式转后缀表达式，同时打印输出
// void midToEnd(char*str,char*&result,charStack*cs){
//     int i=0, j=0, numLen=0, k=0;
//     char tmp;

//     // 开始前打一行说明
//     cout << "------------------------------------------------------------\n";
//     cout << left << setw(COLW) << "运算符栈" << "|  "
//      << left << setw(COLW) << "输出(后缀)" << "|  "
//      << left << setw(COLW) << "输入字符"   << "|  主要操作\n";
//     cout << "------------------------------------------------------------\n";


//     while(str[i]!='\0'){
//         if(str[i]>='0'&&str[i]<='9'){
//             // 识别一个整数并写入后缀串（末尾加空格）
//             j=i; numLen=0;
//             while(str[j]>='0'&&str[j]<='9'){ j++; numLen++; }
//             // 写数字
//             for(int t=i;t<j;t++) result[k++] = str[t];
//             result[k++]=' ';

//             log_step_conv(cs, result, k, str[i], "识别到数字，继续扫描至该整数末位并识别为整数写入后缀");

//             i=j;
//         }else{
//             if(str[i]==' '){ i++; continue; }

//             if(str[i]=='('){
//                 PushCharStack(cs,str[i]);
//                 log_step_conv(cs, result, k, str[i], "左括号入栈");
//                 i++;
//             }else if(str[i]==')'){
//                 // 退栈至 '('
//                 while(!IsCharStackEmpty(cs)&&GetCharStackTop(cs)!='('){
//                     result[k++]=GetCharStackTop(cs);
//                     PopCharStack(cs,tmp);
//                 }
//                 if(!IsCharStackEmpty(cs) && GetCharStackTop(cs)=='('){
//                     PopCharStack(cs,tmp); // 丢弃 '('
//                 }
//                 log_step_conv(cs, result, k, str[i], "遇右括号，弹出至'('");
//                 i++;
//             }else{
//                 // 一般运算符（含单目减记号）
//                 char curOp=str[i];
//                 if(curOp=='-'&&isUnaryMinus(str,i)) curOp='~';

//                 // 弹出优先级更高/相等且不是 '(' 的栈顶运算符
//                 while(!IsCharStackEmpty(cs) && compare(curOp,GetCharStackTop(cs))=='<' && GetCharStackTop(cs)!='('){
//                     result[k++]=GetCharStackTop(cs);
//                     PopCharStack(cs,tmp);
//                 }
//                 PushCharStack(cs,curOp);
//                 log_step_conv(cs, result, k, str[i], "运算符入栈/必要时弹出");
//                 i++;
//             }
//         }
//     }
//     // 把剩余栈中运算符依次输出
//     while(!IsCharStackEmpty(cs)){
//         result[k++]=GetCharStackTop(cs);
//         PopCharStack(cs,tmp);
//         log_step_conv(cs, result, k, '\0', "清空栈到后缀");
//     }
//     result[k]='\0';

//     cout << "------------------------------------------------------------\n";
//     cout << "后缀表达式：" << result << '\n';
//     cout << "============================================================\n";
// }

// // ================== 计算后缀（带仿真打印） ==================
// double calcRPN(char *str,numStack*ns){
//     int i=0;
//     char tokenBuf[64];

//     cout << left << setw(COLW) << "运算数栈" << "|  "
//          << left << setw(COLW) << "读入记号" << "|  主要操作\n";
//     cout << "------------------------------------------------------------\n";


//     while(str[i]!='\0'){
//         if(str[i]>='0'&&str[i]<='9'){
//             int j=i, numLen=0;
//             while(str[j]>='0'&&str[j]<='9'){ j++; numLen++; }
//             double val = (double)charToInt(str,i,numLen);
//             PushNumStack(ns,val);

//             // 记录记号并打印
//             int t=0; for(int p=i;p<j && t<60;p++) tokenBuf[t++]=str[p]; tokenBuf[t]='\0';
//             log_step_eval(ns, tokenBuf, "数字入栈");

//             i=j;
//         }else if(str[i]==' '){
//             i++;
//         }else{
//             // 运算符
//             char op = str[i];
//             if(op=='~'){
//                 double a;
//                 if(!PopNumStack(ns,a)){ fprintf(stderr,"表达式错误\n"); exit(1); }
//                 PushNumStack(ns,-a);
//                 tokenBuf[0]='~'; tokenBuf[1]='\0';
//                 log_step_eval(ns, tokenBuf, "单目减：取反并入栈");
//                 i++;
//             }else{
//                 double a,b;
//                 if(!PopNumStack(ns,a) || !PopNumStack(ns,b)){ fprintf(stderr,"表达式错误\n"); exit(1); }
//                 double r = Operate(b,op,a);
//                 PushNumStack(ns,r);
//                 tokenBuf[0]=op; tokenBuf[1]='\0';
//                 log_step_eval(ns, tokenBuf, "二目运算：出栈计算入栈");
//                 i++;
//             }
//         }
//     }

//     cout << "------------------------------------------------------------\n";
//     return GetNumStackTop(ns);
// }

// // ================== 主函数 ==================
// int expressionCalculator(){
//     charStack cStack;  numStack nStack;
//     charStack* cs=&cStack;  numStack* ns=&nStack;
//     InitCharStack(cs); InitNumStack(ns);

//     // 标题（可按需调整）
//     cout<<"请输入一个整数算术表达式：\n";

//     char* str = Input();          // 读入一整行

//     // 阶段1：中缀→后缀（含逐步打印）
//     midToEnd(str,result,cs);

//     // 阶段2：后缀求值（含逐步打印）
//     double ans = calcRPN(result,ns);

//     // 结果
//     cout<<"结果："<<ans<<endl;

//     delete [] str;
//     return 0;
// }
