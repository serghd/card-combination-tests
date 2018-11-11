/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_MainWindowUi
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QGroupBox *gbTableCards;
    QGroupBox *gbPlayerCards;
    QGroupBox *gbGameTypes;
    QVBoxLayout *verticalLayout_2;
    QRadioButton *rbTexasHoldem;
    QRadioButton *rbOmaha;
    QGroupBox *gbActions;
    QVBoxLayout *verticalLayout_5;
    QPushButton *btnApply;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btnCancel;
    QPushButton *btnLog;
    QVBoxLayout *verticalLayout_4;
    QLabel *lblCardsCombination;
    QVBoxLayout *ltDeck;
    QSpacerItem *verticalSpacer;
    QButtonGroup *bgGameTypes;

    void setupUi(QDialog *MainWindowUi)
    {
        if (MainWindowUi->objectName().isEmpty())
            MainWindowUi->setObjectName(QStringLiteral("MainWindowUi"));
        MainWindowUi->setMinimumSize(QSize(770, 450));
        MainWindowUi->setMaximumSize(QSize(770, 450));
        verticalLayout = new QVBoxLayout(MainWindowUi);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        gbTableCards = new QGroupBox(MainWindowUi);
        gbTableCards->setObjectName(QStringLiteral("gbTableCards"));
        gbTableCards->setMinimumSize(QSize(220, 100));
        gbTableCards->setMaximumSize(QSize(220, 100));

        horizontalLayout->addWidget(gbTableCards);

        gbPlayerCards = new QGroupBox(MainWindowUi);
        gbPlayerCards->setObjectName(QStringLiteral("gbPlayerCards"));
        gbPlayerCards->setMinimumSize(QSize(176, 100));
        gbPlayerCards->setMaximumSize(QSize(176, 100));

        horizontalLayout->addWidget(gbPlayerCards);

        gbGameTypes = new QGroupBox(MainWindowUi);
        gbGameTypes->setObjectName(QStringLiteral("gbGameTypes"));
        gbGameTypes->setMinimumSize(QSize(0, 100));
        gbGameTypes->setMaximumSize(QSize(16777215, 100));
        verticalLayout_2 = new QVBoxLayout(gbGameTypes);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        rbTexasHoldem = new QRadioButton(gbGameTypes);
        bgGameTypes = new QButtonGroup(MainWindowUi);
        bgGameTypes->setObjectName(QStringLiteral("bgGameTypes"));
        bgGameTypes->addButton(rbTexasHoldem);
        rbTexasHoldem->setObjectName(QStringLiteral("rbTexasHoldem"));

        verticalLayout_2->addWidget(rbTexasHoldem);

        rbOmaha = new QRadioButton(gbGameTypes);
        bgGameTypes->addButton(rbOmaha);
        rbOmaha->setObjectName(QStringLiteral("rbOmaha"));

        verticalLayout_2->addWidget(rbOmaha);


        horizontalLayout->addWidget(gbGameTypes);

        gbActions = new QGroupBox(MainWindowUi);
        gbActions->setObjectName(QStringLiteral("gbActions"));
        gbActions->setMinimumSize(QSize(0, 100));
        gbActions->setMaximumSize(QSize(16777215, 100));
        verticalLayout_5 = new QVBoxLayout(gbActions);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        btnApply = new QPushButton(gbActions);
        btnApply->setObjectName(QStringLiteral("btnApply"));

        verticalLayout_5->addWidget(btnApply);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        btnCancel = new QPushButton(gbActions);
        btnCancel->setObjectName(QStringLiteral("btnCancel"));

        horizontalLayout_2->addWidget(btnCancel);

        btnLog = new QPushButton(gbActions);
        btnLog->setObjectName(QStringLiteral("btnLog"));

        horizontalLayout_2->addWidget(btnLog);


        verticalLayout_5->addLayout(horizontalLayout_2);


        horizontalLayout->addWidget(gbActions);


        verticalLayout->addLayout(horizontalLayout);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        lblCardsCombination = new QLabel(MainWindowUi);
        lblCardsCombination->setObjectName(QStringLiteral("lblCardsCombination"));

        verticalLayout_4->addWidget(lblCardsCombination);


        verticalLayout->addLayout(verticalLayout_4);

        ltDeck = new QVBoxLayout();
        ltDeck->setObjectName(QStringLiteral("ltDeck"));

        verticalLayout->addLayout(ltDeck);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(MainWindowUi);

        QMetaObject::connectSlotsByName(MainWindowUi);
    } // setupUi

    void retranslateUi(QDialog *MainWindowUi)
    {
        MainWindowUi->setWindowTitle(QApplication::translate("MainWindowUi", "Combinations", nullptr));
        gbTableCards->setTitle(QApplication::translate("MainWindowUi", "Table cards", nullptr));
        gbPlayerCards->setTitle(QApplication::translate("MainWindowUi", "Player cards", nullptr));
        gbGameTypes->setTitle(QApplication::translate("MainWindowUi", "Game types", nullptr));
        rbTexasHoldem->setText(QApplication::translate("MainWindowUi", "Texas Holdem", nullptr));
        rbOmaha->setText(QApplication::translate("MainWindowUi", "Omaha", nullptr));
        gbActions->setTitle(QApplication::translate("MainWindowUi", "Actions", nullptr));
        btnApply->setText(QApplication::translate("MainWindowUi", "apply", nullptr));
        btnCancel->setText(QApplication::translate("MainWindowUi", "cancel", nullptr));
        btnLog->setText(QApplication::translate("MainWindowUi", "in log", nullptr));
        lblCardsCombination->setText(QApplication::translate("MainWindowUi", "-", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindowUi: public Ui_MainWindowUi {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
