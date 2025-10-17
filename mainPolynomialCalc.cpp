#include "polynomialCalc.h"
using namespace std;


//=============================
// 主函数
//=============================
int main() {
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
                DestroyPolynomial(C);
                C = Derivative(A);
                cout << "A'(x) = "; PrintPolynomial(C);
                break;
            case 8: {
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