#include "base_graph.h"
#include "math/math_primitives.h"

#include <typeinfo>

namespace Graph {

// добавляем к последней вершине, перед собой
Node* Node::insert(Node*n){

    n->next_=this; // мы - следующая для добавляемой
    n->prev_=prev_;// а предыдущая - наша предыдущая

    prev_->next_=n; // для текушей последней - следующей будет n
    prev_=n; // для нас n будет предыдущей
    return n;


//    next_->prev_=n;
//    n->next_=next_;   //
//    n->prev_=this;
//     next_=n;
//     return n;

}
// удаление
Node* Node::remove()
{
prev_->next_=next_;
next_->prev_=prev_;
// свои указатели на себя
prev_=this;
next_=this;
return this;

}



Point Vertex_list::remove(int index)
{
  // если есть что удалять удаляем,
 index=(index>size())?size():index;
if(ptr)
 {
 Vertex*v= operator[](index);//->remove();
 Point r=v->content();
 delete v;
 size_--;
  return r;
  }
return {NAN,NAN};
}
//********************
Vertex_list::Vertex_list(const Vertex_list& cv){
for(int i=0;i<cv.size();++i){
   add(*cv[i]);
}

}
Vertex_list& Vertex_list:: operator=(const Vertex_list& cv)
{
      //remove();  // нужно удалить все существующие точки
   clear(); //
    for(int i=0;i<size();++i){
       add(*cv[i]);
     }

    return *this;
}


Vertex_list::Vertex_list(Vertex_list&& cv):ptr(cv.ptr),size_(cv.size_){
 // move ptr;
cv.ptr=nullptr;
cv.size_=0;
}

Vertex_list& Vertex_list::operator=(Vertex_list&& vl)
{
   if(this==&vl)
       return *this;

    int tmp_sz=size_;
       size_=vl.size_;
   vl.size_=tmp_sz;
  Vertex*tmp=ptr;
 ptr=vl.ptr;
vl.ptr=tmp;

    return *this;
}

void Vertex_list::clear()
{

  for(int i=size();i>0;--i){
    remove(i);
    }

}

Vertex_list::~Vertex_list()
{
 clear();
 ptr=nullptr;
}


void Vertex_list::add(Point p)
{if(ptr)
         ptr->insert(new Vertex(p));

    else ptr=new Vertex(p);
   //  std::cout<<"insert "<<p.x()<<", "<<p.y()<<"\n";
                   size_++;
                  }

Vertex* Vertex_list::operator[](int i)
{
   // std::cout<<" input index : "<<i<<"\n";
 int cnt=(i<size_ -1)?i:size_ -1;
 Vertex*w=ptr;

 while(cnt>0) // while(cnt--){}
 {
 w=w->cv();
 cnt--;
 }

    return w;}

  Vertex* Vertex_list::operator[](int i) const
{
     Vertex*w=ptr;
   int cnt=(i<size_ -1)?i:size_-1;
   while(cnt > 0) // while(cnt--){}
        {
       w=w->cv();
       cnt--;
      }
   return w;
   }



//*****************************

//  Shape& Shape:: operator=(Shape&& sh){
//if(this==&sh)
//    return *this ;
//  v=std::move(sh.v);  // заберем данные
// lcolor=sh.lcolor;
// ls=sh.ls;
// fcolor=sh.fcolor;
// type_=sh.type_;
// return *this;
//}

