#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <regex>
#include <QMessageBox>
#include <string>
#include <sstream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QString event = ui->event->text();
    QString specialist_ = ui->specialist->text();
    QString beginDate_ =  ui->beginDate->text();
    QString beginTime_ = ui->beginTime->text();
    QString duration_ = ui->duration->text();
    std::string specialist = specialist_.toStdString();
    std::string beginDate = beginDate_.toStdString();
    std::string beginTime = beginTime_.toStdString();
    std::string duration__ = duration_.toStdString();
    bool errorSpecialist = 0;
    bool errorDate = 0;
    bool errorTime = 0;
    bool errorDuration = 0;
    {
        std::regex inputPattern(R"(^\s{0,}[a-z,A-Z,а-я,А-Я]{1,20}\s{1,}[a-z,A-Z,а-я,А-Я]{1,20}\s{0,})");
        if (std::regex_match(specialist, inputPattern) == 0) {
            errorSpecialist = 1;
        }
    }
    int day, month, year;
    {
    std::regex inputPattern(R"(^\s{0,}[0-9]{2,2}[.][0-9]{2,2}[.][0-9]{4,4}\s{0,})");
        if (std::regex_match(beginDate, inputPattern) == 0) {
            errorDate = 1;
        } else {
            std::stringstream inputStream1(beginDate);
            char c;
            inputStream1 >> day >> c >> month >> c >> year;
            if (!(day >= 1 && day <= 31 && month >= 1 && month <= 12))
                errorDate = 1;
        }
    }
    int beginHour, beginMinute;
    {
    std::regex inputPattern(R"(^\s{0,}[0-9]{2,2}[.][0-9]{2,2}\s{0,})");
        if (std::regex_match(beginTime, inputPattern) == 0) {
            errorTime = 1;
        } else {
            char c;
            std::stringstream inputStream1(beginTime);
            inputStream1 >> beginHour >> c >> beginMinute;
            if (!(beginHour >= 0 && beginHour <= 23 && beginMinute >= 0 &&
                beginMinute <= 59))
                errorTime = 1;
        }
    }
    int duration;
    {
    std::regex inputPattern(R"(^\s{0,}[0-9]{1,}\s{0,})");
        if (std::regex_match(duration__, inputPattern) == 0) {
            errorDuration = 1;
        } else  {
            std::stringstream inputStream1(duration__);
            inputStream1 >> duration;
        }
    }
    if(errorDate || errorDuration || errorSpecialist || errorTime){
        QString errors = "";
        if(errorSpecialist)
            errors += "Имя специалиста\n";
        if(errorDate)
            errors += "Дата начала\n";
        if(errorTime)
            errors += "Время начала\n";
        if(errorDuration)
            errors += "Длительность";
        QMessageBox::warning(this, "Ошибка", "Следующие поля введены некорректно:\n" + errors);
    } else {
        QMessageBox::information(this, "", "Событие успешно добавлено");
    }
}
