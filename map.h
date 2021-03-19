#ifndef MAP_H
#define MAP_H

#include "country.h"
#include "city.h"
#include <QVector>
#include <QVector2D>
#include <QDialog>
#include <QGridLayout>
#include <QMessageBox>
#include <QMap>
namespace Ui {
    class Map;
}

class Map : public QDialog
{
    Q_OBJECT

private:
    Ui::Map *ui;
    int m_iSize_x;
    int m_iSize_y;
    int m_iCountryNumber;
    int m_iDaysWorked;

    bool CheckCountryOverlay(Point start, Point end);
    bool CheckAll();

protected:

    static Map *ptrMap_;
    explicit Map(QWidget *parent = nullptr, int iRaws = 0, int iCols = 0, int DayStart = 0);


    City **m_aCells;
    QVector<Country*> m_aCountries;

public:

    ~Map();

    static Map *GetInstance( int, int);

    Map(Map &invalid) = delete;
    void operator= (const Map &) = delete;

    int GetSizeX() {return this->m_iSize_x; };
    int GetSizeY() {return this->m_iSize_y; };
    int GetCountryNumber() {return this->m_iCountryNumber; };
    void FillingCells(City **aCellsNew);

    /* Can be EDITED in future */
    void CreatingMapViewModel(QGridLayout *Layout);

    static Map* MakeMap(int iCols, int iRaws);
    void IncCountryNum(int Inc);

    City* FindCityByCoords(int X, int Y);

    void InitTransactionForCountry(Map *map, Country *country);
    void UpdateMap();

    int GetDaysWorked();
    void IncreaseDaysWorked(int iVal);


private slots:
    void on_AddCountryButton_clicked();

    void on_StepButton_clicked();

};
/* Class independent functions */
bool CheckMapSize(int raws, int cols);
bool IsRangesOverlay(int StartX1, int EndX1, int StartX2, int EndX2);



#endif // MAP_H
