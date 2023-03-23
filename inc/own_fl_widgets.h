#ifndef OWN_FL_WIDGETS_H
#define OWN_FL_WIDGETS_H


#include <Fl/Fl.H>
#include <Fl/Fl_Widget.H>
#include <vector>

#include "base_graph.h"

/*
 класс canvas содержит std::vector<Shape*>
  и предоставляет интерфейс для их добавления/удаления, модернизации

  fl_canvas наследуется от Fl_Widget, чтобы соответствовать общей концепции,

1. определить фигуры на уровне fl_canvas,
   в этом случае удобнее обрабатывать события

2. определить фигуры на уровне Canvas
   отлавливать события придется на уровне fl_canvas,
   а реагировать на них в Canvas
   например на уровне callback


*/
using Graph:: Shape;

//class Point;
//using Graph::Shape;

class fl_canvas:public Fl_Widget{
 // в fl_canvas все Shape* принадлежат классу, т.е. любая фигура уже создана
 //   std::vector<Shape*> vec;     //  возможно ref_vector<Shape>
int w_,h_;


public:
fl_canvas(Point p, int w,int h);
~fl_canvas();    // delete Shapes

// работа с Shape

//void add(Shape*);  // Shape&
//void remove(Shape*) ;
//Shape& operator[](int i);
//size_t count() const;


// методы  Fl_Widget
void draw() override;
int handle(int e) override;

};







#endif
