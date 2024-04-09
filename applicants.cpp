#include "applicants.h"

Applicants::Applicants(QObject *parent)
    : QObject{parent}
{}

Applicants::Applicants(QObject *parent, QString name, char sex, int age, double weight, double height)
    : QObject{parent}
{
    this->name = name;
    this->sex = sex;
    this->age = age;
    this->weight = weight;
    this->height = height;
    this->accepted = false;
}

void Applicants::setName(QString name)
{
    this->name = name;
}

void Applicants::setSex(char sex)
{
    this->sex = sex;
}

void Applicants::setAge(int age)
{
    this->age = age;
}

void Applicants::setWeight(double weight)
{
    this->weight = weight;
}

void Applicants::setHeight(double height)
{
    this->height = height;
}

void Applicants::setAcceptance(bool accepted)
{
    this->accepted = accepted;
}

void Applicants::validate()
{
    print();
    setAcceptance( (sex == 'M' && age >= MIN_AGE && age <= MAX_AGE &&
                  weight >= M_MIN_WEIGHT && weight <= M_MAX_WEIGHT &&
                  height >= M_MIN_HEIGHT && height <= M_MAX_HEIGHT) ||
                 (sex == 'F' && age >= MIN_AGE && age <= MAX_AGE &&
                  weight >= F_MIN_WEIGHT && weight <= F_MAX_WEIGHT &&
                                                                                                                                                                               height >= F_MIN_HEIGHT && height <= F_MAX_HEIGHT));
}

QString Applicants::getName() const
{
    return name;
}

char Applicants::getSex() const
{
    return sex;
}

int Applicants::getAge() const
{
    return age;
}

double Applicants::getWeight() const
{
    return weight;
}

double Applicants::getHeight() const
{
    return height;
}

bool Applicants::isAccepted() const
{
    return accepted;
}

void Applicants::print() const
{
    qDebug() << "Name: " << name;
    qDebug() << "Age: " << age;
    qDebug() << "Sex: " << sex;
    qDebug() << "Weight: " << weight;
    qDebug() << "Height: " << height;
}

