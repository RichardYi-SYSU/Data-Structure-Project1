#include <iostream>
#include "polynomialCalc.h"
#include <cmath>
using namespace std;




// 初始化链表
void InitPolynomial(PolyNode*& head) {
    head = nullptr;
}
//销毁链表，避免影响后续操作及内存泄漏
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
    if (!(cin >> n) || n <= 0) {
        cerr << "输入错误：项数必须为正整数。\n";
        cin.clear(); cin.ignore(1024, '\n');
        return;
    }

    cout << "依次输入每项的系数与指数（空格分隔）：\n";
    for (int i = 0; i < n; i++) {
        double c; int e;
        if (!(cin >> c >> e)) {
            cerr << "输入错误：第 " << i + 1 << " 项数据格式错误，应为“系数 指数”。\n";
            cin.clear(); cin.ignore(1024, '\n');
            return;
        }
        InsertTerm(head, c, e);
    }
}


// 输出多项式
void PrintPolynomial(PolyNode* head) {
    if (!head) {
        cout << "0" << endl;
        cout << "输出序列：0" << endl;
        return;
    }

    // 第一行：标准格式输出
    PolyNode* p = head;
    int count = 0;
    while (p) {
        if (p->exp == 0)
            cout << p->coef;
        else
            cout << p->coef << "x^" << p->exp;

        if (p->next && p->next->coef >= 0)
            cout << " +";
        else if (p->next)
            cout << " ";
        count++;
        p = p->next;
    }
    cout << endl;

    // 第二行：整数序列输出（项数 + 系数指数）
    cout << "输出序列：" << count;
    p = head;
    while (p) {
        cout << " " << p->coef << " " << p->exp;
        p = p->next;
    }
    cout << endl;
}


// 深拷贝多项式，返回一个新链表
PolyNode* CopyPolynomial(PolyNode* src) {
    if (!src) return nullptr;
    PolyNode* newHead = nullptr;
    PolyNode* cur = nullptr;
    PolyNode* p = src;

    while (p) {
        PolyNode* node = new PolyNode();
        node->coef = p->coef;
        node->exp = p->exp;
        node->next = nullptr;

        if (!newHead) newHead = node;
        else cur->next = node;

        cur = node;
        p = p->next;
    }
    return newHead;
}





//补充排序算法（降序排列）

//找到链表中点，并断开
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
//合并两个有序链表
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

//递归实现归并排序
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


