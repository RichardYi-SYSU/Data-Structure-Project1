#include <QApplication>
#include "mainwindow.h"
#include "modeselectdialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ModeSelectDialog selector;
    if (selector.exec() == QDialog::Accepted)
    {
        MainWindow w;
        if (selector.getMode() == CalcMode::Expression)
            w.setModeExpression();
        else if (selector.getMode() == CalcMode::Polynomial)
            w.setModePolynomial();

        w.show();
        return a.exec();
    }
    return 0;
}
