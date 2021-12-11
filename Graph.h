#ifndef BASIS_H
#define BASIS_H
#include <Fl/Fl.H>
#include <FL/Fl_Box.H>
//#include <FL/Fl_Widget.H>
#include <FL/Fl_Window.H>
#include <FL/fl_draw.H>
#include <vector>
#include <initializer_list>
#include <iostream>
#include <cstdio>
#include <exception>

namespace  Graph_lib {


void error(const char *s);


using std::vector;
//struct point;

struct point
{
  int x;
  int y;
 point (int c1=0,int c2=0):x(c1),y(c2){}

 bool operator==(const point &p) const;
 bool operator!=(const point &p) const{return !(*this==p);}

//  bool operator!=(const point &p) const {return !(*this==p);}
};


class shape   // :public Fl_Box
{
public:
    virtual void draw();

//      Fl_Box::draw();



//    shape(int x,int y,int w=0,int h=0):Fl_Box(x,y,w,h){}
//    shape(point p,point p2):Fl_Box(p.x,p.y,p2.x,p2.y) {}
   //:Fl_Box (0,0,0,0) {}
    virtual  void add_point(point p){points.push_back(p);}
 void set_point(point p1,point p2); // установить точку p1 в p2
 virtual void move(int dx,int dy); // move shape+=dx and +=dy
 virtual ~shape(){}
 point getPoint(int i) const {return points[i];}
 int num_point() const {return int( points.size());}
protected:
 shape(std::initializer_list<point> lst);//:points{lst} {}
 shape()  {}
 virtual void draw_lines()  ;
  // :Fl_Box( 0,0,0,0) {}
private:
    shape(const shape& sh) =delete;
    shape& operator=(const shape&)=delete;
 vector<point> points;
};





class line   :  public shape
{
    point _b;
    point _e;
public:
    line(point p1,point p2):  _b(p1),_e(p2)
     {
     add_point(p1);
     add_point(p2);
    }

//   void draw()
//    {
// shape::draw();
//   // shape::Fl_Box::resize(_b.x,_b.y,_e.x,_e.y);
//  //shape::Fl_Box::draw();
//     fl_color(Fl_Color(FL_RED));
//    fl_line(_b.x,_b.y,_e.x,_e.y);
// draw_lines();
//   }


};
class lines:  public shape
{ //vector<point> points;


public:
     lines() {}
      lines(std::initializer_list<point> lst): shape{lst}{if(lst.size()%2) error("odd number of points for lines");}
   //void add_points(point p1, point p2);
    void add_line(point p1,point p2);
     void draw_lines() override ;


};


class poly:public shape // замкнутый полигон
{
  vector<point> vec;

void add_point(point p) override; // добавляет всегда предпоследнюю точку,
//void draw();

};

#endif // BASIS_H
}
