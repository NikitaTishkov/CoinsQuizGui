#include "city.h"

City::City(QPushButton *parent) : QPushButton(parent)
{

}

City::City(QPushButton *parent, int X, int Y, bool bIsCity)
    : QPushButton(parent),
      m_bCityOrCell(bIsCity)
{
    this->SetCoord(X, Y);
}

void City::SetCellParams(int X, int Y, bool bIsCity)
{
    this->m_Coord.SetX(X);
    this->m_Coord.SetY(Y);
    this->m_bCityOrCell = bIsCity;
}
/* -------------- */
void City::SetCoord(int xNew, int yNew)
{
    this->m_Coord.SetX(xNew);
    this->m_Coord.SetY(yNew);
}
void City::SetCoordX(int xNew)
{
    this->m_Coord.SetX(xNew);
}
void City::SetCoordY(int yNew)
{
    this->m_Coord.SetY(yNew);
}
Point City::GetCoord()
{
    return this->m_Coord;
}
/* -------------- */
void City::SetCityOrCell(bool bIsCityNew)
{
    this->m_bCityOrCell = bIsCityNew;
}
bool City::GetCityOrCell()
{
    return this->m_bCityOrCell;
}
/* -------------- */
void City::SetCountryID(int IDNew)
{
    this->m_iCountryID = IDNew;
}

int City::GetCoutnryID()
{
    return this->m_iCountryID;
}
