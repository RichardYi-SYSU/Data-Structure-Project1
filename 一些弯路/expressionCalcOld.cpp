#include "expressionCalc.h"
using namespace std;
//字符栈与数据栈的初始化
void InitCharStack(charStack *s)
{
    s->top=-1;
}

void InitNumStack(numStack *s)
{
    s->top=-1;
}

//判断栈空
bool IsCharStackEmpty(charStack *s)
{
    if(s->top==-1)return true;
    else return false;
}

bool IsNumStackEmpty(numStack *s)
{
    if(s->top==-1)return true;
    else return false;
}

//压栈
bool PushCharStack(charStack *s,char x)
{
    if(s->top==MAX_SIZE-1)return false;

    (s->top)++;
    s->data[s->top]=x;
    return true;
}

bool PushNumStack(numStack *s,double x)
{
    if(s->top==MAX_SIZE-1)return false;
    (s->top)++;
    s->data[s->top]=x;
    return true;
}
//弹出
bool PopCharStack(charStack *s,char &x)
{
    if(s->top==-1)return false;
    x=s->data[s->top];
    (s->top)--;
    return true;
}

bool PopNumStack(numStack *s,double &x)
{
    if(s->top==-1)return false;
    x=s->data[s->top];
    (s->top)--;
    return true;
}
//取栈顶
char GetCharStackTop(charStack *s)
{
    if(s->top==-1)return '\0';
    return s->data[s->top];
}

double GetNumStackTop(numStack *s)
{
    if(s->top==-1)return '\0';
    return s->data[s->top];
}


double Operate(double b,char op,double a)
{
    switch(op)
    {
        case '+':
            return b+a;
        case '-':
            return b-a;
        case '*':
            return b*a;
        case '/':
            // if(a==0.0)
            // {
            //     return '?';
            // }else{
            //     return b/a;
            // }
            return b/a;
    }
}





// int getNumLen(int num)
// {
//     int len=0;
//     while(num>0)
//     {
//         num/=10;
//         len++;
//     }
//     return len;
// }


//输入相关函数的实现
char* Input()
{
    char *str=new char[MAX_SIZE];//注意程序结束时delete
    cin.getline(str,MAX_SIZE);//确认能否使用getline
    return str;
}


//仅用于程序调试中使用，用于输出当前字符串
void Print(char* s)
{
    int i=0;
    while(s[i]!='\0')
    {
        cout<<s[i++];
    }
    cout<<'\n'<<"PrintSuccess"<<endl;
}


//将字符形式的整数转为int型整数
int charToInt(char *s,int begin,int len)
{
    //1314
    int num=0;
    for(int i=begin;i<begin+len;i++)
    {
        num=num*10+(s[i]-'0');
    }
    return num;
}


// //运算符优先级比较
// char Precede(char top,char cur)
// {
//     //比较栈顶运算符和当前运算符的关系，其中栈顶运算符在前
//     switch(top)
//     {
//         case '+':
//             switch(cur)
//             {
//                 case '+':
//                 case '-':
//                 case ')':
//                 case '#':return '>';
//                 case '*':
//                 case '/':
//                 case '(':return '<';
//             }
//             break;

//         case '-':
//             switch(cur)
//             {
//                 case '+':
//                 case '-':
//                 case ')':
//                 case '#':return '>';
//                 case '*':
//                 case '/':
//                 case '(':return '<';
//             }
//             break;

//         case '*':
//             switch(cur)
//             {
//                 case '+':
//                 case '-':
//                 case '*':
//                 case '/':
//                 case ')':
//                 case '#':return '>';
//                 case '(':return '<';
//             }
//             break;

//         case '/':
//             switch(cur)
//             {
//                 case '+':
//                 case '-':
//                 case '*':
//                 case '/':
//                 case ')':
//                 case '#':return '>';
//                 case '(':return '<';
//             }
//             break;
            
//         case '(':
//             switch(cur)
//             {
//                 case ')':return '=';
//                 case '#':return '?';
//                 default:return '<';
//             }
//             break;

//         case ')':
//             switch(cur)
//             {
//                 case '(':return '?';
//                 default:return '>';
//             }
//             break;

//         case '#':
//             switch(cur)
//             {
//                 case ')':return '?';
//                 default:return '<';
//             }
//     }
//     return '?';
// }




