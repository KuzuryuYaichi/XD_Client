#ifndef _MY_IP_PART_LINE_EDIT_H_
#define _MY_IP_PART_LINE_EDIT_H_

#include <QLineEdit>
#include <QEvent>
#include <QLabel>
#include <QIntValidator>  
#include <QKeyEvent> 

class MyIpPartLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    MyIpPartLineEdit(QWidget* parent = 0);
    ~MyIpPartLineEdit(void);

    void set_prevtab_edit(QLineEdit* currenttab, QLineEdit* prevtab) { current_tab_ = currenttab, prev_tab_ = prevtab; }
    void set_nexttab_edit(QLineEdit* currenttab, QLineEdit* nexttab) { current_tab_ = currenttab, next_tab_ = nexttab; }

protected:
    virtual void focusInEvent(QFocusEvent* e);
    virtual void keyPressEvent(QKeyEvent* event);

private Q_SLOTS:
    virtual void text_edited(const QString& text);

private:
    QLineEdit* current_tab_ = nullptr,
        * prev_tab_ = nullptr,
        * next_tab_ = nullptr;
};

#endif
