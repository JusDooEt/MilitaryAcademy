#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    connect(this, &Widget::accepted, this, &Widget::editRoster);
}

Widget::~Widget()
{
    for(int i = list.size() - 1; i >= 0; i--)
    {
        delete list[i];
    }
    list.clear();
    delete ui;
}

void Widget::on_enterButton_clicked()
{
    QString name;
    char sex;
    int age;
    double weight;
    double height;

    QMessageBox* inputError;
    QString      errorMsg = "";
    if(!ui->mCheckBox->isChecked() && !ui->fCheckBox->isChecked())
    {
        errorMsg += "Please select a sex.\n";
    }

    if(ui->nameLineEdit->text().length() == 0)
    {
        errorMsg += "Please enter applicant's name.\n";
    }

    if(ui->ageSpinBox->value() == 0)
        errorMsg += "Please enter applicant's age.\n";

    if(ui->weightDSpinBox->value() == 0)
        errorMsg += "Please enter applicant's weight.\n";

    if(ui->heightDSpinBox->value() == 0)
        errorMsg += "Please enter applicant's height.\n";

    if(errorMsg.length() > 0)
    {
        inputError = new QMessageBox(this);
        inputError->setText(errorMsg);
        inputError->setWindowTitle("Incomplete data fields");
        inputError->exec();
    }
    else
    {
        if(ui->mCheckBox->isChecked())
        {
            sex = 'M';
        }
        else
        {
            sex = 'F';
        }

        name = ui->nameLineEdit->text();
        age = ui->ageSpinBox->value();
        weight = ui->weightDSpinBox->value();
        height = ui->heightDSpinBox->value();
        Applicants* ptr = new Applicants(this, name, sex, age, weight, height);
        ptr->validate();
        if(ptr->isAccepted())
        {
            inputError = new QMessageBox(this);
            inputError->setText("Applicant is Accepted!");
            inputError->setWindowTitle("Status");
            inputError->exec();
            emit accepted(ptr);
        }
        else
        {
            inputError = new QMessageBox(this);
            inputError->setText("Applicant is Rejected!");
            inputError->setWindowTitle("Status");
            inputError->exec();
        }
        list.push_back(ptr);
    }
}

void Widget::on_fCheckBox_stateChanged(int arg1)
{
    if(ui->mCheckBox->isChecked() && ui->fCheckBox->isChecked())
    {
        ui->mCheckBox->setCheckState(Qt::Unchecked);
    }
}


void Widget::on_mCheckBox_stateChanged(int arg1)
{
    if(ui->mCheckBox->isChecked() && ui->fCheckBox->isChecked())
    {
        ui->fCheckBox->setCheckState(Qt::Unchecked);
    }
}

void Widget::editRoster(Applicants *ptr)
{
    QString data;
    data = ptr->getName() + "\n" +
           "Age: " + QString::number(ptr->getAge()) + "\n" +
           "Sex: " + ptr->getSex() + "\n";
    ui->rosterTextEdit->append(data);
    roster.push_back(ptr);
}


