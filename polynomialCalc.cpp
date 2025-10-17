#include <iostream>
#include "polynomialCalc.h"
#include <cmath>
using namespace std;




// 函数实现部分
void InitPolynomial(PolyNode*& head) {
    head = nullptr;
}

void DestroyPolynomial(PolyNode*& head) {
    PolyNode* p = head;
    while (p != nullptr) {
        PolyNode* temp = p;
        p = p->next;
        delete temp;
    }
    head = nullptr;
}

// 按指数降序插入新项
void InsertTerm(PolyNode*& head, double coef, int exp) {
    if (fabs(coef) < 1e-8) return;

    PolyNode* prev = nullptr;
    PolyNode* curr = head;

    // 找到插入位置
    while (curr && curr->exp > exp) {
        prev = curr;
        curr = curr->next;
    }

    if (curr && curr->exp == exp) {
        // 同指数项合并
        curr->coef += coef;
        if (fabs(curr->coef) < 1e-8) {
            // 删除该节点
            if (prev) prev->next = curr->next;
            else head = curr->next;
            delete curr;
        }
    } else {
        // 创建新节点
        PolyNode* node = new PolyNode;
        node->coef = coef;
        node->exp = exp;
        node->next = curr;

        if (prev) prev->next = node;
        else head = node;
    }
}

// 创建多项式
void CreatePolynomial(PolyNode*& head) {
    int n;
    cout << "请输入多项式项数：";
    cin >> n;
    cout << "依次输入每项的系数与指数（空格分隔）：\n";
    for (int i = 0; i < n; i++) {
        double c; int e;
        cin >> c >> e;
        InsertTerm(head, c, e);
    }
}

// 输出多项式
void PrintPolynomial(PolyNode* head) {
    if (!head) {
        cout << "0" << endl;
        return;
    }
    PolyNode* p = head;
    while (p) {
        if(p->exp==0)
        {
            cout<<p->coef;
        }else{
        cout << p->coef << "x^" << p->exp;
        }
        if (p->next && p->next->coef >= 0)
            cout << " +";
        else if (p->next)
            cout << " ";
        p = p->next;
    }
    cout << endl;
}

//补充排序算法（降序排列）


PolyNode* findMid(PolyNode*A)
{
    if(A==nullptr||A->next==nullptr)
    {
        return A;
    }
    PolyNode*slow=A;
    PolyNode*fast=A;
    PolyNode*pre=nullptr;
    while(fast!=nullptr&&fast->next!=nullptr)
    {
        pre=slow;
        slow=slow->next;
        fast=fast->next->next;
    }
    pre->next=nullptr;
    return slow;

}

PolyNode* merge(PolyNode* A,PolyNode* B)
{
    PolyNode*dum=new PolyNode();
    dum->next=nullptr;
    PolyNode*cur=dum;
    PolyNode*p1=A;
    PolyNode*p2=B;

    while(p1!=nullptr&&p2!=nullptr)
    {
        if((p1->exp)>(p2->exp))
        {
            cur->next=p1;
            p1=p1->next;
            cur=cur->next;
        }else{
            cur->next=p2;
            p2=p2->next;
            cur=cur->next;
        }
    }
    if(p1==nullptr)
    {
        cur->next=p2;
    }
    if(p2==nullptr)
    {
        cur->next=p1;
    }
    PolyNode *ans=dum->next;
    delete(dum);
    return ans;
}



PolyNode* mergeSort(PolyNode* A)
{
    if(A==nullptr||A->next==nullptr)
    {
        return A;
    }
    
    PolyNode*mid=findMid(A);
    
    PolyNode*left=mergeSort(A);
    PolyNode*right=mergeSort(mid);

    return merge(left,right);
}











