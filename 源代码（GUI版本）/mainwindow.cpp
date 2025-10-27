#include "mainwindow.h"
#include "ui_mainwindow.h"



#include <QPushButton>
#include <QLineEdit>
#include <QString>
#include <QMessageBox>

// 引入多项式逻辑与适配器接口
#include "polynomialCalc.h"
#include "expressionCalc.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->display->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    ui->display->setReadOnly(true);

    wireSignals();
    updateTitle();
}

MainWindow::~MainWindow() {
    delete ui;
}

//信号绑定
void MainWindow::wireSignals()
{
    // 数字与符号输入按钮
    const QList<QPushButton*> inputBtns = {
        ui->btn0, ui->btn1, ui->btn2, ui->btn3, ui->btn4,
        ui->btn5, ui->btn6, ui->btn7, ui->btn8, ui->btn9,
        ui->btnPlus, ui->btnMinus, ui->btnMul, ui->btnPow,
        ui->btnX, ui->btnDot,
        ui->btnLParen,ui->btnRParen,
        ui->btnDivide
    };
    for (auto *b : inputBtns) {
        connect(b, SIGNAL(clicked()), this, SLOT(appendText()));
    }

    // 控制键
    connect(ui->btnClear, SIGNAL(clicked()), this, SLOT(clearText()));
    connect(ui->btnBack,  SIGNAL(clicked()), this, SLOT(backspace()));

    // A / B 编辑与保存
    connect(ui->btnEditA, SIGNAL(clicked()), this, SLOT(setEditA()));
    connect(ui->btnSaveA, SIGNAL(clicked()), this, SLOT(saveA()));
    connect(ui->btnEditB, SIGNAL(clicked()), this, SLOT(setEditB()));
    connect(ui->btnSaveB, SIGNAL(clicked()), this, SLOT(saveB()));

    // Eval A at x
    connect(ui->btnEvalA, SIGNAL(clicked()), this, SLOT(evalA()));

    // 多项式运算
    connect(ui->btnAdd,     SIGNAL(clicked()), this, SLOT(addPolynomials()));
    connect(ui->btnSub,     SIGNAL(clicked()), this, SLOT(subPolynomials()));
    connect(ui->btnMulPoly, SIGNAL(clicked()), this, SLOT(mulPolynomials()));
    connect(ui->btnDerivA,  SIGNAL(clicked()), this, SLOT(derivA()));
    connect(ui->btnDerivB,  SIGNAL(clicked()), this, SLOT(derivB()));

    // 添加表达式求值按钮连接
    connect(ui->btnEvalExpression, SIGNAL(clicked()), this, SLOT(evalExpression()));

}

//基础输入逻辑
void MainWindow::appendText()
{
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;
    QString t = btn->text().trimmed();
    inputBuffer += t;
    ui->display->setText(inputBuffer);
}

void MainWindow::clearText()
{
    inputBuffer.clear();
    ui->display->clear();
}

void MainWindow::backspace()
{
    if (!inputBuffer.isEmpty()) {
        inputBuffer.chop(1);
        ui->display->setText(inputBuffer);
    }
}


//A/B 编辑逻辑
void MainWindow::setEditA()
{
    currentTarget = EditTarget::A;
    inputBuffer = polyAString;
    ui->display->setText(inputBuffer);
    updateTitle();
}

void MainWindow::setEditB()
{
    currentTarget = EditTarget::B;
    inputBuffer = polyBString;
    ui->display->setText(inputBuffer);
    updateTitle();
}

void MainWindow::saveA()
{
    polyAString = inputBuffer;
    ui->lineA->setText("A = " + polyAString);
    currentTarget = EditTarget::None;
    ui->display->clear();
    updateTitle();
}

void MainWindow::saveB()
{
    polyBString = inputBuffer;
    ui->lineB->setText("B = " + polyBString);
    currentTarget = EditTarget::None;
    ui->display->clear();
    updateTitle();
}

//表达式求值逻辑
void MainWindow::evalExpression()
{
    QString expr = ui->display->text();  // 获取输入的表达式
    double result = EvaluateExpression(expr.toStdString());  // 调用适配器函数进行求值

    if (std::isnan(result)) {
        ui->display->setText("表达式错误！");
    } else {
        ui->display->setText(QString::number(result));
    }
}


//多项式计算逻辑
void MainWindow::evalA()
{
    if (polyAString.isEmpty()) {
        ui->display->setText("请先输入并保存多项式 A");
        return;
    }
    QString xv = ui->xInput->text();
    double x = xv.toDouble();

    PolyNode *A = fromString(polyAString.toStdString());
    double result = evaluatePolynomial(A, x);
    if(std::isnan(result))
    {
        ui->display->setText("除零错误！");
    }else{
    ui->display->setText(QString("A(%1) = %2").arg(x).arg(result));
    }
    DestroyPolynomial(A);
}

