/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLabel *labelHint;
    QLineEdit *display;
    QVBoxLayout *layoutPolys;
    QLineEdit *lineA;
    QLineEdit *lineB;
    QHBoxLayout *layoutOps;
    QPushButton *btnAdd;
    QPushButton *btnSub;
    QPushButton *btnMulPoly;
    QPushButton *btnDerivA;
    QPushButton *btnDerivB;
    QHBoxLayout *layoutEval;
    QLabel *labelEval;
    QLineEdit *xInput;
    QPushButton *btnEvalA;
    QHBoxLayout *layoutEdit;
    QPushButton *btnEditA;
    QPushButton *btnSaveA;
    QPushButton *btnEditB;
    QPushButton *btnSaveB;
    QGridLayout *layoutKeys;
    QPushButton *btn7;
    QPushButton *btnMinus;
    QPushButton *btn1;
    QPushButton *btn4;
    QPushButton *btn3;
    QPushButton *btn5;
    QPushButton *btn8;
    QPushButton *btnBack;
    QPushButton *btn2;
    QPushButton *btnMul;
    QPushButton *btn6;
    QPushButton *btnClear;
    QPushButton *btn9;
    QPushButton *btnPow;
    QPushButton *btn0;
    QPushButton *btnDot;
    QPushButton *btnDivide;
    QPushButton *btnPlus;
    QPushButton *btnLParen;
    QPushButton *btnRParen;
    QPushButton *btnX;
    QHBoxLayout *layoutEvalExpression;
    QPushButton *btnEvalExpression;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(416, 638);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        labelHint = new QLabel(centralwidget);
        labelHint->setObjectName("labelHint");
        labelHint->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(labelHint);

        display = new QLineEdit(centralwidget);
        display->setObjectName("display");
        display->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        display->setReadOnly(true);

        verticalLayout->addWidget(display);

        layoutPolys = new QVBoxLayout();
        layoutPolys->setObjectName("layoutPolys");
        lineA = new QLineEdit(centralwidget);
        lineA->setObjectName("lineA");
        lineA->setReadOnly(true);

        layoutPolys->addWidget(lineA);

        lineB = new QLineEdit(centralwidget);
        lineB->setObjectName("lineB");
        lineB->setReadOnly(true);

        layoutPolys->addWidget(lineB);


        verticalLayout->addLayout(layoutPolys);

        layoutOps = new QHBoxLayout();
        layoutOps->setObjectName("layoutOps");
        btnAdd = new QPushButton(centralwidget);
        btnAdd->setObjectName("btnAdd");

        layoutOps->addWidget(btnAdd);

        btnSub = new QPushButton(centralwidget);
        btnSub->setObjectName("btnSub");

        layoutOps->addWidget(btnSub);

        btnMulPoly = new QPushButton(centralwidget);
        btnMulPoly->setObjectName("btnMulPoly");

        layoutOps->addWidget(btnMulPoly);

        btnDerivA = new QPushButton(centralwidget);
        btnDerivA->setObjectName("btnDerivA");

        layoutOps->addWidget(btnDerivA);

        btnDerivB = new QPushButton(centralwidget);
        btnDerivB->setObjectName("btnDerivB");

        layoutOps->addWidget(btnDerivB);


        verticalLayout->addLayout(layoutOps);

        layoutEval = new QHBoxLayout();
        layoutEval->setObjectName("layoutEval");
        labelEval = new QLabel(centralwidget);
        labelEval->setObjectName("labelEval");

        layoutEval->addWidget(labelEval);

        xInput = new QLineEdit(centralwidget);
        xInput->setObjectName("xInput");

        layoutEval->addWidget(xInput);

        btnEvalA = new QPushButton(centralwidget);
        btnEvalA->setObjectName("btnEvalA");

        layoutEval->addWidget(btnEvalA);


        verticalLayout->addLayout(layoutEval);

        layoutEdit = new QHBoxLayout();
        layoutEdit->setObjectName("layoutEdit");
        btnEditA = new QPushButton(centralwidget);
        btnEditA->setObjectName("btnEditA");

        layoutEdit->addWidget(btnEditA);

        btnSaveA = new QPushButton(centralwidget);
        btnSaveA->setObjectName("btnSaveA");

        layoutEdit->addWidget(btnSaveA);

        btnEditB = new QPushButton(centralwidget);
        btnEditB->setObjectName("btnEditB");

        layoutEdit->addWidget(btnEditB);

        btnSaveB = new QPushButton(centralwidget);
        btnSaveB->setObjectName("btnSaveB");

        layoutEdit->addWidget(btnSaveB);


        verticalLayout->addLayout(layoutEdit);

        layoutKeys = new QGridLayout();
        layoutKeys->setObjectName("layoutKeys");
        btn7 = new QPushButton(centralwidget);
        btn7->setObjectName("btn7");

        layoutKeys->addWidget(btn7, 0, 0, 1, 1);

        btnMinus = new QPushButton(centralwidget);
        btnMinus->setObjectName("btnMinus");

        layoutKeys->addWidget(btnMinus, 2, 4, 1, 1);

        btn1 = new QPushButton(centralwidget);
        btn1->setObjectName("btn1");

        layoutKeys->addWidget(btn1, 3, 0, 1, 1);

        btn4 = new QPushButton(centralwidget);
        btn4->setObjectName("btn4");

        layoutKeys->addWidget(btn4, 2, 0, 1, 1);

        btn3 = new QPushButton(centralwidget);
        btn3->setObjectName("btn3");

        layoutKeys->addWidget(btn3, 3, 2, 1, 1);

        btn5 = new QPushButton(centralwidget);
        btn5->setObjectName("btn5");

        layoutKeys->addWidget(btn5, 2, 1, 1, 1);

        btn8 = new QPushButton(centralwidget);
        btn8->setObjectName("btn8");

        layoutKeys->addWidget(btn8, 0, 1, 1, 1);

        btnBack = new QPushButton(centralwidget);
        btnBack->setObjectName("btnBack");

        layoutKeys->addWidget(btnBack, 5, 0, 1, 1);

        btn2 = new QPushButton(centralwidget);
        btn2->setObjectName("btn2");

        layoutKeys->addWidget(btn2, 3, 1, 1, 1);

        btnMul = new QPushButton(centralwidget);
        btnMul->setObjectName("btnMul");

        layoutKeys->addWidget(btnMul, 3, 4, 1, 1);

        btn6 = new QPushButton(centralwidget);
        btn6->setObjectName("btn6");

        layoutKeys->addWidget(btn6, 2, 2, 1, 1);

        btnClear = new QPushButton(centralwidget);
        btnClear->setObjectName("btnClear");

        layoutKeys->addWidget(btnClear, 5, 1, 1, 1);

        btn9 = new QPushButton(centralwidget);
        btn9->setObjectName("btn9");

        layoutKeys->addWidget(btn9, 0, 2, 1, 1);

        btnPow = new QPushButton(centralwidget);
        btnPow->setObjectName("btnPow");

        layoutKeys->addWidget(btnPow, 4, 4, 1, 1);

        btn0 = new QPushButton(centralwidget);
        btn0->setObjectName("btn0");

        layoutKeys->addWidget(btn0, 4, 1, 1, 1);

        btnDot = new QPushButton(centralwidget);
        btnDot->setObjectName("btnDot");

        layoutKeys->addWidget(btnDot, 5, 2, 1, 1);

        btnDivide = new QPushButton(centralwidget);
        btnDivide->setObjectName("btnDivide");

        layoutKeys->addWidget(btnDivide, 5, 4, 1, 1);

        btnPlus = new QPushButton(centralwidget);
        btnPlus->setObjectName("btnPlus");

        layoutKeys->addWidget(btnPlus, 0, 4, 1, 1);

        btnLParen = new QPushButton(centralwidget);
        btnLParen->setObjectName("btnLParen");

        layoutKeys->addWidget(btnLParen, 0, 5, 1, 1);

        btnRParen = new QPushButton(centralwidget);
        btnRParen->setObjectName("btnRParen");

        layoutKeys->addWidget(btnRParen, 2, 5, 1, 1);

        btnX = new QPushButton(centralwidget);
        btnX->setObjectName("btnX");

        layoutKeys->addWidget(btnX, 3, 5, 1, 1);


        verticalLayout->addLayout(layoutKeys);

        layoutEvalExpression = new QHBoxLayout();
        layoutEvalExpression->setObjectName("layoutEvalExpression");
        btnEvalExpression = new QPushButton(centralwidget);
        btnEvalExpression->setObjectName("btnEvalExpression");

        layoutEvalExpression->addWidget(btnEvalExpression);


        verticalLayout->addLayout(layoutEvalExpression);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Polynomial Calculator", nullptr));
        labelHint->setText(QCoreApplication::translate("MainWindow", "\345\244\232\351\241\271\345\274\217\344\270\216\350\241\250\350\276\276\345\274\217\346\261\202\345\200\274\350\256\241\347\256\227\345\231\250", nullptr));
        display->setPlaceholderText(QCoreApplication::translate("MainWindow", "\346\230\276\347\244\272\347\273\223\346\236\234\346\210\226\351\224\231\350\257\257\344\277\241\346\201\257", nullptr));
        lineA->setText(QCoreApplication::translate("MainWindow", "A = ", nullptr));
        lineB->setText(QCoreApplication::translate("MainWindow", "B = ", nullptr));
        btnAdd->setText(QCoreApplication::translate("MainWindow", "A + B", nullptr));
        btnSub->setText(QCoreApplication::translate("MainWindow", "A - B", nullptr));
        btnMulPoly->setText(QCoreApplication::translate("MainWindow", "A \303\227 B", nullptr));
        btnDerivA->setText(QCoreApplication::translate("MainWindow", "d(A)/dx", nullptr));
        btnDerivB->setText(QCoreApplication::translate("MainWindow", "d(B)/dx", nullptr));
        labelEval->setText(QCoreApplication::translate("MainWindow", "Eval A at x:", nullptr));
        xInput->setPlaceholderText(QCoreApplication::translate("MainWindow", "x", nullptr));
        btnEvalA->setText(QCoreApplication::translate("MainWindow", "Go", nullptr));
        btnEditA->setText(QCoreApplication::translate("MainWindow", "Edit A", nullptr));
        btnSaveA->setText(QCoreApplication::translate("MainWindow", "Save A", nullptr));
        btnEditB->setText(QCoreApplication::translate("MainWindow", "Edit B", nullptr));
        btnSaveB->setText(QCoreApplication::translate("MainWindow", "Save B", nullptr));
        btn7->setText(QCoreApplication::translate("MainWindow", "7", nullptr));
        btnMinus->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        btn1->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        btn4->setText(QCoreApplication::translate("MainWindow", "4", nullptr));
        btn3->setText(QCoreApplication::translate("MainWindow", "3", nullptr));
        btn5->setText(QCoreApplication::translate("MainWindow", "5", nullptr));
        btn8->setText(QCoreApplication::translate("MainWindow", "8", nullptr));
        btnBack->setText(QCoreApplication::translate("MainWindow", "\342\214\253", nullptr));
        btn2->setText(QCoreApplication::translate("MainWindow", "2", nullptr));
        btnMul->setText(QCoreApplication::translate("MainWindow", "*", nullptr));
        btn6->setText(QCoreApplication::translate("MainWindow", "6", nullptr));
        btnClear->setText(QCoreApplication::translate("MainWindow", "C", nullptr));
        btn9->setText(QCoreApplication::translate("MainWindow", "9", nullptr));
        btnPow->setText(QCoreApplication::translate("MainWindow", "^", nullptr));
        btn0->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        btnDot->setText(QCoreApplication::translate("MainWindow", ".", nullptr));
        btnDivide->setText(QCoreApplication::translate("MainWindow", "/", nullptr));
        btnPlus->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
        btnLParen->setText(QCoreApplication::translate("MainWindow", "(", nullptr));
        btnRParen->setText(QCoreApplication::translate("MainWindow", ")", nullptr));
        btnX->setText(QCoreApplication::translate("MainWindow", "x", nullptr));
        btnEvalExpression->setText(QCoreApplication::translate("MainWindow", "Evaluate Expression", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