// 以下为算法函数接口（供你自己实现）
PolyNode* AddPolynomial(PolyNode* A, PolyNode* B) {
    PolyNode*dum = new PolyNode();
    dum->next=nullptr;
    PolyNode*cur=dum;
    // TODO: 双指针法，按指数合并
    PolyNode*p1=mergeSort(A);
    PolyNode*p2=mergeSort(B);
    while(p1!=nullptr&&p2!=nullptr)
    {
        if((p1->exp)>(p2->exp))
        {
            PolyNode* node=new PolyNode();
            node->coef=p1->coef;
            node->exp=p1->exp;
            node->next=nullptr;
            cur->next=node;
            cur=cur->next;
            p1=p1->next;

        }else if((p1->exp)<(p2->exp))
        {
            PolyNode* node=new PolyNode();
            node->coef=p2->coef;
            node->exp=p2->exp;
            node->next=nullptr;
            cur->next=node;
            cur=cur->next;
            p2=p2->next;
        }else{
            //两个式子当前项的指数相同
            double sum=p1->coef+p2->coef;
            if(fabs(sum)>1e-8)
            {
                PolyNode*node=new PolyNode();
                node->coef=sum;
                node->exp=p1->exp;
                node->next=nullptr;
                cur->next=node;
                cur=cur->next;
            }
            p1=p1->next;
            p2=p2->next;
        }
        
        
    }
    //连接剩下的链表
    while(p1!=nullptr)
    {
        PolyNode*node=new PolyNode();
        node->coef=p1->coef;
        node->exp=p1->exp;
        node->next=nullptr;
        cur->next=node;
        cur=cur->next;
        p1=p1->next;
    }
    while(p2!=nullptr)
    {
        PolyNode*node=new PolyNode();
        node->coef=p2->coef;
        node->exp=p2->exp;
        node->next=nullptr;
        cur->next=node;
        cur=cur->next;
        p2=p2->next;
    }

    PolyNode*ans=dum->next;
    delete(dum);
    return ans;
}

PolyNode* SubPolynomial(PolyNode* A, PolyNode* B) {
    PolyNode*dum=new PolyNode();
    dum->next=nullptr;
    PolyNode*cur=dum;
    PolyNode*p=B;
    while(p!=nullptr)
    {
        PolyNode*node=new PolyNode();
        node->coef=-p->coef;
        node->exp=p->exp;
        node->next=nullptr;
        cur->next=node;
        cur=cur->next;
        p=p->next;

    }
    PolyNode*ans=dum->next;
    delete(dum);
    return AddPolynomial(A,ans);
   

}



//链表去重，对原链表进行操作
//在原来的指数降序排列的链表中将相同指数的累加在一起
void removeDuplicates(PolyNode*head)//head为头节点
{
    PolyNode*dum=head;
    PolyNode*cur=dum->next;
    PolyNode*tmp=nullptr;
    while(cur->next!=nullptr&&cur!=nullptr)
    {
        if(cur->next->exp==cur->exp)
        {
            cur->coef+=cur->next->coef;
            tmp=cur->next;
            cur->next=tmp->next;
            delete(tmp);
        }else{
            cur=cur->next;
        }
    }
}





PolyNode* MulPolynomial(PolyNode* A, PolyNode* B) {
    PolyNode*dum = new PolyNode();//最终返回的结果链表
    PolyNode*temp=new PolyNode();//每次循环中使用的暂存链表
    PolyNode*cur=dum;


    
    PolyNode*p1=mergeSort(A);
    PolyNode*p2=mergeSort(B);
    
    while(p1!=nullptr)
    {
        p2=B;
        while(p2!=nullptr)
        {
            //在暂存链表后增加一个新节点，并初始化
            PolyNode*node=new PolyNode();
            node->coef=p1->coef*p2->coef;
            node->exp=p1->exp+p2->exp;
            node->next=nullptr;
            
            cur->next=node;
            cur=cur->next;
        

            p2=p2->next;//p2步进
        }
        

        p1=p1->next;//p1步进

    }

    dum->next=mergeSort(dum->next);
    removeDuplicates(dum);

    PolyNode*ans=dum->next;
    delete(dum);
    return ans;
}

PolyNode* Derivative(PolyNode* A) {
    // TODO: coef*=exp; exp--; 跳过常数项
    PolyNode*dum=new PolyNode();
    dum->next=nullptr;

    PolyNode*cur=dum;
    PolyNode*p=A;
    while(p!=nullptr)
    {
        if(p->exp==0)
        {
            p=p->next;
        }else{
            PolyNode*node=new PolyNode();
            node->coef=p->exp*p->coef;
            node->exp=p->exp-1;
            node->next=nullptr;
            cur->next=node;
            cur=cur->next;
            p=p->next;
        }
    }

    if(dum->next==nullptr)
    {
        PolyNode*node=new PolyNode();
        node->coef=0;
        node->exp=0;
        node->next=nullptr;
        dum->next=node;

    }
    PolyNode*ans=dum->next;
    delete(dum);
    return ans;
}

double Evaluate(PolyNode* A, double x) {
    double sum = 0;
    PolyNode* p = A;
    while (p) {

        sum+=p->coef*pow(x,p->exp);
        p = p->next;
    }
    return sum;
}


