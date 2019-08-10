#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QAuthenticator>
#include <QIODevice>
#include <QAction>
#include <QTextCodec>
#include <QStringLiteral>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QStringListModel>
#include <QMap>
#include <QRegExp>

#include "forms/settingswindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *manager;
    QNetworkRequest request;
    QMap<int, QJsonObject> m_hErrorElements;
    QRegExp m_pRE_Http;

    QString host;
    QString user;
    QString password;

    void updateSettings();

private slots:
    void onAuthenticationRequestSlot(QNetworkReply *reply, QAuthenticator *ator);
    void response(QNetworkReply *reply);
    void httpFinished();
    void httpReadyRead();
    void on_pushButton_clicked();
    void openSettingsWindow();
    void on_ErrorList_clicked(const QModelIndex &index);
};

#endif // MAINWINDOW_H
