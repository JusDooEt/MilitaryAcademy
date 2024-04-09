#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMessageBox>
#include "applicants.h"
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_enterButton_clicked();

    void on_fCheckBox_stateChanged(int arg1);

    void on_mCheckBox_stateChanged(int arg1);

    void editRoster(Applicants* ptr);

private:
    Ui::Widget *ui;
    std::vector<Applicants*> list;
    std::vector<Applicants*> roster;


signals:
    void accepted(Applicants*);
};


bool validate(Applicants*);
#endif // WIDGET_H
