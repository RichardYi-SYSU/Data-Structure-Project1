/********************************************************************************
** Form generated from reading UI file 'modeselectdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODESELECTDIALOG_H
#define UI_MODESELECTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ModeSelectDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *labelTitle;
    QPushButton *btnExpr;
    QPushButton *btnPoly;

    void setupUi(QDialog *ModeSelectDialog)
    {
        if (ModeSelectDialog->objectName().isEmpty())
            ModeSelectDialog->setObjectName("ModeSelectDialog");
        ModeSelectDialog->resize(300, 180);
        verticalLayout = new QVBoxLayout(ModeSelectDialog);
        verticalLayout->setObjectName("verticalLayout");
        labelTitle = new QLabel(ModeSelectDialog);
        labelTitle->setObjectName("labelTitle");
        labelTitle->setAlignment(Qt::AlignCenter);
        QFont font;
        font.setPointSize(11);
        font.setBold(true);
        labelTitle->setFont(font);

        verticalLayout->addWidget(labelTitle);

        btnExpr = new QPushButton(ModeSelectDialog);
        btnExpr->setObjectName("btnExpr");
        btnExpr->setMinimumHeight(40);

        verticalLayout->addWidget(btnExpr);

        btnPoly = new QPushButton(ModeSelectDialog);
        btnPoly->setObjectName("btnPoly");
        btnPoly->setMinimumHeight(40);

        verticalLayout->addWidget(btnPoly);


        retranslateUi(ModeSelectDialog);

        QMetaObject::connectSlotsByName(ModeSelectDialog);
    } // setupUi

    void retranslateUi(QDialog *ModeSelectDialog)
    {
        ModeSelectDialog->setWindowTitle(QCoreApplication::translate("ModeSelectDialog", "\351\200\211\346\213\251\350\256\241\347\256\227\345\231\250\346\250\241\345\274\217", nullptr));
        labelTitle->setText(QCoreApplication::translate("ModeSelectDialog", "\350\257\267\351\200\211\346\213\251\350\246\201\344\275\277\347\224\250\347\232\204\350\256\241\347\256\227\345\231\250\346\250\241\345\274\217\357\274\232", nullptr));
        btnExpr->setText(QCoreApplication::translate("ModeSelectDialog", "\350\241\250\350\276\276\345\274\217\346\261\202\345\200\274\350\256\241\347\256\227\345\231\250", nullptr));
        btnPoly->setText(QCoreApplication::translate("ModeSelectDialog", "\347\250\200\347\226\217\345\244\232\351\241\271\345\274\217\350\256\241\347\256\227\345\231\250", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ModeSelectDialog: public Ui_ModeSelectDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODESELECTDIALOG_H
