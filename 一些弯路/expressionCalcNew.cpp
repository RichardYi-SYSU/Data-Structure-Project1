// #include "expressionCalc.h"
// using namespace std;
// //字符栈与数据栈的初始化


// void InitCharStack(charStack *s)
// {
//     s->top=-1;
// }

// void InitNumStack(numStack *s)
// {
//     s->top=-1;
// }

// //判断栈空
// bool IsCharStackEmpty(charStack *s)
// {
//     if(s->top==-1)return true;
//     else return false;
// }

// bool IsNumStackEmpty(numStack *s)
// {
//     if(s->top==-1)return true;
//     else return false;
// }

// //压栈
// bool PushCharStack(charStack *s,char x)
// {
//     if(s->top==MAX_SIZE-1)return false;

//     (s->top)++;
//     s->data[s->top]=x;
//     return true;
// }

// bool PushNumStack(numStack *s,double x)
// {
//     if(s->top==MAX_SIZE-1)return false;
//     (s->top)++;
//     s->data[s->top]=x;
//     return true;
// }
// //弹出
// bool PopCharStack(charStack *s,char &x)
// {
//     if(s->top==-1)return false;
//     x=s->data[s->top];
//     (s->top)--;
//     return true;
// }

// bool PopNumStack(numStack *s,double &x)
// {
//     if(s->top==-1)return false;
//     x=s->data[s->top];
//     (s->top)--;
//     return true;
// }
// //取栈顶
// char GetCharStackTop(charStack *s)
// {
//     if(s->top==-1)return '\0';
//     return s->data[s->top];
// }

// double GetNumStackTop(numStack *s)
// {
//     if(s->top==-1)return '\0';
//     return s->data[s->top];
// }


// double Operate(double b,char op,double a)
// {
//     switch(op)
//     {
//         case '+':
//             return b+a;
//         case '-':
//             return b-a;
//         case '*':
//             return b*a;
//         case '/':
//             if(a==0.0)
//             {
//                 cerr<<"除零错误\n";
//                 exit(1);
//             }
//             return b/a;
//         case '^':
//             if(b==0.0&&a<0.0)
//             {
//                 cerr<<"除零错误\n";
//                 exit(1);
//             }
//             return pow(b,a);
//     }
//     return 0.0;
// }



// //输入相关函数的实现
// char* Input()
// {
//     char *str=new char[MAX_SIZE];//注意程序结束时delete
//     cin.getline(str,MAX_SIZE);//确认能否使用getline
//     return str;
// }


// //仅用于程序调试中使用，用于输出当前字符串
// void Print(char* s)
// {
//     int i=0;
//     while(s[i]!='\0')
//     {
//         cout<<s[i++];
//     }
//     cout<<'\n'<<"PrintSuccess"<<endl;
// }


// //将字符形式的整数转为int型整数
// int charToInt(char *s,int begin,int len)
// {
//     int num=0;
//     for(int i=begin;i<begin+len;i++)
//     {
//         num=num*10+(s[i]-'0');
//     }
//     return num;
// }

// // 判断 str[i] 这个 '-' 是否是单目减
// bool isUnaryMinus(char* str, int i)
// {
//     // 左侧找第一个“有效字符”（跳过空格）
//     int p = i - 1;
//     while (p >= 0 && str[p] == ' ') p--;

//     // 情况1：表达式开头 -> 单目
//     if (p < 0) return true;

//     // 情况2：左括号后 -> 单目
//     if (str[p] == '(') return true;

//     // 情况3：另一个运算符后 -> 单目
//     if (str[p] == '+' || str[p] == '-' || str[p] == '*' || str[p] == '/' || str[p]=='^')
//         return true;

//     // 其它情况视为二目减
//     return false;
// }

// char compare(char a,char b)//a为当前元素 b为栈顶元素,当前元素优先级高于栈顶返回>,当前元素优先级低于栈顶返回<
// {
   
//     switch (a)
//     {
//         case '+':
//         {
//             switch(b)
//             {
//                 case '+':
//                 case '-':
//                 case '*':
//                 case '/': return '<';
//                 case '^': return '<';
//                 case '~': return '<';
//             }
//         }
//         break;
//         case '-':
//         {
//             switch(b)
//             {
//                 case '+':
//                 case '-':
//                 case '*':
//                 case '/': return '<';
//                 case '^': return '<';
//                 case '~': return '<';
//             }
//         }
//         break;
//         case '*':
//         {
//             switch(b)
//             {
//                 case '+':
//                 case '-': return '>';
//                 case '*':
//                 case '/': return '<';
//                 case '^': return '<';
//                 case '~': return '<';
//             }
//         }
//         break;
//         case '/':
//         {
//             switch(b)
//             {
//                 case '+':
//                 case '-': return '>';
//                 case '*':
//                 case '/': return '<';
//                 case '^': return '<';
//                 case '~': return '<';
//             }
//         }
//         break;
//         case '^':
//         {
//             switch(b)
//             {
//                 case '^':return '>';
//                 case '~':
//                 case '*':
//                 case '/':
//                 case '+':
//                 case '-':return '>';
//             }
//         }
//         break;

