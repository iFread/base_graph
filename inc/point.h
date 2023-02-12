#ifndef POINT_H
#define POINT_H
#include <cmath>

const float fl_eps=0.001;
struct Point{

  //int x_,y_;
    float x_,y_;
public:
  Point (float x, float y):x_(x),y_(y){}
  Point():x_(NAN),y_(NAN) {}
  bool isValid()const {if(x_!=x_||y_!=y_) return false; return true;}
  float x() const{return x_;}
   float  y() const{return y_;}
   float & x(){return  x_;}
   float & y(){return  y_;}

  bool operator==(const Point &p) const
  {
      return fabs(x_- p.x_)< fl_eps &&fabs(y_-p.y_) < fl_eps;
  }
  bool operator!=(const Point &p) const {return !(*this==p);}
  Point operator+(float i) const {return {x_+i,y_+i};}
  Point operator-(float i) const {return {x_-i,y_-i};}
  Point operator*(float i) const {return {x_*i,y_*i};}


  // операторы работы с точкой больше оперируют векторам,


virtual ~Point(){}
};
#endif // POINT_H
