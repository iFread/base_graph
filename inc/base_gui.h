 #ifndef BASE_GUI_H_
 #define BASE_GUI_H_

#include <Fl/Fl_Widget.H>
#include "point.h"
#include <string>
namespace Graph {
class window;
using Address= void*;
using  Callback=void(*)(Address,Address);
class Widget {


public:
// Widget(Fl_Widget* p=nullptr):pw(p){}
    Widget(Point p, int ww, int hh,const std::string &s="", Callback cb=nullptr ):
        own(nullptr),pw(nullptr),loc(p),w_(ww),h_(hh),label(s),do_it(cb){}

    // копирование виджетов недоступно
  Widget(const Widget &w) =delete;
  Widget& operator=(const Widget& w)=delete;

  virtual ~Widget();

protected:
 window *own;
 Fl_Widget *pw;
 Point loc;
 int w_,h_;
 std::string label;
 Callback do_it;

 // методы работы с виджетами
public:
  void attach(window &w);
  void hide();
  void show();
  void move(int x,int y);
  int w() const {return w_;}
  int h() const {return h_;}
  Point position() const {return loc;}
   void callback(Callback,Address);
  virtual int handle(int e) {return pw->handle(e);}
  virtual Fl_Widget* create(Point p,int w,int h)=0;

//  template<typename T>
  virtual Fl_Widget& content() {return *pw;} //{return *reinterpret_cast<T&>(pw);}

};

class Button:public Widget{
public:
    Button(Point x, int w,int h,const std::string &s="",Callback cb=nullptr):Widget(x,w,h,s,cb){}
   Fl_Widget * create(Point p,int w,int h);

};

}



#endif
