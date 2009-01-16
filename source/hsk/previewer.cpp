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
#include <QWebSettings>
#include <QWebFrame>
#include "previewer.h"
#include <iostream>
#include <QFileInfo>



//! [0]
Previewer::Previewer(QWidget *parent)
    : QWidget(parent)
{
    setupUi(this);

    downloadedPages = 0;
    authenticatedUser = 0;
    usernameProvided = "";
    passwordProvided = "";

    connect(webView->page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()),
            this, SLOT(populateJavaScriptWindowObject()));

    connect(&manager, SIGNAL(finished(QNetworkReply*)),
            SLOT(downloadFinished(QNetworkReply*)));

}
//! [0]



void Previewer::registerUser(const QString &userName, const QString &userPass)
{

  usernameProvided = userName;
  passwordProvided = userPass;

  if (authenticatedUser == 0) {
    QUrl myUrl0 = QUrl("http://www.popupchinese.com/software/authenticate.php?username="+usernameProvided+"&password="+passwordProvided);
    QNetworkRequest request0(myUrl0);
    QNetworkReply *reply0 = manager.get(request0);
    currentDownloads.append(reply0);
  } else {
    QUrl myUrl1 = QUrl("http://www.popupchinese.com/software/hskIntermediate.html");
    QNetworkRequest request1(myUrl1);
    QNetworkReply *reply1 = manager.get(request1);

    QUrl myUrl2 = QUrl("http://www.popupchinese.com/software/hskBeginner.html");
    QNetworkRequest request2(myUrl2);
    QNetworkReply *reply2 = manager.get(request2);

    QUrl myUrl3 = QUrl("http://www.popupchinese.com/software/hskAdvanced.html");
    QNetworkRequest request3(myUrl3);
    QNetworkReply *reply3 = manager.get(request3);

    QUrl myUrl4 = QUrl("http://www.popupchinese.com/software/splash2.html");
    QNetworkRequest request4(myUrl4);
    QNetworkReply *reply4 = manager.get(request4);

    currentDownloads.append(reply1);
    currentDownloads.append(reply2);
    currentDownloads.append(reply3);
    currentDownloads.append(reply4);
  }
}


void Previewer::downloadFinished(QNetworkReply *reply)
{
    QUrl url = reply->url();
    QString basename = QFileInfo(url.path()).fileName();
    QString filename  = "content/"+basename;

    if (authenticatedUser == 0) {
      if (reply->error()) {
        QString xxx = "document.getElementById(\"mainText\").innerHTML = \"Error Updating Software. Are you connected to the Internet? If so, please try again in a moment and contact us at service@popupchinese.com in the event of failure.\";";
        webView->page()->mainFrame()->evaluateJavaScript(xxx);
      } else {
	QString testing = reply->readAll();
	if (testing.indexOf("approved") == 0) {
	authenticatedUser = 1;
	registerUser(usernameProvided, passwordProvided);
        } else {
          QString xxx = "document.location.href = \"register2.html\";";
          webView->page()->mainFrame()->evaluateJavaScript(xxx);
	} 
      }
    } else { 
    
      if (reply->error()) {

        QString xxx = "document.getElementById(\"mainText\").innerHTML = \"Error Updating Software. Are you connected to the Internet? If so, please try again in a moment and contact us at service@popupchinese.com in the event of failure.\";";
        webView->page()->mainFrame()->evaluateJavaScript(xxx);

        fprintf(stderr, "Download of %s failed: %s\n",
                url.toEncoded().constData(),
                qPrintable(reply->errorString()));
      } else {
	
	downloadedPages++;

        if (saveToDisk(filename, reply)) {
          QString xxx = "document.getElementById(\"mainText\").innerHTML = \"<img src=\\\"loader-big-circle.gif\\\" /> Upgrade in progress.... please check your internet connection if this message lasts longer than a minute, or contact us by email at service@popupchinese.com.\";";
          webView->page()->mainFrame()->evaluateJavaScript(xxx);
	}
        if (downloadedPages == 4) {
          QString xxx = "document.location.href = \"splash2.html\";";
          webView->page()->mainFrame()->evaluateJavaScript(xxx);
        }
      }
    }

    currentDownloads.removeAll(reply);
    reply->deleteLater();

}



bool Previewer::saveToDisk(const QString &filename, QIODevice *data)
{

    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) {
        fprintf(stderr, "Could not open %s for writing: %s\n",
                qPrintable(filename),
                qPrintable(file.errorString()));
        return false;
    }

    file.write(data->readAll());
    file.close();

    return true;
}



//! [1]
void Previewer::populateJavaScriptWindowObject()
{
    webView->page()->mainFrame()->addToJavaScriptWindowObject("previewer", this);
}



//! [1]
