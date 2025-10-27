#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QPushButton;
class QLineEdit;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    void setModeExpression();
    void setModePolynomial();


private slots:
    // 输入与控制
    void appendText();
    void clearText();
    void backspace();
    //void equalClicked();

    // A/B 编辑与保存
    void setEditA();
    void saveA();
    void setEditB();
    void saveB();

    // 运算功能
    void evalA();
    void addPolynomials();
    void subPolynomials();
    void mulPolynomials();
    void derivA();
    void derivB();

    void evalExpression();

private:
    void wireSignals();
    void updateTitle();

    enum class EditTarget { None, A, B };

    Ui::MainWindow *ui = nullptr;
    EditTarget currentTarget = EditTarget::None;

    QString inputBuffer;   // 当前正在编辑/拼接的字符串
    QString polyAString;   // 暂存 A 的字符串
    QString polyBString;   // 暂存 B 的字符串
};

#endif // MAINWINDOW_H
