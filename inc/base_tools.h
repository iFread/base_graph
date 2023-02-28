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

   // virtual void draw()=0;
  //  virtual void action()=0; // нужен ли здесь Canvas* p_can //
  //  virtual int handle(int e)=0;

    virtual ~base_tool(){}
protected:
     void capche(Shape* cur);  // Логика: Canvas определяет когда мышь наведена на фигуру
            // т.е. при нажатии на выделенной(подсвеченна при наведении) фигуре capche() захватывает указатель,
            // позволяя через него модифицировать фигуры

   // очищает указатель current, причем, нужно понимать владеем мы этой фигурой или нет


protected:
    Shape* current{nullptr};
};


// установка указателя функции
//class Point;
class tst_create{

public:
    Shape* operator()(Point p){return new line(p,p);}

};


class creat_tool:public base_tool
 {
   // указатель на функцию создания фигуры
    using creat_ptr= Shape*(*)(Point);


public:
    creat_tool(){}
      void set_shape(creat_ptr ptr); //create=ptr ;
      /*
       callback([](Address ,Address adr){
   reference_to<Canvas*>(adr).set_tool(creat_tool(foo)); //
         },&can)
можно перегрузить функцию  1. set_tool(tool*)
                           2. set_tool(Shape*(*ptr)()){ if(tool&& tool->type(creating))  как передать тогда  } ; //
reference_to<create_tool*>(tool)->set_shape(ptr);


*/
       // создание фигуры:
    /*   установить указатель на функцию Canvas.set_create_func()  // устанавливается через callback Button
     и будет вызываться в функции action()
        */
creat_ptr create{nullptr};
private:
                 //   action() {      // Возможно определить статический флаг, для вызова action
                                            //   if(create) current =create(Point p); // если функция установлена
                                           //..модификация созданной фигуры
                                            // if(current)  // после вызова функ
                                            // Canvas *can->add(current); // добавление фигуры в канву}
};

// функции для создания фигур

Shape* get_line(Point p);


class modify_tool:public base_tool {



};

}






#endif