  Shape::line_type Shape:: type() const {return type_;}

void Shape:: draw()const{

      Fl_Color old=fl_color();
        fl_color(lcolor.as_int());
        fl_line_style(ls.style(),ls.width());
        draw_lines();
    //draw_lines()
        fl_color(old);
        fl_line_style(0);
    }

void Shape::set_limits(Point p) // установить лимит для фигуры, если p превышает установленные
{ // control x
    lim_x=  { (p.x()<lim_x.x())?p.x():lim_x.x(),
              (p.x()>lim_x.y())?p.x():lim_x.y()
              };
 // constrol y
    lim_y ={  (p.y()< lim_y.x())?p.y():lim_y.x() ,
               (p.y()>lim_y.y())?p.y():lim_y.y()
               };
}



void Shape::add(Point p){
    v.add(p); // если точка добавляется нет смысла перебирать всю фигуру,
               // просто проверить, что данная точка лежит в диапазоне фигуры, либо изменить диапазон если это не так
set_limits(p);
}

// при удалении вершины следует так же проверять на изменение пределов

void Shape::remove(int index)
{
 // index=(index>size()-1)?size()-1:index;
   index=(index>size())?size():index;
 Point p=v.remove(index);
   if((p.x()==lim_x.x()||p.x()==lim_x.y())||p.y()==lim_y.x()||p.y()==lim_y.y())
    { control_limits();
    }
}
void Shape::draw(Point o,int sc) const {
//vertex_visible(true);
    Fl_Color old=fl_color();
  // Fl_Color f_old=fl_color()
    fl_color(lcolor.as_int());
      fl_line_style(ls.style(),ls.width());
       draw_lines(o,sc);
   if(vertex_visible())
          draw_vertex(o,sc);
      fl_color(old);
      fl_line_style(0);
}
void Shape::draw_vertex(Point p, int sc) const
{
for(int i=0;i<size();++i)
{
    int k=vs.v_r()/2;
  fl_color(vs.v_color());
  fl_pie(v[i]->x()*sc+p.x()-k,v[i]->y()*sc+p.y()-k,vs.v_r() ,vs.v_r() ,0,360);
}

}

// здесь const  метод, он не может вызывать не константные методы
 void Shape:: draw_lines()const {

 // std::cout<<typeid (this).name()<<"\n";
for(int i=1;i<v.size();i++) // перемещение
{
  fl_line(v[i-1]->x(),v[i-1]->y(),v[i]->x(),v[i]->y());
}

 }

 void Shape:: draw_lines(Point p, int scale)const{

     for(int i=1;i<v.size();i++) // перемещение
     {
       fl_line(v[i-1]->x()*scale+p.x(), v[i-1]->y()*scale+p.y(), v[i]->x()*scale+p.x(),v[i]->y()*scale+p.y());
     }


 }

void Shape::move(int x, int y)
{
 for(int i=0;i<v.size();++i)
 {
   v[i]->change({v[i]->x()+x,v[i]->y()+y});
 }
 control_limits();
}


 void Shape::control_limits()
 { // проходит по всем точкам фигуры, устанавливая максимальную,

  lim_x.x()=lim_x.y() =v[0]->x();
  lim_y.x()=lim_y.y()  =v[0]->y();
    for(int i=0;i<v.size();++i)
     {
       set_limits(*v[i]);//->content()) ;
     }

 }

// проверка, что точка лежит внутри фигуры
 bool Shape::contain(const Point &p) const
 {  using namespace math;
     // пройти по всем ребрам, определить что точка лежит с одинаковой стороны справа
   // не проверяет последнюю грань

     bool flg=true;
  for(int i=1;i<=size();++i)
   {  line_t vec(*v[i-1],*v[i]); // при i==size() вернет нулевой вектор,
     // проверка последней грани
      if(i==size())
           vec=line_t(*v[size()],*v[0]);

      if(vec.get_area(p)==LEFT)
            flg=false;
      }
     return flg;
 }
//  для каждой грани фигуры проверить, пересечение с каждой гранью другой фигуры
 bool Shape::intersect(const Shape *sh) const
 {
   for(int i=1;i<size();++i)
   {
     if(sh->contain(*v[i]))
         return true;
   }
   return false;
 }

//************************************************************
 //**********************

 void line::draw_lines()const{
 //    Shape::draw_lines();
     for(int i=1;i<v.size();i++) // перемещение
     {
       fl_line(v[i-1]->x(),v[i-1]->y(),v[i]->x(),v[i]->y());
     }
 }