//         case '~': 
//         {
//             switch(b)
//             {
//                 case '^': return '>';
//                 case '~': return '>';
//                 case '+':
//                 case '-':
//                 case '*':
//                 case '/': return '>';
//             }
//         }
//         break;

//     }
//     return '<';
// }

// char *result=new char[MAX_SIZE];

// void midToEnd(char*str,char*&result,charStack*cs)//中缀转后缀
// {
//     int i=0;int j=0;int numLen=0;int k=0;char tmp;
//     while(str[i]!='\0')
//     {
//         if(str[i]>='0'&&str[i]<='9')
//         {
//             numLen=0;
//             j=i;
//             while(str[j]!='\0'&&str[j]!='#'&&str[j]!='/'&&str[j]!='*'&&str[j]!='+'&&str[j]!='-'&&str[j]!='('&&str[j]!=')'&&str[j]!='^')
//             {
//                 result[k++]=str[j];
//                 j++;
//             }
//             result[k++]=' ';
//             i=j;
//         }
//         else{
//             if(str[i]==' ')
//             {
//                 i++;
//             }
//             else if(str[i]=='(')
//             {
//                 PushCharStack(cs,str[i]);
//                 i++;
//             }else if(str[i]==')')
//             {
//                 while(!IsCharStackEmpty(cs)&&GetCharStackTop(cs)!='(')
//                 {
//                     result[k++]=GetCharStackTop(cs);
//                     PopCharStack(cs,tmp);
//                 }
//                 if (!IsCharStackEmpty(cs) && GetCharStackTop(cs) == '(') {
//                     PopCharStack(cs, tmp); // 为了删除左括号
//                 }
//                 i++;
//             }else{
//                 char curOp=str[i];
//                 if(curOp=='-'&&isUnaryMinus(str,i))
//                 {
//                     curOp='~';
//                 }

//                 while(!IsCharStackEmpty(cs)&&compare(curOp,GetCharStackTop(cs))=='<'&&GetCharStackTop(cs)!='(')
//                 {
//                     result[k++]=GetCharStackTop(cs);
//                     PopCharStack(cs,tmp);
//                 }
//                 PushCharStack(cs,curOp);
//                 i++;
//             }
//         }
//     }
//     while(!IsCharStackEmpty(cs))
//     {
//         result[k++]=GetCharStackTop(cs);
//         PopCharStack(cs,tmp);
//     }
//     result[k]='\0';
    
// }

// double calcRPN(char *str,numStack*ns)
// {
//     int i=0;double tmp=0;
//     while(str[i]!='\0')
//     {
//         if(str[i]>='0'&&str[i]<='9')
//         {
//             int j=i;
//             int numLen=0;
//             while(str[j]>='0'&&str[j]<='9')
//             {
//                 j++;
//                 numLen++;
//             }
//             PushNumStack(ns,charToInt(str,i,numLen));
//             i=j;
//         }else if(str[i]==' ')
//         {
//             i++;
//         }else{
//             // 运算符
//             char op = str[i];
//             if(op=='~')
//             {
//                 double a;
//                 if (!PopNumStack(ns, a)) {
//                     cerr << "表达式错误\n";//传出错误信息
//                     exit(1);
//                 }
//                 PushNumStack(ns, -a);
//                 i++;
//             }
//             else
//             {
//                 double a, b;
//                 if (!PopNumStack(ns, a) || !PopNumStack(ns, b)) {
//                     cerr << "表达式错误\n";//传出错误信息
//                     exit(1);
//                 }
//                 PushNumStack(ns, Operate(b, op, a)); 
//                 i++;
//             }

//         }
//     }
//     return GetNumStackTop(ns);
// }


// int main()
// {
//     charStack cStack;
//     numStack nStack;
//     charStack*cs=&cStack;
//     numStack*ns=&nStack;

//     InitCharStack(cs);
//     InitNumStack(ns);


//     //中缀转后缀测试
//     char*str=Input();
//     // Print(str);
//     midToEnd(str,result,cs);
//     cout<<result<<endl;
//     cout<<calcRPN(result,ns)<<endl; 

//     // char* str=Input();
//     // Print(str);
    
//     // double ans=expressionCalc(str,cs,ns);
//     // cout<<ans<<endl;



//     return 0;

// }
