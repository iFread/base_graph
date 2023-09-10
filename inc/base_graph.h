#ifndef BASE_GRAPH_H
#define BASE_GRAPH_H
 #include <iostream>
#include "gui_attributes.h"
#include "point.h"
namespace Graph {

/*
 Вариант 1 : Представить вершины фигуры в виде сортированной структуры, например двоичной кучи
 Вариант 2: Определить экстренумы фигуры по x и у
   Тогда если точка попадает в этот промежуток, точка может наодиться внутри фигуры


*/

enum shape_type:uint8_t {sh_none_t,sh_line_t,sh_polyline_t,sh_rectangle_t,sh_polygon_t,sh_circle_t,sh_arc_t,sh_ellipse_t} ;
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
      Point content()const {return *this;}

      Vertex & operator=(const Vertex& v) =delete;

    // const Vertex* v()const {return this;}
   //  const Vertex* ccv() const {return reinterpret_cast<Vertex*>(this->Node::prev());}
   //  const Vertex*cv() const {return reinterpret_cast<Vertex*>(next());}
     Vertex* v() {return this;}
     Vertex* ccv() {return reinterpret_cast<Vertex*>(prev());}
     Vertex*cv() {return static_cast<Vertex*>(next());}

     void change(Point p){this->x()=p.x();this->y()=p.y();}

     Point operator*(){return *this;}

    void trace(std::ostream &os){
       // Vertex*p=reinterpret_cast<Vertex*>(ptr->next()) ;
       // while (p!=ptr)
        {
            os<<x()<<" "<<y()<<"\n";
        //p=reinterpret_cast<Vertex*>(p->next());
        }
}


};


// Vertex_list
 // инкапсулирует указатель на Vertex
class Vertex_list{

Vertex* ptr;
int size_{0};
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
Point remove(int index);
int size()const {return size_;}

 Vertex* operator[](int i);

 Vertex* operator[](int i)const;

//Vertex* operator->(){return ptr;}

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
public: // тип фигуры должен быть доступен, во внешней среде
     enum line_type :uint8_t {none_,open_line,close_line};
protected: // но это не точно

   Vertex_list v;
   Color lcolor{FL_BLACK};
  Line_style ls{0};
  Color fcolor{Color::invisible};
  Vertex_style vs;
  line_type type_{none_};
Point lim_x;  //vector2d
Point lim_y; // vector2d

public:
 Shape(Point a,line_type tp=none_):v(),type_(tp),lim_x({a.x_,a.x_}),lim_y({a.y_,a.y_}) {v.add(a);}
// определить copy operator=()
//Shape(const Shape&)=delete;
// Shape(const Shape& sp):v(sp.v) {}
 //Shape(Shape&& sh):v(std::move(sh.v)),lcolor(sh.lcolor),ls(sh.ls),fcolor(sh.fcolor),vs(sh.vs),type_(none_) {}
 //Shape& operator=(Shape&& sh);

 virtual ~Shape(){}

// функции для отображения фигур

// Вершины
void vertex_visible(bool b){ls.set_vertex(b);};
bool vertex_visible() const {return ls.vertex_visible();}
void set_vertex(Color c,int r=1){vs.set_vertex_style(c,r);}
 // ребра
  Color color() const{return lcolor;}
  Line_style style() const {return ls;}
  Color fillcolor() const {return fcolor;}

void set_color(Color col) { lcolor = col; }
void set_style(Line_style sty) { ls = sty; }
 void set_fillcolor(Color col) { fcolor = col; }

virtual void trace(std::ostream &os) {

    os<< get_shape_type()<<" "<<v.size()<<"\n";

    for(int i=0;i<v.size();++i)
      v[i]->trace(os);
// далее можно записать специфические данные (виртуальная функция) например радиус, или угол поворота
 }



//Vertex_list& operator->(){return v;}

// доступ только к точке
Point operator[](int i) const { return *(v[i]); }

Vertex_list& operator*(){return v;}

int size()const {return v.size();}
 void draw() const;
 void draw(Point o,int sc=1) const; // рисовать относительно точки

protected:
virtual void draw_lines() const=0;
 virtual void draw_lines(Point p,int scale ) const=0;
 void draw_vertex(Point o,int sc) const; // рисовать вершину
 // virtual???

