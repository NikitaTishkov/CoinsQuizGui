#include "country.h"

Country::Country(int ID, Point StartP, Point EndP, City **aCities)
    : m_iID(ID),
      m_StartPoint(StartP),
      m_EndPoint(EndP)
{
    for(int i = StartP.GetY(); i <= EndP.GetY(); i++)
    {
        for(int j = StartP.GetX(); j <= EndP.GetX(); j++)
        {
            aCities[i][j].SetCountryID(ID);
            aCities[i][j].SetCityOrCell(true);
            QString qs_id = QString::number(ID);
            aCities[i][j].setText(qs_id);
            this->m_aCities.push_back(&aCities[i][j]);
        }
    }
}

void Country::SetStartCoord(int X, int Y)
{
    this->m_StartPoint.SetX(X);
    this->m_StartPoint.SetY(Y);
}

void Country::SetEndCoord(int X, int Y)
{
    this->m_EndPoint.SetX(X);
    this->m_EndPoint.SetY(Y);
}

Point Country::GetStartCoord()
{
    return this->m_StartPoint;
}

Point Country::GetEndCoord()
{
    return this->m_EndPoint;
}
