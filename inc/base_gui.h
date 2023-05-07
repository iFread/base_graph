 #ifndef BASE_GUI_H_
 #define BASE_GUI_H_

#include <Fl/Fl_Widget.H>
#include "point.h"
#include <string>
#include <vector>
 //#include "window.h"
namespace Graph {

using Address= void*;
using  Callback=void(*)(Address,Address);

template <typename T>
T& reference_to(Address ptr){return  *static_cast<T*>(ptr);}




//template <typename T> T& content(Address adr){ return *reinterpret_cast<T*>(adr);}
//template <typename T> T& content2(Widget *adr){ return *reinterpret_cast<T*>(adr);}



 class window;
class Widget {

public:
// Widget(Fl_Widget* p=nullptr):pw(p){}
    Widget(Point p, int ww, int hh,const std::string &s="", Callback cb=nullptr ):
        own(nullptr),pw(nullptr),loc(p),w_(ww),h_(hh),label(s),do_it(cb){}

    // копирование виджетов недоступно
  Widget(const Widget &w) =delete;
  Widget& operator=(const Widget& w)=delete;
 // нужно перемещение ресурса ( Fl_Widget* pw)

Widget(Widget&& w):own(w.own),pw(w.pw),loc(w.loc),w_(w.w_),h_(w.h_),label(w.label) ,do_it(nullptr){
w.pw=nullptr;
w.own=nullptr;
}
  virtual ~Widget();

protected:
 window *own;  // Fl_Widget ???
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
  void set_label(const std::string &s){label=s;if(pw)pw->label(label.c_str());}
  int w() const {return w_;}
  int h() const {return h_;}
  virtual void resize(int w,int h);
  Point position() const {return loc;}
 void set_position(Point x){loc=x;}
  void callback(Callback,Address);

  // virtual int handle(int e) {return pw->handle(e);}

   virtual void create(Point p,int w,int h)=0;
  virtual Widget& create()=0;

  //  template<typename T>
  virtual Fl_Widget& content() {return *pw;} //{return *reinterpret_cast<T&>(pw);}


  // template< class T>
   Fl_Widget& operator->(){return *pw;}
};

// this class on creating set Fl_Widget::user_data  how Widget*

class Empty:public Widget
{


public:
    Empty(Point p,int w,int h):Widget(p,w,h){}
    virtual void draw()const=0;
    virtual int handle(int e)=0;
   virtual ~Empty(){ if(pw)pw->user_data(nullptr);}
protected:
    void create(Point p,int w,int h);
    Widget& create()=0;

};

class Button:public Widget{
public:
    Button(Point x, int w,int h,const std::string &s="",Callback cb=nullptr):Widget(x,w,h,s,cb){}

   Fl_Widget& content();
protected:
   void create(Point p,int w,int h);
  virtual Widget& create();
};



class In_Box:public Widget{

public:
    In_Box(Point p,int w,int h, const std::string & s):Widget(p,w,h,s){}
    Fl_Widget& content();


    int get_int() const;
    // float get_
     std::string get_string() const;
protected:
  void create(Point p,int w,int h);
 virtual Widget& create();
};

class Out_Box:public Widget {
 public:
    Out_Box(Point p,int w,int h,const std::string &s=""):Widget(p,w,h,s){}
   void create(Point p,int w,int h);
   virtual Widget& create();
   Fl_Widget& content();
       void put(int);
       void put(float);
       void put(const std::string&s);
};

}



#endif
