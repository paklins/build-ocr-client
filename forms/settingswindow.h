#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QDebug>
#include <QSettings>
#include <QFile>
#include <QIODevice>
#include <QTextCodec>

namespace Ui {
class SettingsWindow;
}

class SettingsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsWindow(QWidget *parent = nullptr);
    ~SettingsWindow();

    static void open(QWidget* parent);
    static QSettings* settings();

private:
    QString m_sSettingsFile;
    Ui::SettingsWindow *ui;
    QTextCodec* latinCodec;
    void load();

private slots:
    void onSaveSettings();
};

#endif // SETTINGSWINDOW_H
