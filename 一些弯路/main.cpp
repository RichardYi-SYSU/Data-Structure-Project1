#include <iostream>
using namespace std;

// 函数声明
// int expressionCalculator();
void ExpressionEvaluator();
int polynomialCalculator();

int main() {
    int choice = -1;
    while (true) {
        cout << "\n=====================================\n";
        cout << "多项式与表达式求值计算器\n";
        cout << "=====================================\n";
        cout << "1. 算术表达式求值计算器\n";
        cout << "2. 稀疏多项式计算器\n";
        cout << "0. 退出程序\n";
        cout << "-------------------------------------\n";
        cout << "请输入你的选择：";
        cin >> choice;
        cin.ignore(1024, '\n'); // 清除输入缓存，防止getline问题

        switch (choice) {
            case 1:
                ExpressionEvaluator();
                break;
            case 2:
                polynomialCalculator();
                break;
            case 0:
                cout << "感谢使用，再见！" << endl;
                return 0;
            default:
                cout << "输入无效，请重新选择。\n";
        }
    }
}