// 判断 str[i] 这个 '-' 是否是单目减
bool isUnaryMinus(char* str, int i)
{
    // 左侧找第一个“有效字符”（跳过空格）
    int p = i - 1;
    while (p >= 0 && str[p] == ' ') p--;

    // 情况1：表达式开头 -> 单目
    if (p < 0) return true;

    // 情况2：左括号后 -> 单目
    if (str[p] == '(') return true;

    // 情况3：另一个运算符后 -> 单目
    if (str[p] == '+' || str[p] == '-' || str[p] == '*' || str[p] == '/' )
        return true;

    // 其它情况视为二目减
    return false;
}


char compare(char a,char b)//a为当前元素 b为栈顶元素,当前元素优先级高于栈顶返回>,当前元素优先级低于栈顶返回<
{
   
    switch (a)
    {
        case '+':
        {
            switch(b)
            {
                case '+':
                case '-':
                case '*':
                case '/': return '<';
                //case '(': return '>';
            }
        }
        break;
        case '-':
        {
            switch(b)
            {
                case '+':
                case '-':
                case '*':
                case '/': return '<';
                //case '(': return '>';
            }
        }
        break;
        case '*':
        {
            switch(b)
            {
                case '+':
                case '-': return '>';
                case '*':
                case '/': return '<';
                //case '(': return '>';
            }
        }
        break;
        case '/':
        {
            switch(b)
            {
                case '+':
                case '-': return '>';
                case '*':
                case '/': return '<';
                //case '(': return '>';
            }
        }
        break;
        case '~':   // 单目减，最高优先级，右结合
        {
            switch(b)
            {
                // 栈顶若也是 '~'，为了右结合，这里返回 '>'（表示“当前优先级更高/不弹栈”）
                case '~': return '>';
                // 栈顶是其它任意二目运算符或括号外的比较（括号本身在 midToEnd 里单独处理）
                case '+':
                case '-':
                case '*':
                case '/': return '>';
            }
        }
        break;

    }
}




char *result=new char[MAX_SIZE];

void midToEnd(char*str,char*&result,charStack*cs)//中缀转后缀
{
    int i=0;int j=0;int numLen=0;int k=0;char tmp;
    while(str[i]!='\0')
    {
        if(str[i]>='0'&&str[i]<='9')
        {
            numLen=0;
            j=i;
            while(str[j]!='\0'&&str[j]!='#'&&str[j]!='/'&&str[j]!='*'&&str[j]!='+'&&str[j]!='-'&&str[j]!='('&&str[j]!=')')
            {
                // numLen++;
                // j++;
                result[k++]=str[j];
                j++;
            }
            // result[k++]=charToInt(str,i,numLen);
            result[k++]=' ';
            i=j;
        }
        else{
            if(str[i]=='(')
            {
                PushCharStack(cs,str[i]);
                i++;
            }else if(str[i]==')')
            {
                while(!IsCharStackEmpty(cs)&&GetCharStackTop(cs)!='(')
                {
                    result[k++]=GetCharStackTop(cs);
                    PopCharStack(cs,tmp);
                }
                PopCharStack(cs,tmp);//为了删除左括号
                i++;
            }else{
                //识别单目减,用～表示，并按最高优先级入栈
                char curOp=str[i];
                if(curOp=='-'&&isUnaryMinus(str,i))
                {
                    curOp='~';
                }

                while(!IsCharStackEmpty(cs)&&compare(str[i],GetCharStackTop(cs))=='<'&&GetCharStackTop(cs)!='(')
                {
                    result[k++]=GetCharStackTop(cs);
                    PopCharStack(cs,tmp);
                }
                PushCharStack(cs,curOp);
                i++;
            }
        }
    }
    while(!IsCharStackEmpty(cs))
    {
        result[k++]=GetCharStackTop(cs);
        PopCharStack(cs,tmp);
    }
    result[k]='\0';
    
}

