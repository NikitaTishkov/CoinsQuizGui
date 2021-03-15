#include "map.h"
#include "ui_map.h"
#define MIN(a, b) (a < b) ? a : b

void Map::CreatingMapViewModel(QGridLayout *Layout)
{
    for(int i = 0; i < this->m_iSize_y; i++)
    {
        for(int j = 0; j < m_iSize_x; j++)
        {
            Layout->addWidget(&m_aCells[i][j], i + 1, j + 1, Qt::AlignCenter);
        }
    }
}


Map::Map(QWidget *parent, int raws, int cols) :
    QDialog(parent),
    ui(new Ui::Map),
    m_iSize_x(cols),
    m_iSize_y(raws)
{

    ui->setupUi(this);
    QGridLayout *MainMapLayout = ui->MainMapLayout;
    m_aCells = new City*[raws];

    FillingCells(m_aCells);

    CreatingMapViewModel(MainMapLayout);


}

Map* Map::ptrMap_ = nullptr;

Map::~Map()
{
    delete ui;

    for(int i = 0; i < this->m_iSize_y; i++)
        delete[] m_aCells[i];

    free (ptrMap_);

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

void Map::FillingCells(City **aCellsNew)
{
    for(int i = 0; i < this->m_iSize_y; i++)
    {
       aCellsNew[i] = new City[this->m_iSize_x];
    }
}