 void line:: draw_lines(Point p, int scale)const{

     for(int i=1;i<v.size();i++) // перемещение
     {
       fl_line(v[i-1]->x()*scale+p.x(), v[i-1]->y()*scale+p.y(), v[i]->x()*scale+p.x(),v[i]->y()*scale+p.y());
     }
 }

 void line:: change( Point p, int i)
 {
   // для линии только 1 и 2
   //  i=(v.size()-1<i)?v.size()-1:i;
 if(p.isValid())
  {   v[i]->change(p);

  }
 control_limits();
 }

 bool line::contain(const Point &p) const
 {
     return math::vector2d(*v[0],*v[1]).contain(p);
 }
// пересечение с точки зрения линии
 bool line::intersect(const Shape *sh) const
 {

   // return Shape::intersect(sh);
 math::vector2d vec(*v[0],*v[1]);
      for(int i=1;i<sh->size();++i)
      { if(vec.intersect(math::vector2d(sh->operator[](i-1), sh->operator[](i))))
             return true  ;
     }
      return false;
 }




//***************************************************************
//***************************lines
 void lines::draw_lines()const{
for(int b=1,e= (type_==close_line)?v.size():v.size()-1;b<=e;++b) // на последней вершине так же итерируемся
{
if(type_==close_line && b==e ) {
    fl_line(v[0]->x(),v[0]->y(),v[b-1]->x(),v[b-1]->y());
    break;
}
fl_line(v[b-1]->x(),v[b-1]->y(),v[b]->x(),v[b]->y());
 }
 }

 void lines::draw_lines(Point p, int sc)const{
for(int b=1,e= (type_==open_line)?v.size():v.size();b<=e;) // на последней вершине так же итерируемся
{
 fl_line(v[b-1]->x()*sc+p.x(),v[b-1]->y()*sc+p.y(),v[b]->x()*sc+p.x(),v[b]->y()*sc+p.y());
++b;
//if(b==e)
//    break;
}
 }
 void lines:: change( Point p,int i)
 {
  // i=(v.size()-1<i)?v.size() :i;
   if(i==-1) {
        i=size() ;
      }
   if(p.isValid()) {
      v[i]->change(p);
  control_limits();}
 }
// пресечение для ломанной
bool lines::contain(const Point &p) const
{
    for(int i=1;i<size();++i)

        if(math::vector2d(*v[i-1],*v[i]).contain(p))
            return true;;
    return false;
}

bool lines::intersect(const Shape *sh) const
{
    for(int i=0;i<size();++i)
    {
       if(line(*v[i-1],*v[i]).intersect(sh))
           return true;
    }
    return false;

}



