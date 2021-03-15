#ifndef MAP_H
#define MAP_H

#include "country.h"
#include "city.h"
#include <QVector>
#include <QVector2D>
#include <QDialog>
#include <QGridLayout>

namespace Ui {
    class Map;
}

class Map : public QDialog
{
    Q_OBJECT

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
protected:

    static Map *ptrMap_;
    explicit Map(QWidget *parent = nullptr, int iRaws = 0, int iCols = 0);


    City **m_aCells;
    QVector<Country*> m_aCountries;



private slots:
    void on_AddCountryButton_clicked();

private:
    Ui::Map *ui;
    int m_iSize_x;
    int m_iSize_y;
    int m_iCountryNumber;

};

bool CheckMapSize(int raws, int cols);

#endif // MAP_H
