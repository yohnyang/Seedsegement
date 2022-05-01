/********************************************************************************
** Form generated from reading UI file 'Seedseg.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEEDSEG_H
#define UI_SEEDSEG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SeedsegClass
{
public:
    QAction *open;
    QAction *saveas;
    QWidget *centralWidget;
    QLabel *imgshow;
    QTextEdit *txtout;
    QLabel *label;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QComboBox *comboBox;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QComboBox *comboBox_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *SeedsegClass)
    {
        if (SeedsegClass->objectName().isEmpty())
            SeedsegClass->setObjectName(QString::fromUtf8("SeedsegClass"));
        SeedsegClass->resize(1086, 792);
        open = new QAction(SeedsegClass);
        open->setObjectName(QString::fromUtf8("open"));
        saveas = new QAction(SeedsegClass);
        saveas->setObjectName(QString::fromUtf8("saveas"));
        centralWidget = new QWidget(SeedsegClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        imgshow = new QLabel(centralWidget);
        imgshow->setObjectName(QString::fromUtf8("imgshow"));
        imgshow->setGeometry(QRect(0, 0, 771, 621));
        imgshow->setStyleSheet(QString::fromUtf8("\n"
"background-color: rgb(110, 111, 107);"));
        txtout = new QTextEdit(centralWidget);
        txtout->setObjectName(QString::fromUtf8("txtout"));
        txtout->setGeometry(QRect(10, 660, 1071, 71));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 630, 71, 31));
        label->setStyleSheet(QString::fromUtf8("font: 9pt \"Arial\";\n"
"text-decoration: underline;\n"
"font: 14pt \"\346\245\267\344\275\223\";"));
        label->setTextFormat(Qt::AutoText);
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(810, 40, 91, 31));
        pushButton->setStyleSheet(QString::fromUtf8("font: 14pt \"\346\245\267\344\275\223\";"));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(950, 40, 91, 31));
        pushButton_2->setStyleSheet(QString::fromUtf8("font: 14pt \"\346\245\267\344\275\223\";"));
        comboBox = new QComboBox(centralWidget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(950, 110, 101, 31));
        comboBox->setStyleSheet(QString::fromUtf8("font: 14pt \"\346\245\267\344\275\223\";"));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(810, 110, 91, 31));
        label_2->setStyleSheet(QString::fromUtf8("font: 14pt \"\346\245\267\344\275\223\";"));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(770, 370, 311, 251));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(820, 170, 71, 31));
        label_4->setStyleSheet(QString::fromUtf8("font: 14pt \"\346\245\267\344\275\223\";"));
        comboBox_2 = new QComboBox(centralWidget);
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
        comboBox_2->setGeometry(QRect(950, 170, 101, 31));
        comboBox_2->setStyleSheet(QString::fromUtf8("font: 14pt \"\346\245\267\344\275\223\";"));
        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(820, 250, 91, 31));
        pushButton_3->setStyleSheet(QString::fromUtf8("font: 14pt \"\346\245\267\344\275\223\";"));
        pushButton_4 = new QPushButton(centralWidget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(950, 250, 91, 31));
        pushButton_4->setStyleSheet(QString::fromUtf8("font: 14pt \"\346\245\267\344\275\223\";"));
        SeedsegClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(SeedsegClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1086, 23));
        SeedsegClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(SeedsegClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        SeedsegClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(SeedsegClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        SeedsegClass->setStatusBar(statusBar);

        retranslateUi(SeedsegClass);

        QMetaObject::connectSlotsByName(SeedsegClass);
    } // setupUi

    void retranslateUi(QMainWindow *SeedsegClass)
    {
        SeedsegClass->setWindowTitle(QCoreApplication::translate("SeedsegClass", "Seedseg", nullptr));
        open->setText(QCoreApplication::translate("SeedsegClass", "\346\211\223\345\274\200", nullptr));
        saveas->setText(QCoreApplication::translate("SeedsegClass", "\345\217\246\345\255\230\344\270\272", nullptr));
        imgshow->setText(QString());
        label->setText(QCoreApplication::translate("SeedsegClass", "\350\276\223\345\207\272\357\274\232", nullptr));
        pushButton->setText(QCoreApplication::translate("SeedsegClass", "\346\211\223\345\274\200\345\233\276\345\203\217", nullptr));
        pushButton_2->setText(QCoreApplication::translate("SeedsegClass", "\344\277\235\345\255\230\345\233\276\345\203\217", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("SeedsegClass", "------", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("SeedsegClass", "\347\201\260\345\272\246\345\214\226", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("SeedsegClass", "\344\272\214\345\200\274\345\214\226", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("SeedsegClass", "\351\227\255\350\277\220\347\256\227", nullptr));
        comboBox->setItemText(4, QCoreApplication::translate("SeedsegClass", "\347\247\215\345\255\220\345\210\206\345\211\262", nullptr));

        label_2->setText(QCoreApplication::translate("SeedsegClass", "\347\256\227\346\263\225\345\256\236\347\216\260\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("SeedsegClass", "\345\260\217\347\252\227", nullptr));
        label_4->setText(QCoreApplication::translate("SeedsegClass", "\345\217\257\350\247\206\345\214\226\357\274\232", nullptr));
        comboBox_2->setItemText(0, QCoreApplication::translate("SeedsegClass", "------", nullptr));
        comboBox_2->setItemText(1, QCoreApplication::translate("SeedsegClass", "\345\244\226\350\275\256\345\273\223", nullptr));
        comboBox_2->setItemText(2, QCoreApplication::translate("SeedsegClass", "\345\244\226\346\216\245\347\237\251\345\275\242", nullptr));
        comboBox_2->setItemText(3, QCoreApplication::translate("SeedsegClass", "\345\207\270\345\214\205", nullptr));

        pushButton_3->setText(QCoreApplication::translate("SeedsegClass", "\350\256\241\347\256\227\347\211\271\345\276\201", nullptr));
        pushButton_4->setText(QCoreApplication::translate("SeedsegClass", "\347\247\215\345\255\220\345\210\206\347\261\273", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SeedsegClass: public Ui_SeedsegClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEEDSEG_H
