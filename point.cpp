#include "point.h"

Point::Point()
{

}

Point::Point(int xNew, int yNew)
    : m_X(xNew), m_Y(yNew)
{}

void Point::SetX(int xNew)
{
    this->m_X = xNew;
}
void Point::SetY(int yNew)
{
    this->m_Y = yNew;
}
int Point::GetX()
{
    return this->m_X;
}
int Point::GetY()
{
    return this->m_Y;
}