 // изменение текущей фигуры :
public:

 virtual shape_type get_shape_type()const=0;
line_type type() const;
 void remove(int index=-1);
 virtual void change(Point p,int i=-1) =0;
 virtual void add(Point p) =0;//{v.add(p);}
 void move(int x,int y);// void move(vector2d vec){}  // {12,15} => for(auto el: v) {el.x+vec.x, el.y+vec.y }
 // Анализ фигуры :

protected:
 void set_limits(Point p); // установить экстремумы фигуры , если p, больше их
 virtual void control_limits();



public:
inline Point limit_x()const{return lim_x;}
inline Point limit_y() const {return lim_y;}

// отношения фигур
virtual bool intersect(const Shape* sh)const =0; // пересечение фигур
virtual bool contain(const Point& p)const =0;     //проверка на содержание точки
// Point point_intersect();
};
//*******************************
//      text



 // одиночная линия
class line:public Shape{

public:
    line(Point a,Point b):Shape(a){
        Shape::add(b);
                                 }
    bool intersect(const Shape* sh) const; // пересечение фигур
    bool contain(const Point &p) const;

    void change(Point p,int i=1);

    shape_type get_shape_type()const {return shape_type::sh_line_t;}
protected:
 void draw_lines()const;
 void draw_lines(Point p, int sc=1)const;
private:
 void add(Point ) {return;} // ничего не делаем
};

// линии от них наследуются полигон и ломанная линия
class lines:public Shape
{ protected:

public:

    lines(Point a,line_type tp=open_line):Shape(a,tp){}//line_type::open_line){}             // ломанная
  //  lines(Point a,Point b):Shape(a),type_(line_type::close_line){add(b);}  // полигон
   void add(Point p){Shape::add(p);}
    void change( Point p,int i=-1);

    bool intersect(const Shape* sh)const; // пересечение фигур
    bool contain(const Point& p) const;

     shape_type get_shape_type()const {return shape_type::sh_polyline_t;}
protected:
   void draw_lines()const;
   void draw_lines(Point p, int sc=1)const;

private:
//line_type type_;

};


class rectangle:  public Shape
{

public:
    rectangle(Point a,Point b,line_type tp=Shape::none_);
     void change(Point p,int i=2);
     bool intersect(const Shape* sh) const; // пересечение фигур
     bool contain(const Point &p) const;
//  bool contain(const Shape* sh) const;
      shape_type get_shape_type()const {return shape_type::sh_rectangle_t;}

protected:
void draw_lines() const;
void draw_lines(Point p, int sc=1)const;

private:
void add(Point x) {Shape::add(x);}
};


class polygon:public lines{

public:
    polygon(Point a):lines(a,lines::close_line){}
    void add(Point o);
     void change(Point p,int i=0);  //как бы получить размер фигуры?

     bool intersect(const Shape* sh) const; // пересечение фигур
     bool contain(const Point &p) const;

      shape_type get_shape_type()const {return shape_type::sh_polygon_t;}
protected:
    void draw_lines(Point p, int sc=1)const;
    // полигон выпуклый, но при изменении вершины это свойство может нарушится,
    // но для наглядности, при пересечении отображаем другим цветом
    bool isAcross(int idx=0) const; // проверка пересечения смежных ребер вершины idx с остальными
    bool isAcross(int id1,int id2) const; // проверка пересечения для конкретного ребра
};

