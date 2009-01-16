/********************************************************************************
** Form generated from reading ui file 'previewer.ui'
**
** Created: Wed Dec 3 18:46:41 2008
**      by: Qt User Interface Compiler version 4.4.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_PREVIEWER_H
#define UI_PREVIEWER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QWidget>
#include <QtWebKit/QWebView>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QHBoxLayout *horizontalLayout_4;
    QWebView *webView;

    void setupUi(QWidget *Form)
    {
    if (Form->objectName().isEmpty())
        Form->setObjectName(QString::fromUtf8("Form"));
    Form->resize(921, 698);
    horizontalLayout_4 = new QHBoxLayout(Form);
    horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
    webView = new QWebView(Form);
    webView->setObjectName(QString::fromUtf8("webView"));
    webView->setUrl(QUrl("about:blank"));

    horizontalLayout_4->addWidget(webView);


    retranslateUi(Form);

    QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
    Q_UNUSED(Form);
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PREVIEWER_H
