#include "expressionCalc.h"
#include <iostream>
using namespace std;
int main()
{
    charStack cStack;
    numStack nStack;
    charStack*cs=&cStack;
    numStack*ns=&nStack;

    InitCharStack(cs);
    PushCharStack(cs,'#');
    InitNumStack(ns);

    // for(int i=0;i<=5;i++)
    // {
    //     PushNumStack(ns,i);
    // }

    // int temp;
    // for(int i=0;i<2;i++)
    // {
    //     PopNumStack(ns,temp);
    //     cout<<temp<<endl;
    // }





    // cout<<GetNumStackTop(ns)<<endl;

    char* str=Input();
    Print(str);
    
    return 0;

}