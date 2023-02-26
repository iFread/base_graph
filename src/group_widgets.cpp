
#include <Fl/Fl_Box.H>
#include <Fl/Fl_Pack.H>
#include <Fl/Fl_Scroll.H>
#include <iostream>
#include <typeinfo>

#include "group_widgets.h"
namespace Graph {


void Layout::create(Point o,int w,int h)
{
    loc=o;
    w_=w;
    h_=h;
std::cout<<"size layout base: "<<typeid(*this).name()<<" "<<w_<<", "<<h_<<"\n";
pw= new Fl_Group(o.x(),o.y(),w_,h_);
pw->box(Fl_Boxtype::FL_BORDER_BOX);
//reference_to<Fl_Group>(pw).end();
element=loc;

 for(int i=0;i<vec.size();++i)
  {  // vec[i].create(vec[i].position(),vec[i].w(),vec[i].h());
     // reference_to<Fl_Group>(pw).add(vec[i].content());
  add(vec[i]);
 }
  //  pw->resize(loc.x(),loc.y(),children_size().x(),children_size().y());

}

void Layout::add(Widget &w){
    w.set_position(element);
    w.create({element.x(),element.y()},w.w(),w.h());
      // t.create({loc.x()+w().position().x(),loc.y()+w().position().y()},w.w(),w.h());
    element={element.x()+w.w(),element.y()+w.h()};
     reference_to<Fl_Group>(pw).add(w.content());
}


void Layout::resize(int x, int y){

   //  if( resizable){
//    reference_to<Fl_Group>(pw).resize(loc.x_,loc.y_,x,y); //  Widget::resize(x,y);
  //        w_=x;
   // h_=y;   //}
//    else // изменение размера без изменения виджета
if(pw) {
 // reference_to<Fl_Group>(pw).resize(loc.x_,loc.y_,w_,h_);
  //reference_to<Fl_Group>(pw).resize(loc.x_,loc.y_,content().w(),content().h());
Point n_element={loc.x_,loc.y_};
Point sz={0,0};
for(int i=0;i<vec.size();++i)
 {   Widget & w= vec[i];
   w.set_position(n_element);
   if(k_==horisontal)
   n_element={n_element.x()+w.w()+1,n_element.y()};
  if(k_==vertical)
     n_element={n_element.x(),n_element.y()+w.h()+1};

   w.resize(w.w(),w.h());
sz={sz.x()+w.w(),sz.y()+w.h()};
    }
  reference_to<Fl_Group>(pw).resize(loc.x_,loc.y_,sz.x(),sz.y());
}
 std::cout<<"size layout base: "<<typeid(*this).name()<<" "<<w_<<", "<<h_<<"\n";

}
Point Layout::children_size(){
    Point sz={0,0};
    for(int i=0;i<vec.size();++i)
     {   Widget & w= vec[i];
       sz={sz.x()+w.w(),sz.y()+w.h()};
        }
    return sz;
}
Layout::~Layout(){

//  for(auto &el:owns)
//      delete el;
}

//***************************

void HLayout:: add(Widget& w){
w.set_position(element);
if(pw){
w.create(element,w.w(),w.h());


reference_to<Fl_Group>(pw).add(w.content());


//
element={element.x()+w.w(),loc.y()};
w_+=w.w();
h_=(this->h()<w.h())?w.h():this->h();
// resize(this->w()+w.w(),(this->h()<w.h())?w.h():this->h());
  }
}


void HLayout::resize(int x, int y){
    static int cnt=0;
   //   w_=x;
// h_= h_<children_size().y()? children_size().y():h_;
 w_= w_<children_size().x()? children_size().x():w_;
 // h_=y;
   std::cout<<"in cnt : "<<cnt++<<" w_= "<<w_<<", h_ ="<<h_<<" with "<<x<<", "<<y<<"\n";
if(pw)  // если pw инициализирован, изменение может прити от изменения размера окна
{
// меняем размер виджетов в группе
  reference_to<Fl_Group>(pw).resize(loc.x(),loc.y(),w_,h_);
//  loc.x()=pw->x();
//  loc.y()=pw->y();
    Point n_elem={loc.x(),loc.y()};
//int higth=0;
for(int i=0;i<size();++i)
{
 Widget& w=vec[i];
  w.set_position(n_elem);
  n_elem={n_elem.x()+w.w() ,n_elem.y()};
  w.resize(w.w(),w.h());
//higth=(higth<w.h())?w.h():higth;
 h_= h_<w.h()? w.h():h_;
  std::cout<<"next widget size {"<<w.w()<<", "<<w.h()<<"}\n";
   }
 //  reference_to<Fl_Group>(pw).resize(loc.x() ,loc.y(),children_size().x(),h_); //hight// меняем размер виджетов в группе


}
 //reference_to<Fl_Group>(pw).redraw();
 //pw->redraw();
std::cout<<"in HLayout  {"<<w()<<", "<<h()<<"}\n";
}

Widget& HLayout:: create(){

    return *new HLayout(std::move(*this));

}

// void HLayout:: create(Point p,int w,int h){
//     Layout::create(p,w,h);
// }

//**********************************
void VLayout::add(Widget &w){
    w.set_position(element);
if(pw)
   { w.create(element,w.w(),w.h());

  reference_to<Fl_Group>(pw).add(w.content());

w_=this->w()<w.w()?w.w():this->w();
 h_+=w.h();
 // resize((this->w()<w.w())?w.w():this->w(),this->h()+w.h()+1);
}
 element={loc.x(),element.y()+w.h() };

}


void VLayout::resize(int x, int y){
    static int cnt=0;
 //     w_=x;
    h_= h_<children_size().y()? children_size().y():h_;
//    w_= w_<children_size().x()? children_size().x():w_;
  //   h_=y;

    if(pw)  // если pw инициализирован, изменение может прити от изменения размера окна
    { reference_to<Fl_Group>(pw).resize(loc.x(),loc.y(),w_,h_);
    // меняем размер виджетов в группе
    Point n_elem={loc.x(),loc.y()};
  //  int width=0;
    for(int i=0;i<size();++i)
    {
     Widget& w=vec[i];
      w.set_position(n_elem);
      n_elem={n_elem.x(),n_elem.y()+w.h()};
      w.resize(w.w(),w.h());
   //   std::cout<<typeid (w).name()<<" position "<<w.content().label()<<" :"<<w.position().x()<<", "<<w.position().y()<<"\n";
   //   width=(width<w.w())?w.w():width;
   // std::cout<<typeid (w.content()).name()<<" position "<<w.content().label()<<" :"<<w.content().x()<<", "<<w.content().y()<<"\n";
   w_= w_<w.w()? w.w():w_;
    }
  //     reference_to<Fl_Group>(pw).resize(loc.x(),loc.y(),w_,children_size().y()); // меняем размер виджетов в группе
 //std::cout<<"new size {"<<this->w()<<", "<<this->h()<<"} in loc "<<loc.x()<<", "<<loc.y()<<"\n";

    }

// reference_to<Fl_Group>(pw).redraw();
std::cout<<"layout cnt = "<<cnt++<<"\n";
 //reference_to<Fl_Group>(pw).redraw();

}


Widget& VLayout:: create(){

    return *new VLayout(std::move(*this));

}

// void VLayout::create(Point p, int w, int h){
//    Layout::create(p,w,h);
// }
//*********************************************************

void Scroll::create(Point p, int w, int h) {
   // создать область скроллинга и добавить в нее элементы
 std::cout<<" create scroll :"<<w<<", "<<h<<"\n";
    scrl=new Fl_Scroll(p.x(),p.y(),w,h);
   scrl->type(Fl_Scroll::BOTH);
   // здесь добавить все виджеты
   Layout::create(p,w,h);
   for(int i=0;i<size();++i)
      { //operator[](i).create()

       scrl->add(this->operator[](i).content());

    }
std::cout<<"scroll size "<<loc.x()<<", "<<loc.y()<<" ,"<<w_<<", "<<h_<<"\n";
 // scrl->redraw();
}

  Scroll::~Scroll(){  }

  Widget& Scroll:: create(){
      return *new Scroll(std::move(*this));
    }

  void Scroll::add(Widget&w){
 //Layout::add(w);
    //  w.set_position(element);
      if(pw){
       //   scrl->begin();
      w.create(element,w.w(),w.h());
 Layout::add(w);
      //reference_to<Fl_Group>(pw).add(w.content());
      scrl->add(w.content());

     // scrl->end();
      }
 //     resize(this->w()+w.w(),(this->h()<w.h())?w.h():this->h());
  //    element={element.x()+w.w(),element.y()};

      }
  void Scroll::resize(int x,int y)
  {
    Layout::resize(x,y);
       std::cout<<"in Scroll Layout  {"<<w()<<", "<<h_<<"}\n";
     w_=x;
      h_=y;
    // reference_to<Fl_Group>(pw).resize(loc.x(),loc.y(),pw->w(),pw->h());
 // if(scrl)
     scrl->resize(loc.x(),loc.y(),scrl->w(),scrl->h());
  std::cout<<"scroll size "<<loc.x()<<", "<<loc.y()<<" ,"<<scrl->w()<<", "<<scrl->h()<<"\n";
  }





}


