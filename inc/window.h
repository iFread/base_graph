#ifndef _WINDOW_H_
#define WINDOW_H_
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

class Widget;
//template <typename T>

class window: public Fl_Window
{
//std::vector<Shape*> shapes;
// std::vector<Shape*> own_shapes;

 std::vector<Widget*> wid;
 // создание собственных виджетов, не очень удобно,
 // для работы с ними, искать их в векторе
 std::vector<Widget*> owns;
int w_,h_;
public:
    window(Point p,int w,int h,const char* s);
void draw()override;
virtual ~window() ;
void init();
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



//template<typename T>
//void attach(T&& w)
//{
//Widget*ww =new T(std::move(w));//w.create(w.position(),w.w(),w.h());
//owns.push_back(ww);
//begin();
//ww->attach(*this);
//end();
//}

// template<typename T>
void attach  ( Widget &&N);

int handle(int e);

//template<typename T>
void attach (Widget& sh);

//template<typename T=Widget>

//template<typename T=Widget>



// void attach(Shape*)
void resize(int x,int y,int w,int h);
void detach(Shape& sh);
void detach(Shape&& sh); // сравнение sh
};

}
#endif // WINDOW_H