class circle:public Shape{
 int r;

public:
 // circle состоит из двух точек, центр окружности C(x,y), и P1(C.x+r,C.y)   точка с координатами x центра +радиус, y центра,
 // таким образом радиус отдельно можно не хранить
 circle(Point p,int rad=0):Shape(p),r(rad){set_limits(p+r);set_limits(p-r);Shape::add(Point(p.x()+r,p.y()));}//{p.x()+r,p.y()+r});set_limits({p.x()-r,p.y()-r});}
  // варианты, если r<=0, то устанваливаем радиус как расстояние между точками,
   // если r>0, изменяется центр(move(shape???))
    void change(Point p,int r=-1);
   int radius()const {return r;}
    bool intersect(const Shape* sh) const; // пересечение фигур
    bool contain(const Point& p) const;
 void trace(std::ostream &os);
     shape_type get_shape_type()const {return shape_type::sh_circle_t;}
protected:
    void draw_lines(Point p,int sc=1) const;
   void draw_lines() const;
   void control_limits();
private:
    void add(Point ){return;}



};


class arc:public Shape // public circle?
{
   // содержит 3, или 4 точки
    // 1 - центр окружности, 2 радиус, 3 точка начала, 4 точка конца,
    // создание arc: 1 нажатие - установить центр, привязать r,a,b к курсору:
    // где положение курсора = a,b, а радиус расстояние до центра
    // 2 нажатие установить точку start,и привязать точку end к курсору,
      // далее отрисовываем фигуру от start до курсора мыши

    // взаимодействие с пользователем: если точка захвата лежит в сегменте круга перемещение всей фигуры
    // если точка захвата в окрестностях дуги окружности изменять углы точек start,end пропорционально движению мыши,
        // еще вариант менять значение радиуса
    // если точка захвата у одной из точек (start или end) изменять ее угол (дуга окружности увеличивается или уменьшается)
    //
public:
    arc(Point c,Point st,Point e);
    // fl_arc(c.x,c.y,r /* угол между e,st*/)

    void change(Point p,int i); // здесь можем менять точку начала, точку окончания, радиус
    bool intersect(const Shape* sh) const; //
    bool contain(const Point& p)const;
   // void trace(std::ostream &o); // для сохраниния
    shape_type get_shape_type() const {return sh_arc_t;}  // дуга окружности
protected:
    void draw_lines() const{} // not use
    void draw_lines(Point o,int sm)const;
    void control_limits();

private:
    void add(Point) {return;}

};



class ellipse:public Shape
{
    // добавляется точка центра,
//    int a_; // большая полуось
//    int b_; // малая полуось

public:
//    ellipse(Point c,int a,int b):Shape(c),a_(a),b_(b){}
    ellipse(Point c,Point p): // точка центра v[0]
        Shape(Point( c.x()>p.x()?((int)(c.x()+(c.x()-p.x()+1)/2)):((int)(c.x()+(p.x()-c.x()+1)/2)), c.y()>p.y()?((int)(c.y()+(c.y()-p.y()+1)/2)):(int(c.y()+(p.y()-c.y()+1)/2))))
//      a_(c.x()>p.x()?((c.x()-p.x()+1)/2):((p.x()-c.x()+1)/2)),
//      b_(c.y()>p.y()?((c.y()-p.y()+1)/2):((p.y()-c.y()+1)/2))
    {

       Shape::add(p);//{c.x()+v[0]a_,c.y()});
//       Shape::add({c.y()+b_,c.x()});
       // после этого меняем полуоси если  a_<b_
      /*  if(a_<b_)
        { int tmp=a_;
            a_=b_;
            b_=tmp;
       }*/ //  здесь возможно направление обхода, если по часам, точки v[1], v[2]  больше центра на a_,b_ соответственно, если против часов меньше
         // понять какая полуось больше x(или y)
//  y=kx+c, где
        //double k=(y1-y2)/(x1-x2);
      // с=y-kx;
    }

    void change(Point p,int);                   //
    bool intersect(const Shape* sh) const;      //
    bool contain(const Point &p) const;         //

    shape_type get_shape_type() const {return sh_ellipse_t;}



protected:
    void draw_lines() const {}
    void draw_lines(Point o, int sm=1) const;   //
   void control_limits();                     //
private:
   void add(Point) {return;}
   //  возвращает точку пересечения эллипса с диагональю прямоугольника, в который вписан эллипс
   Point diag(Point p);
   Point diag2(Point p);
   int a() const; // большая полуось
   int b() const;
   Point ab() const; // возвращает полуоси по x,y
};


}
#endif // BASE_GRAPH_H
