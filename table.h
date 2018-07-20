#ifndef TABLE_H
#define TABLE_H

#include <QWidget>
#include <QTableWidget>
#include <QHeaderView>
#include <QTime>

#define ROWH 30
#define COLW 40

class Table : public QWidget{
    Q_OBJECT

public:
    Table(QWidget *parent = 0);
    QTableWidget* get_tableWidget();
    void build_table(int, int, int);
    void set_t3();
    void set_t45();
    void set_t6();
    void set_t7();

    double ser_time();
	double pers_prod();

    double get_intens();
    double wait_time();
    double all_time();
    double get_koef();

	double hv_hod(double);
	double hod_hv(double);

private:
    int nrow;
    int ncol;
    QTableWidget *table;
    QStringList header;

};

#endif // TABLE_H
