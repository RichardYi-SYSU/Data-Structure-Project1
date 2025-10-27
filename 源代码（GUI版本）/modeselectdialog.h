#ifndef MODESELECTDIALOG_H
#define MODESELECTDIALOG_H

#include <QDialog>

// 模式枚举
enum class CalcMode {
    None,
    Expression,
    Polynomial
};

namespace Ui {
class ModeSelectDialog;
}

class ModeSelectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ModeSelectDialog(QWidget *parent = nullptr);
    ~ModeSelectDialog();

    // 获取用户选择的模式
    CalcMode getMode() const { return selectedMode; }

private slots:
    void chooseExpression();
    void choosePolynomial();

private:
    Ui::ModeSelectDialog *ui;
    CalcMode selectedMode = CalcMode::None;
};

#endif // MODESELECTDIALOG_H
