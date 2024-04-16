#ifndef APPLICANTS_H
#define APPLICANTS_H

#include <QObject>
#include <QWidget>
#include <QDebug>
#include <QMessageBox>

const int M_MIN_HEIGHT = 65;
const int M_MAX_HEIGHT = 80;
const int M_MIN_WEIGHT = 130;
const int M_MAX_WEIGHT = 250;
const int F_MIN_HEIGHT = 62;
const int F_MAX_HEIGHT = 75;
const int F_MIN_WEIGHT = 110;
const int F_MAX_WEIGHT = 185;
const int MIN_AGE = 17;
const int MAX_AGE = 40;

enum RejectReason
{
    LOW_AGE,
    HIGH_AGE,
    LOW_WEIGHT,
    HIGH_WEIGHT,
    LOW_HEIGHT,
    HIGH_HEIGHT,
    NONE
};

class Applicants : public QObject
{
    Q_OBJECT
public:
    explicit Applicants(QObject *parent = nullptr);
    Applicants(QObject *parent, QString name, char sex, int age, double weight, double height);

    void setName(QString name);
    void setSex(char sex);
    void setAge(int age);
    void setWeight(double weight);
    void setHeight(double height);
    void setAcceptance(bool accepted);
    void validate();

    QString getName() const;
    char getSex() const;
    int getAge() const;
    double getWeight() const;
    double getHeight() const;
    bool isAccepted() const;
    void print() const;
    RejectReason getReason() const;


private:
    QString name;
    char    sex;
    int     age;
    double  weight;
    double  height;
    bool    accepted;
    RejectReason reason;
signals:
};


#endif // APPLICANTS_H
