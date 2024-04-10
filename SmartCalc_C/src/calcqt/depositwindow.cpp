#include "depositwindow.h"
#include "ui_depositwindow.h"
#include "../calc.h"

depositWindow::depositWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::depositWindow)
{
    ui->setupUi(this);
}

depositWindow::~depositWindow()
{
    delete ui;
}

void depositWindow::deposit_calc(){
    double sum_dep = ui->doubleSpinBox_sum_dep->value();
    int time_dep = ui->doubleSpinBox_month->value();
    double interest = ui->doubleSpinBox_interest->value();
    double add_dep = ui->doubleSpinBox_add->value();
    int cap_type = 0;

    if(ui->radioButton_cap->isChecked()){
        cap_type = 1;
    }
    if(cap_type){
        cap_deposit(sum_dep, time_dep, interest, add_dep,&total_sum, &pay_interest);
        ui->label_total_sum->setText(QLocale::system().toString(total_sum, 'f', 2));
        ui->label_interst_total->setText(QLocale::system().toString(pay_interest, 'f', 2));

    }else{
        simpl_deposit(sum_dep, time_dep, interest, add_dep,&total_sum, &pay_interest);
        ui->label_total_sum->setText(QLocale::system().toString(total_sum, 'f', 2));
        ui->label_interst_total->setText(QLocale::system().toString(pay_interest, 'f', 2));
    }


}

void depositWindow::on_pushButton_2_clicked()
{
    deposit_calc();
}


void depositWindow::on_pushButton_3_clicked()
{
    ui->label_interst_total->setText("");
    ui->label_total_sum->setText("");
}

