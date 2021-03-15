#include "city.h"

City::City(QPushButton *parent) : QPushButton(parent)
{

}

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
int City::GetCoordX()
{
    return this->m_Coord.GetX();
}
int City::GetCoordY()
{
    return this->m_Coord.GetY();
}


void City::SetCityOrCell(bool bIsCityNew)
{
    this->m_bCityOrCell = bIsCityNew;
}
bool City::GetCityOrCell()
{
    return this->m_bCityOrCell;
}

void City::SetCountryID(int IDNew)
{
    this->m_iCountryID = IDNew;
}

int City::GetCoutnryID()
{
    return this->m_iCountryID;
}
