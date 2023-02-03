#ifndef BASE_GRAPH_H
#define BASE_GRAPH_H
 #include <iostream>
#include "gui_attributes.h"
namespace Graph {


class Point{

  int x_,y_;

public:
  Point (int x,int y):x_(x),y_(y){}
  Point():x_(-9999),y_(-9999) {}
  bool isValid()const {if(x_==-9999||y_==-9999) return false; return true;}
 int &x(){return x_;}
 int& y(){return y_;}

  virtual ~Point(){}
};

class Node{

 Node* prev_,*next_;

public:
 Node():prev_(this),next_(this){}
 Node* insert(Node*);
 Node* remove();
 Node* prev(){return prev_;}
 Node* next(){return next_;}
  virtual ~Node(){}

};

class Vertex:public Node,public Point{

public:
    Vertex(Point p):Node(),Point(p){}
     Vertex(const Vertex &v)  =delete;
     Vertex(Vertex&& v)=delete;
~Vertex(){}
     // для Vertex следует определить  сравнение
     //

     Point content()const {return *this;}
     Vertex & operator=(const Vertex& v) =delete;
 //{
         //  НАшу точку выставить равной точке v
      //     this->next()=v.next();
     //    this->prev()=v.prev();
 // *reinterpret_cast<Point*>(this) =v.content();
 // return *this;
 // }

    // const Vertex* v()const {return this;}
   //  const Vertex* ccv() const {return reinterpret_cast<Vertex*>(this->Node::prev());}
   //  const Vertex*cv() const {return reinterpret_cast<Vertex*>(next());}
     Vertex* v() {return this;}
     Vertex* ccv() {return reinterpret_cast<Vertex*>(prev());}
     Vertex*cv() {return reinterpret_cast<Vertex*>(next());}


     void trace(std::ostream &os){
       // Vertex*p=reinterpret_cast<Vertex*>(ptr->next()) ;
       // while (p!=ptr)
        {os<<x()<<", "<<y()<<"\n";
        //p=reinterpret_cast<Vertex*>(p->next());
        }
}
};


// Vertex_list
 // инкапсулирует указатель на Vertex
class Vertex_list{

Vertex* ptr;
int size_;
public:
Vertex_list():ptr(nullptr),size_(0){}
Vertex_list(const Vertex_list& cv);
Vertex_list(Vertex_list&& cv);

Vertex_list& operator=(const Vertex_list& cv);

Vertex_list& operator=(Vertex_list&& vl);
// Это все нужно убрать отсюда
// Интерфейс работы с Vertex
 // добавление точек должно быть доступно только в полигоне
// но не для уже определенных фигур, как прямоугольник, окружность и т.д.
void add(Point p);
// -->  void add(Point p);   -->   // нужно добавлять вершину после определенной вершины

void add(const Vertex *v, Point p); //добавить вершину, после ,v
Vertex* remove();
int size()const {return size_;}

 Vertex* operator[](int i);

 Vertex* operator[](int i)const;
Vertex* operator->(){return ptr;}

//пройти по всему списку, и удалить вершины
// удаляем в обратном порядке

 // Только для присваивания???
void clear();

~Vertex_list() ;

};


//реcурсом  Shape должен быть контейнер содержащий  Vertex
    // и этот ресурс копируется при копировании, или перемещается при move ctor
  //  std::list<Vertex>;
 //  std::vector<Vertex*> v;


class Shape {
Vertex_list v;
   Color lcolor{Fl_Color()};
  Line_style ls{0};
  Color fcolor{Color::invisible};

public:

Shape(){std::cout<<"default shape\n";}
// определить copy operator=()
Shape(const Shape& sp):v(sp.v) {}
Shape(Shape&& sh):v(std::move(sh.v)),lcolor(sh.lcolor),ls(sh.ls),fcolor(sh.fcolor)
{}


virtual ~Shape(){}


void add(Point p){v.add(p);}
void trace(std::ostream &os) {
    Vertex*vp=v->cv();//reinterpret_cast<Vertex*>(v->next());
while(true){
 vp->ccv()->trace(os);
 vp=vp->cv();
  if(vp==v->v()){
vp->ccv()->trace(os);
 break;
  }
}
}
Vertex_list& operator->(){return v;}

//
Point operator[](int i) const { return *(v[i]); }

int size()const {return v.size();}
void draw() const;
protected:
virtual void draw_lines() const ;




};


class line:public Shape{

public:
    line(Point a,Point b){
        add(a);add(b);
                                 }

 void draw_lines()const;

};


class lines:public Shape
{
public:
    enum line_type :uint8_t {single_line, open_line,close_line};

private:
line_type type_;
};






}
#endif // BASE_GRAPH_H
