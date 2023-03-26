#include "../../inc/math/math_primitives.h"

namespace math {


line_t::line_t(Point p1,Point p2)
{
    // направляющий вектор
     Point vec {p2.x()-p1.x(),p2.y()-p1.y()};

     a=p1.y_-p2.y_;
     b=p2.x_-p1.x_;//-(p2.x_-p1.x_);
   //  c=p1.y_*p2.x_-p1.x_*p2.y_;
c=-a*p1.x_-b*p1.y_;
       // float tmp=(p2.x_-p1.x_)*p2.y_-(p2.y_-p1.y_)*p2.x_;
     //float tmp=p1.y_*p2.x_-p1.x_*p2.y_;
      // float m= a < (tmp=(c<b)?c:b)?a:tmp;

float z=std::sqrt(a*a+b*b);

    //    float m=(a<b)?((a<c)?a:c):((b<c)?b:c);
        //  float m=(vec.y_ < vec.x_)?((vec.y_ < tmp)?vec.y_:tmp ):((vec.x_< tmp)?vec.x_:tmp);
//       if(fabs(m)>2) {
//m=(m<0)?-m:m;
         a/=z;
      b/=z;
      c/=z;
// }
//c=tmp;
//        a= vec.y_;//p2.y_-p1.y_;
//        b=-vec.x_;//-(p2.x_-p1.x_);
//        c= tmp;//p1.y_*p2.x_-p1.x_*p2.y_;//tmp;//vec.x()*p2.y()-p2.x()*vec.y();

}


area_t line_t::get_area(const Point &p) const{
// подставим координаты в уравнение

    float side= a*p.x()+b*p.y()+c;

if(side>fl_eps*100) return RIGHT;  // Почему то в cam_as наоборот,
if((side<fl_eps)&& (side>-fl_eps)) return INTER;
return LEFT;
}

bool line_t::separates(const Point &p1, const Point &p2) const
{

 area_t s1=get_area(p1);
 area_t s2=get_area(p2);
 if(s1==INTER||s2==INTER)
     return false;
 return !(s1==s2);
    }
/*из формулы, решая систеиу уравнений получаем:

x=-(b2*c1-b1*c1)/(b2*a1-b1*a2)
y=-(a1*c2-a2*c1)/(b2*a1-b1*a2)
отсюда, если значенатель =0, точки пересечения не существует, прямые параллельны
но, т.к нужно абсолютное значение, используем fabs()


*/
// для определения пересечения, достаточно знать что знаменатель не равен нулю
bool line_t::intersect(const line_t &other) const
{
      return std::fabs(a*other.b-b*other.a)>=fl_eps;
}

Point line_t::point_intersect(const line_t &other) const{
    float det=a*other.b-b*other.a;
    if(fabs(det)<=0.0+fl_eps)
        return {NAN,NAN};
    float x=-(other.b*c-b*other.c)/det;
    float y=-(a*other.c-c*other.a)/det;
    return {x,y};
}



void line_t::show(std::ostream &os) const
{
    char ch1,ch2;
    ch1=(b>0)?'+':0;
    ch2=(c>0)?'+':0;

  os<<a<<"x"<<ch1<<b<<"y"<<ch2<<c<<"= 0\n";

}
// в качестве отрезка будет использоваться vector2d,
   // помимо функций отрезка, класс дополнен операциями с векторами
 // vector2d

// если хоть одна точка невалидна, создаем нулевой вектор
vector2d::vector2d(const Point &p1,const Point &p2):b(p1),e(p2)
{
  if(!(p1.isValid()&&p2.isValid())) {
      b={0,0};
      e={0,0};
  } }

bool vector2d::isNull() const
{
    return b==e; // проверить эквивалентность точек
}

float vector2d::length() const
{ // длина отрезка вычисляется по пифагору
    float x=e.x()-b.x();
    float y=e.y()-b.y();
    return sqrtf((x*x)+(y*y));
  }
// в отличие от прямой , отрезок конечен, и точка может быть расположенна впереди или позади отрезка,
 // проверяем, если точка расположенна на прямой, содержащей отрезок,
//  то нужно убедиться, что прямая лежит внутри отрезка

vector2d::quarters vector2d::direction() const
{
   if(isNull()) return none;
   if(e.x()>=b.x() && e.y()<= b.y()) return qw_one;
   if(e.x()<b.x()&&e.y()<=b.y()) return qw_two;
   if(e.x()<=b.x() && e.y()>b.y()) return qw_three;
   if(e.x()>b.x()&& e.y()>b.y()) return qw_four;
   return none;
}

area_t vector2d::get_area(const Point &p) const
{
    area_t s=line_t(begin(),end()).get_area(p);
    if(s==INTER){
      //проверить что точка между началом и концом отрезка
// проверка начала, и конца
       if(b==p) return ORIGIN;
       if(e==p) return DESTINATION;
  // далее сонаправленность отрезка, с отрезком образованным нашим началом и данной точкой
       // если направления совпадают, проверяем длину
       if(vector2d(b,p).direction()==direction()){
          if(length()>vector2d(b,p).length())
              return INTER;
       // примечание: при одинаковом направлении длина не может
          // быть одинаковой, т.к. в этом случае p==e, что было проверенно ранее
        else
           return BEHIND;
       } // если направления несовпадают, тогда точка лежит перед
       return BEYOND;
       //
       /*
  Point a=as_vector();
  Point b=segment_t(begin(),p).as_vector();
   float sa=a._x*b._y-a._y*b._x; // косое произведение
  if(sa>0.0) return RIGHT;
   return LEFT;

*/

     } return s; // иначе, слева или справа

 }

bool vector2d::contain(const Point &a) const
{    return get_area(a)==INTER;
  }
bool vector2d::intersect(const vector2d &other) const
{
    line_t ln(b,e);
    if(ln.separates(other.begin(),other.end())) {
        Point pt=ln.point_intersect(line_t(other.b,other.e));
      if(pt.isValid())
          return get_area(pt)==INTER && other.get_area(pt)==INTER;
    }
    return false;

}

Point vector2d::point_intersect(const vector2d &other) const
{
    Point pt=line_t(b,e).point_intersect(line_t(other.b,other.e));
    if(pt.isValid())
        if(get_area(pt)==INTER&& other.get_area(pt)==INTER)
            return pt;
    return {NAN,NAN};
}

}


