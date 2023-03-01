 #include "base_tools.h"
#include "own_gui_widgets.h"

namespace Graph {


void creat_tool::set_shape(creat_ptr ptr) {
create=ptr;
}

//enum canvas_event{.// основные event для canvas ...}
void creat_tool:: action(Canvas *c, int ev){
// создание фигуры
   // для взаимодействия с клавиатурой Fl_Widget должен быть активным
Fl::focus(&c->content());
    if(stage==none_sh && ev==FL_PUSH) {
      if(create && Fl::event_button1())
      { current=create(c->cursor_position());
         c->add(current);
         stage=modify_sh; }}

 else if (stage==modify_sh){  // если фигура создана можно завершить модификацию, или модифицировать фигуру
      switch (ev)
      {
      case FL_MOVE: // change виртуальная функция
            // здесь нужно как то определять вершину для изменения
           current->change(c->cursor_position());
          break;
            // проблема: как добавлять новые точки в фигуры типа полигона и ломанной
       case FL_PUSH:
      switch (Fl::event_button())
      {
       case FL_LEFT_MOUSE:  // левая кнопка, сохраняет фигуру, переводим в раздел готова
        if(current->type()==Shape::none_)
          {  stage=ready_sh;
             break;
            }
          current->add(c->cursor_position());
          break;
      case FL_RIGHT_MOUSE: // удалить фигуру, из canvas
  if(current->type()==Shape::none_){
          c->remove(current);
           current=nullptr;
          stage=none_sh;
          break;}
  // для polyline and polygon  убираем последнюю точку
   current->remove(current->size()-1);
          stage=ready_sh;
              break;
        }
          break;
      default:
          std::cout<<"unknoun event :"<<ev<<"\n";   }}

  else {
        // при установке ready_sh  фигура должна быть выделенной , в этот момент ее можно удалить правой кнопкой
     if(ev==FL_PUSH) {
      if(Fl::event_button()==FL_RIGHT_MOUSE)
       {
          c->remove(current);
             current=nullptr;
             stage=none_sh;
     }
      if(Fl::event_button()==FL_LEFT_MOUSE)
         {
          current=nullptr;
          stage=none_sh;
       }
     }
  if(Fl::event_key(FL_Delete)){
      c->remove(current);
         current=nullptr;
         stage=none_sh;
   }
    }
}





//  if(current){
 //    current->change(2,c->cursor_position());

 //  else
  //  if(create){
     //create(c->cursor_position()));
        // c->set_tool()


// в tool мщжем проверять состояние



Shape* get_line(Point p){

    return new line(p,p);
}

Shape* get_rectangle(Point p){
    return new rectangle(p,p);
}
Shape* get_polyline(Point p) {
     lines* pl= new lines(p);
           pl->add(p);
           return pl; }

}
