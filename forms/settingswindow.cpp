#include "settingswindow.h"
#include "ui_settingswindow.h"

SettingsWindow::SettingsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsWindow)
{
    ui->setupUi(this);
    latinCodec = QTextCodec::codecForName("utf-8");
    connect(ui->save, &QPushButton::clicked, this, &SettingsWindow::onSaveSettings);

    setAttribute(Qt::WA_DeleteOnClose);

    m_sSettingsFile = QApplication::applicationDirPath() + "/settings.ini";

    load();
}

SettingsWindow::~SettingsWindow()
{
    delete ui;
}

void SettingsWindow::open(QWidget* parent)
{
    SettingsWindow* window = new SettingsWindow(parent);
    window->exec();
}

QSettings* SettingsWindow::settings()
{
    SettingsWindow* window = new SettingsWindow();

   QSettings* settings = new QSettings(window->m_sSettingsFile, QSettings::IniFormat);
   settings->setIniCodec("utf-8");

   return settings;
}

void SettingsWindow::load()
{
    QFile file(m_sSettingsFile);

    if(!file.exists())
    {
        file.open(QIODevice::WriteOnly);
        file.close();
    }

    QSettings settings(m_sSettingsFile, QSettings::IniFormat);
    settings.setIniCodec("utf-8");

    ui->host->setPlainText(
        settings.value("task-manager/host", "").toString());
    ui->user->setText(
        settings.value("task-manager/user", "").toString());
    ui->password->setText(
        settings.value("task-manager/password", "").toString());
    ui->pathToResult->setText(
        settings.value("results/pathToResult", "").toString());
}

void SettingsWindow::onSaveSettings()
{
    QSettings settings(m_sSettingsFile, QSettings::IniFormat);
    settings.setIniCodec("utf-8");

    settings.setValue("task-manager/host", ui->host->toPlainText());
    settings.setValue("task-manager/user", ui->user->text());
    settings.setValue("task-manager/password", ui->password->text());
    settings.setValue("results/pathToResult", ui->pathToResult->text());

    close();
}
