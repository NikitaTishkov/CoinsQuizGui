#ifndef POINT_H
#define POINT_H

/* Class representing coordinate */
class Point
{
private:
    int m_X;
    int m_Y;
public:
    Point();
    Point(int x, int y);
    void SetX(int xNew);
    void SetY(int yNew);
    int GetX();
    int GetY();
};

#endif // POINT_H
