
#ifndef OWN_WIDGETS_H
#define OWN_WIDGETS_H

#include "base_gui.h"
#include "own_fl_widgets.h"
#include "base_tools.h"
#include "shape_factory.h"

namespace Graph
{
// возможно следует унаследовать от Widget общий класс,
//  и от него порождать нужные
// плюсом будет то, что в наследниках Fl_Widget, user_data можно приводить к общему наследнику,
// реализовывая таким образом различную обработку handle(event)

/*
 handle() отвечает за основные действия по модификации фигур
 получив сигнал из fl_canvas
 // обрабатываем его,
добавить фигуру:
  1. Выбран инструмент creat_tool
  2. по координатам от fl_canvas создается фигура
  3. add(tool->create()) ;
Так же и удаление фигуры
 remove(tool->remove())

 Т.к. фигуры можно копировать, можно передавать в tool копию фигуры,
  и после модификации заменять оригинал на измененную копию,
   и получить эффект, при котором будут видны изменения

4. Так же следует подумать над capche() захватом фигуры
    т.е. фигура захватывается всегда,
         например для удаления фигуры ее копия не делается
  если модификация - копируем фигуру и модифицируем копию,
  далее решаем, заменить оригинал копией или нет
        но в какой то момент принимается решение:

Исходя из user_data = parent
 Canvas сам может хранить Shape* и выводить и отображать их

 fl_canvas только определяет события и служит передатчиком сигналов родителю:

 например в handle() { ((Canvas*) user_data)->handle(e)}
 или в draw() {((Canvas*)user_data)->draw()}


*/
using tool =base_tool;
using cb_creating_t= Shape*(*)(Point);  // указатель на функцию возвращающую созданную фигуру

class File;

class Canvas: public Widget  //
{
    class cursor
    {  Shape*cursor_{nullptr};
        bool vsbl{false};
    public:
        cursor():cursor_(new rectangle({0,0},{5,5})){}
        Point position()const;
        void position(Point p);
      // если nullptr тогда все поломается
         Shape& data(){return *cursor_;}
   Shape& operator*(){return *cursor_;}
    const Shape& operator*()const{return *cursor_;}
        ~cursor(){delete cursor_;}
         void visible(bool fl){vsbl=fl;}
         bool visible() const{return vsbl;}
       void selected(Point p);
    };

     Factory factory;
     select_tool select;
     mod2 mod;
     cursor cursor;

  //   Point current{0,0};  // текущее положение мыши
   //  tool* tl_{nullptr};
public:
    Canvas(Point p,int w,int h):Widget(p,w,h){}//,cursor(new rectangle(p,p+5)){ }
  Canvas(Canvas&& c):Widget(std::move(c)){}//,tl_(c.tl_){}//,cursor(new rectangle(c.cursor_position(),c.cursor_position()+5)){}
    Widget& create();
 void create(Point p,int w,int h);
  ~Canvas();// {if(tl_) delete tl_;}
Fl_Widget& content();
Shape& operator[](int i);
//void cursor_position(Point p){current.x()=p.x();current.y()=p.y();}//cursor.position(p);}
Point cursor_position() const {return  Point (Fl::event_x()-pw->x(),Fl::event_y()-pw->y());}//current;}
void draw()const;

void add(Shape*);
void remove(Shape*);
int handle(int i);  // Для общего базового virtual int handle();
size_t count()const;
// установить либо новый инструмент creat_tool/modify_tool либо указатель на функцию создания объекта фигура
void set_tool(tool*);
void set_tool(cb_creating_t  p);
void set_tool(shape_type tp){factory.set_type(tp);select.clear();}
 void set_file(File* fl){file=fl;}
protected:
void set_parent(void *v);  // tool*

// работа с фигурами
 void creating_shape(int ev); // добавляет новую фигуру
 void selecting_shape(int ev); // выбор фигуры из уже созданных
 void modify_shape(int ev);     // изменение фигуры


// обработка курсора
//void init_cursor();



private:
//std::vector<Shape*> vec;
File *file;
 };






}

#endif

