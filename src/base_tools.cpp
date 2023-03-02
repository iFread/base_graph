 #include "base_tools.h"
#include "own_gui_widgets.h"

namespace Graph {


void creat_tool::set_shape(creat_ptr ptr) {

    if(current)
    {

 if( stage==modify_sh && !(current->type()==Shape::none_)) // если многоугольник удаляем последнюю точку
         current->remove(current->size());

 free(current);
      current=nullptr;
    stage=none_sh;
    }
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

 else if (stage==modify_sh) {  // если фигура создана можно завершить модификацию, или модифицировать фигуру
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
            capche(current);
             break;
            }
          current->add(c->cursor_position());
          break;
      case FL_RIGHT_MOUSE: // удалить фигуру, из canvas
   if(current->type()==Shape::none_){
          c->remove(current);
           current=nullptr;
          stage=none_sh;
          break;
        }
  // для polyline and polygon  убираем последнюю точку

          current->remove(current->size());
          capche(current);
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
         free(current);
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

void creat_tool:: capche(Shape* cur){
   cur->vertex_visible(true);
    cur->set_vertex(Color::red,5);
}

void creat_tool::free(Shape *cur){
    cur->vertex_visible(false);
     cur->set_vertex(Color::black,1);


}



Shape* get_line(Point p) {
    return new line(p,p);
 }

Shape* get_rectangle(Point p) {
    return new rectangle(p,p);
    }
Shape* get_polyline(Point p) {
     lines* pl= new lines(p,Shape::close_line);
           pl->add(p);
           return pl; }
Shape* get_polygon(Point p) {
     polygon* pl= new polygon(p);
     pl->add(p);
           return pl; }
Shape *get_circle(Point p)
{
    return new circle(p);
}
}
