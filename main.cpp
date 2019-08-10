#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>
#include <QLocale>
#include <QFontDatabase>

#include "styles/DarkStyle.h"
#include "styles/onecstyle.h"
#include "forms/framelesswindow.h"

int main(int argc, char *argv[])
{
    QLocale curLocale(QLocale("ru_RU"));
    QLocale::setDefault(curLocale);

    QTextCodec::setCodecForLocale(
         QTextCodec::codecForName("utf-8"));

    QApplication a(argc, argv);
    a.setStyle(new OneCStyle());

    if(QFontDatabase::addApplicationFont(":/fonts/ffa") < 0)
        qWarning() << "FontAwesome cannot be loaded";

    FramelessWindow window;

    MainWindow w;
    window.setContent(&w);
    window.show();

    return a.exec();
}
