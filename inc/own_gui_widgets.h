#include "base_gui.h"
#include "own_fl_widgets.h"
#include "base_tools.h"
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
using creating_t=Shape*(*)(Point);
class Canvas: public Widget  //
{
    Point current{0,0};  // текущее положение мыши
    tool* t{nullptr};
public:
    Canvas(Point p,int w,int h):Widget(p,w,h){}
  Canvas(Canvas&& c):Widget(std::move(c)),t(c.t){}
    Widget& create();
 void create(Point p,int w,int h);
  ~Canvas() {if(t) delete t;}
Fl_Widget& content();

void cursor_position(Point p){current.x()=p.x();current.y()=p.y();}
Point cursor_position() const {return current;}

void add(Shape*);
void remove(Shape*);
int handle(int i);  // Для общего базового virtual int handle();
void set_tool(tool*);
void set_tool(creating_t  p);

protected:
void set_parent(void *v);  // tool*

};






}

