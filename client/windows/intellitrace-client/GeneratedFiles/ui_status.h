/********************************************************************************
** Form generated from reading UI file 'status.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATUS_H
#define UI_STATUS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_StatusDialog
{
public:
    QLabel *labelHistory;
    QPushButton *btnSave;
    QTextEdit *textHistory;

    void setupUi(QDialog *StatusDialog)
    {
        if (StatusDialog->objectName().isEmpty())
            StatusDialog->setObjectName(QStringLiteral("StatusDialog"));
        StatusDialog->resize(712, 851);
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/app.png"), QSize(), QIcon::Normal, QIcon::Off);
        StatusDialog->setWindowIcon(icon);
        labelHistory = new QLabel(StatusDialog);
        labelHistory->setObjectName(QStringLiteral("labelHistory"));
        labelHistory->setGeometry(QRect(20, 20, 101, 20));
        btnSave = new QPushButton(StatusDialog);
        btnSave->setObjectName(QStringLiteral("btnSave"));
        btnSave->setGeometry(QRect(590, 800, 93, 28));
        textHistory = new QTextEdit(StatusDialog);
        textHistory->setObjectName(QStringLiteral("textHistory"));
        textHistory->setGeometry(QRect(20, 50, 671, 731));
        textHistory->setReadOnly(true);
        QWidget::setTabOrder(textHistory, btnSave);

        retranslateUi(StatusDialog);

        QMetaObject::connectSlotsByName(StatusDialog);
    } // setupUi

    void retranslateUi(QDialog *StatusDialog)
    {
        StatusDialog->setWindowTitle(QApplication::translate("StatusDialog", "Intellitrace", 0));
        labelHistory->setText(QApplication::translate("StatusDialog", "History List", 0));
        btnSave->setText(QApplication::translate("StatusDialog", "Save", 0));
    } // retranslateUi

};

namespace Ui {
    class StatusDialog: public Ui_StatusDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATUS_H
