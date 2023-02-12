#ifndef BASE_DATA_H
#define BASE_DATA_H
#include <cmath>
int nod(int a,int b);

const float ftolerance=0.0001;

enum area_t {LEFT_SIDE,RIGHT_SIDE,INTER_SIDE}; // принадлежность точки и прямой


struct point_t
{
    float x,y;
    point_t():x(NAN),y(NAN){}
    point_t(float a,float b):x{a},y{b}{}
 bool isValid()const;
 bool isEqual(const point_t &p) const;

};

class line_t
{
    float a,b,c;
public:
// линия задается двумя точками
    // возможно ли изменить линию,
    line_t(const point_t& p1,const point_t &p2);
   bool isValid() const;
   void print();
   area_t get_side_area(const point_t &p) const; // определяет положение точки относительно линии
  bool separates(const point_t & p1,const point_t p2) const;
                                                         // определяет разделяет ли данная линия переданные точки
bool intersect(const line_t & another) const; // определяет есть ли пересечение прямых
point_t point_of_intersect(const line_t& ln) const;
};




#endif // BASE_DATA_H
