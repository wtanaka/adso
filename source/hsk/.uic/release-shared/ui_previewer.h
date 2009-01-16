/********************************************************************************
** Form generated from reading ui file 'previewer.ui'
**
** Created: Fri Nov 14 21:24:28 2008
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
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSplitter>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <QtWebKit/QWebView>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QHBoxLayout *horizontalLayout_4;
    QSplitter *splitter;
    QGroupBox *editorBox;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_2;
    QPlainTextEdit *plainTextEdit;
    QHBoxLayout *horizontalLayout;
    QPushButton *clearButton;
    QPushButton *previewButton;
    QGroupBox *previewerBox;
    QHBoxLayout *horizontalLayout_3;
    QWebView *webView;

    void setupUi(QWidget *Form)
    {
    if (Form->objectName().isEmpty())
        Form->setObjectName(QString::fromUtf8("Form"));
    Form->resize(911, 688);
    horizontalLayout_4 = new QHBoxLayout(Form);
    horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
    splitter = new QSplitter(Form);
    splitter->setObjectName(QString::fromUtf8("splitter"));
    splitter->setOrientation(Qt::Horizontal);
    editorBox = new QGroupBox(splitter);
    editorBox->setObjectName(QString::fromUtf8("editorBox"));
    horizontalLayout_2 = new QHBoxLayout(editorBox);
    horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
    verticalLayout_2 = new QVBoxLayout();
    verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
    plainTextEdit = new QPlainTextEdit(editorBox);
    plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));

    verticalLayout_2->addWidget(plainTextEdit);

    horizontalLayout = new QHBoxLayout();
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    clearButton = new QPushButton(editorBox);
    clearButton->setObjectName(QString::fromUtf8("clearButton"));

    horizontalLayout->addWidget(clearButton);

    previewButton = new QPushButton(editorBox);
    previewButton->setObjectName(QString::fromUtf8("previewButton"));

    horizontalLayout->addWidget(previewButton);


    verticalLayout_2->addLayout(horizontalLayout);


    horizontalLayout_2->addLayout(verticalLayout_2);

    splitter->addWidget(editorBox);
    previewerBox = new QGroupBox(splitter);
    previewerBox->setObjectName(QString::fromUtf8("previewerBox"));
    horizontalLayout_3 = new QHBoxLayout(previewerBox);
    horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
    webView = new QWebView(previewerBox);
    webView->setObjectName(QString::fromUtf8("webView"));
    webView->setUrl(QUrl("about:blank"));

    horizontalLayout_3->addWidget(webView);

    splitter->addWidget(previewerBox);

    horizontalLayout_4->addWidget(splitter);


    retranslateUi(Form);
    QObject::connect(clearButton, SIGNAL(clicked()), plainTextEdit, SLOT(clear()));

    QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
    Form->setWindowTitle(QApplication::translate("Form", "Form", 0, QApplication::UnicodeUTF8));
    editorBox->setTitle(QApplication::translate("Form", "HTML Editor", 0, QApplication::UnicodeUTF8));
    clearButton->setText(QApplication::translate("Form", "Clear", 0, QApplication::UnicodeUTF8));
    previewButton->setText(QApplication::translate("Form", "Preview", 0, QApplication::UnicodeUTF8));
    previewerBox->setTitle(QApplication::translate("Form", "HTML Preview", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(Form);
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PREVIEWER_H
