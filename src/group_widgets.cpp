#include "group_widgets.h"
#include <Fl/Fl_Box.H>
#include <Fl/Fl_Pack.H>
#include <iostream>
#include <typeinfo>

namespace Graph {


void Layout::create(Point o,int w,int h)
{
pw= new Fl_Group(o.x(),o.y(),w,h);
pw->box(Fl_Boxtype::FL_BORDER_BOX);
element=loc;
 for(int i=0;i<size();++i)
  {   owns[i]->create(owns[i]->position(),owns[i]->w(),owns[i]->h());
   reference_to<Fl_Group>(pw).add(owns[i]->content());
 }
}

void Layout::add(Widget &w){
    w.set_position(element);
    w.create({element.x(),element.y()},w.w(),w.h());
      // t.create({loc.x()+w().position().x(),loc.y()+w().position().y()},w.w(),w.h());
    element={element.x()+w.w(),element.y()+w.h()};
     reference_to<Fl_Group>(pw).add(w.content());
}

// нужно отличать изменение размера вызванное от класса window
// и изменение размера вызванное добавлением элемента
void Layout::resize(int x, int y){

   //  if( resizable){
//    reference_to<Fl_Group>(pw).resize(loc.x_,loc.y_,x,y); //  Widget::resize(x,y);
         w_=x;
         h_=y;   //}
//    else // изменение размера без изменения виджета
if(pw) {
 reference_to<Fl_Group>(pw).resize(loc.x_,loc.y_,w_,h_);
  //reference_to<Fl_Group>(pw).resize(loc.x_,loc.y_,content().w(),content().h());
Point n_element={loc.x_,loc.y_};
 for(int i=0;i<size();++i)
 {   Widget & w=*owns[i];
   w.set_position(n_element);
   if(k_==horisontal)
   n_element={n_element.x()+w.w()+1,n_element.y()};
  if(k_==vertical)
     n_element={n_element.x(),n_element.y()+w.h()+1};

   w.resize(w.w(),w.h());

    }
}
 std::cout<<"size layout: "<<typeid(*this).name()<<" "<<w_<<", "<<h_<<"\n";

}

Layout::~Layout(){

  for(auto &el:owns)
      delete el;
}

//***************************
void HLayout:: add(Widget& w){
w.set_position(element);
if(pw){
w.create(element,w.w(),w.h());


reference_to<Fl_Group>(pw).add(w.content());
}
resize(this->w()+w.w(),(this->h()<w.h())?w.h():this->h());
element={element.x()+w.w(),element.y()};

}

Widget& HLayout:: create(){

    return *new HLayout(std::move(*this));

}

void HLayout:: create(Point p,int w,int h){
    Layout::create(p,w,h);
}

//**********************************
void VLayout::add(Widget &w){
    w.set_position(element);
if(pw)
   { w.create(element,w.w(),w.h());


  reference_to<Fl_Group>(pw).add(w.content());
}
 resize((this->w()<w.w())?w.w():this->w(),this->h()+w.h()+1);
element={element.x(),element.y()+w.h()+1};

}

Widget& VLayout:: create(){

    return *new VLayout(std::move(*this));

}

void VLayout::create(Point p, int w, int h){
    Layout::create(p,w,h);
}



}

