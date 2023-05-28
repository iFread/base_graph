 #include "base_gui.h"
#include <Fl/Fl_Button.H>
#include <Fl/Fl_Output.H>
#include <Fl/Fl_Input.H>
#include "own_fl_widgets.h"
#include <typeinfo>

#include <iostream>
#include "window.h"


namespace Graph {

Widget::~Widget(){
 //  pw->hide();
//   own->detach(*this);
   // pw->user_data(0);
 if(pw){ delete pw;
 pw=nullptr;}

//own=nullptr;
 }

void Widget::attach(window &w)
{
 own=&w;
  create(loc,w_,h_);

//  /own->resizable(pw);
//own->attach(pw);
}

void Widget::show(){if(pw) pw->show();}
void Widget::hide(){if(pw)
                      pw->hide();}

void Widget::move(int x, int y){
  hide();
  loc=Point(loc.x_+x,loc.y_+y);
  pw->position(loc.x_,loc.y_);
  show();
 }

void Widget::resize(int w,int h)
{

 if( pw)
    pw->resize(loc.x(),loc.y(),w,h);
  w_=w;
  h_=h;
 //  own->redraw();

}

void Widget::callback(Callback cb,Address adr){

  do_it=cb;
 pw->callback(reinterpret_cast<Fl_Callback*>(do_it),adr);

}
// ********************EMPTY

void Empty::create(Point p,int w,int h)
{
loc=p;
w_=w;
h_=h;

 pw=new fl_empty(p,w,h);
pw->user_data(this);
}

Widget& Empty::create()
{
    return *this;
}


//***************************

void Button::create(Point x,int w,int h)
{
    loc=x;
    w_=w;
    h_=h;
   pw= new Fl_Button(x.x_,x.y_,w,h,label.c_str());
}
Widget& Button::create(){

    return *new Button(std::move(*this));
}

Fl_Widget& Button::content(){return reference_to<Fl_Button>(pw);}

//***********************************************
void In_Box::create(Point x,int w,int h) {
 //Fl_Input *p=
    loc=x;
    w_=w;
    h_=h;
    pw= new Fl_Input(x.x(),x.y(),w,h,label.c_str());
//p->box(Fl_Boxtype:: FL_UP_FRAME  );
// p->value("27");
//return p;
}

Widget& In_Box::create(){

    return *this;
}

Fl_Widget &In_Box:: content(){return  reference_to<Fl_Input>(pw);}

int In_Box:: get_int() const{

   const char *s=  reference_to<Fl_Input>(pw).value();
    //return pw->;
  // нужно проверить что строка содержит корректные числа
   // возможно перегрузить для дробных чисел, atof()
   std::cout<<"in func, value = "<<s<<"\n";
   return  atoi(s);
}
std::string In_Box::get_string() const
{
    return reference_to<Fl_Input>(pw).value();
}

//******************************************************************
void Out_Box::create(Point p, int w, int h)
{
loc=p;
w_=w;
h_=h;
   pw= new Fl_Output(p.x(),p.y(),w,h,label.c_str());
 //op->value("determinant");
  // return op;
}

Fl_Widget& Out_Box::content(){return  reference_to<Fl_Output>(pw);}


Widget& Out_Box::create(){

    return * this;
}

void Out_Box::put(int n)
{
  reference_to<Fl_Output>(pw).value(std::to_string(n).c_str());
}

void Out_Box::put(float f){
  reference_to<Fl_Output>(pw).value(std::to_string(f).c_str());
}
void Out_Box::put(const std::string &s)
{
  reference_to<Fl_Output>(pw).value(s.c_str());
}



}