 //******************
 rectangle::rectangle(Point a,Point b,line_type tp):Shape(a,tp)
{ // добавляет еще три вершины
 Shape::add({b.x(),a.y()});
 Shape:: add(b);
 Shape::add({a.x(),b.y()});
}
 void rectangle::draw_lines() const
 {    std::cout<<typeid (this).name()<<"\n";
    std::cout<<"size is "<<v.size()<<"\n";
     for(int b=1,e=  v.size()+1;b<=e;++b) // на последней вершине так же итерируемся
     {
     if(b==e ) {
         fl_line(v[0]->x(),v[0]->y(),v[b-1]->x(),v[b-1]->y());
         break;
     }
     fl_line(v[b-1]->x(),v[b-1]->y(),v[b]->x(),v[b]->y());
     std::cout<<"iteration\n";
     }

 }
void rectangle::draw_lines(Point p,int sc) const {

    for(int b=1,e=  v.size()+1;b<=e;++b) // на последней вершине так же итерируемся
    {
    if(b==e ) {
        fl_line(v[0]->x()*sc+p.x(),v[0]->y()*sc+p.y(),v[b-1]->x()*sc+p.x(),v[b-1]->y()*sc+p.y());
        break;
    }
    fl_line(v[b-1]->x()*sc+p.x(),v[b-1]->y()*sc+p.y(),v[b]->x()*sc+p.x(),v[b]->y()*sc+p.y());

 }
}

void rectangle:: change( Point p,int i)
{ // сохранить инвариант прямоугольника
   // для этого нужна вершина диагональная данной
//i=(v.size()<i)?v.size():i;
if(i==-1) i=2;//size()/2;
v[i]->change(p);// меняем нужную вершину
Vertex* cross=v[i]->ccv()->ccv();//->content(); // соординаты противоположной точки
 // для импользования move operator, всеравно вызывать конструктор
// v= rectangle(*cross,*v[i]).v ;
int w=v[i]->x()-cross->x();//(v[i]->content()<cross)?v[i]->x()-cross.x():v[i]->x()-cross.x();
 int h=v[i]->y()-cross->y();
// меняем остальные фигуры
 cross->ccv()->change({cross->x(),cross->y()+h});
 cross->cv()->change({cross->x()+w,cross->y()});
control_limits();
}

// прямоугольник будет содержать точку, если точка лежит одинаково относительно всех его граней
bool rectangle::contain(const Point &p) const
{
//    using namespace math;
//         // пройти по всем ребрам, определить что точка лежит с одинаковой стороны справа
//       // не проверяет последнюю грань

//         //bool flg=true;
//      for(int i=1;i<=size();++i)
//       {  line_t vec(*v[i-1],*v[i]); // при i==size() вернет нулевой вектор,
//         // проверка последней грани
//          if(i==size())
//               vec=line_t(*v[size()-1],*v[0]);

//          if(vec.get_area(p)==LEFT)
//               return false;
//          }
//         return true;

bool result=false;
         for(int i=0,j=size()-1;i<size();j=i++)
{if( (v[i]->y() > p.y())!=(v[j]->y()>p.y()) &&
    (p.x()< (v[j]->x()-v[i]->x())* (p.y()-v[i]->y())/ (v[j]->y()-v[i]->y())+v[i]->x()))
     result=!result;

}

         return result;

}




//bool rectangle::contain(const Shape *sh) const
//{
//   for(int i=0;i<sh->size();++i)
//   {
//    if(contain(sh->operator[](i)))
//        return true;
//   }
//   return false;
//}

// bool rectangle::separates(Point p1,Point p2) const
bool rectangle::intersect(const Shape *sh) const
{ using namespace math;
// bool lies_in =true;
  const Shape& ref=*sh;

  for(int i=1;i<=size();++i)
    {    vector2d vec(v[i-1]->content(),v[i]->content());
               if(i==size())
             vec= vector2d (v[size()-1]->content(),v[0]->content());

        for(int j=1;j<=sh->size();++j)
        {if(vec.isNull())
               { //lies_in=false;
               // break;
                return false;
             }
            vector2d oth(ref[j-1],ref[j]);
            if(j==ref.size()&& ref.type()!=Shape::open_line)
                oth=vector2d(ref[ref.size()-1],ref[0]);
          if(vec.intersect(oth))//ref[j-1],ref[j])))
          {
              return true;
          }
        // если sh лежит снаружи прямоугольника
//        if(vec.get_area(oth.begin())==math::LEFT && vec.get_area(oth.end())==math::LEFT)

//          lies_in=false;
        }

   }
  for(int i=0;i<sh->size();++i)
   if(contain((*sh)[i]))
      return true;

    return   false;//lies_in;
}



