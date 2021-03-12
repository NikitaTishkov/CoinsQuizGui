#ifndef CITY_H
#define CITY_H

#include "cell.h"

class City : public Cell
{
    Q_OBJECT
public:
    explicit City(Cell *parent = nullptr);

signals:

};

#endif // CITY_H
