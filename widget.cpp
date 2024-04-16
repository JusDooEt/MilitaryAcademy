#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    appLogDialog = nullptr;
    fileName = "applicantList.txt";
    rosterFile = "roster.txt";
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
    QString      name;
    char         sex;
    int          age;
    double       weight;
    double       height;

    QMessageBox* inputError;
    QString      errorMsg;

    /*
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
*/

    errorMsg = checkInput();
    if(errorMsg.length() > 0)
    {
        inputError = new QMessageBox(this);
        inputError->setText(errorMsg);
        inputError->setWindowTitle("Incomplete data fields");
        inputError->exec();
    }
    else
    {
        /*
        if(ui->mCheckBox->isChecked())
        {
            sex = 'M';
        }
        else
        {
            sex = 'F';
        }
        */
        sex = ui->mCheckBox->isChecked() ? 'M' : 'F';
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
            inputError->setWindowTitle("Applicant Accepted");
            inputError->exec();

            emit accepted(ptr);
        }
        else
        {
            QString msgText;
            msgText = ("Applicant is Rejected\nReason: ");
            switch(ptr->getReason())
            {
            case LOW_AGE:
                msgText += "Below the age limit (" + QString::number(MIN_AGE) + ")";
                break;

            case HIGH_AGE:
                msgText += "Above the age limit (" + QString::number(MAX_AGE) + ")";
                break;

            case LOW_HEIGHT:
                msgText += "Below the height limit (" +
                           QString::number(ptr->getSex() == 'M' ? M_MIN_HEIGHT : F_MIN_HEIGHT) + ")";
                break;

            case HIGH_HEIGHT:
                msgText += "Above the height limit (" +
                           QString::number(ptr->getSex() == 'M' ? M_MAX_HEIGHT : F_MAX_HEIGHT) + ")";
                break;

            case LOW_WEIGHT:
                msgText += "Below the weight limit (" +
                           QString::number(ptr->getSex() == 'M' ? M_MIN_WEIGHT : F_MIN_WEIGHT) + ")";
                break;

            case HIGH_WEIGHT:
                msgText += "Above the weight limit (" +
                           QString::number(ptr->getSex() == 'M' ? M_MAX_WEIGHT : F_MAX_WEIGHT) + ")";
                break;

            default:
                break;
            }

            inputError = new QMessageBox(this);
            inputError->setText(msgText);
            inputError->setWindowTitle("Applicant Rejected");
            inputError->exec();
        }

        list.push_back(ptr);
        appendTextFile(fileName,list.back());
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

void Widget::on_pushButton_2_clicked()
{
    if(appLogDialog == nullptr)
    {
        ui->pushButton_2->setDisabled(true);

        appLogDialog = new AppLogDialog(this, list);
        connect(appLogDialog, &QDialog::finished, this, [&](){
            delete appLogDialog;
            appLogDialog = nullptr;
            ui->pushButton_2->setEnabled(true);
            //qDebug() << "appLogDialog = nullptr";
        });
        appLogDialog->show();
    }
}

QString Widget::checkInput()
{
    QString errorMsg = "";
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

    return errorMsg;
}

void Widget::appendTextFile(QString name, Applicants *ptr)
{
    QFile       file(name);

    if(!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
    {
        qDebug() << "Error opening " << file.fileName() << ": " << file.OpenError;
    }
    else
    {
        QTextStream fout(&file);

        fout << ptr->getName() << Qt::endl;
        fout << ptr->getSex() << Qt::endl;
        fout << ptr->getAge() << Qt::endl;
        fout << ptr->getWeight() << Qt::endl;
        fout << ptr->getHeight() << Qt::endl;
        fout << QString::number(ptr->isAccepted() ? 1 : 0) << Qt::endl;
    }
    file.close();
}