 //******************* poligon


bool polygon::isAcross(int idx) const
{    if(size()>3)   // если у нас только меньше 4 точек, проверять не нужно
    { int next,prev;
       next=(idx==size()-1)?0:idx+1;
       prev=(idx==0)?size()-1:idx-1;
        if(isAcross(idx,next)||isAcross(idx,prev))
            return true;
    }
    return false;
}
bool polygon::isAcross(int id1,int id2) const{

if(size()>3)
{
    using namespace math ;
    vector2d v1(*v[id1],*v[id2]);
    for(int i=1;i<=size();++i){
    //  if(i==id1||i==id2) continue;
   if(i==size()) {
       if(v1.intersect({*v[i-1],*v[0]}))
           return true;
       return false;
    }
      if(v1.intersect({*v[i-1],*v[i]}))
          return true;
    }

}return false;
}

 void polygon::add(Point o){
// проверить что для  отрезков [v[0],p] и  [v[size()-1],p]  нет пересечения с другими  гранями
 // точка o - уже является вершиной полигона,- последней вершиной по индексу size()-1
    if(!isAcross(size()-1)){
        Shape::add(o);
     set_limits(o);
    }
 }

 void polygon:: draw_lines(Point p, int sc)const {
     Fl_Color old =fl_color();
     for(int b=1,e= v.size();b<= e;++b) // на последней вершине так же итерируемся
     {

         if(isAcross(b-1,b))
            fl_color(FL_RED);
       if(b==e) {
         if(isAcross(0,b-1))
          fl_color(FL_RED);
              fl_line(v[0]->x()*sc+p.x(),v[0]->y()*sc+p.y(),v[b-1]->x()*sc+p.x(),v[b-1]->y()*sc+p.y());
              fl_color(old);
            break;
      }
  fl_line(v[b-1]->x()*sc+p.x(),v[b-1]->y()*sc+p.y(),v[b]->x()*sc+p.x(),v[b]->y()*sc+p.y());

   fl_color(old);
      }
 }

 void polygon::change( Point p,int i) {
     if(i==-1) {
          i=size()-1 ;
        }
    // if(!isAcross(size()-1))
     lines:: change(p,i);

 }

 bool polygon::contain(const Point &p) const
 {
//return Shape::contain(p);
     bool result=false;
              for(int i=0,j=size()-1;i<size();j=i++)
     {if( (v[i]->y() > p.y())!=(v[j]->y()>p.y()) &&
         (p.x()< (v[j]->x()-v[i]->x())* (p.y()-v[i]->y())/ (v[j]->y()-v[i]->y())+v[i]->x()))
          result=!result;

     }

              return result;
 }
bool polygon::intersect(const Shape *sh) const
{
    using namespace math;
    // bool lies_in =true;
      const Shape& ref=*sh;

    //return rectangl::intersect(sh);
    for(int i=1;i<=size();++i)
      {    vector2d vec(v[i-1]->content(),v[i]->content());
                 if(i==size())
               vec= vector2d (v[size()-1]->content(),v[0]->content());

          for(int j=1;j<=sh->size();++j)
          {if(vec.isNull())
                 { //lies_in=false;
                 // break;
                  return false;
               }
              vector2d oth(ref[j-1],ref[j]);
              if(j==ref.size()&& ref.type()!=Shape::open_line)
                  oth=vector2d(ref[ref.size()-1],ref[0]);
            if(vec.intersect(oth))//ref[j-1],ref[j])))
            {
                return true;
            }
          // если sh лежит снаружи прямоугольника
  //        if(vec.get_area(oth.begin())==math::LEFT && vec.get_area(oth.end())==math::LEFT)

  //          lies_in=false;
          }

     }
    for(int i=0;i<sh->size();++i)
     if(contain((*sh)[i]))
        return true;

      return   false;//lies_in;

}

 //*********************circle

 void circle::draw_lines(Point p,int sc) const {

  fl_arc((v[0]->x()-r)*sc+p.x(),(v[0]->y()-r)*sc+p.y(),(r+r)*sc,(r+r)*sc,0,360);
//fl_begin_polygon();
//     fl_arc((v[0]->x())*sc+p.x(),(v[0]->y() )*sc+p.y(), (r)*sc,0,360);
// fl_end_polygon();
     //  fl_circle((v[0]->x())*sc+p.x(),(v[0]->y())*sc+p.y(), r*sc);
 }
 void circle::draw_lines() const{

 }
 // устанавливает новый радиус как расстояние между p и центром

