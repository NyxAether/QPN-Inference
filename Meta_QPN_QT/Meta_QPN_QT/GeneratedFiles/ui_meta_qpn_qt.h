/********************************************************************************
** Form generated from reading UI file 'meta_qpn_qt.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_META_QPN_QT_H
#define UI_META_QPN_QT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Meta_QPN_QTClass
{
public:
    QWidget *centralWidget;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_3;
    QPushButton *addNodeButton;
    QPushButton *addEdgeButton;
    QListView *nodeView;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Meta_QPN_QTClass)
    {
        if (Meta_QPN_QTClass->objectName().isEmpty())
            Meta_QPN_QTClass->setObjectName(QStringLiteral("Meta_QPN_QTClass"));
        Meta_QPN_QTClass->resize(436, 289);
        centralWidget = new QWidget(Meta_QPN_QTClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayoutWidget = new QWidget(centralWidget);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(0, 0, 291, 211));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        addNodeButton = new QPushButton(gridLayoutWidget);
        addNodeButton->setObjectName(QStringLiteral("addNodeButton"));

        verticalLayout_3->addWidget(addNodeButton);

        addEdgeButton = new QPushButton(gridLayoutWidget);
        addEdgeButton->setObjectName(QStringLiteral("addEdgeButton"));

        verticalLayout_3->addWidget(addEdgeButton);


        gridLayout->addLayout(verticalLayout_3, 0, 1, 1, 1);

        nodeView = new QListView(gridLayoutWidget);
        nodeView->setObjectName(QStringLiteral("nodeView"));

        gridLayout->addWidget(nodeView, 0, 0, 1, 1);

        Meta_QPN_QTClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Meta_QPN_QTClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 436, 21));
        Meta_QPN_QTClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Meta_QPN_QTClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Meta_QPN_QTClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Meta_QPN_QTClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Meta_QPN_QTClass->setStatusBar(statusBar);

        retranslateUi(Meta_QPN_QTClass);

        QMetaObject::connectSlotsByName(Meta_QPN_QTClass);
    } // setupUi

    void retranslateUi(QMainWindow *Meta_QPN_QTClass)
    {
        Meta_QPN_QTClass->setWindowTitle(QApplication::translate("Meta_QPN_QTClass", "Meta_QPN_QT", 0));
        addNodeButton->setText(QApplication::translate("Meta_QPN_QTClass", "Add node", 0));
        addEdgeButton->setText(QApplication::translate("Meta_QPN_QTClass", "Add edge", 0));
    } // retranslateUi

};

namespace Ui {
    class Meta_QPN_QTClass: public Ui_Meta_QPN_QTClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_META_QPN_QT_H
