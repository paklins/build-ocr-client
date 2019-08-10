#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "forms/framelesswindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    manager = new QNetworkAccessManager();

    ui->setupUi(this);

    QObject::connect(
        manager, &QNetworkAccessManager::finished, this, &MainWindow::response);

    QObject::connect(
        ui->settingsForm, &QAction::triggered, this, &MainWindow::openSettingsWindow);

    QObject::connect (manager, SIGNAL(authenticationRequired(QNetworkReply*,QAuthenticator*)),
        this, SLOT(onAuthenticationRequestSlot(QNetworkReply*,QAuthenticator*)) );

    updateSettings();

    m_pRE_Http = QRegExp("http://.*\n", Qt::CaseSensitivity::CaseInsensitive, QRegExp::RegExp);
}

void MainWindow::updateSettings()
{
    QSettings* settings = SettingsWindow::settings();
    auto keys = settings->allKeys();
    host = settings->value("task-manager/host", "").toString();
    user = settings->value("task-manager/user", "").toString();
    password = settings->value("task-manager/password", "").toString();

    delete  settings;
}

void MainWindow::openSettingsWindow()
{
    SettingsWindow::open(this);

    updateSettings();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete manager;
}

void MainWindow::onAuthenticationRequestSlot(QNetworkReply *reply, QAuthenticator *ator)
{
    if (reply->error()) {
        qDebug() << reply->errorString();
        return;
    }

    QByteArray usernameInBytes = user.toLocal8Bit();
    QLatin1String latinUserName(usernameInBytes);

    ator->setUser(latinUserName);
    ator->setPassword(password);
}

void MainWindow::on_pushButton_clicked()
{
    request.setUrl(QUrl(host));

    QNetworkReply* reply = manager->get(request);

    connect(reply, &QNetworkReply::finished, this, &MainWindow::httpFinished);
    connect(reply, &QIODevice::readyRead, this, &MainWindow::httpReadyRead);
}

void MainWindow::httpFinished()
{
    qDebug() << "finished";
}

void MainWindow::httpReadyRead()
{
    qDebug() << "readyRead";
}

void MainWindow::response(QNetworkReply *reply)
{
    if (reply->error()) {
        qDebug() << reply->errorString();
        return;
    }

    QByteArray buffer = reply->readAll();

    QJsonDocument jsonDoc(QJsonDocument::fromJson(buffer));
    QJsonObject jsonReply = jsonDoc.object();

    QJsonArray errors = jsonReply["value"].toArray();

    QStringList errorsList;

    m_hErrorElements.clear();

    QJsonObject errorDescription;
    QString errorCode;

    for (int index=0; index < errors.count(); index++) {
        errorDescription = errors[index].toObject();
        errorCode = errorDescription["Code"].toString();

        errorsList.append(errorCode);

        m_hErrorElements[errorCode.toInt()] = errorDescription;
    }

    QStringListModel* errorsModel = new QStringListModel(errorsList);

    ui->ErrorList->setModel(errorsModel);
}

void MainWindow::on_ErrorList_clicked(const QModelIndex &index)
{
    QVariant currentValue = ui->ErrorList->model()->data(index);
    int codeKey = currentValue.toInt();

    QString errorDescription = m_hErrorElements[codeKey]["ОписаниеОшибки"].toString();
    int urlIndex = m_pRE_Http.indexIn(errorDescription);

    if(urlIndex)
    {
        QString ct = m_pRE_Http.cap(0);

        qDebug() << ct;
       // ui->ErrorDescription->s QUrl(m_pRE_Http.capturedTexts()[0]));
    }
}