 void circle::change( Point p,int ) {
int w=std::abs(v[0]->x()-p.x());
int h=std::abs(v[0]->y()-p.y());

 r=sqrt(w*w+h*h)+0.5;

 set_limits(*v[0]+r);
 set_limits(*v[0]-r);
 v[1]->change(Point(v[0]->content().x_+r,v[0]->content().y()));
// std::cout<<"Limits x ="<<lim_x.x()<<","<<lim_x.y()<<"\n";

// std::cout<<"Limits y ="<<lim_y.x()<<","<<lim_y.y()<<"\n";
  // устанавливаем новый предел
 }

//1. проверить , что не лежит на оси x/y


 bool circle::contain(const Point &p) const
 {
     Point s=Point(p.x()-v[0]->x(),p.y()-v[0]->y());


    if(r*r >= (s.x()*s.x()+s.y()*s.y()))
             return true;
    return false;

 }
 bool circle::intersect(const Shape *sh) const
 {
     for(int i=0;i<sh->size();++i)
     {
       if(contain(sh->operator[](i)))
           return true;
     }
     return false;
 }

 void circle::control_limits()
 {
     lim_x = Point(v[0]->x()-r,v[0]->x()+r);
     lim_y = Point(v[0]->y()-r,v[0]->y()+r);

 }

 void circle::trace(std::ostream &os)
 {
      os<< get_shape_type()<<" "<<2<<"\n";

    v[0]->trace(os);
     os<<v[0]->x()+r<<" "<<v[0]->y()<<"\n";
 }
  // ***********************************arc


arc::arc(Point c,Point a,Point b):Shape(c) {
    int r=math::vector2d(c,a).length();
    Shape::add(Point((c.x()+r),c.y()));
    Shape::add(a);Shape::add(b);
  }
 void arc::change(Point p, int i)
 {    //1. установить радиус, после первого нажатия ЛКМ
     // далее Point start=Point end= точка пересечения окружности с линией от центра до  cursor_position,

     // если изменять точку центра, это отдельный случай
int r=0;

     if(i==-1||i==1) // if()
  {
    int r= std::abs(v[0]->x()-p.x());//math::vector2d(v[0]->x(),p.x()).length()+0.5;
  v[1]->change(Point(v[0]->content().x()+r,v[0]->content().y()));

  double angl1=  atan2(v[2]->y()-v[0]->y(),v[2]->x()-v[0]->x());

  // после смены радиуса v[2],v[3] нужно переместить на новый радиус,
  double angl2= atan2(v[3]->y()-v[0]->y(),v[3]->x()-v[0]->x());
  // std::cout<<"angle is "<<angl1 *180/M_PI<<", "<<angl2*180/M_PI<<" "<<"\n";
//   if(angl1<0)
//   {angl1=2*M_PI+angl1;
//   }
//   if(angl2<0)
//   {angl2=2*M_PI+angl2;
//   }

   v[2]->change(Point(v[0]->x()+r*cos(angl1 ),v[0]->y()+r*sin(angl1 )));
  v[3]->change(Point(v[0]->x()+r*cos(angl2 ),v[0]->y()+r*sin(angl2 )));

 } else {
    //math::vector2d(v[0]->x(),v[0][1]).length();//std::abs(select[0][0].x()-select[0][1].x());
  //   math::vector2d vec(select[0][0],select[0][1]);
      r= (v[1]->x()-v[0]->x());
int x,y;
      //     int x= p.x()-v[0]->x();//v[0][1].x();
  //    int y=p.y()-v[0]->y();//v[0][1].y();
   //   double k=r/(sqrt(x*x+y*y));//r



//      x=((v[0]->x()+ x*k)  +0.5);
//      y=((v[0]->y()+ y*k)  +0.5);

      double angl= atan2( p.y()-v[0]->y(),p.x()-v[0]->x());

//      if(angl<0)
//      {
//        angl=2*M_PI+angl;
//      }
        x= v[0]->x()+r*cos(angl)+0.5;
        y=v[0]->y()+r*sin(angl)+0.5;


      v[i]->change(Point(x,y));

      std::cout<<"Point "<<i<<"in angle "<<180/M_PI*angl<<" with coord "<<x<<", "<<y<<"\n";

      std::cout<<" fmode : " <<std::fmod((angl * 180 / M_PI) + 360, 360)<<"\n";

 }

     control_limits();
 }

