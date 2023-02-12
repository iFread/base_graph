#ifndef WINDOW_H
#define WINDOW_H
#include <Fl/Fl_Window.H>
#include <Fl/Fl.H>
#include <string>
#include <vector>
#include "base_graph.h"
//#include "graph/point.h"
namespace Graph {

//using common::Point;
//class Point;

inline int gui_run(){return Fl::run();}

class window:public Fl_Window
{
std::vector<Shape*> shapes;
 std::vector<Shape*> own_shapes;
int w_,h_;
public:
    window(Point p,int w,int h,const char* s);
void draw()override;
virtual ~window() ;


template<typename T>
void attach(T &&sh) {   //  rect & &&

own_shapes.push_back(new T(std::move(sh)));
}

 template<typename  T>
void attach(T& sh)
{ // нужно добавлять наследника
 shapes.push_back(&sh);
}


// void attach(Shape*)
void detach(Shape& sh);
void detach(Shape&& sh); // сравнение sh
};

}
#endif // WINDOW_H
