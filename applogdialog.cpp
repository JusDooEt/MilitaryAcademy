#include "applogdialog.h"
#include "ui_applogdialog.h"

AppLogDialog::AppLogDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AppLogDialog)
{
    ui->setupUi(this);
    list.clear();
}

AppLogDialog::AppLogDialog(QWidget *parent, std::vector<Applicants*> appLog)
    : QDialog(parent)
    , ui(new Ui::AppLogDialog)
{
    ui->setupUi(this);

    readFile("applicantList.txt");
}

AppLogDialog::~AppLogDialog()
{
    delete ui;

    for(auto &element : list)
    {
        delete element;
        element = nullptr;
    }
    list.clear();

}

void AppLogDialog::setList(std::vector<Applicants*> appLog)
{
    list = appLog;
}

void AppLogDialog::readFile(QString fileName)
{
    QString name;
    int age;
    int num;
    char sex;
    double weight;
    double height;
    bool accepted;
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Error opening " << file.fileName() << ": " << file.OpenError;
    }
    else
    {
        QTextStream fin(&file);
        while(!fin.atEnd())
        {
            name = fin.readLine();
            fin >> sex;
            fin.readLine();
            fin >> age;
            fin.readLine();
            fin >> weight;
            fin.readLine();
            fin >> height;
            fin.readLine();
            fin >> num;
            fin.readLine();
            if(num == 1)
                accepted = true;
            else
                accepted = false;


            list.push_back(new Applicants(this, name, sex, age, weight, height));
            list.back()->validate();
            list.back()->setAcceptance(accepted);
            addWidgetListItem(list.back());
            qDebug() << "Applicant Read";
            qDebug() << "Name: " << name;
            qDebug() << "Sex: " << sex;
            qDebug() << "Age: " << age;
            qDebug() << "Weight: " << weight;
            qDebug() << "Height: " << height;
            qDebug() << "Accepted: " << (list.back()->isAccepted() ? "true" : "false");
        }


    }
    file.close();

}

void AppLogDialog::addWidgetListItem(Applicants *applicant)
{
    QString text;
    text = applicant->getName() + "\n" +
           "Sex: " + applicant->getSex() + "\n" +
           "Age: " + QString::number(applicant->getAge());
    ui->appListWidget->addItem(text);
}

void AppLogDialog::on_appListWidget_itemActivated(QListWidgetItem *item)
{
    QString text;

    int index;

    index = ui->appListWidget->row(item);

    text = list[index]->getName() + "\n" +
           "Weight: " + QString::number(list[index]->getWeight()) + "\n" +
           "Height: " + QString::number(list[index]->getHeight()) + "\n";
    if(list[index]->isAccepted())
    {
        text += "Applicant Accepted";
    }
    else
    {
        switch(list[index]->getReason())
        {
        case LOW_AGE:
            text += "Below the age limit (" + QString::number(MIN_AGE) + ")";
            break;

        case HIGH_AGE:
            text += "Above the age limit (" + QString::number(MAX_AGE) + ")";
            break;

        case LOW_HEIGHT:
            text += "Below the height limit (" +
                       QString::number(list[index]->getSex() == 'M' ? M_MIN_HEIGHT : F_MIN_HEIGHT) + ")";
            break;

        case HIGH_HEIGHT:
            text += "Above the height limit (" +
                       QString::number(list[index]->getSex() == 'M' ? M_MAX_HEIGHT : F_MAX_HEIGHT) + ")";
            break;

        case LOW_WEIGHT:
            text += "Below the weight limit (" +
                       QString::number(list[index]->getSex() == 'M' ? M_MIN_WEIGHT : F_MIN_WEIGHT) + ")";
            break;

        case HIGH_WEIGHT:
            text += "Above the weight limit (" +
                       QString::number(list[index]->getSex() == 'M' ? M_MAX_WEIGHT : F_MAX_WEIGHT) + ")";
            break;

        default:
            break;
        }
    }
    ui->detailsTextEdit->setText(text);
}

