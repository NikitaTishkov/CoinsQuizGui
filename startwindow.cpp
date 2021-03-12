#include "startwindow.h"
#include "ui_startwindow.h"
#include "map.h"
StartWindow::StartWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StartWindow)
{
    ui->setupUi(this);
}

StartWindow::~StartWindow()
{
    delete ui;
}


void StartWindow::on_pushButton_clicked()
{
    int iColsNew, iRawsNew;
    QString qsColsInput, qsRawsInput;

    qsColsInput = ui->input_cols->text();
    qsRawsInput = ui->input_raws->text();

    iColsNew = qsColsInput.toInt();
    iRawsNew = qsRawsInput.toInt();

    Map *map = Map::MakeMap(iColsNew, iRawsNew);
    map->exec();

}
