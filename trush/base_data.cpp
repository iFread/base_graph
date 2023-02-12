#include "base_data.h"
#include <cmath>
#include<iostream>
int nod(int a,int b)
{
    while(a!=b)
    {
        if(a>b)
            a-=b;
        else b-=a;
    }
    return a;
}



bool point_t::isValid()const
{  // валидность точки
    if(x!=x||y!=y) return false;
    return true;
}

bool point_t::isEqual(const point_t &p) const
{
   if(isValid())  //x-p.x       p.x-x;
      if((std::fabs(x-p.x)<ftolerance) && (std::fabs(y-p.y)<ftolerance))
       return true;
   return false;
}

// line_t


//line_t::line_t(const point_t &p1,const point_t &p2)
//{
//    float angle=std::atan((p2.y-p1.y)/(p2.x-p1.x));
//    float sin_angl=std::sin(angle);  // sin - отношение противолежащего катета к гипотенузе
//    float cos_angl=std::sqrt(1.0-sin_angl*sin_angl); // cos^2a = (1-sin^2 a) // отношение прилежащего к гипотенузе
//    point_t normal_vec={-sin_angl,cos_angl};
//    a=normal_vec.x;
//    b=normal_vec.y;
//    c=-(p1.x*normal_vec.x+p1.y*normal_vec.y);
//}



line_t::line_t(const point_t& p1,const point_t& p2)
{
  a=p1.y-p2.y;
b=p2.x-p1.x;
c=p1.x*p2.y-p2.x*p1.y;
float min=1000;

while (min>1||min<-1)
{
    min=((a<b)?((a<c)?a:c):((b<c)?b:c));//:c;
   // min=std::abs(min);
 if(min==0) break;
   a/=min;
   b/=min;
   c/=min;
 //  std::cout<<min<<" "<<a<<" "<<b<<" "<<c<<std::endl;
}  }

area_t line_t::get_side_area(const point_t & p) const
{
    float offset=a*p.x+b*p.y+c;
    if(offset>0.0+ftolerance*100)
        return LEFT_SIDE;
    if(offset>0.0-ftolerance*100)
        return INTER_SIDE;
    return RIGHT_SIDE;
}

bool line_t::separates(const point_t &p1, const point_t p2) const
{
  area_t side1=get_side_area(p1);
 area_t side2=get_side_area(p2);
 if(side1==INTER_SIDE|| side2==INTER_SIDE)
     return  false;    // одна из точек лежит на данной прямой.
 return !(side1==side2);  // если точки находятся в разных полуплоскостях вернет true

}

bool line_t::intersect(const line_t &another) const
{
    return std::abs(a*another.b-another.a*b)>=ftolerance; // если больше ftolerance пересечение есть, если меньше нету
}
 /* пересечение прямых по формуле крамора:
  *     Если прямые пересекаются то у них обеих есть точка P(x,y) для которой будет верны уравнения каждой прямой
  *    / A1*x+B1*y+C1=0
       / A2*x+B2*y+C2=0
   по Крамору  имеем, если знаменатель в пропорции нулевой,
        A1*B2-A2*B1 = 0, то система не имеет решений(прямые паралельны), или имеет бесконечно много решений(прямые совпадают)

Точка пересечения так же находится по Крамору
*/
point_t line_t:: point_of_intersect(const line_t &ln) const
{
    if(!intersect(ln)) return  point_t{}; // если пересечения нет вернем невалидную точку
    float det=a*ln.b-ln.a*b;
    float det1=-(c*ln.b-ln.c*b);
    float det2=-(a*ln.c-ln.a*c);
    return {det1/det,det2/det};
}



void line_t::print()
{

   std::cout<<a<<"x "<<b<<"y "<<c<<std::endl;
}


