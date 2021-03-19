#include "map.h"
#include "ui_map.h"
#define MIN(a, b) (a < b) ? a : b
/* Creating UI and Attaching Cells to GridLayout */
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
/* Singletones behavior functions */
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
/* Helper function that checks if one range layover another */
bool IsRangesOverlay(int StartX1, int EndX1, int StartX2, int EndX2)
{
    int aCouCheckCoordsX[2] = {
        StartX1,
        EndX1
    };
    int aCouCheckCoordsNewX[2] = {
        StartX2,
        EndX2
    };
    int *aFirstRange;
    int *aSecondRange;
    if(aCouCheckCoordsNewX[0] < aCouCheckCoordsX[0])
    {
        aFirstRange = aCouCheckCoordsNewX;
        aSecondRange = aCouCheckCoordsX;
    }
    else
    {
        aFirstRange = aCouCheckCoordsX;
        aSecondRange = aCouCheckCoordsNewX;
    }

    if(aSecondRange[0] >= aFirstRange[0] &&
            aSecondRange[0] <= aFirstRange[1])
    {
        return true;
    }
    else
    {
        return false;
    }
}
/* Checking Squares overlaying */
bool Map::CheckCountryOverlay(Point start, Point end)
{
    for(int i = 0; i < this->m_aCountries.size(); i++)
    {
        bool IsXOverlay = IsRangesOverlay(this->m_aCountries[i]->GetStartCoord().GetX(),
                                          this->m_aCountries[i]->GetEndCoord().GetX(),
                                          start.GetX(),
                                          end.GetX());
        if(IsXOverlay)
        {
            bool IsYOverlay = IsRangesOverlay(this->m_aCountries[i]->GetStartCoord().GetY(),
                                              this->m_aCountries[i]->GetEndCoord().GetY(),
                                              start.GetY(),
                                              end.GetY());
            if(IsYOverlay)
            {
                return true;
            }
        }
    }
    return false;
}

/* Creating Map */

Map *Map::MakeMap(int iCols, int iRaws)
{
    Map* ptrNewMap = Map::GetInstance(iCols, iRaws);
    return ptrNewMap;
}

/* Filling the composition of Map`s cells */
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

/* Adds buttons to GridLayout */
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
/* Increase country counter */
void Map::IncCountryNum(int Inc)
{
    this->m_iCountryNumber += Inc;
}

/* Getting reference by coords */
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

/* Initialize sending money from all cities in country */
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
/* Visualize changes on the mao */
void Map::UpdateMap()
{
    for(int i = 0; i < this->m_aCountries.size(); i++)
    {
        this->m_aCountries[i]->UpdateVaultInfoCountry();
    }
}
/* Manipulating with Days counter */
int Map::GetDaysWorked()
{
    return this->m_iDaysWorked;
}

void Map::IncreaseDaysWorked(int iVal)
{
    this->m_iDaysWorked += iVal;
}
/* Handle country creation */
void Map::on_AddCountryButton_clicked()
{

    bool bCheckStartX, bCheckStartY, bCheckEndX, bCheckEndY;

    Point start(ui->inputStartX->text().toInt(&bCheckStartX, 10),
                ui->inputStartY->text().toInt(&bCheckStartY, 10)
                );
    Point end(ui->inputEndX->text().toInt(&bCheckEndX, 10),
              ui->inputEndY->text().toInt(&bCheckEndY, 10)
              );
    if(bCheckStartX
            && bCheckStartY
            && bCheckEndX
            && bCheckEndY
            && start.GetX() >= 1
            && start.GetY() >= 1
            && end.GetX() >= 1
            && end.GetY() >= 1)
    {
        bool IsCountryOverlay = CheckCountryOverlay(start, end);

        if(IsCountryOverlay)
        {
            QMessageBox ErrOverlayMsg;
            ErrOverlayMsg.setWindowTitle("Error!");
            ErrOverlayMsg.setText("Incorrect input");
            ErrOverlayMsg.setInformativeText("Please do not overlay previous countries");
            ErrOverlayMsg.exec();
        }
        else
        {
            start.SetX(start.GetX() - 1);
            start.SetY(start.GetY() - 1);
            end.SetX(end.GetX() - 1);
            end.SetY(end.GetY() - 1);
            Country *pNewCountry = new Country(this->GetCountryNumber(), start, end, this->m_aCells);

            this->m_aCountries.push_back(pNewCountry);
            this->IncCountryNum(1);
            ui->CountryNum->setText(QString::number(this->GetCountryNumber()));
        }
    }
    else
    {
        QMessageBox ErrInputMsg;
        ErrInputMsg.setWindowTitle("Error!");
        ErrInputMsg.setText("Incorrect input");
        ErrInputMsg.setInformativeText("Please input integer coords > 0");
        ErrInputMsg.exec();
    }
}

/* Checking if all countries have each other currencies */
bool Map::CheckAll()
{
    for(int i = 0; i < this->m_aCountries.size(); i++)
    {
        if(!this->m_aCountries[i]->CheckVaultNumber(m_aCountries.size()))
            return false;
    }
    return true;
}

/* Stepping through days */
void Map::on_StepButton_clicked()
{
    int iStepsNum = ui->inputStep->text().toInt();
    this->IncreaseDaysWorked(iStepsNum);
    for(int j = 0; j < iStepsNum; j++)
    {
        if(CheckAll())
        {
            this->IncreaseDaysWorked(j + 1);
            QMessageBox DoneMsg;
            DoneMsg.setWindowTitle("Done!");
            DoneMsg.setText("All Cities have all currencies");
            DoneMsg.setInformativeText("Days: " + QString::number(this->GetDaysWorked()));
            DoneMsg.exec();
            break;

        }
        for(int i = 0; i < this->m_aCountries.size(); i++)
            this->InitTransactionForCountry(this ,this->m_aCountries[i]);
    }
    UpdateMap();
}
