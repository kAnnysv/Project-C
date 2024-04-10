#include "crediwindow.h"
#include "ui_crediwindow.h"
#include "../calc.h"

crediWindow::crediWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::crediWindow)
{
    ui->setupUi(this);
}

crediWindow::~crediWindow()
{
    delete ui;
}

void crediWindow::credit_calc() {
    double credit_ammount = ui->doubleSpinBox_credit->value();
    int months = ui->spinBox_months->value();
    double interest = ui->doubleSpinBox_intetrest->value();
    int credit_type = 0;

    if (ui->radioButton_annuitet->isChecked()) {
       credit_type = 1;
     } else if (ui->radioButton_differentet->isChecked()) {
       credit_type = 2;
     }
    if(credit_type == 1){
        annuitet_credit(credit_ammount, months, interest, &monthly_payment, &overpayment, &total_payout);

        ui->label_overpayment->setText(
                QLocale::system().toString(overpayment, 'f', 2));
        ui->label_total_payout->setText(
                QLocale::system().toString(total_payout, 'f', 2));
        ui->label_monthly_payment->setText(
                QLocale::system().toString(monthly_payment, 'f', 2));
    }else if(credit_type == 2){
        diffirent_credit(credit_ammount,  months,  interest, &min_monthly_payment, &max_monthly_payment, &overpayment, &total_payout);

        ui->label_overpayment->setText(
                QLocale::system().toString(overpayment, 'f', 2));
        ui->label_total_payout->setText(
                QLocale::system().toString(total_payout, 'f', 2));
        ui->label_monthly_payment->setText(
                QLocale::system().toString(min_monthly_payment, 'f', 2) + " ... " +
                QLocale::system().toString(max_monthly_payment, 'f', 2));

    }



}


void crediWindow::on_pushButton_clicked()
{
    credit_calc();
}

