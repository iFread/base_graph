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

    typedef struct
    {
       Widget* w ;
         int ev ;
    }Active;
//std::vector<Shape*> shapes;
// std::vector<Shape*> own_shapes;
    Active waiting{nullptr,FL_NO_EVENT};
 std::vector<Widget*> wid;
 // создание собственных виджетов, не очень удобно,
 // для работы с ними, искать их в векторе
 std::vector<Widget*> owns;
    //
int w_,h_;
public:
    window(Point p,int w,int h,const char* s);
void draw()override;
virtual ~window() ;
void init();



//template<typename T>
//void attach(T&& w)
// \a {
//Widget*ww =new T(std::move(w));//w.create(w.position(),w.w(),w.h());
//owns.push_back(ww);
//begin();
//ww->attach(*this);
//end();
//}

// set Widget w,to which next event "event" will be send
void set_active(Widget &w, int event);

int handle(int e);
void attach  ( Widget &&N);
void attach (Widget& sh);

void detach(Widget &w);

void resize(int x,int y,int w,int h);
void detach(Shape& sh);
void detach(Shape&& sh); // сравнение sh
void hide();

};

}
#endif // WINDOW_H
