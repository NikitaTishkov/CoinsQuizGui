#include "startwindow.h"
#include "ui_startwindow.h"
#include "map.h"
#include <QMessageBox>
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

/* Creating Map Handler */
void StartWindow::on_pushButton_clicked()
{

    int iColsNew, iRawsNew;
    QString qsColsInput, qsRawsInput;
    bool bInColsCheck, bInRawsCheck;

    qsColsInput = ui->input_cols->text();
    qsRawsInput = ui->input_raws->text();

    iColsNew = qsColsInput.toInt(&bInColsCheck, 10);
    iRawsNew = qsRawsInput.toInt(&bInRawsCheck, 10);
    if(bInColsCheck && bInRawsCheck
            && iColsNew > 0
            && iRawsNew > 0)
    {
        Map *map = Map::MakeMap(iColsNew, iRawsNew);
        //map->setAttribute(Qt::WA_DeleteOnClose);
        map->exec();
        //map->done(map_close_val);
    }else
    {
        QMessageBox ErrMsg;
        ErrMsg.setText("Incorrect input value");
        ErrMsg.setInformativeText("Please enter integer value > 0");
        ErrMsg.setWindowTitle("Error!");
        ErrMsg.exec();
    }
}