 bool arc::contain(const Point &p) const
 {
     Point s=Point(p.x()-v[0]->x(),p.y()-v[0]->y());
int r=v[0]->x()-v[1]->x();

    if(r*r >= (s.x()*s.x()+s.y()*s.y()))
             return true;
    return false;
 }
 bool arc::intersect(const Shape *sh) const
 {
     for(int i=0;i<sh->size();++i)
     {
       if(contain(sh->operator[](i)))
           return true;
     }
     return false;
 }

 void arc::draw_lines(Point o, int sm) const
 {
   // нужен угол между a, b
  double angl1= -atan2((v[2]->y()-v[0]->y()),(v[2]->x()-v[0]->x()));
  double angl2= -atan2((v[3])->y()-v[0]->y(),v[3]->x()-v[0]->x());
//  if(angl1*180/M_PI<0)
  if(angl1<0)
  angl1=2*M_PI+angl1;

  if(angl2<0)
  angl2=2*M_PI+angl2;


   int r= v[1]->x()-v[0]->x();//math:: vector2d(v[1]->content()
  if(angl1>angl2)
  {// если angl1 больше, рисуем от angl1 до 360
   fl_arc((v[0]->x()-r)*sm+o.x(),(v[0]->y()-r)*sm+o.y(),(r+r)*sm,(r+r)*sm,180/M_PI*angl1,360);
      angl1=0;
  }
//  if(angl1<angl2)

//     std::swap(angl1,angl2);




// std::cout<<"angle : "<< angl1*180/M_PI<<", "<< angl2*180/M_PI<<" with r = "<<r<<"\n";
  fl_arc((v[0]->x()-r)*sm+o.x(),(v[0]->y()-r)*sm+o.y(),(r+r)*sm,(r+r)+sm, 180/M_PI* angl1, 180/M_PI* angl2);
   }


 void arc::control_limits()
 {
     // проходим по всем точкам
     // если  угол больше 180
     int r=v[0]->x()-v[1]->x();
     // проверять по углам какие точки огранич
     lim_x = Point(v[0]->x()-r,v[0]->x()+r);
     lim_y = Point(v[0]->y()-r,v[0]->y()+r);
 }

 //**********************************ellipse ************************************




 void ellipse::draw_lines(Point o, int sm) const
 {
     // если заполнен
  int a_=std::abs(v[1]->x()-v[0]->x());
  int b_=std::abs(v[1]->y()-v[0]->y());
//     if(fillcolor().visibility())
//     {
//         fl_color(fillcolor().as_int());
//         fl_pie(v[0]->x()*sm+o.x(),v[0]->y()*sm+o.y(),(a_+a_-1)*sm,(b_+b_-1)*sm,0,360);
//         fl_color(color().as_int()); // reset color
//      }
//  std::cout<<"draw_ellipse with center : "<<v[0]->x()<<", "<<v[0]->y()
//          <<"and r1 "<<v[1]->x()-v[0]->x()<<" ,"<<b_<<"\n";
fl_color(FL_BLACK);
     fl_arc((v[0]->x()-a_)*sm+o.x(),(v[0]->y()-b_)*sm+o.y(),(a_+a_)*sm,(b_+b_)*sm,0,360);
 }
// ellipse вписан в прямоугольник,
 void ellipse::change(Point p,int i)
 {
 //if(i==0||i==-1) {
//   return;  /// move
//// // смещение всех точек


 //}
 // для точки 1 меняем  полуось x,
// для точки 2 полуось y
v[1]->change(diag2(p));
 }

