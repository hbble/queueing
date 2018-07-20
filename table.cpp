#include "table.h"

Table::Table(QWidget *parent) : QWidget(parent){

    //table size
    nrow = 1;
    ncol = 8;
    //create table
    table = new QTableWidget(nrow, ncol, parent);
    table->verticalHeader()->hide();

    //title
    header.push_back("N");
	for(int i = 1; i < ncol; i++){
		if (i >= 3 && i <= 5)
            header.push_back("t" + QString::number(i) + ", h/min");
		else
            header.push_back("t" + QString::number(i) + ", min");
	}
    table->setHorizontalHeaderLabels(header);

    //column size
    for(int i = 0; i < ncol; i++){
        table->setColumnWidth(i, COLW);
        table->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
    }

}

QTableWidget* Table::get_tableWidget(){
    return table;
}

void Table::build_table(int row, int max_1, int max_2){
    nrow = row;
    table->setRowCount(nrow);

    //table elements
    for(int i = 0; i < nrow; i++){
        for(int j = 0; j < ncol; j++){
            QTableWidgetItem *item = new QTableWidgetItem();
            item->setFlags(item->flags() ^ Qt::ItemIsEditable);
            item->setTextAlignment(Qt::AlignRight);

            table->setItem(i,j,item);
        }
    }

    //first three columns
    for(int i = 0; i < nrow; i++){//first
        table->item(i,0)->setText(QString::number(i + 1));
        table->item(i,0)->setTextAlignment(Qt::AlignCenter);
        table->item(i,0)->setBackgroundColor(QColor(200,200,200));
    }

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    table->item(0,1)->setText("-");
    for(int i = 1; i < nrow; i++){//second
        int r = qrand() % max_1 + 1;
        table->item(i,1)->setText(QString::number(r));
    }

    for(int i = 0; i < nrow; i++){//third
        int r = qrand() % max_2 + 1;
        table->item(i,2)->setText(QString::number(r));
    }

    //remain columns
    set_t3();
    set_t45();
    set_t6();
    set_t7();

}

void Table::set_t3(){

    table->item(0,3)->setText(QString::number(0,'f',2));

	double temp;
    for(int i = 1; i < nrow; i++){
		temp = hod_hv(table->item(i-1,3)->text().toDouble()) + table->item(i,1)->text().toDouble();//t3 + t1
		table->item(i,3)->setText(QString::number(hv_hod(temp),'f',2));
    }
}

void Table::set_t45(){

    table->item(0,4)->setText(QString::number(0,'f',2));

    double t5, t3, temp;
    for(int i = 1; i < nrow; i++){
        //searching t5(i-1)
		t5 = hv_hod(hod_hv(table->item(i-1,4)->text().toDouble()) + table->item(i-1,2)->text().toDouble());//t4 + t2
		table->item(i-1,5)->setText(QString::number(t5,'f',2));
		t3 = table->item(i,3)->text().toDouble();
        //t4(i)
        temp = (t5 > t3) ? t5 : t3; //MAX {t5(i-1), t3(i)
        table->item(i,4)->setText(QString::number(temp,'f',2));
    }
    //last t5
	t5 = hod_hv(table->item(nrow-1,4)->text().toDouble()) + table->item(nrow-1,2)->text().toDouble();//t4 + t2
	table->item(nrow-1,5)->setText(QString::number(hv_hod(t5),'f',2));
}

void Table::set_t6(){
    int temp, t5, t3;
    for(int i = 0; i < nrow; i++){
		t5 = hod_hv(table->item(i,5)->text().toDouble());
		t3 = hod_hv(table->item(i,3)->text().toDouble());
        temp = t5 - t3;//t5 - t3
        table->item(i,6)->setText(QString::number(temp));
    }
}

void Table::set_t7(){

    table->item(0,7)->setText(QString::number(0));

    int temp, t3, t5;
    for(int i = 1; i < nrow; i++){
		t3 = hod_hv(table->item(i,3)->text().toDouble());
		t5 = hod_hv(table->item(i-1,5)->text().toDouble());
        if (t3 > t5){
            temp = t3 - t5;//t5 - t3
            table->item(i,7)->setText(QString::number(temp));
        }
        else
            table->item(i,7)->setText(QString::number(0));
    }

}

double Table::pers_prod(){
	return 100 - get_koef();
}

double Table::get_intens(){
    double temp = 0;

    for(int i = 0; i < nrow - 1; i++){
		temp += hod_hv(table->item(i + 1,3)->text().toDouble()) - hod_hv(table->item(i,3)->text().toDouble());
    }
    temp /= nrow;

    return 1 / temp;
}

double Table::wait_time(){

    double temp = 0;

    for(int i = 0; i < nrow; i++)
		temp += hod_hv(table->item(i,4)->text().toDouble()) - hod_hv(table->item(i,3)->text().toDouble());
    temp /= nrow;

    return temp;
}

double Table::all_time(){

    double temp = 0;

    for(int i = 0; i < nrow; i++)
        temp += table->item(i,6)->text().toDouble();
    temp /= nrow;

    return temp;
}

double Table::get_koef(){

	double temp = 0, lambda = get_intens();

    for(int i = 0; i < nrow - 1; i++){
		temp += hod_hv(table->item(i,5)->text().toDouble()) - hod_hv(table->item(i,4)->text().toDouble());
    }
    temp /= nrow;
    temp = 1 / temp;

	return lambda * 100 / temp;

}

double Table::hv_hod(double hv){
	double temp1 = (int)(hv / 60);
	double temp2 = (hv - (temp1 * 60)) / 100;

	return temp1 + temp2;
}

double Table::hod_hv(double hod){
	double temp1 = (int)hod;
	double temp2 = (hod - temp1) * 100;

	return temp1 * 60 + temp2;

}
