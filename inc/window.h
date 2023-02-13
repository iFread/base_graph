#ifndef WINDOW_H
#define WINDOW_H
#include <Fl/Fl_Window.H>
#include <Fl/Fl.H>
#include <string>
#include <vector>
#include "base_graph.h"
#include "base_gui.h"
//#include "graph/point.h"
namespace Graph {

//using common::Point;
//class Point;
//class Widget;
inline int gui_run(){return Fl::run();}

class window:public Fl_Window
{
//std::vector<Shape*> shapes;
// std::vector<Shape*> own_shapes;

 std::vector<Widget*> wid;
int w_,h_;
public:
    window(Point p,int w,int h,const char* s);
void draw()override;
virtual ~window() ;

//template<typename T>
//void attach(T t){
//std::cout<<"global\n";
//}

// Shape не нужен, т.к. работаем только с Widget
//  Для std::vector<Shape*> используем отдельный виджет work_field, который позволяет работать с рисунками
//template<typename T >
//void attach(T &&sh) {   //  rect & &&

//own_shapes.push_back(new T(std::move(sh)));
//}

 template<typename T>
void attach  (T &N){
   wid.push_back(&N);
   begin();
   N.attach(*this);
   end();
}


//template<typename T>
//void attach (T& sh)
//{ // нужно добавлять наследника
//shapes.push_back(&sh);
//}

//template<typename T=Widget>

//template<typename T=Widget>



// void attach(Shape*)
void detach(Shape& sh);
void detach(Shape&& sh); // сравнение sh
};

}
#endif // WINDOW_H
