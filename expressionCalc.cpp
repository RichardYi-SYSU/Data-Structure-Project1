#include "expressionCalc.h"

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

bool PushNumStack(numStack *s,int x)
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

bool PopNumStack(numStack *s,int &x)
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

int GetNumStackTop(numStack *s)
{
    if(s->top==-1)return '\0';
    return s->data[s->top];
}


double Operate(int b,char op,int a)
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
            if(a==0)
            {
                return '?';
            }else{
                return b/a;
            }
    }
}



//输入相关函数的实现
void Input(numStack *ns,charStack *cs)
{
    int sum=0;
    int temp1=0;
    int temp2=0;
    char temp;
    int ans=0;
    int digit=0;
    int j=0;
    int i=0;
    int len=0;
    char str[MAX_SIZE];
    //cin.getline(str,1000);
    while(i!='\0')
    {
        
        if(str[i]>='0'&&str[i]<='9')
        {
            j=i;
            len=0;
            sum=0;
            while(str[j]>='0'&&str[j]<='9')
            {
                len++;
                j++;
            }
            //转为整数并压栈
            for(;i<j;i++)
            {
                sum+=(str[i]-'0')*pow(10,len-1-i);
            }
            PushNumStack(ns,sum);
        }else
        {
            switch(str[i])
            {
                case '+':
                    switch(GetCharStackTop(cs))
                    {
                        case '+':
                            PushCharStack(cs,str[i]);
                            break;                            
                        case '-':
                            PushCharStack(cs,str[i]);
                            break;
                        case '*':
                            PopCharStack(cs,temp);
                            PopNumStack(ns,temp1);
                            PopNumStack(ns,temp2);
                            Operate(temp2,GetCharStackTop(cs),temp1);
                            PushCharStack(cs,str[i]);
                            break;
                        case '/':
                            PopCharStack(cs,temp);
                            PopNumStack(ns,temp1);
                            PopNumStack(ns,temp2);
                            if(temp1==0)
                            {
                                //出错了，考虑如何传出报错
                                return;
                            }else{
                                PushNumStack(ns,temp2/temp1);
                                PushCharStack(cs,str[i]);
                            }
                            break;
                        case '(':
                            PushCharStack(cs,str[i]);
                            break;
                        case '#':
                            PushCharStack(cs,str[i]);
                            break;
                    }
                    break;
                case '(':
                    PushCharStack(cs,str[i]);
                    break;
                case ')':
                    {
                        while(GetCharStackTop(cs)!='(')
                        {
                            PopCharStack(cs,temp);
                            PopNumStack(ns,temp1);
                            PopNumStack(ns,temp2);

                        }

                    }
                    
            }
        }
        

    }
}