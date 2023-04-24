 #include "own_gui_widgets.h"


namespace Graph {

Canvas:: ~Canvas() {
   // if(tl_) delete tl_;
       for(Shape*p: vec)
         delete p;
//       if(cursor)
//           delete  cursor;
}


void Canvas::create(Point p, int w, int h){
loc=p;
w_=w;
h_=h;
    pw=new fl_canvas(p,w,h);
   // связь с родителем по умолчанию, можно переопределить
    pw->user_data(this); //
}

Widget & Canvas::create(){
     return *new Canvas(std::move(*this));
}

Fl_Widget & Canvas::content() {

    return reference_to<fl_canvas>(pw);
}

void Canvas::add(Shape *sh)
{
    vec.push_back(sh);
// reference_to<fl_canvas>(pw).add(sh);
 }

void Canvas::remove(Shape *sh){


    for(size_t i=0;i<vec.size();++i)
 {
   if(sh==vec[i])
     {
        *vec.erase(vec.begin()+i);
       delete sh;
       break;
      }
 }
   // reference_to<fl_canvas>(pw).remove(sh);
}
void Canvas::set_parent(void *v) {

pw->user_data(v);
}

Shape& Canvas::operator[](int i)
{
   // return reference_to<fl_canvas>(pw)[i];
    return *vec[i] ;
}

void Canvas::draw()const
{
    // здесь передается реальная позиция fl_canvas, т.к. смещение позиции может быть по Fl_scroll
     //  в дальнейшем подумать, как передавать позицию pw, в loc, помещенного в Scroll контейнера
   for(size_t i=0;i<vec.size();++i)
     vec[i]->draw(Point(pw->x(),pw->y()));//reference_to<>position());
//if(tl_) tl_->draw(Point(pw->x(),pw->y()));
if(cursor.visible())
    (*cursor).draw(Point(pw->x(),pw->y()));
 //   std::cout<<"Draw Canvas calling\n";
}

size_t Canvas::count()const
{
    return vec.size();
    //return reference_to<fl_canvas>(pw).count();
}

//void Canvas::set_tool(cb_creating_t p)
//{
//    if( tl_ )
//   {   if(tl_->type()!=tool::creating_t)
//     {
//       delete tl_;
//     tl_=new creat_tool();
//     }
//    } else
//        tl_=new creat_tool();

//    reference_to<creat_tool>(tl_).set_shape(p);
//     pw->redraw();
//}

//void Canvas::set_tool(tool* tl){
//if(tl_) {delete tl_; }
//tl_=tl;
//  }

 Point Canvas::cursor::position()const
{
     return (*cursor_)[0];
}

 void Canvas::cursor::position(Point p)
 { // move cursor_ в позицию p
  cursor_->move(p.x()-(*cursor_)[0].x(),p.y()-(*cursor_)[0].y());
  cursor_->change((*cursor_)[0]+5,2);

 }

