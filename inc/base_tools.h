 #ifndef BASE_TOOL_H_
#define  BASE_TOOL_H_
#include "base_graph.h"
/*
  Инструмнент может иметь собственные Shape, или нет:
Вариант 1. Может: например при модификации фигуры, инструмент получает копию и модифицирует ее,
     Для отображения должна бьть вызвана draw() инструмента

 Вариант 2: Если добавлять фигуру непосредственно в canvas, и затем удалять ее???
  -- Если в canvas фигуры хранятся в виде двоичной кучи?


*/

struct  Point;
namespace Graph {

class Shape;

class Canvas;
  // intrface


class base_tool {

public:
    enum   tool_type:uint8_t{none_t,creating_t,mogify_t};

    base_tool(tool_type tp):tp_(tp){}
   virtual ~base_tool(){}//if(current) delete current;}

    virtual void action(Canvas* c,int ev)=0; // нужен ли здесь Canvas* p_can //
  // Для дальнейшего определения функций
    //  virtual int handle(int e)=0;
   // virtual void draw()=0;
    tool_type type()const {return tp_;}
protected:
     void capche(Shape* cur);
     void free(Shape *cur);
     // Логика: Canvas определяет когда мышь наведена на фигуру
              // т.е. при нажатии на выделенной(подсвеченна при наведении) фигуре capche() захватывает указатель,
              // позволяя через него модифицировать фигуры
               // очищает указатель current, причем, нужно понимать владеем мы этой фигурой или нет
 void insert(Shape *p) ;// захват фигуры
 void erase(Shape* p); // удаление фигуры, здесь фигура уже захваченна, возможно не стоит передавать параметр
protected:
    Shape* current{nullptr};
    tool_type tp_{tool_type::none_t};
};

// !!!!
/*
 current указывает на фигуру которая не находится в canvas



*/

class creat_tool:public base_tool
 {
   // указатель на функцию создания фигуры
    using creat_ptr= Shape*(*)(Point);
 //этапы создания фигуры,
enum stage_tool:uint8_t {none_sh, modify_sh,ready_sh};

public:
    creat_tool():base_tool(tool_type::creating_t){}

   ~creat_tool() { ;}

    void set_shape(creat_ptr ptr); //create=ptr ;
 // ac
  void action(Canvas *c,int ev); // Widget *w ???
protected:  // virtual in base class??
  void capche(Shape* cur);
  void free(Shape *cur);

private:
                 //   action() {      // Возможно определить статический флаг, для вызова action
                                            //   if(create) current =create(Point p); // если функция установлена
                                           //..модификация созданной фигуры
   creat_ptr create{nullptr};                                         // if(current)  // после вызова функ
   stage_tool stage{none_sh};                                         // Canvas *can->add(current); // добавление фигуры в канву}
};
//
// функции для создания фигур

 Shape* get_line(Point p);
Shape* get_rectangle(Point p);
Shape* get_polyline(Point p);// {return new lines(p);}
Shape* get_polygon(Point p);
Shape* get_circle(Point p);
class modify_tool:public base_tool {



};

}






#endif
