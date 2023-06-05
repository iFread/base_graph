 #include "base_tools.h"
#include "own_gui_widgets.h"
#include "math/math_primitives.h"

namespace Graph {


void base_tool:: capche(Shape* cur)
{
   cur->vertex_visible(true);
    cur->set_vertex(Color::red,5);
}

void base_tool::free(Shape *cur)
{
    cur->vertex_visible(false);
     cur->set_vertex(Color::black,1);
 }
void base_tool::draw(Point p) const
{
   if(current) current->draw(p);
}
//*******************************************************
void creat_tool::set_shape(creat_ptr ptr) {

    if(current)
    {

 if( stage==modify_sh && !(current->type()==Shape::none_)) // если многоугольник удаляем последнюю точку
         current->remove(current->size());

 free(current);   // востановление свойств фигуры,
      current=nullptr;
    stage=none_sh;
    }
create=ptr; // ставим указатель на новую функцию
}

//enum canvas_event{.// основные event для canvas ...}
// handle(ev);
void creat_tool:: action(Canvas *c, int ev){
// создание фигуры
   // для взаимодействия с клавиатурой Fl_Widget должен быть активным
Fl::focus(&c->content());
    if(stage==none_sh && ev==FL_PUSH) {
      if(create && Fl::event_button1())
      { current=create(c->cursor_position());
         c->add(current);
         stage=modify_sh; }
    }

 else if (stage==modify_sh) {  // если фигура создана можно завершить модификацию, или модифицировать фигуру
      switch (ev)
      {



      case FL_MOVE: // change виртуальная функция
            // здесь нужно как то определять вершину для изменения
           current->change(c->cursor_position(),current->size());
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
          std::cout<<"unknoun event :"<<ev<<"\n";
      }
    }
  else // другие события
    {
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
    c->content().redraw();
}


// ***********************************
Shape* get_line(Point p) {
    return new line(p,p);
 }

Shape* get_rectangle(Point p) {
    return new rectangle(p,p);
    }
Shape* get_polyline(Point p) {
     lines* pl= new lines(p);
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
//**********************************************
//**********************************************
// *****************selected_tool
select_tool::select_tool()//:curs(nullptr)//:base_tool(tool_type::selected_t),curs(new rectangle(s->cursor_position(),s->cursor_position()+2))
{
 //init_tree(s);// можно публично передавать вектор
}

void select_tool::init_tree(Canvas *s)
{ tr.clear();
    for(size_t i=0;i<s->count();++i)
       tr.insert(&(*s)[i]);
}

void select_tool::search_under_cursor(Shape* cursor)
{
    line ln(cursor->operator[](2),cursor->operator[](2)+2);

        auto It=tr.upper_bound(&ln);//cursor);
               auto I=tr.begin();
            //  if(It==I&&It!=tr.end()){list.push_back((*It).data);}
               for(;I!=It;I.greater_than())
                  { // здесь уже проверяем по x, чтобы незаканчивалась раньше курсора,
                   // и по y, что лежит в пределах курсора
                 // if((*I).data->limit_x().x()<cursor->limit_x().y())// && (*I).data->limit_x().x()<cursor->limit_x().y())
                      //Point y=(*I).data->limit_y();
                      //if (y.x()<cursor->limit_y().x()&& y.y()>cursor->limit_y().x())
                       //{
                  if(cursor->intersect((*I).data)||(*I).data->intersect(cursor))
                    add((*I).data); //vec.push_back( (*I).data);
                         //  }
                   }
            if(It!=tr.end()&&cursor->intersect((*It).data))
              add((*It).data);//vec.push_back( (*It).data);


}

void select_tool::action(Canvas *c, int ev)
{
    std::cout<<"select action active \n";

}
//void select_tool::draw(Point p) const
//{

//}

//********************************
//**********************************
// дерево нужно строить один раз, при установке инструмента

transform_tool::transform_tool(Canvas *can):base_tool(base_tool::transform_t),curs(new rectangle(can->position(),can->position()+5))
{
    init_tree(can);
}


void transform_tool::init_tree(Canvas *s)
{
  for(size_t i=0;i<s->count();++i)
   tr.insert(&(*s)[i]);
//tr.push_back(&(*s)[i]);
}


 void transform_tool::draw(Point p) const
 {

if(curs) {
    Fl_Color old=curs->fillcolor().as_int();

    curs->set_fillcolor(Color::grey);
    curs->draw(p);
curs->set_fillcolor(old);
}
}
// в list нельзя положить пустой указатель, т.к. при возврате будет попытка разименовать его
void transform_tool::search_under2(Shape* cursor)
{ // если в list были добавлены фигуры идем от них до новой фигуры


   if(list.size())
   {
       line ln((*cursor)[2],(*cursor)[2]+3); // формируем новую фигуру по последней точке курсора
       auto It=tr.upper_bound(&ln);   // ищем  фигуру следующую ща ней //lower_bound2(cursor);
   // ставим итератор на фигуру в списке, и добавляем фигуры если нужно
       for(auto i= tr.search(list[list.size()-1]);i!=It;i.greater_than())
       { // if((*i).data->limit_x().x()<cursor->limit_x().x()) //(*i).data->limit_x().y()>cursor->limit_x().y() &&

           //    Point y=(*i).data->limit_y();
             // if(y.x()<cursor->limit_y().x()&& y.y()>cursor->limit_y().x())
         if(cursor->intersect((*i).data))
           list.push_back( &(*i).data);

       }
    } else // если же список пуст то, первый заход , заполняем от начала до cursor
       { auto It=tr.upper_bound(cursor);
       auto I=tr.begin();
      //if(It==I){list.push_back((*It).data);}
       for( ;I!=It;I.greater_than())
          { // здесь уже проверяем по x, чтобы незаканчивалась раньше курсора,
           // и по y, что лежит в пределах курсора
         // if((*I).data->limit_x().x()<cursor->limit_x().y())// && (*I).data->limit_x().x()<cursor->limit_x().y())
              //Point y=(*I).data->limit_y();
              //if (y.x()<cursor->limit_y().x()&& y.y()>cursor->limit_y().x())
               //{
          if(cursor->intersect((*I).data))
           list.push_back( &(*I).data);
                 //  }

           }
        }
 }

void transform_tool::search_under3(Shape *cursor)
{ line ln(cursor->operator[](2),cursor->operator[](2)+2);

    auto It=tr.upper_bound(&ln);//cursor);
           auto I=tr.begin();
        //  if(It==I&&It!=tr.end()){list.push_back((*It).data);}
           for(;I!=It;I.greater_than())
              { // здесь уже проверяем по x, чтобы незаканчивалась раньше курсора,
               // и по y, что лежит в пределах курсора
             // if((*I).data->limit_x().x()<cursor->limit_x().y())// && (*I).data->limit_x().x()<cursor->limit_x().y())
                  //Point y=(*I).data->limit_y();
                  //if (y.x()<cursor->limit_y().x()&& y.y()>cursor->limit_y().x())
                   //{
              if(cursor->intersect((*I).data))
               list.push_back( &(*I).data);
                     //  }
               }
           if(It!=tr.end()&&cursor->intersect((*It).data))
               list.push_back( &(*It).data);

}

void transform_tool::search_under(Shape* cursor)
{
    auto It=tr.upper_bound(cursor);//lower_bound2(cursor);
    if(list.size())
    { // если в list есть фигуры/фигура то смещение можно посмотреть по ней
      // если It указывает на фигуру больше чем в list идем от нее до It
    // сначала убедиться что курсор покинул окрестности фигуры по x и y
//        Point x_l=list[list.size()-1]->limit_x();
//        Point y_l=list[list.size()-1]->limit_y();

//        if(cursor->limit_x().y()< list[list.size()-1]->limit_x().y()&&cursor->limit_x().x()>list[list.size()-1]->limit_x().x())
//            return;
        // if(list[list.size()-1]->contain(cursor->operator[](0))||list[list.size()-1]->contain(cursor->operator[](1)))
          //   return;

         if( !It.value ||(*It).data->limit_x().x()>list[list.size()-1]->limit_x().x())
        { // если же покинули фигуру ищем от list[size()-1] до It
          // сохраняем итератор, на фигуру не меньшую чем cursor
                rbtree<Shape*,Comparator<Shape>>::iterator i= tr.search( list[list.size()-1]);
         // очищаем список,
        clear_list();
          // идем от последнего в list
         for(;i!=It;i.greater_than())
          {   if((*i).data->limit_x().y()>cursor->limit_x().y() && (*i).data->limit_x().x()<cursor->limit_x().y())
             { Point y=(*i).data->limit_y();
                if(y.x()<cursor->limit_y().x()&& y.y()>cursor->limit_y().x())
                  list.push_back( &(*i).data);
                  }
              }
        }
         else { // если сдвинули курсор в меньшую сторону
//            for(size_t i=0;i<list.size();++i)
//      {  // если It в списке, значит курсор сместился, на уменьшение
//          if(It.value && (*It).data==list[i]){ // if((*It)->data()
//             //tr.remove(*It[]);
//             // удалить из списка адрес
//              return;

//          }
//      }
    //********************************
// востановление свойств фигур  и очищение списка
 clear_list();
    }
    } else
    // если лист пуст , то и очищать нечего

    for( auto I=tr.begin();I!=It;I.greater_than())//greater_than())
      { //Point x=(*It).data->limit_x();
             if((*I).data->limit_x().y()>cursor->limit_x().y() && (*I).data->limit_x().x()<cursor->limit_x().y())
             { Point y=(*I).data->limit_y();
                 // далее проверить что курсор попадает в область фигуры
                if(y.x()<cursor->limit_y().x()&& y.y()>cursor->limit_y().x())
                {
                // (*It).data->vertex_visible(true);
                // (*It).data->set_vertex(Color::red,5);
                   list.push_back( &(*I).data);
                     }
               }
             }
}

// логика action:
/*
 1. Если есть фигура - нужно обрабатывать ее
 2. Если фигуры нет, при движении искать подходящие варианты
 3. При нажатии захватывать фигуру (захваченную фигуру удалять из дерева, т.к. ее параметры изменятся и изменится ее положение в дереве)
---
2: поиск вариантов

*/

/*
 1. Разграничить захват одной фигуры, и нескольких фигур
   1.1 Для захвата нескольких фигур, движение с зажатой клавишей мыши,
   1.2. Если захвачено несколько фигур, модификации производятся над всеми ними


 2. Формирование области курсора: курсор представить как прямоугольник, который формируется от точки нажатия
  до точки отпускания мыши: далее по границе этого прямоугольника понимаем какие фигуры входят в него
*/

void transform_tool::action(Canvas *c, int ev)
{  // если есть добавленная вершина обрабатываем ее
  //  tr->clear();
  // смещение курсора


  Fl::focus(&c->content());

 //curs->move()//c->cursor_position(),0);
   //   line ln(c->cursor_position(),c->cursor_position()+3);

      //  инициализация объекта курсор должна поисходить по необходимости
     //..как  отображать курсор?, т.е. метод draw() из fl_canvas вызывает метод draw()  //
    switch (ev)
    {

    case FL_DRAG:

        if(Fl::event_button1())
        curs->change(c->cursor_position(),2);
           break;

case FL_MOVE:
 init_cursor(c->cursor_position());
       if(stage==transform_tool::none_md)
        { // здесь можно визуализировать изменение значка курсора, когда курсор попадает в активную область

         }
         break;

       // зажатие кнопки, зависит от текущего действия
case FL_PUSH:

 //   if(stage==transform_tool::cur_md) {
        switch (Fl::event_button()) {
     case FL_LEFT_MOUSE:
            //???
             clear_list();
         //   search_under3(curs);
      break;
     case FL_RIGHT_MOUSE:
         // если правая кнопка, нужно возвращать все как было
          stage=none_md;
          clear_list();
      break;
         }
   //  }
        break;
 case FL_RELEASE:
 //init_cursor(c->cursor_position());
        switch (Fl::event_button())
     {
         case FL_LEFT_MOUSE:
        //  curs->change(c->cursor_position(),2);
            search_under3(curs);
            for(size_t i=0;i<list.size();++i)
             if(curs->intersect(list[i]))
                capche(list[i]);

            if(list.size())
                 stage=transform_tool::cur_md;

            std::cout<<"left mouse release\n";
            init_cursor(c->cursor_position());
         break;
          case FL_RIGHT_MOUSE:
        std::cout<<"right mouse release\n";

            break;


        }
        break;

    default:
        break;
    }

    if(Fl::event_key(FL_Delete)){

        if(list.size())
        { //tr.clear();
          // std::cout<<"list size: "<<list.size()<<"\n";
          for(size_t i=list.size();i>0;--i)
            c->remove(list[i-1]);

          list.clear();
          current=nullptr;
          tr.clear();
          init_tree(c);
        }
           stage=none_md;
        }
 c->content().redraw();
 }

bool transform_tool::isAcross(Shape* sh,Shape*cur)
{  /*using namespace math;
 vector2d vec((*cur)[0],(*cur)[1]);
     for(int i=1;i<sh->size();++i)
        {if(vec.intersect(vector2d(sh->operator[](i-1),sh->operator[](i)) ))
          return true;
        }
     return false;*/
    Shape& p=*cur;
    //line ln((*cur)[0],(*cur)[2]);
    return cur->intersect(sh);//sh->contain(p[0])||sh->contain(p[2]);
}

// при захвате точки нужно изменять change(*curs[cusr.size()/2]) // (*curs)[2]

void transform_tool::init_cursor(Point p)
{
    int dx= p.x()-curs->operator[](0).x();
    int dy=  p.y()-curs->operator[](0).y();

    curs->move(dx,dy);
curs->change((*curs)[0],2);

}


}
