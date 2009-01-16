/****************************************************************************
**
** Copyright (C) 2008 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Qt Software Information (qt-info@nokia.com)
**
** This file is part of the example classes of the Qt Toolkit.
**
** Commercial Usage
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License versions 2.0 or 3.0 as published by the Free
** Software Foundation and appearing in the file LICENSE.GPL included in
** the packaging of this file.  Please review the following information
** to ensure GNU General Public Licensing requirements will be met:
** http://www.fsf.org/licensing/licenses/info/GPLv2.html and
** http://www.gnu.org/copyleft/gpl.html.  In addition, as a special
** exception, Nokia gives you certain additional rights. These rights
** are described in the Nokia Qt GPL Exception version 1.3, included in
** the file GPL_EXCEPTION.txt in this package.
**
** Qt for Windows(R) Licensees
** As a special exception, Nokia, as the sole copyright holder for Qt
** Designer, grants users of the Qt/Eclipse Integration plug-in the
** right for the Qt/Eclipse Integration to link to functionality
** provided by Qt Designer and its related libraries.
**
** If you are unsure which license is appropriate for your use, please
** contact the sales department at qt-sales@nokia.com.
**
****************************************************************************/

#include <QtGui>
#include <QtWebKit>
#include "mainwindow.h"
#include <qtextcodec.h>
#include <QFile>

#include <iostream>

//! [0]
MainWindow::MainWindow()
{
    createActions();
    createMenus();
    centralWidget = new Previewer(this);
    setCentralWidget(centralWidget);

    setStartupText();
}
//! [0]

//! [1]
void MainWindow::createActions()
{
    test1Act = new QAction(tr("HSK &Beginner..."), this);
    test1Act->setShortcut(tr("Ctrl+B"));
    test1Act->setStatusTip(tr("Study for the Beginner HSK"));
    connect(test1Act, SIGNAL(triggered()), this, SLOT(hskBeginner()));

    test2Act = new QAction(tr("HSK &Intermediate..."), this);
    test2Act->setShortcut(tr("Ctrl+I"));
    test2Act->setStatusTip(tr("Study for the Intermediate HSK"));
    connect(test2Act, SIGNAL(triggered()), this, SLOT(hskIntermediate()));

    test3Act = new QAction(tr("HSK &Advanced..."), this);
    test3Act->setShortcut(tr("Ctrl+A"));
    test3Act->setStatusTip(tr("Study for the Advanced HSK"));
    connect(test3Act, SIGNAL(triggered()), this, SLOT(hskAdvanced()));

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setStatusTip(tr("Exit the application"));
    exitAct->setShortcut(tr("Ctrl+Q"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    registerAct = new QAction(tr("&Download More Questions"), this);
    registerAct->setStatusTip(tr("Register to download hundreds of more test questions"));
    connect(registerAct, SIGNAL(triggered()), this, SLOT(userRegister()));
/*
    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));
*/
}

void MainWindow::hskBeginner()
{
	QString destinationUrl = "hskBeginner.html";
	QFile fileToLoad("content/hskBeginner.html");
        if (fileToLoad.exists()) {} else { destinationUrl = "register.html"; }

        QString text = "<html><body><script language=\"javascript\">document.location.href = \""+destinationUrl+"\";</script></body></html>";
        QString myDirPath = QApplication::applicationDirPath() + "/content/";
        QUrl myUrl = QUrl(myDirPath);
        centralWidget->webView->setHtml(text,myUrl);
}
void MainWindow::hskIntermediate()
{
	QString destinationUrl = "hskIntermediate.html";
	QFile fileToLoad("content/hskIntermediate.html");
        if (fileToLoad.exists()) {} else { destinationUrl = "register.html"; }

        QString text = "<html><body><script language=\"javascript\">document.location.href = \""+destinationUrl+"\";</script></body></html>";
        QString myDirPath = QApplication::applicationDirPath() + "/content/";
        QUrl myUrl = QUrl(myDirPath);
        centralWidget->webView->setHtml(text,myUrl);
}
void MainWindow::hskAdvanced()
{

	QString destinationUrl = "hskAdvanced.html";
	QFile fileToLoad("content/hskAdvanced.html");
        if (fileToLoad.exists()) {} else { destinationUrl = "register.html"; }

        QString text = "<html><body><script language=\"javascript\">document.location.href = \""+destinationUrl+"\";</script></body></html>";
        QString myDirPath = QApplication::applicationDirPath() + "/content/";
        QUrl myUrl = QUrl(myDirPath);
        centralWidget->webView->setHtml(text,myUrl);
}
void MainWindow::userRegister()
{
	// Use Javascript to Load HTML Page Directly
        QString text = "<html><body><script language=\"javascript\">document.location.href = \"register.html\";</script></body></html>";
        QString myDirPath = QApplication::applicationDirPath() + "/content/";
        QUrl myUrl = QUrl(myDirPath);
        centralWidget->webView->setHtml(text,myUrl);
}


//! [2]
void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&Start"));
    fileMenu->addAction(test1Act);
    fileMenu->addAction(test2Act);
    fileMenu->addAction(test3Act);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    menuBar()->addSeparator();

    helpMenu = menuBar()->addMenu(tr("&Upgrade"));
    //helpMenu->addAction(aboutAct);
    helpMenu->addAction(registerAct);
}
//! [2]

//! [3]
void MainWindow::about() {
/*
    QMessageBox::about(this, tr("About Application"),
        tr("Popup Chinese provides resources for students and translators. Visit us online at http://popupchinese.com")
    );
*/
	// Use Javascript to Load Splash Page Directly
       QString text = "<html><body><script language=\"javascript\">document.location.href = \"about.html\";</script></body></html>";
       QString myDirPath = QApplication::applicationDirPath() + "/content/";
       QUrl myUrl = QUrl(myDirPath);
       centralWidget->webView->setHtml(text,myUrl);


}
//! [3]

void MainWindow::setStartupText()
{
	int content_directory_missing = 0;

	QString destinationUrl = "splash2.html";
	QFile fileToLoad("content/splash2.html");
        if (fileToLoad.exists()) {} else { 
	  QFile fileToLoad("content/splash.html");
          if (fileToLoad.exists()) {} else { content_directory_missing = 1; }
          destinationUrl = "splash.html"; 
        }

 	if (content_directory_missing == 1) {

	  // Use Javascript to Load Splash Page Directly
          QString text = "<html><body>Cannot find directory containing test content. Please run this application from the location where you unpacked it. If you have difficulty, please contact us at service@popupchinese.com</body></html>";
          QString myDirPath = QApplication::applicationDirPath() + "/content/";
          QUrl myUrl = QUrl(myDirPath); 
          centralWidget->webView->setHtml(text,myUrl);

	} else {

	  // Use Javascript to Load Splash Page Directly
          QString text = "<html><body><script language=\"javascript\">document.location.href = \""+destinationUrl+"\";</script></body></html>";
          QString myDirPath = QApplication::applicationDirPath() + "/content/";
          QUrl myUrl = QUrl(myDirPath); 
          centralWidget->webView->setHtml(text,myUrl);

	}



}

//! [8]
