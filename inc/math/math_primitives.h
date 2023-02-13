

#ifndef MATH_PRIMITIVES_H
#define MATH_PRIMITIVES_H

#include "../point.h"
#include "stdint.h"
#include <iostream>
namespace math
{
enum area_t : uint8_t {NONE,LEFT,RIGHT,INTER,BEHIND,BEYOND,ORIGIN,DESTINATION};

class line_t{

    float a,b,c;
public:
    line_t(Point a,Point b);
    area_t get_area(const Point &p) const;
    bool separates(const Point &p1, const Point &p2) const;
    bool intersect(const line_t &other) const;
   // точка должна быть float
    Point point_intersect(const line_t & other) const;

    void show(std::ostream &os)const;
};


// класс отрезка vector2d : если линия бесконечна, то отрезок ограничен точками
class vector2d {
Point b,e;
public:
  // в качестве направления вектора используем четверти окружности
// предполагаем, что начало отрезка, лежит в начале координат,
// и отрезок продолжается в одну из четвертей, при этом,
// ели отрезок лежит на одной из осей, т.е. одна из его координат не меняется
//  относить его одинаково, например к меньшей четверти
//private:
enum quarters:uint8_t {none,qw_one,qw_two,qw_three,qw_four};

public:
vector2d(const Point& p1={0.0,0.0},const Point &p2={0.0,0.0});
Point begin() const {return b;}
Point end() const {return e;}

bool isNull() const;
float length() const ;
bool contain(const Point &a) const;
quarters direction() const;
area_t get_area(const Point &p) const;

bool intersect(const vector2d & other) const;
Point point_intersect(const vector2d& other) const; // --

};
//

}



#endif // MATH_PRIMITIVES_H
