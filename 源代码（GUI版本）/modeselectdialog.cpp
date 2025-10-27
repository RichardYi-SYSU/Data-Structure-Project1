#include "modeselectdialog.h"
#include "ui_modeselectdialog.h"

ModeSelectDialog::ModeSelectDialog(QWidget *parent)
    : QDialog(parent),
      ui(new Ui::ModeSelectDialog)
{
    ui->setupUi(this);
    setWindowTitle("选择计算器模式");
    setFixedSize(300, 180);

    // 信号与槽连接
    connect(ui->btnExpr, SIGNAL(clicked()), this, SLOT(chooseExpression()));
    connect(ui->btnPoly, SIGNAL(clicked()), this, SLOT(choosePolynomial()));
}

ModeSelectDialog::~ModeSelectDialog()
{
    delete ui;
}

void ModeSelectDialog::chooseExpression()
{
    selectedMode = CalcMode::Expression;
    accept(); // 关闭对话框并返回 Accepted
}

void ModeSelectDialog::choosePolynomial()
{
    selectedMode = CalcMode::Polynomial;
    accept();
}
