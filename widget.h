#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "appLogDialog.h"
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
    void clearRoster();

    void initializeRoster();

    void on_enterButton_clicked();

    void on_fCheckBox_stateChanged(int arg1);

    void on_mCheckBox_stateChanged(int arg1);

    void editRoster(Applicants* ptr);

    void on_pushButton_2_clicked();



    void on_clearButton_2_clicked();

private:
    Ui::Widget              *ui;
    AppLogDialog            *appLogDialog;
    std::vector<Applicants*> list;
    std::vector<Applicants*> roster;
    QString                  fileName;
    QString                  rosterFile;

    QString checkInput();
    void appendTextFile(QString name, Applicants *ptr);

signals:
    void accepted(Applicants*);

};


bool validate(Applicants*);
#endif // WIDGET_H
