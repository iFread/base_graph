#include "Graph.h"

namespace  Graph_lib {


void error(const char *s)
{
 throw std::runtime_error(s);
}


bool point:: operator==(const point& p) const
 {
     return x==p.x && y==p.y;
 }

void shape::draw_lines()
{
    for(unsigned int i=1;i<points.size(); i+=2)
    {
        fl_line(points[i-1].x,points[i-1].y,points[i].x,points[i].y);
    }
}

void shape::draw()
{ //  Fl_Box::draw();
   fl_color(Fl_Color(FL_RED));
    draw_lines();
}

void shape::move(int dx, int dy)
{

}



// poly
void poly::add_point(point p)
{
  vec.push_back(p);
}


// lines
void lines::add_line(point p1, point p2)
{
  add_point(p1);
 add_point(p2);
}
void lines::draw_lines()
{ // Fl_Box::box(FL_UP_FRAME);
   for(unsigned int i=1;i<num_point();i+=2)
    //{
        fl_line(getPoint(i-1).x,getPoint(i-1).y,getPoint(i).x,getPoint(i).y);
    //}
//shape::draw();
}
}
