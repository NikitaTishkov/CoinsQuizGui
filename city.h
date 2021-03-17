#ifndef CITY_H
#define CITY_H

#include <QPushButton>
#include <QMap>
#include "point.h"
#define COINS_PER_DAY 1000
#define INITIAL_COINS_IN_CITY 1000000
class City : public QPushButton
{
    Q_OBJECT
public:
    explicit City(QPushButton *parent = nullptr);
    City(QPushButton *parent, int X, int Y, bool bIsCity);
    void SetCellParams(int X, int Y, bool bIsCity = false);

    /* Set of function for manipulating
     *              Coords*/
    void SetCoord(int xNew, int yNew);
    void SetCoordX(int xNew);
    void SetCoordY(int yNew);
    Point GetCoord();

    void SetIsCity(bool bIsCityNew);
    bool GetIsCity();

    void SetCountryID(int IDNew);
    int GetCoutnryID();

    bool IsNeighbourTo(City Neighb);
    int GetVaultSum();
    int GetForeignSum();
    void IncreaseVaultVal(int ID, int iVal);
    void DecreaseVaultVal(int ID, int iVal);
    void ChangeVaultVal(int ID, int iValNew);
    /* City:: is_valid
       CHECK: if it can be private*/
    bool CheckVault();

    void SendMoney(City *Neighb);
    void UpdateCityInfo();
    bool IsThereAllCurrsInCity(int iNum);
private:
    Point m_Coord;
    /* If it is City = true */
    bool m_bIsCity;
    int m_iCountryID;
    QMap<int, int> m_aVault;
signals:

};

#endif // CITY_H