void MainWindow::addPolynomials()
{
    if (polyAString.isEmpty() || polyBString.isEmpty()) {
        ui->display->setText("请先输入并保存多项式 A 和 B");
        return;
    }
    PolyNode *A = fromString(polyAString.toStdString());
    PolyNode *B = fromString(polyBString.toStdString());
    PolyNode *C = AddPolynomial(A, B);

    QString res = QString::fromStdString(toString(C));
    ui->display->setText("A + B = " + res);

    DestroyPolynomial(A); DestroyPolynomial(B); DestroyPolynomial(C);
}

void MainWindow::subPolynomials()
{
    if (polyAString.isEmpty() || polyBString.isEmpty()) {
        ui->display->setText("请先输入并保存多项式 A 和 B");
        return;
    }
    PolyNode *A = fromString(polyAString.toStdString());
    PolyNode *B = fromString(polyBString.toStdString());
    PolyNode *C = SubPolynomial(A, B);

    QString res = QString::fromStdString(toString(C));
    ui->display->setText("A - B = " + res);

    DestroyPolynomial(A); DestroyPolynomial(B); DestroyPolynomial(C);
}

void MainWindow::mulPolynomials()
{
    if (polyAString.isEmpty() || polyBString.isEmpty()) {
        ui->display->setText("请先输入并保存多项式 A 和 B");
        return;
    }
    PolyNode *A = fromString(polyAString.toStdString());
    PolyNode *B = fromString(polyBString.toStdString());
    PolyNode *C = MulPolynomial(A, B);

    QString res = QString::fromStdString(toString(C));
    ui->display->setText("A × B = " + res);

    DestroyPolynomial(A); DestroyPolynomial(B); DestroyPolynomial(C);
}

void MainWindow::derivA()
{
    if (polyAString.isEmpty()) {
        ui->display->setText("请先输入并保存多项式 A");
        return;
    }
    PolyNode *A = fromString(polyAString.toStdString());
    PolyNode *D = Derivative(A);
    QString res = QString::fromStdString(toString(D));
    ui->display->setText("A' = " + res);
    DestroyPolynomial(A); DestroyPolynomial(D);
}

void MainWindow::derivB()
{
    if (polyBString.isEmpty()) {
        ui->display->setText("请先输入并保存多项式 B");
        return;
    }
    PolyNode *B = fromString(polyBString.toStdString());
    PolyNode *D = Derivative(B);
    QString res = QString::fromStdString(toString(D));
    ui->display->setText("B' = " + res);
    DestroyPolynomial(B); DestroyPolynomial(D);
}

//模式设置与窗口标题
void MainWindow::updateTitle()
{
    QString mode = "Ready";
    if (currentTarget == EditTarget::A)
        mode = "Editing A";
    else if (currentTarget == EditTarget::B)
        mode = "Editing B";
    setWindowTitle(QString("Polynomial Calculator — %1").arg(mode));
}

void MainWindow::setModeExpression()
{
    setWindowTitle("表达式求值计算器");
    ui->labelHint->setText("表达式求值计算器");
    // 隐藏多项式计算器控件
    ui->btnAdd->setVisible(false);
    ui->btnSub->setVisible(false);
    ui->btnMulPoly->setVisible(false);
    ui->btnDerivA->setVisible(false);
    ui->btnDerivB->setVisible(false);
    ui->xInput->setVisible(false);
    ui->btnEvalA->setVisible(false);
    ui->btnX->setVisible(false);

    ui->lineA->setVisible(false);
    ui->lineB->setVisible(false);

    ui->labelEval->setVisible(false);
    ui->xInput->setVisible(false);
    ui->btnEvalA->setVisible(false);

    ui->btnEditA->setVisible(false);
    ui->btnEditB->setVisible(false);
    ui->btnSaveB->setVisible(false);
    ui->btnSaveA->setVisible(false);

    ui->btnDot->setVisible(false);


    // 显示表达式求值所需控件（例如：输入框、求值按钮）
    ui->btnEvalExpression->setVisible(true);  // 新增的按钮
}


void MainWindow::setModePolynomial()
{
    setWindowTitle("稀疏多项式求值计算器");
    ui->labelHint->setText("稀疏多项式求值计算器");
    // 显示多项式计算器控件
    ui->btnAdd->setVisible(true);
    ui->btnSub->setVisible(true);
    ui->btnMulPoly->setVisible(true);
    ui->btnDerivA->setVisible(true);
    ui->btnDerivB->setVisible(true);
    ui->xInput->setVisible(true);
    ui->btnEvalA->setVisible(true);
    ui->btnX->setVisible(true);

    ui->btnDivide->setVisible(false);
    ui->btnRParen->setVisible(false);
    ui->btnLParen->setVisible(false);
    ui->btnMul->setVisible(false);


    // 隐藏表达式求值控件
    ui->btnEvalExpression->setVisible(false);  // 隐藏表达式求值按钮
}



