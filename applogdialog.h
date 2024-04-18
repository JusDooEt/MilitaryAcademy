#ifndef APPLOGDIALOG_H
#define APPLOGDIALOG_H

#include <QDialog>
#include <QFile>
#include "applicants.h"
#include <QListWidget>

namespace Ui {
class AppLogDialog;
}

class AppLogDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AppLogDialog(QWidget *parent = nullptr);
    AppLogDialog(QWidget *parent, std::vector<Applicants*> appLog);
    ~AppLogDialog();

    void setList(std::vector<Applicants*> appLog);

private slots:
    void clearList();

    void on_appListWidget_itemActivated(QListWidgetItem *item);

    void on_clearButton_clicked();


private:
    Ui::AppLogDialog *ui;
    std::vector<Applicants*> list;

    void readFile(QString fileName);
    void addWidgetListItem(Applicants *applicant);
};

#endif // APPLOGDIALOG_H
