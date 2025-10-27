#ifndef POLYNOMIALCALC_H
#define POLYNOMIALCALC_H

#include <iostream>
#include <cmath>
#include <string>
using namespace std;

// 一元稀疏多项式链表节点定义
struct PolyNode {
    double coef;        // 系数
    int exp;            // 指数
    PolyNode* next;     // 指向下一项
};

// 基础函数
void InitPolynomial(PolyNode*& head);
void DestroyPolynomial(PolyNode*& head);
void InsertTerm(PolyNode*& head, double coef, int exp);
void CreatePolynomial(PolyNode*& head);
void PrintPolynomial(PolyNode* head);
void removeDuplicates(PolyNode* head);
PolyNode* findMid(PolyNode* A);
PolyNode* merge(PolyNode* A, PolyNode* B);
PolyNode* mergeSort(PolyNode* A);

// 多项式运算函数
PolyNode* AddPolynomial(PolyNode* A, PolyNode* B);
PolyNode* SubPolynomial(PolyNode* A, PolyNode* B);
PolyNode* MulPolynomial(PolyNode* A, PolyNode* B);
PolyNode* Derivative(PolyNode* A);
double Evaluate(PolyNode* A, double x);

// Qt GUI 适配接口
PolyNode* fromString(const std::string& s);
std::string toString(PolyNode* head);
double evaluatePolynomial(PolyNode* head, double x);


#endif // POLYNOMIALCALC_H