 int ellipse:: a() const
 {
     int a=v[0]->x()>v[1]->x()?v[0]->x()-v[1]->x():v[1]->x()-v[0]->x();
    int b=v[0]->y()>v[1]->y()?v[0]->x()-v[1]->x():v[1]->x()-v[0]->x();
    return a>b?a:b;
 }

 int ellipse::b() const
 {
     int a=v[0]->x()>v[1]->x()?v[0]->x()-v[1]->x():v[1]->x()-v[0]->x();
    int b=v[0]->y()>v[1]->y()?v[0]->y()-v[1]->y():v[1]->y()-v[0]->y();
    return a<b?a:b;
 }
 Point ellipse::ab() const
 {
     int a=v[0]->x()>v[1]->x()?v[0]->x()-v[1]->x():v[1]->x()-v[0]->x();
    int b=v[0]->y()>v[1]->y()?v[0]->y()-v[1]->y():v[1]->y()-v[0]->y();

    return Point(a,b);

 }

 void ellipse::control_limits()
 {
Point half_ax=ab();
// точка центра v[0]
    lim_x=Point(v[0]->x_-half_ax.x(),v[0]->x()+half_ax.x());
    lim_y=Point(v[0]->y()-half_ax.y(),v[0]->y()+half_ax.y());


 }

 bool ellipse::contain(const Point &p) const
 {
   if(!p.isValid()) return false;
    Point hlf=ab();
 // std::cout<<hlf.x()<<" , "<<hlf.y()<<" and "<<p.x()<<", "<<p.y()<<"\n";
  // учитывать центр
  int a=std::abs(p.x()-v[0]->x());
  int b=std::abs(p.y()-v[0]->y());
  return ((a*a)/(hlf.x()*hlf.x())+(b*b)/(hlf.y()*hlf.y())<=1);//-hlf.x()*hlf.x()*hlf.y()*hlf.y()<0);

//  return ((p.x()*p.x())/(hlf.x()*hlf.x())+(p.y()*p.y())/(hlf.y()*hlf.y())-hlf.x()*hlf.x()*hlf.y()*hlf.y()<0);

 }
 bool ellipse::intersect(const Shape *sh) const
 {
     for(int i=0;i<sh->size();++i)
     {
       if(contain(sh->operator[](i)))
           return true;
     }
     return false;
 }

Point ellipse::diag(Point p)
{
    // 1 уравнение прямой по 2 точкам, точке центра и p

    double k=(p.y()-v[0]->y())/p.x()-v[0]->x();
    double c=v[0]->y()-v[0]->x()*k;
    int a_=v[0]->x()-v[1]->x();
    int b_=v[0]->y()-v[1]->y();
// ищем коэффициенты квадратного уравнения
    double A=(a_*a_+b_*b_*k*k);
    double B=2*k*c*b_*b_;//2*v[0]->x()*b_*b_-k*(c-v[0]->y())*a_*a_;
    double C=b_*b_*c*c-a_*a_*b_*b_;//b_*b_*v[0]->x()+a_*a_*(c-v[0]->y()*(c-v[0]->y())-a_*a_*b_*b_);


    double discr=B*B-4*A*C;

    if(discr<0)
        return {NAN,NAN};
    else //if(discr==0)
    {
        int x=  (-B)/(2 * A);
        int y=k*x+c+0.5;


     //   std::cout<<"Piont : "<<x<<", "<<y<<"\n";
        return Point(x,y);
    }
    return {NAN,NAN};
}

Point ellipse::diag2(Point p)
{

    return Point(int(p.x()+0.4),(int)(p.y()+0.4));
}

 }




