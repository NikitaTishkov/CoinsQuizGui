#include "map.h"
#include "ui_map.h"
#define MIN(a, b) (a < b) ? a : b

Map::Map(QWidget *parent, int raws, int cols, int DaysStart) :
    QDialog(parent),
    ui(new Ui::Map),
    m_iSize_x(cols),
    m_iSize_y(raws),
    m_iDaysWorked(DaysStart)
{

    ui->setupUi(this);
    QGridLayout *MainMapLayout = ui->MainMapLayout;
    MainMapLayout->setSizeConstraint(QLayout::SetMaximumSize);
    m_aCells = new City*[raws];
    this->m_iCountryNumber = 0;
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

    for(int i = 0; i < this->m_iSize_y; i++)
    {
        for(int j = 0; j < this->m_iSize_x; j++)
        {
            aCellsNew[i][j].SetCellParams(j, i);
        }
    }
}

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

void Map::IncCountryNum(int Inc)
{
    this->m_iCountryNumber += Inc;
}

City* Map::FindCityByCoords(int X, int Y)
{
    if( X >= this->GetSizeX()
     || Y >= this->GetSizeY()
     || X < 0
     || Y < 0)
    {
        return nullptr;
    }
    if(this->m_aCells[Y][X].GetIsCity() == false)
        return nullptr;

    return &this->m_aCells[Y][X];
}

void Map::InitTransactionForCountry(Map *map, Country *country)
{
    QVector<City*> aCities = country->GetCitiesVector();
    for(int i = 0; i < aCities.size(); i++)
    {
        /* Get Left neighbour */
        City *Neighbour = map->FindCityByCoords(aCities[i]->GetCoord().GetX() - 1,
                                                aCities[i]->GetCoord().GetY());
        if(Neighbour != nullptr)
            aCities[i]->SendMoney(Neighbour);

        Neighbour = map->FindCityByCoords(aCities[i]->GetCoord().GetX(),
                                          aCities[i]->GetCoord().GetY() - 1);
        if(Neighbour != nullptr)
            aCities[i]->SendMoney(Neighbour);

        Neighbour = map->FindCityByCoords(aCities[i]->GetCoord().GetX() + 1,
                                          aCities[i]->GetCoord().GetY());
        if(Neighbour != nullptr)
            aCities[i]->SendMoney(Neighbour);

        Neighbour = map->FindCityByCoords(aCities[i]->GetCoord().GetX(),
                                          aCities[i]->GetCoord().GetY() + 1);
        if(Neighbour != nullptr)
            aCities[i]->SendMoney(Neighbour);
    }
}

void Map::UpdateMap()
{
    for(int i = 0; i < this->m_aCountries.size(); i++)
    {
        this->m_aCountries[i]->UpdateVaultInfoCountry();
    }
}

int Map::GetDaysWorked()
{
    return this->m_iDaysWorked;
}

void Map::IncreaseDaysWorked(int iVal)
{
    this->m_iDaysWorked += iVal;
}

void Map::on_AddCountryButton_clicked()
{
    this->IncCountryNum(1);
    Point start(ui->inputStartX->text().toInt(),
                ui->inputStartY->text().toInt()
                );

    Point end(ui->inputEndX->text().toInt(),
              ui->inputEndY->text().toInt()
              );

    Country *pNewCountry = new Country(this->GetCountryNumber(), start, end, this->m_aCells);

    this->m_aCountries.push_back(pNewCountry);

    ui->CountryNum->setText(QString::number(this->GetCountryNumber()));
}

void Map::on_StepButton_clicked()
{
    int iStepsNum = ui->inputStep->text().toInt();
    this->IncreaseDaysWorked(iStepsNum);
    for(int j = 0; j < iStepsNum; j++)
    {
        for(int i = 0; i < this->m_aCountries.size(); i++)
            this->InitTransactionForCountry(this ,this->m_aCountries[i]);
    }
    UpdateMap();
}
