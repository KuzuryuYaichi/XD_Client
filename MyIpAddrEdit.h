#ifndef _MY_IP_ADDR_EDIT_H_
#define _MY_IP_ADDR_EDIT_H_

#include "MyIpPartLineEdit.h"
#include <QRegExpValidator>
#include <QJsonDocument>

class MyIpAddrEdit : public QWidget
{
    Q_OBJECT

public:
    MyIpAddrEdit(QWidget* parent = 0);
    ~MyIpAddrEdit();

    void settext(const QString& text);
    QString text();
    void getIp(QString& ip1, QString& ip2, QString& ip3, QString& ip4);
    void setStyleSheet(const QString& styleSheet);

Q_SIGNALS:
    void textchanged(const QString& text);
    void textedited(const QString& text);

private Q_SLOTS:
    void textchangedslot(const QString& text);
    void texteditedslot(const QString& text);

private:
    MyIpPartLineEdit* ip_part1_;
    MyIpPartLineEdit* ip_part2_;
    MyIpPartLineEdit* ip_part3_;
    MyIpPartLineEdit* ip_part4_;

    QLabel* labeldot1_;
    QLabel* labeldot2_;
    QLabel* labeldot3_;
};

#endif
