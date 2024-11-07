/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "shvizualization.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *find_countour;
    QAction *action_zoom_in;
    QAction *action_zoom_out;
    QAction *shift_up_y;
    QAction *actionshift_down_y;
    QAction *shift_left;
    QAction *shift_right;
    QAction *Save;
    QAction *action;
    QAction *action_2;
    QAction *actionOneAreaTriang;
    QAction *actionSvg_save;
    QAction *actionCany;
    QAction *actionTesttriangCanny;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    ShVizualization *widget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QSlider *horizontalSlider;
    QLabel *label_4;
    QSpinBox *NumbContour;
    QPushButton *Shredding;
    QPushButton *Triangulation;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_5;
    QCheckBox *checkBox_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QComboBox *comboBox;
    QLabel *label;
    QSpinBox *spinBox;
    QSpacerItem *horizontalSpacer_2;
    QCheckBox *checkBox;
    QLabel *numtriang;
    QMenuBar *menubar;
    QMenu *menu;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1250, 661);
        QIcon icon;
        icon.addFile(QString::fromUtf8("resources/icon.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        find_countour = new QAction(MainWindow);
        find_countour->setObjectName(QString::fromUtf8("find_countour"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Image/resources/Font-Tonicons/SVG/Folder-2.svg"), QSize(), QIcon::Normal, QIcon::Off);
        find_countour->setIcon(icon1);
        action_zoom_in = new QAction(MainWindow);
        action_zoom_in->setObjectName(QString::fromUtf8("action_zoom_in"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Image/resources/Font-Tonicons/SVG/Zoom In.svg"), QSize(), QIcon::Normal, QIcon::Off);
        action_zoom_in->setIcon(icon2);
        action_zoom_out = new QAction(MainWindow);
        action_zoom_out->setObjectName(QString::fromUtf8("action_zoom_out"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Image/resources/Font-Tonicons/SVG/Zoom Out.svg"), QSize(), QIcon::Normal, QIcon::Off);
        action_zoom_out->setIcon(icon3);
        shift_up_y = new QAction(MainWindow);
        shift_up_y->setObjectName(QString::fromUtf8("shift_up_y"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Image/resources/Font-Tonicons/SVG/arrow-up-thick.svg"), QSize(), QIcon::Normal, QIcon::Off);
        shift_up_y->setIcon(icon4);
        actionshift_down_y = new QAction(MainWindow);
        actionshift_down_y->setObjectName(QString::fromUtf8("actionshift_down_y"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/Image/resources/Font-Tonicons/SVG/arrow-down-thick.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionshift_down_y->setIcon(icon5);
        shift_left = new QAction(MainWindow);
        shift_left->setObjectName(QString::fromUtf8("shift_left"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/Image/resources/Font-Tonicons/SVG/arrow-left-thick.svg"), QSize(), QIcon::Normal, QIcon::Off);
        shift_left->setIcon(icon6);
        shift_right = new QAction(MainWindow);
        shift_right->setObjectName(QString::fromUtf8("shift_right"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/Image/resources/Font-Tonicons/SVG/arrow-right-thick.svg"), QSize(), QIcon::Normal, QIcon::Off);
        shift_right->setIcon(icon7);
        Save = new QAction(MainWindow);
        Save->setObjectName(QString::fromUtf8("Save"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/Image/resources/Font-Tonicons/SVG/Inbox-1.svg"), QSize(), QIcon::Normal, QIcon::Off);
        Save->setIcon(icon8);
        action = new QAction(MainWindow);
        action->setObjectName(QString::fromUtf8("action"));
        action_2 = new QAction(MainWindow);
        action_2->setObjectName(QString::fromUtf8("action_2"));
        actionOneAreaTriang = new QAction(MainWindow);
        actionOneAreaTriang->setObjectName(QString::fromUtf8("actionOneAreaTriang"));
        actionSvg_save = new QAction(MainWindow);
        actionSvg_save->setObjectName(QString::fromUtf8("actionSvg_save"));
        actionCany = new QAction(MainWindow);
        actionCany->setObjectName(QString::fromUtf8("actionCany"));
        actionTesttriangCanny = new QAction(MainWindow);
        actionTesttriangCanny->setObjectName(QString::fromUtf8("actionTesttriangCanny"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        centralwidget->setMaximumSize(QSize(1920, 1080));
        centralwidget->setSizeIncrement(QSize(2, 2));
        centralwidget->setBaseSize(QSize(1920, 1080));
        centralwidget->setMouseTracking(false);
        centralwidget->setLocale(QLocale(QLocale::Russian, QLocale::Russia));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget = new ShVizualization(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));

        verticalLayout->addWidget(widget);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        horizontalSlider = new QSlider(centralwidget);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setStyleSheet(QString::fromUtf8(""));
        horizontalSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(horizontalSlider);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_2->addWidget(label_4);

        NumbContour = new QSpinBox(centralwidget);
        NumbContour->setObjectName(QString::fromUtf8("NumbContour"));
        NumbContour->setMinimum(1);
        NumbContour->setMaximum(1);

        horizontalLayout_2->addWidget(NumbContour);


        gridLayout->addLayout(horizontalLayout_2, 1, 1, 1, 1);

        Shredding = new QPushButton(centralwidget);
        Shredding->setObjectName(QString::fromUtf8("Shredding"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(Shredding->sizePolicy().hasHeightForWidth());
        Shredding->setSizePolicy(sizePolicy1);
        Shredding->setMinimumSize(QSize(130, 30));
        Shredding->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"   border: 1px solid gray;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 #dadbde, stop: 1 #f6f7fa);\n"
"}"));

        gridLayout->addWidget(Shredding, 2, 0, 1, 1);

        Triangulation = new QPushButton(centralwidget);
        Triangulation->setObjectName(QString::fromUtf8("Triangulation"));
        sizePolicy1.setHeightForWidth(Triangulation->sizePolicy().hasHeightForWidth());
        Triangulation->setSizePolicy(sizePolicy1);
        Triangulation->setMinimumSize(QSize(130, 30));
        Triangulation->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"   border: 1px solid gray;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 #dadbde, stop: 1 #f6f7fa);\n"
"}"));

        gridLayout->addWidget(Triangulation, 1, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 2, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_3->addWidget(label_5);

        checkBox_2 = new QCheckBox(centralwidget);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));

        horizontalLayout_3->addWidget(checkBox_2);


        gridLayout->addLayout(horizontalLayout_3, 2, 3, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);

        comboBox = new QComboBox(centralwidget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        horizontalLayout->addWidget(comboBox);

        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(label);

        spinBox = new QSpinBox(centralwidget);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));

        horizontalLayout->addWidget(spinBox);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        checkBox = new QCheckBox(centralwidget);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setEnabled(true);
        sizePolicy1.setHeightForWidth(checkBox->sizePolicy().hasHeightForWidth());
        checkBox->setSizePolicy(sizePolicy1);
        checkBox->setMaximumSize(QSize(130, 30));
        checkBox->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(checkBox);


        gridLayout->addLayout(horizontalLayout, 2, 1, 1, 1);

        numtriang = new QLabel(centralwidget);
        numtriang->setObjectName(QString::fromUtf8("numtriang"));
        numtriang->setStyleSheet(QString::fromUtf8("QLabel {\n"
"  qproperty-alignment: 'AlignVCenter | AlignRight';\n"
"  border: 1px solid gray;\n"
"}\n"
"\n"
"background-color : white;"));

        gridLayout->addWidget(numtriang, 1, 3, 1, 1);


        verticalLayout->addLayout(gridLayout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1250, 22));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menu->menuAction());
        menu->addAction(find_countour);
        menu->addAction(action);
        menu->addAction(action_2);
        menu->addAction(actionOneAreaTriang);
        menu->addAction(actionSvg_save);
        menu->addAction(actionCany);
        menu->addAction(actionTesttriangCanny);
        toolBar->addAction(find_countour);
        toolBar->addAction(action_zoom_in);
        toolBar->addAction(action_zoom_out);
        toolBar->addAction(shift_up_y);
        toolBar->addAction(actionshift_down_y);
        toolBar->addAction(shift_left);
        toolBar->addAction(shift_right);
        toolBar->addAction(Save);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Triangulation", nullptr));
        find_countour->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \320\272\320\276\320\275\321\202\321\203\321\200", nullptr));
        action_zoom_in->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\270\320\261\320\273\320\270\320\267\320\270\321\202\321\214", nullptr));
        action_zoom_out->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        shift_up_y->setText(QCoreApplication::translate("MainWindow", "\320\241\320\264\320\262\320\270\320\263 \320\262\320\262\320\265\321\200\321\205", nullptr));
        actionshift_down_y->setText(QCoreApplication::translate("MainWindow", "\320\241\320\264\320\262\320\270\320\263 \320\262\320\275\320\270\320\267", nullptr));
        shift_left->setText(QCoreApplication::translate("MainWindow", "\320\241\320\264\320\262\320\270\320\263 \320\262\320\273\320\265\320\262\320\276", nullptr));
        shift_right->setText(QCoreApplication::translate("MainWindow", "\320\241\320\264\320\262\320\270\320\263 \320\262\320\277\321\200\320\260\320\262\320\276", nullptr));
        Save->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
        action->setText(QCoreApplication::translate("MainWindow", "\320\242\321\200\320\270\320\260\320\275\320\263\321\203\320\273\321\217\321\206\320\270\321\217", nullptr));
        action_2->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\265\320\275\320\270\320\265 \320\275\320\276\320\262\320\276\320\271 \320\272\320\260\321\200\321\202\320\270\320\275\320\272\320\270", nullptr));
        actionOneAreaTriang->setText(QCoreApplication::translate("MainWindow", "OneAreaTriang", nullptr));
        actionSvg_save->setText(QCoreApplication::translate("MainWindow", "Svg save", nullptr));
        actionCany->setText(QCoreApplication::translate("MainWindow", "Cany ", nullptr));
        actionTesttriangCanny->setText(QCoreApplication::translate("MainWindow", "TesttriangCanny", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\320\241\321\202\320\265\320\277\320\265\320\275\321\214 \320\260\320\277\320\277\321\200\320\276\320\272\321\201\320\270\320\274\320\260\321\206\320\270\320\270", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\320\235\320\276\320\274\320\265\321\200 \320\272\320\276\320\275\321\202\321\203\321\200\320\260", nullptr));
        Shredding->setText(QCoreApplication::translate("MainWindow", "\320\230\320\267\320\274\320\265\320\273\321\214\321\207\320\265\320\275\320\270\320\265", nullptr));
        Triangulation->setText(QCoreApplication::translate("MainWindow", "\320\242\321\200\320\270\320\260\320\275\320\263\321\203\320\273\321\217\321\206\320\270\321\217", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\276\320\261\321\200\320\260\320\266\320\260\321\202\321\214 \320\262\321\201\320\265 \320\272\320\276\320\275\321\202\321\203\321\200\321\213", nullptr));
        checkBox_2->setText(QString());
        label_3->setText(QCoreApplication::translate("MainWindow", "\320\220\320\273\320\263\320\276\321\200\320\270\321\202\320\274 \321\202\321\200\320\270\320\260\320\275\321\203\320\273\321\217\321\206\320\270\321\217 \320\275\320\265\320\262\321\213\320\277\321\203\320\272\320\273\320\276\320\271 \320\276\320\261\320\273\320\260\321\201\321\202\320\270", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "\320\220\320\273\320\276\320\263\321\200\320\270\321\202\320\274 \"\320\236\321\202\321\200\320\265\320\267\320\260\320\275\320\270\320\265 \321\203\321\210\320\265\320\271\" \320\261\320\265\320\267 \320\264\320\276\320\277. \321\202\320\276\321\207\320\265\320\272", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("MainWindow", "\320\242\321\200\320\270\320\260\320\275\320\263\321\203\320\273\321\217\321\206\320\270\321\217 \320\224\320\265\320\273\320\276\320\275\320\265 \321\201 \320\276\320\263\321\200\320\260\320\275\320\270\321\207\320\265\320\275\320\270\321\217\320\274\320\270 \"\320\243\320\264\320\260\320\273\321\217\320\271-\320\270-\321\201\321\202\321\200\320\276\320\271\"", nullptr));

        label->setText(QCoreApplication::translate("MainWindow", "\320\241\321\202\320\265\320\277\320\265\320\275\321\214 \320\270\320\267\320\274\320\265\320\273\321\214\321\207\320\265\320\275\320\270\321\217", nullptr));
        checkBox->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\276\320\261\321\200\320\260\320\266\320\260\321\202\321\214 \320\272\320\276\320\275\321\202\321\203\321\200", nullptr));
        numtriang->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \321\202\321\200\320\265\321\203\320\263\320\276\320\273\321\214\320\275\320\270\320\272\320\276\320\262: 0", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\320\234\320\265\320\275\321\216", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
