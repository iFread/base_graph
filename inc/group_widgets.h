#ifndef GROUP_GUI_WIDGETS_H
#define GROUP_GUI_WIDGETS_H

#include "base_gui.h"
#include <vector>
#include <FL/Fl_Group.H>

class Fl_Scroll;


namespace Graph {



class ref_vector{
 std::vector<Widget*> owns;
 std::vector<Widget*> data;

public:
 void add(Widget&& t){
    owns.push_back(&t.create());   // создать виджет и дпометить как собственный
    data.push_back(owns.back());  // вектор для управления виджетами
  }

ref_vector(){}
 ref_vector(const ref_vector& v)=delete;
ref_vector& operator=(const ref_vector&)=delete;

ref_vector(ref_vector&& v):owns(std::move(v.owns)),data(std::move(v.data)) {

 }
ref_vector& operator=(ref_vector&& v) {
owns=std::move(v.owns);
data=std::move(v.data);

    return *this;}


 void add(Widget &w){
 data.push_back(&w);
 }

 int size() {return data.size();}

 Widget& operator[](int i) {return *data[i];} // проверка на диапазон
 const Widget& operator[](int i) const {return *data[i];}

~ref_vector()
    {
    for(Widget* w:owns)
        delete w;
    }

};





class Layout:public Widget{
public:
    enum Kind{none,horisontal,vertical};
 // хранит собственные виджеты
// возможно виджеты должны быть одного типа, например кнопки, и т.д
private:
  // std::vector<Widget*> owns;

    Kind k_{none};
   bool resizable{true};
protected:
   Point element{0,0};
  ref_vector vec;

public:
   Layout(Point p,int ww,int hh,const std::string &s="",Kind k=none):Widget(p,ww,hh,s),k_(k){}
//  void attach(window &w);
Layout(Layout&& lv):Widget(std::move(lv)),vec(std::move(lv.vec)),k_(lv.k_){}
   ~Layout();
  Widget& operator[](int i){return vec[i];}

protected:
   void create(Point p,int w,int h);
   Widget& create()=0;
   Fl_Widget& content(){return *pw;};
   int size(){return vec.size();}
   Point children_size();
public:


   // нужно отличать изменение размера вызванное от класса window
   // и изменение размера вызванное добавлением элемента

   // размер добавляемого layout не учитывается, т.к. пустой layout, определяется размером 0,0
   // а при добавлении в него элементов, новый размер не учитывается внешним контейнером

 virtual void resize(int x,int y)=0;

  void attach(Widget&&t){
  // owns.push_back(&t.create());
vec.add(std::move(t));
  add(vec[vec.size()-1]);//reference_to<Widget>(t);

  }

  void attach(Widget&t){
  // owns.push_back(&t.create());
vec.add(t);
  add(vec[vec.size()-1]);//reference_to<Widget>(t);
  }
virtual void add(Widget& w);

protected:
  // метод add() учитывает состояние класса,
  // при добавлении виджета:
  // 1.  если класс-контейнер [Fl_Group] уже создан, т.е. pw-
  // контейнера проинициализирован, метод add() вызывает create() у добавляемого виджета
  // 2. если pw не был проинациализирован, то create() у добавляемого виджета не вызывается
  // 3. при этом метод create() у Layout, вызывает create() у всех виджетов, которые содержит


};

class HLayout:public Layout{


public:
    HLayout(Point p,int w=0,int h=0,const std::string &s=""):Layout(p,w,h,s,horisontal) {}
void resize(int x,int y);
protected:
    void add(Widget& w);
 // void create(Point p,int w,int h);
Widget& create();

};


class VLayout:public Layout{

public:
    VLayout(Point p,int w=0,int h=0,const std::string &s=""):Layout(p,w,h,s,vertical){}
void resize(int x,int y);
protected:
    void add(Widget& w);
 //  void create(Point p,int w,int h);
Widget& create();

};


// создает Fl_Group
// и принимает Widget


class Scroll:public Layout {
    Fl_Scroll* scrl{nullptr};
public:
    Scroll(Point p,int w,int h):Layout(p,w,h,"",none){}
   Scroll(Scroll&& scr):Layout(std::move(scr)),scrl(scr.scrl){scr.scrl=nullptr;}
   void create(Point p,int w,int h);
    Widget& create();
    ~Scroll();//{delete scrl;}
  void add(Widget&w);
  void resize(int x,int y);
};



}

#endif // GROUP_GUI_WIDGETS_H
