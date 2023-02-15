 #include "base_gui.h"
#include <Fl/Fl_Button.H>
#include <Fl/Fl_Output.H>
#include <Fl/Fl_Input.H>

#include <iostream>



namespace Graph {

Widget::~Widget(){
  pw->hide();
  delete pw;
 }

void Widget::attach(window &w)
{
 own=&w;
   pw=create(loc,w_,h_);

//own->attach(pw);
}

void Widget::show(){pw->show();}
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
    w_=w;
    h_=h;
  pw->resize(loc.x(),loc.y(),w_,h_);
}

void Widget::callback(Callback cb,Address adr){

  do_it=cb;
 pw->callback(reinterpret_cast<Fl_Callback*>(do_it),adr);

}

//***************************

Fl_Widget* Button::create(Point x,int w,int h)
{
    return new Fl_Button(x.x_,x.y_,w,h,label.c_str());
}


Fl_Widget& Button::content(){return *reference_to<Fl_Button*>(pw);}

//***********************************************
Fl_Widget * In_Box::create(Point x,int w,int h) {
 Fl_Input *p=
     new Fl_Input(x.x(),x.y(),w,h,label.c_str());
p->box(Fl_Boxtype:: FL_UP_FRAME  );
 p->value("27");
return p;
}
Fl_Widget &In_Box:: content(){return  reference_to<Fl_Input>(pw);}

int In_Box:: get_int() const{

   const char *s=  reference_to<Fl_Input>(pw).value();
    //return pw->;
   std::cout<<"in func, value = "<<s<<"\n";
   return  atoi(s);
}

//******************************************************************
Fl_Widget* Out_Box::create(Point p, int w, int h)
{
    return new Fl_Output(p.x(),p.y(),w,h,label.c_str());
}

Fl_Widget& Out_Box::content(){return *reference_to<Fl_Output*>(pw);}

}
