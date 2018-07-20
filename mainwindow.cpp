#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
	ui(new Ui::MainWindow){
	ui->setupUi(this);

    //create table
    table = new Table();

    //hiding results widgets
	//ui->label_6->setVisible(false);
    ui->label_7->setVisible(false);
    ui->label_8->setVisible(false);
    ui->label_9->setVisible(false);
    ui->label_10->setVisible(false);
    ui->label_11->setVisible(false);
	//ui->lineEdit_1->setVisible(false);
    ui->lineEdit_2->setVisible(false);
    ui->lineEdit_3->setVisible(false);
    ui->lineEdit_4->setVisible(false);
    ui->lineEdit_5->setVisible(false);
    ui->lineEdit_6->setVisible(false);



}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_buildButton_clicked(){
    ui->gridLayout_table->removeItem(ui->verticalSpacer);

    //building and showing table
    table->build_table(ui->customers_spinBox->value(),
                       ui->max_send_time_spinBox->value(), ui->max_serv_time_spinBox->value());
    ui->gridLayout_table->addWidget(table->get_tableWidget(),0,0);

	//ui->label_6->setVisible(true);
    ui->label_7->setVisible(true);
    ui->label_8->setVisible(true);
    ui->label_9->setVisible(true);
    ui->label_10->setVisible(true);
    ui->label_11->setVisible(true);
	//ui->lineEdit_1->setVisible(true);
    ui->lineEdit_2->setVisible(true);
    ui->lineEdit_3->setVisible(true);
    ui->lineEdit_4->setVisible(true);
    ui->lineEdit_5->setVisible(true);
    ui->lineEdit_6->setVisible(true);

    //counting values
    //ui->lineEdit_1->setText(QString::number(table->ser_time(), 'f',1)  + " min");
	ui->lineEdit_2->setText(QString::number(table->pers_prod(), 'f', 1) + " %");
    ui->lineEdit_3->setText(QString::number(table->get_intens(),'f',4));
    ui->lineEdit_4->setText(QString::number(table->wait_time(), 'f',1) + " min");
    ui->lineEdit_5->setText(QString::number(table->all_time(), 'f',1) + " min");
	ui->lineEdit_6->setText(QString::number(table->get_koef(), 'f',1) + " %");

}
