#ifndef CITY_H
#define CITY_H

#include <QPushButton>
#include "point.h"
class City : public QPushButton
{
    Q_OBJECT
public:
    explicit City(QPushButton *parent = nullptr);

    /* Set of function for manipulating
     *              Coords*/
    void SetCoord(int xNew, int yNew);
    void SetCoordX(int xNew);
    void SetCoordY(int yNew);
    int GetCoordX();
    int GetCoordY();

    void SetCityOrCell(bool bIsCityNew);
    bool GetCityOrCell();

    void SetCountryID(int IDNew);
    int GetCoutnryID();
private:
    Point m_Coord;
    /* If it is City = true */
    bool m_bCityOrCell;
    int m_iCountryID;

signals:

};

#endif // CITY_H
