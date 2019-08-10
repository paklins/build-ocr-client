#ifndef ONECSTYLE_HPP
#define ONECSTYLE_HPP

#include <QApplication>
#include <QFile>
#include <QFont>
#include <QProxyStyle>
#include <QStyleFactory>

class OneCStyle : public QProxyStyle {
  Q_OBJECT

 public:
  OneCStyle();
  explicit OneCStyle(QStyle *style);

  QStyle *baseStyle() const;

  void polish(QPalette &palette) override;
  void polish(QApplication *app) override;

 private:
  QStyle *styleBase(QStyle *style = Q_NULLPTR) const;
};

#endif  // ONECSTYLE_HPP
