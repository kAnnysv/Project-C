#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "../calc.h"
#include <QInputDialog>
#include <QMessageBox>
#include "iostream"
#include <QtMath>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_00,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_12,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_22,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_33,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_44,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_55,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_66,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_77,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_88,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_99,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->result_show, SIGNAL(returnPressed()), this,SLOT(get_result()));
    connect(ui->pushButton_res, SIGNAL(clicked()), this, SLOT(get_result()));
    connect(ui->pushButton_add,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_brecLeft,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_brecRight,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_div,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_dot,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_mod,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_mult,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_sub,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_cos,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_sin,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_tan,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_acos,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_asin,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_atan,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_ln,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_log,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_sqrt,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_exp,SIGNAL(clicked()),this,SLOT(digits_numbers()));
    connect(ui->pushButton_x,SIGNAL(clicked()),this,SLOT(digits_numbers()));

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::get_result(){
    double res = 0.0;

   if(ui->result_show->text().length() < 256){
       QByteArray arr_ex = ui->result_show->text().toLocal8Bit();
       char *str = arr_ex.data();
       pars_express(str, x, &res);
       QString result = QString::number(res, 'g', 15);
       ui->result_show->setText(result);
       

   }




}


void MainWindow::digits_numbers(){

    QPushButton *button = (QPushButton *)sender();

   

    QString new_label;

    new_label = ui->result_show->text() + button->text();
    if (button->text() == "sin" || button->text() == "cos" ||
          button->text() == "tan" || button->text() == "acos" ||
          button->text() == "asin" || button->text() == "atan" ||
          button->text() == "sqrt" || button->text() == "ln" ||
          button->text() == "log") {
        new_label += "(";
      }

    ui->result_show->setText(new_label);
}




void MainWindow::on_pushButton_AC_clicked()
{
    ui->result_show->setText("");

}





void MainWindow::on_pushButton_graf_clicked()
{
    // получаем максимальные и минимальные значения осей
        double x_min = ui->doubleSpinBox_x_min->value();
        double x_max = ui->doubleSpinBox_x_max->value();


        // шаг
        double h = 0.1;
        QVector<double> x, y;  // Массивы координат точек

        // собираем все точки
        for (double X = x_min; X <= x_max; X += h) {
          x.push_back(X);
          double res = 0;

          pars_express(ui->result_show->text().toStdString().c_str(), X, &res);
          y.push_back(res);
        }

        // добавляем один график в widget
        ui->graph_frame->addGraph();

        // говорим, что отрисовать нужно график по нашим двум массивам x и y
        ui->graph_frame->graph(0)->setData(x, y);

        // устанавливаем область, которая будет показываться на графике
        ui->graph_frame->xAxis->setRange(x_min, x_max);
        ui->graph_frame->yAxis->setRange(-10, 10);


        // задаем возможность зумировать график
        ui->graph_frame->setInteraction(QCP::iRangeZoom, true);

        // задаем цвет точки и толщину линии
        ui->graph_frame->graph(0)->setPen(QColor(61, 82, 62, 255));
        ui->graph_frame->setInteraction(QCP::iRangeZoom, true);
        QPen graphPen = ui->graph_frame->graph(0)->pen();
        graphPen.setWidth(2);
        ui->graph_frame->graph(0)->setPen(graphPen);

        // перерисуем график на нашем graph_frame
        ui->graph_frame->replot();
}


void MainWindow::on_pushButton_credit_clicked()
{
    crediWindow *credit = new crediWindow(this);
    credit->show();
}





void MainWindow::on_pushButton_deposit_clicked()
{
    depositWindow *deposit = new depositWindow(this);
    deposit->show();
}

