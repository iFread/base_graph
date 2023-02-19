#ifndef GROUP_GUI_WIDGETS_H
#define GROUP_GUI_WIDGETS_H

#include "base_gui.h"
#include <vector>
#include <FL/Fl_Group.H>

namespace Graph {


class Layout:public Widget{
public:
    enum Kind{none,horisontal,vertical};
 // хранит собственные виджеты
// возможно виджеты должны быть одного типа, например кнопки, и т.д
private:
   std::vector<Widget*> owns;
   Kind k_{none};
   bool resizable{true};
protected:
   Point element{0,0};


public:
   Layout(Point p,int ww,int hh,const std::string &s="",Kind k=none):Widget(p,ww,hh,s),k_(k){}
//  void attach(window &w);
Layout(Layout&& lv):Widget(std::move(lv)),owns(std::move(lv.owns)),k_(lv.k_){}
   ~Layout();
  Widget& operator[](int i){return *owns[i];}
 virtual void resize(int x,int y);
protected:
   void create(Point p,int w,int h);
   Fl_Widget& content(){return *pw;};
   int size(){return owns.size();}
public:

  // template<class T>
//  void add(Widget&w){
//owns.push_back (&w);
//w.create({element.x()+w.position().x(),element.y()+w.position().y()},w.w(),w.h());
//reference_to<Fl_Group>(pw).add(w.content());
//   }

template<class T>
  void attach(T&&t){
   owns.push_back(new T(std::move(t)));

  add(*owns.back());//reference_to<Widget>(t);

  //  Widget* w=

// reinterpret_cast<Fl_Group*>(pw)->add(ref.content());
  }

protected:
  virtual void add(Widget& w)=0;

};

class HLayout:public Layout{


public:
    HLayout(Point p,const std::string &s=""):Layout(p,0,0,s,horisontal) {}
protected:
    void add(Widget& w);
   void create(Point p,int w,int h);

};


class VLayout:public Layout{

public:
    VLayout(Point p,const std::string &s=""):Layout(p,0,0,s,vertical){}
protected:
    void add(Widget& w);
    void create(Point p,int w,int h);


};




}

#endif // GROUP_GUI_WIDGETS_H