 void Canvas::cursor::selected(Point p)
 {
 cursor_->change(p,2);

 }
//void Canvas::init_cursor()
//{
//    int dx= cursor_position().x()-cursor->operator[](0).x();
//    int dy=  cursor_position().y()-cursor->operator[](0).y();

//    cursor->move(dx,dy);
////cursor->change((*cursor)[0],2);
//}

// этапы создания  фигуры:
     /*
1. Создать фигуру в заданной точке          // левая кнопка мыши
2. Модифицировать ее до нужного состояния   // движение мыши, после создания фигуры
3. Передать в canvas или удалить    // левая кнопка мыши=зафиксировать состояние фигуры (и передать в canvas)
 // либо правая кнопка удаляет фигуру


*/

int Canvas::handle(int i){
 // по ссылке удобнее: it(tl_)tl_-action(*this,i)

  /* если factory == sh_none_t
    режим захвата, (инструмент захвата)
     режим модификации  ()
 */

// создание фигуры и модификацию выделенной фигуры отделить друг от друга по принципу:
    //1. При создании фигуры не происходит выделения фигур, созданная фигура (уже является выделенной), сразу модифицируется
    //2. При модификации , необходимо сначала выделять фигуру,(т.е. если нет выделенной фигуры, или фигур модификация не включается)
    // таким образом: создали фигуру ==> модифицировали ее(после окончания модификации),==> очистить список выделения,
       // при создании фигуры доступна только модификация (изменение вершины), и никакие другие
       // создание фигуры отключается правой кнопкой мыши, при очищенном списке модификации

     // обработка создания фигуры, пока флаг создания фигуры установлен,
     // иначе будем обрабатывать выделение фигуры, и/или модификацию:
      // {модификация обрабатывается если есть выделенные фигуры, и курсор находится в области для модификации:
      //    ==> если курсор внутри фигуры, или в области фигуры(прямоугольника описанного вокруг фигуры
      //        применяется модификатор move, если же в область курсора попадает вершина фигуры
    //          применяется модификатор change() для данной вершины, или вершин, если же включен режим mod2 модификатор  rotate()
    //          вокруг точки по центру выделения )}
    if(factory.type()==sh_none_t)
    {  if(!select.isEmpty()) // обработка  модификации фигур
      {
            modify_shape(i);
           }
// если в select нет фигур пытаемся выделить
         else
         {

      selecting_shape(i);

            }
    }
      else    // add_new_shape(i)
    {
       creating_shape(i);
       }

  //  if(tl_) tl_->action(this,i);

     pw->redraw();

    return i;
}


void Canvas::modify_shape(int ev)
{
    switch (ev)
 {
      case FL_PUSH:
    { int i=0;
    i=Fl::event_clicks();
    if(i) std::cout<<"Double click detected >>"<<i<<"\n";
    }   switch (Fl::event_button())
       {
         case FL_LEFT_MOUSE:   // по движению мыши устанавливаем/сбрасываем модификатор, если установлен, применяем его,
            //если же нет, очистить select и пытаться выделить
        cursor.position(cursor_position());
            break;
         case FL_RIGHT_MOUSE:
           select.clear();
            break;
                    }
        break;
      case FL_RELEASE:
        switch (Fl::event_button())
        {
         case FL_LEFT_MOUSE:
            // если нет выделенных фигур курсор unvisible
          // select.search_under_cursor(&cursor.data());
        //    cursor.visible(false);
            break;
         case FL_RIGHT_MOUSE:
  select.clear();
   select.init_tree(this);
            break;

        }
        break;
   case FL_DRAG:
        // нужен флаг для захвата фигуры\точки
if(mod.type()==mod2::change_t)
{
    mod(select[0],cursor_position());
 } else
    for(size_t i=0;i<select.size();++i)
         mod(select[i],{cursor_position().x()-cursor.position().x(),cursor_position().y()-cursor.position().y()});
       cursor.position(cursor_position());
        break;
    case FL_MOVE: // можно изменять курсор обозначая момент когда фигуру можно выделить нажатием
std::cout<<"mod==";
if(mod.type()==mod2::change_t)
    std::cout<<"change_t\n";
else if(mod.type()==mod2::move_t)
    std::cout<<"move_t\n";
else
    std::cout<<"none_t\n";
cursor.position(cursor_position());
   mod.set_type(mod2::none_t);
   if(select.size()==1){
            for(size_t i=0;i<select.size();++i)
            {
               for(int j=0;j<select[i].size();j++)
               if(cursor.data().contain(select[i].operator[](j)))
              {   std::cout<<" Point "<<j<<"in cursor\n" ;
                 mod.set_type(mod2::change_t,j);
                 break;
               }
            }
        }
   if(mod.type()!=mod2::change_t)
        for(size_t i=0;i<select.size();++i)
        { if((select[i]).intersect(&cursor.data()))
            { // здесь проверять все фигуры, и если хоть одна попадает в

            mod.set_type(mod2::move_t);
            }
         }
break;
default:
break;    }
}


//***********************************************************************
// *****************Select Shape


void Canvas::selecting_shape(int ev)
{
    switch (ev)
    {
    case FL_PUSH:
        switch (Fl::event_button())
        { case FL_LEFT_MOUSE:  // при нажатии левой кнопки фиксируем точку курсора
                                // при отжатии расчитываем фигуры какие попали в область курсора, или  содержат/пересекают курсор
        cursor.position(cursor_position());
            cursor.visible(true);
                        break;
         case FL_RIGHT_MOUSE:
            select.clear();
            break;
        }
        break;
    case FL_RELEASE:
        switch (Fl::event_button())
        {
         case FL_LEFT_MOUSE:
            // если нет выделенных фигур курсор unvisible
         select.search_under_cursor(&cursor.data());
            cursor.visible(false);
            break;
         case FL_RIGHT_MOUSE:
  select.init_tree(this);
            break;

        }
        break;
     case FL_DRAG:
     cursor.selected(cursor_position());
      break;
     case FL_MOVE:  // при выделенной фигуре, меняем тип модификатора, если попадаем нужную в область

        break;
       }
}


//*******************************************************************
//******* создание фигуры
void Canvas::creating_shape(int ev)
{
    switch (ev)
    {
    case FL_PUSH:
        switch (Fl::event_button())
        {    // если левая кнопка мыши: создать фигуру, если она не созданна, либо дабавить точку к созданной фигуре
          case FL_LEFT_MOUSE:
           if(!select.isEmpty()) // если есть созданная фигура, и  она не простая(полигон или polyline)
          { if(select.state()==select_tool::ready_state) {
               select.clear();
             //break;
               } else  // фигура не готова
               if(select[0].type()!=Shape::none_)  // добавить к ней следующую вершину
             { select[0].add(cursor_position()); //
                   break;
                 } else // для простой фигуры очищаем select
                    {// для простой фигуры переводим в разряд готовый
                    if(select.state()!=select_tool::ready_state){
                      select.set_state(select_tool::ready_state);
                        break;
                     }

                      }
           }// else    // здесь select пуст, добавим новую фигуру
              //может быть здесь else??
             { add(factory.create(cursor_position()));// добавить в canvas/ или не добавлять в canvas???
              select.add(vec[vec.size()-1]);
              select.set_state(select_tool::modify_state);
              mod.set_type(mod2::change_t,-1);
            }
            break;
           case FL_RIGHT_MOUSE:  // для сложных фигур сначала удалить последнюю вершину
            if(!select.isEmpty())
            { if(select.state()!=select_tool::ready_state)
                {
                    if(select[0].type()!=Shape::none_)
                    {   select[0].remove(select[0].size());
                        select.set_state(select_tool::ready_state);
                        break;
                    }
                   }
                Shape& pt=select[0];
                 select.clear();
                 remove(&pt);

            } else // select пуст
                 { factory.set_type(sh_none_t);
                    select.init_tree(this);    }
        }
        break;
     case FL_RELEASE:
        switch (Fl::event_button())
        {
          case FL_LEFT_MOUSE:

            break;
          case FL_RIGHT_MOUSE:

            break;
        }

        break;
    case FL_MOVE:  // модификатор ==change(Shape,point, int n);
if(!select.isEmpty()&&select.state()==select_tool::modify_state)
{     mod(select[0],cursor_position());
// select[0].change(cursor_position());
}
     break;
     case FL_DRAG:
        break;
}

}


}