double calcRPN(char *str,numStack*ns)
{
    int i=0;double tmp=0;
    while(str[i]!='\0')
    {
        if(str[i]>='0'&&str[i]<='9')
        {
            int j=i;
            int numLen=0;
            while(str[j]>='0'&&str[j]<='9')
            {
                j++;
                numLen++;
            }
            PushNumStack(ns,charToInt(str,i,numLen));
            i=j;
        }else if(str[i]==' ')
        {
            i++;
        }else{
            // 运算符
            char op = str[i];
            if(op=='~')
            {
                // 单目减：只弹出一个数
                double a;
                PopNumStack(ns,a);
                PushNumStack(ns,-a);
                i++;
            }
            else
            {
                // 二目运算：弹出 a，再弹出 b，计算 b op a
                double a,b;
                PopNumStack(ns,a);
                PopNumStack(ns,b);
                PushNumStack(ns,Operate(b,op,a));
                i++;
            }

        }
    }
    return GetNumStackTop(ns);
}









// double expressionCalc(char *str,charStack *cs,numStack *ns)
// {
//     int i=0;
//     int j=0;
//     char cur;
//     int numLen=0;
//     char topOp;
//     char relation;
//     char tmp;
//     char Op;
//     double num1=0;
//     double num2=0;
//     double ans;
    
//     while(str[i]!='\0')//后续可用#替换\0?
//     {
//         //cout<<i<<endl;
//         cur=str[i];
//         //是数字就找到数字的末位，转换成int再压栈
//         if(cur>='0'&&cur<='9')
//         {
//             numLen=0;
//             j=i;
//             while(str[j]!='\0'&&str[j]!='#'&&str[j]!='/'&&str[j]!='*'&&str[j]!='+'&&str[j]!='-'&&str[j]!='('&&str[j]!=')')
//             {
//                 numLen++;
//                 j++;
//             }
//             PushNumStack(ns,charToInt(str,i,numLen));
//             i=j;
//         }else{
//             //是运算符执行以下操作
//             topOp=GetCharStackTop(cs);
//             relation=Precede(topOp,cur);

//             if(relation=='<')
//             {
//                 PushCharStack(cs,cur);
//                 i++;
//             }else if(relation=='=')
//             {
//                 PopCharStack(cs,tmp);
//                 i++;
//             }else if(relation=='>')
//             {
//                 while(relation=='>')
//                 {
//                     PopCharStack(cs,Op);
//                     PopNumStack(ns,num2);
//                     PopNumStack(ns,num1);
//                     PushNumStack(ns,Operate(num1,Op,num2));
//                     topOp=GetCharStackTop(cs);
//                     relation=Precede(topOp,cur);
//                 }
//                 if(relation=='<')
//                 {
//                     PushCharStack(cs,cur);
//                     i++;
//                 }else if(relation=='=')
//                 {
//                     PushCharStack(cs,tmp);
//                     i++;
//                 }
//             }else{
//                 i++;
//                 //cout<<"Wrong Expression"<<endl;
//             }



//         }
       





        
//     }

//     cur = '#';
//     relation = Precede(GetCharStackTop(cs), cur);
//     while(true)
//     {
//         if(relation=='>')
//         {
//             PopCharStack(cs,Op);
//             PopNumStack(ns,num2);
//             PopNumStack(ns,num1);
//             PushNumStack(ns, Operate(num1,Op,num2));
//             relation = Precede(GetCharStackTop(cs), cur);
//         }
//         else if(relation=='=')
//         {
//             PopCharStack(cs,tmp);  // 匹配到 # #
//             break;                 // 规约完成
//         }
//         else if(relation=='<')
//         {
//             // 理论上此时不会发生（栈底已有 '#'），留作健壮性兜底
//             PushCharStack(cs,cur);
//             relation = Precede(GetCharStackTop(cs), cur);
//         }
//         else
//         {
//             // 非法关系：按“假定合法”不处理
//             break;
//         }
//     }

//     PopNumStack(ns,ans);
//     return ans;
// }



int main()
{
    charStack cStack;
    numStack nStack;
    charStack*cs=&cStack;
    numStack*ns=&nStack;

    InitCharStack(cs);
    // PushCharStack(cs,'#');
    InitNumStack(ns);

    
    
    //中缀转后缀测试
    char*str=Input();
    // Print(str);
    midToEnd(str,result,cs);
    cout<<result<<endl;
    cout<<calcRPN(result,ns)<<endl; 

    
    

    // char* str=Input();
    // Print(str);
    
    // double ans=expressionCalc(str,cs,ns);
    // cout<<ans<<endl;



    return 0;

}