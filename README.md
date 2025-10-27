# 算术表达式求值计算器与稀疏多项式求值计算器
> 数据结构课程Project1作业，使用C++与Qt构建

各文件用途介绍：

**用于命令行版本的文件**

- polynomialCalc.h：包含多项式计算器相关函数的头文件
- polynomialCalc.cpp：包含多项式计算器的相关函数的实现
- expressionCalc.cpp：包含表达式求值计算器的相关函数的实现
- main.cpp：包含命令行的菜单界面，指引用户选择对应计算器

**用于GUI的部分文件**

> 此部分文件位于"源代码（GUI版本）"文件夹中

- Calculator.app：Qt构建好的.app文件，点击后运行图形化计算器界面
- mainwindow.ui：计算器的界面文件
- mainwindow.cpp：计算器的界面文件的点击逻辑
- main.cpp：GUI计算器的模式选择
- expressionCalcGUI.cpp：包含适用于GUI的表达式计算器相关函数
-  poly_adapter.cpp：包含对接GUI接口的多项式求值函数的转换函数	




