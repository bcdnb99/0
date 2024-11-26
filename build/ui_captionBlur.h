/********************************************************************************
** Form generated from reading UI file 'captionBlur.ui'
**
** Created by: Qt User Interface Compiler version 5.12.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAPTIONBLUR_H
#define UI_CAPTIONBLUR_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_captionBlur
{
public:
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pb_start;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pb_close;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QWidget *captionBlur)
    {
        if (captionBlur->objectName().isEmpty())
            captionBlur->setObjectName(QString::fromUtf8("captionBlur"));
        captionBlur->setEnabled(true);
        captionBlur->resize(1000, 100);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(captionBlur->sizePolicy().hasHeightForWidth());
        captionBlur->setSizePolicy(sizePolicy);
        captionBlur->setMinimumSize(QSize(0, 0));
        captionBlur->setMaximumSize(QSize(111111, 111111));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/resources/manualmode.png"), QSize(), QIcon::Normal, QIcon::Off);
        captionBlur->setWindowIcon(icon);
        captionBlur->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	background-color: rgb(107, 107, 107);\n"
"	border-radius:1px;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"	background-color: rgb(150, 150, 150);\n"
"	\n"
"}\n"
"QPushButton:pressed{\n"
"	background-color: rgb(115, 183, 255);\n"
"}\n"
"\n"
"\n"
"\n"
"\n"
""));
        horizontalLayout = new QHBoxLayout(captionBlur);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 1, -1, 1);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pb_start = new QPushButton(captionBlur);
        pb_start->setObjectName(QString::fromUtf8("pb_start"));
        pb_start->setMinimumSize(QSize(100, 40));
        pb_start->setStyleSheet(QString::fromUtf8("\n"
"QPushButton{\n"
"	background-color: rgb(145, 145, 145);\n"
"	\n"
"	font: 18pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"	\n"
"	color: rgb(255, 255, 255);\n"
"	border-radius:2px;\n"
"	border-style:outset;\n"
"	border-width:2px;\n"
"	border-color:rgb(255,255,255);\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"	background-color: rgb(180, 180, 180);\n"
"	\n"
"}\n"
"QPushButton:pressed{\n"
"	background-color: rgb(115, 183, 255);\n"
"}\n"
"\n"
"\n"
"\n"
"\n"
""));

        horizontalLayout->addWidget(pb_start);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        pb_close = new QPushButton(captionBlur);
        pb_close->setObjectName(QString::fromUtf8("pb_close"));
        pb_close->setMinimumSize(QSize(100, 40));
        pb_close->setStyleSheet(QString::fromUtf8("\n"
"QPushButton{\n"
"	background-color: rgb(145, 145, 145);\n"
"	\n"
"	font: 18pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"	\n"
"	color: rgb(255, 255, 255);\n"
"	border-radius:2px;\n"
"	border-style:outset;\n"
"	border-width:2px;\n"
"	border-color:rgb(255,255,255);\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"	background-color: rgb(180, 180, 180);\n"
"	\n"
"}\n"
"QPushButton:pressed{\n"
"	background-color: rgb(115, 183, 255);\n"
"}\n"
"\n"
"\n"
"\n"
"\n"
""));

        horizontalLayout->addWidget(pb_close);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        retranslateUi(captionBlur);

        QMetaObject::connectSlotsByName(captionBlur);
    } // setupUi

    void retranslateUi(QWidget *captionBlur)
    {
        captionBlur->setWindowTitle(QApplication::translate("captionBlur", "captionBlur", nullptr));
        pb_start->setText(QApplication::translate("captionBlur", "\345\274\200\345\220\257", nullptr));
        pb_close->setText(QApplication::translate("captionBlur", "\345\205\263\351\227\255", nullptr));
    } // retranslateUi

};

namespace Ui {
    class captionBlur: public Ui_captionBlur {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAPTIONBLUR_H