/* other variant
 *
    switch (i)
    {
    case FL_PUSH:
        switch (Fl::event_button())
   {
        case FL_LEFT_MOUSE:  // выбираем что делать: если выбран тип фигуры, создать фигуру, добавить в select, установить модификатор change()
    if(select.isEmpty()){
   if(factory.type()!=sh_none_t)    //иначе, если есть выделенная фигура, активировать модификатор ()
   {                                              // иначе пробуем выделить фигуру
    add(factory.create(cursor_position()+100));
    select.add(vec[vec.size()-1]);
        mod.set_type(transform::change_t); // для определенной вершины
    }
  } else
       select.action(this,i);  // захватить точку курсора, по отжатию определить область выделения ,
     // если же тип для создания не установлен,
            break;
       case FL_RIGHT_MOUSE:

         break;
         }
        break;
    case FL_RELEASE:
        switch (Fl::event_button())
        {
         case FL_LEFT_MOUSE:     // по отжатию левой мыши, модификатор или расчет selected
        if(select.isEmpty())
         {  select.action(this,i); // считаем новое выделение
         } else  // если же в select есть какая то фигура,- то считаем что модифицировали ее
             {
              std::cout<<"modification creating shape\n";
             tl_->action(this,i);// tl_->action(select.data()); //
               }

            break;
       case FL_RIGHT_MOUSE:
           std::cout<<"clear selected\n";
       select.clear(); // по правой кнопке очищаем
         break;
        }
        break;
    case FL_MOVE:

        break;
    case FL_DRAG:
                //
        break;
    }


*/


