 #include "base_gui.h"
#include <Fl/Fl_Button.H>
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


void Widget::callback(Callback cb,Address adr){

  do_it=cb;
 pw->callback(reinterpret_cast<Fl_Callback*>(do_it),adr);

}

//***************************

Fl_Widget* Button::create(Point x,int w,int h)
{
    return new Fl_Button(x.x_,x.y_,w,h,label.c_str());
}





}
