#include <iostream>
#include <cmath>
using namespace std;

// 一元稀疏多项式链表节点定义
struct PolyNode {
    double coef;        // 系数
    int exp;            // 指数
    PolyNode* next;     // 指向下一项
};
//链表创建与删除指令
void InitPolynomial(PolyNode*& head);
void DestroyPolynomial(PolyNode*& head);
void InsertTerm(PolyNode*& head, double coef, int exp);
void CreatePolynomial(PolyNode*& head);
void PrintPolynomial(PolyNode* head);
//去重函数
void removeDuplicates(PolyNode*head);
//归并排序相关函数
PolyNode* findMid(PolyNode*A);
PolyNode* merge(PolyNode* A,PolyNode* B);
PolyNode* mergeSort(PolyNode* A);
//加减乘、求导、x值计算函数
PolyNode* AddPolynomial(PolyNode* A, PolyNode* B);
PolyNode* SubPolynomial(PolyNode* A, PolyNode* B);
PolyNode* MulPolynomial(PolyNode* A, PolyNode* B);
PolyNode* Derivative(PolyNode* A);
double Evaluate(PolyNode* A, double x);


//接入Qt GUI界面的函数，在poly_adapter.cpp中


//从字符串转换为链表
PolyNode* fromString(const std::string&s);
//从链表转换为字符串
std::string toString(PolyNode*head);