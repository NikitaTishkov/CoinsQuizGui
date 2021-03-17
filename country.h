#ifndef COUNTRY_H
#define COUNTRY_H
#include "city.h"
#include "point.h"

#include <QVector>
class Country
{
private:
    const int m_iID;


    Point m_StartPoint;
    Point m_EndPoint;

    QVector<City*> m_aCities;




public:
    Country(int ID, Point StartP, Point EndP, City **aCities);
    int getID();
    Point GetStartCoord();
    Point GetEndCoord();
    void SetStartCoord(int X, int Y);
    void SetEndCoord(int X, int Y);
    QVector<City*> GetCitiesVector();
    void UpdateVaultInfoCountry();
    bool CheckVaultNumber(int iNum);


};

#endif // COUNTRY_H
