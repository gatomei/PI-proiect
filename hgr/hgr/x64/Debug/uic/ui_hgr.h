/********************************************************************************
** Form generated from reading UI file 'hgr.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HGR_H
#define UI_HGR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HGR
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton;
    QComboBox *ImageCmbBox;
    QLabel *selectImglbl;
    QGraphicsView *graphicsView;
    QLabel *prediction_lbl;
    QLabel *ouput_lbl;
    QLabel *label;
    QPushButton *failure;
    QPushButton *succes;
    QLabel *label_2;
    QLabel *accuracy;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *HGR)
    {
        if (HGR->objectName().isEmpty())
            HGR->setObjectName(QString::fromUtf8("HGR"));
        HGR->resize(799, 516);
        HGR->setMaximumSize(QSize(16777215, 16777215));
        centralwidget = new QWidget(HGR);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(590, 80, 111, 41));
        pushButton->setMaximumSize(QSize(500, 500));
        QFont font;
        font.setPointSize(12);
        pushButton->setFont(font);
        ImageCmbBox = new QComboBox(centralwidget);
        ImageCmbBox->setObjectName(QString::fromUtf8("ImageCmbBox"));
        ImageCmbBox->setGeometry(QRect(60, 80, 251, 31));
        ImageCmbBox->setEditable(true);
        selectImglbl = new QLabel(centralwidget);
        selectImglbl->setObjectName(QString::fromUtf8("selectImglbl"));
        selectImglbl->setGeometry(QRect(110, 30, 171, 31));
        selectImglbl->setFont(font);
        selectImglbl->setLayoutDirection(Qt::LeftToRight);
        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(40, 130, 311, 291));
        prediction_lbl = new QLabel(centralwidget);
        prediction_lbl->setObjectName(QString::fromUtf8("prediction_lbl"));
        prediction_lbl->setGeometry(QRect(570, 230, 171, 51));
        prediction_lbl->setFont(font);
        prediction_lbl->setAlignment(Qt::AlignCenter);
        ouput_lbl = new QLabel(centralwidget);
        ouput_lbl->setObjectName(QString::fromUtf8("ouput_lbl"));
        ouput_lbl->setGeometry(QRect(580, 160, 141, 41));
        QFont font1;
        font1.setPointSize(14);
        ouput_lbl->setFont(font1);
        ouput_lbl->setAlignment(Qt::AlignCenter);
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(470, 230, 71, 31));
        label->setFont(font);
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        failure = new QPushButton(centralwidget);
        failure->setObjectName(QString::fromUtf8("failure"));
        failure->setGeometry(QRect(490, 320, 111, 41));
        succes = new QPushButton(centralwidget);
        succes->setObjectName(QString::fromUtf8("succes"));
        succes->setGeometry(QRect(620, 320, 121, 41));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(490, 390, 161, 31));
        label_2->setFont(font);
        accuracy = new QLabel(centralwidget);
        accuracy->setObjectName(QString::fromUtf8("accuracy"));
        accuracy->setGeometry(QRect(660, 390, 121, 31));
        accuracy->setFont(font1);
        HGR->setCentralWidget(centralwidget);
        menubar = new QMenuBar(HGR);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 799, 21));
        HGR->setMenuBar(menubar);
        statusbar = new QStatusBar(HGR);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        HGR->setStatusBar(statusbar);

        retranslateUi(HGR);

        QMetaObject::connectSlotsByName(HGR);
    } // setupUi

    void retranslateUi(QMainWindow *HGR)
    {
        HGR->setWindowTitle(QCoreApplication::translate("HGR", "HGR", nullptr));
        pushButton->setText(QCoreApplication::translate("HGR", "Predict", nullptr));
        selectImglbl->setText(QCoreApplication::translate("HGR", "Choose image for test", nullptr));
        prediction_lbl->setText(QString());
        ouput_lbl->setText(QCoreApplication::translate("HGR", "Output", nullptr));
        label->setText(QString());
        failure->setText(QCoreApplication::translate("HGR", "Failure", nullptr));
        succes->setText(QCoreApplication::translate("HGR", "Succes", nullptr));
        label_2->setText(QCoreApplication::translate("HGR", "Prediction Accuracy:", nullptr));
        accuracy->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class HGR: public Ui_HGR {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HGR_H
