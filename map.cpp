#include "map.h"
#include "ui_map.h"

Map::Map(QWidget *parent, int raws, int cols) :
    QDialog(parent),
    ui(new Ui::Map),
    m_iSize_x(cols),
    m_iSize_y(raws)
{
    ui->setupUi(this);

}

Map* Map::ptrMap_ = nullptr;

Map::~Map()
{
    delete ui;
    delete ptrMap_;
}

/* Getting singleton Object */
Map *Map::GetInstance( int colums, int raws)
{
    if(ptrMap_ == nullptr)
        ptrMap_ = new Map(nullptr, raws, colums);

    return ptrMap_;
}

/* Checking input Data */
bool CheckMapSize(int raws, int cols)
{
    return (raws > 0 && cols > 0);
}

/* Creating Map */

Map *Map::MakeMap(int iCols, int iRaws)
{
    Map* ptrNewMap = Map::GetInstance(iCols, iRaws);
    return ptrNewMap;
}