//多项式相加
PolyNode* AddPolynomial(PolyNode* A, PolyNode* B) {
    // 如果两者都为空，返回0多项式
    if (!A && !B) {
        PolyNode* node = new PolyNode{0, 0, nullptr};
        return node;
    }
    
    // 若某一方为空，则返回另一方的拷贝
    if (!A) return CopyPolynomial(B);
    if (!B) return CopyPolynomial(A);
    
    PolyNode*dum = new PolyNode();
    dum->next=nullptr;
    PolyNode*cur=dum;
    // 双指针法，按指数合并
    // 此处先调用mergeSort函数将两个多项式链表均进行按指数降序排序，方便后续计算
    PolyNode*p1=mergeSort(A);
    PolyNode*p2=mergeSort(B);
    while(p1!=nullptr&&p2!=nullptr)
    {
        //如果指数不同就单纯将两项连接
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
            //两个式子当前项的指数相同，则将系数相加，指数不变
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
    delete(dum);//及时删除，避免内存泄漏
    return ans;
}


//多项式相减
PolyNode* SubPolynomial(PolyNode* A, PolyNode* B) {
    if (!A && !B) {
        PolyNode* node = new PolyNode{0, 0, nullptr};
        return node;
    }
    if (!A) {
        // 0 - B = -B
        PolyNode* negB = nullptr;
        PolyNode* p = B;
        //此处操作为遍历多项式B，将其每一项的系数取负后放入新链表，并返回其头节点
        while (p) {
            InsertTerm(negB, -p->coef, p->exp);
            p = p->next;
        }
        return negB;
    }
    if (!B) return CopyPolynomial(A);

    PolyNode*dum=new PolyNode();
    dum->next=nullptr;
    PolyNode*cur=dum;
    PolyNode*p=B;
    //此处操作为遍历多项式B，将其每一项的系数取负后放入新链表，并返回其头节点
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
    delete(dum);//及时删除，避免内存泄漏
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


//多项式相乘
PolyNode* MulPolynomial(PolyNode* A, PolyNode* B) {
    if (!A || !B) {
        PolyNode* node=new PolyNode{0,0,nullptr};
        return node;
    }
    
    PolyNode*dum = new PolyNode();//最终返回的结果链表
    PolyNode*cur=dum;
    //先排序，保证按指数降序排列
    PolyNode*p1=mergeSort(A);
    PolyNode*p2=mergeSort(B);
    
    while(p1!=nullptr)
    {
        p2=B;
        while(p2!=nullptr)
        {
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
    //保险起见，将结果按指数降序排序下
    dum->next=mergeSort(dum->next);
    //因为采用两重循环遍历的话会出现指数相同的项，需要removeDuplicates函数来对指数相同的项进行合并
    removeDuplicates(dum);

    PolyNode*ans=dum->next;
    delete(dum);//及时删除，避免内存泄漏
    return ans;
}

//多项式求导
PolyNode* Derivative(PolyNode* A) {
    // coef*=exp; exp--; 跳过常数项
    PolyNode*dum=new PolyNode();
    dum->next=nullptr;

    PolyNode*cur=dum;
    PolyNode*p=A;
    while(p!=nullptr)
    {
        //若为常数项则跳过
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
    //若为空链表，则返回0
    if(dum->next==nullptr)
    {
        PolyNode*node=new PolyNode();
        node->coef=0;
        node->exp=0;
        node->next=nullptr;
        dum->next=node;

    }
    PolyNode*ans=dum->next;
    delete(dum);//及时删除，避免内存泄漏
    return ans;
}

//多项式在x处的值
double Evaluate(PolyNode* A, double x) {
    if (!A) {
        cerr << "错误：多项式为空，无法计算。\n";
        return NAN;
    }
    double sum = 0;
    PolyNode* p = A;
    while (p) {
        if (x == 0 && p->exp < 0) {
            cerr << "错误：x=0 时存在除零项 x^" << p->exp << "。\n";
            return NAN;
        }

        //term表示当前项在x处的值
        double term = p->coef * pow(x, p->exp);


        if (isnan(term) || isinf(term)) {
            cerr << "错误：计算溢出或非法运算。\n";
            return NAN;
        }
        sum += term;
        p = p->next;
    }
    return sum;
}

//最终的计算器命令行界面
int polynomialCalculator() {
    PolyNode* A = nullptr;
    PolyNode* B = nullptr;
    PolyNode* C = nullptr;

    int choice;
    do {
        cout << "\n===== 稀疏多项式计算器 =====\n";
        cout << "1. 创建多项式 A\n";
        cout << "2. 创建多项式 B\n";
        cout << "3. 输出多项式 A, B\n";
        cout << "4. A + B\n";
        cout << "5. A - B\n";
        cout << "6. A * B\n";
        cout << "7. 求 A 的导函数\n";
        cout << "8. 计算 A 在 x 处的值\n";
        cout << "0. 退出\n";
        cout << "请输入选项：";
        cin >> choice;

        switch (choice) {
            case 1:
                DestroyPolynomial(A);
                CreatePolynomial(A);
                break;
            case 2:
                DestroyPolynomial(B);
                CreatePolynomial(B);
                break;
            case 3:
                cout << "A(x) = "; PrintPolynomial(A);
                cout << "B(x) = "; PrintPolynomial(B);
                break;
            case 4:
                if (!A && !B) { cerr << "错误：请先创建多项式 A 与 B。\n"; break; }
                DestroyPolynomial(C);
                C = AddPolynomial(A, B);
                cout << "A + B = "; PrintPolynomial(C);
                break;
            case 5:
                DestroyPolynomial(C);
                C = SubPolynomial(A, B);
                cout << "A - B = "; PrintPolynomial(C);
                break;
            case 6:
                DestroyPolynomial(C);
                C = MulPolynomial(A, B);
                cout << "A * B = "; PrintPolynomial(C);
                break;
            case 7:
                if (!A) { cerr << "错误：多项式 A 为空，无法求导。\n"; break; }
                DestroyPolynomial(C);
                C = Derivative(A);
                cout << "A'(x) = "; PrintPolynomial(C);
                break;
            case 8: {
                if (!A) { cerr << "错误：多项式 A 为空，无法求值。\n"; break; }
                double x;
                cout << "请输入 x：";
                cin >> x;
                cout << "A(" << x << ") = " << Evaluate(A, x) << endl;
                break;
            }
            case 0:
                cout << "程序结束。\n";
                break;
            default:
                cout << "无效选项，请重新输入。\n";
        }
    } while (choice != 0);

    DestroyPolynomial(A);
    DestroyPolynomial(B);
    DestroyPolynomial(C);
    return 0;
}