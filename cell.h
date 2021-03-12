#ifndef CELL_H
#define CELL_H

#include <QPushButton>

class Cell : public QPushButton
{
    Q_OBJECT
public:
    explicit Cell(QPushButton *parent = nullptr);

signals:

};

#endif // CELL_H
