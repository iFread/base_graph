#ifndef BASE_GRAPH_H
#define BASE_GRAPH_H
 #include <iostream>

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
     Vertex(const Vertex &v);
     Vertex(Vertex&& v);
~Vertex(){}
     // для Vertex следует определить  сравнение
     //

     Point content()const {return *this;}
     Vertex & operator=(const Vertex& v){
         //  НАшу точку выставить равной точке v
    //     this->next()=v.next();
     //    this->prev()=v.prev();
        *reinterpret_cast<Point*>(this) =v.content();
         return *this;
     }
    Vertex* v(){return this;}
     Vertex* ccv(){return reinterpret_cast<Vertex*>(prev());}
     Vertex*cv(){return reinterpret_cast<Vertex*>(next());}

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
public:
Vertex_list():ptr(nullptr){}
Vertex_list(const Vertex_list& cv);
Vertex_list(Vertex_list&& cv);


// Это все нужно убрать отсюда
// Интерфейс работы с Vertex
void add(Point p) {if(ptr)
         ptr->insert(new Vertex(p));
         else ptr=new Vertex(p);
                  }
// -->  void add(Point p);   -->   // нужно добавлять вершину после определенной вершины

void add(const Vertex *v, Point p); //добавить вершину, после ,v
Vertex* remove();

//void trace(std::ostream &os){
//   Vertex*p=reinterpret_cast<Vertex*>(ptr->next()) ;
//   while (p!=ptr)
//   {os<<((Vertex*)p->prev())->x()<<", "<<((Vertex*)p->prev())->y()<<"\n";
//   p=reinterpret_cast<Vertex*>(p->next());
//   }

//}





Vertex* operator->(){return ptr;}

//пройти по всему списку, и удалить вершины
// удаляем в обратном порядке

~Vertex_list(){
//    Vertex *p=ptr->ccv();
    Vertex*p=ptr->ccv();
    while (p!=ptr)
    {
     delete p->remove();
  p=ptr->ccv();
    }
  delete ptr;
 }

};





class Shape {


//реcурсом  Shape должен быть контейнер содержащий  Vertex
    // и этот ресурс копируется при копировании, или перемещается при move ctor
  //  std::list<Vertex>;
 //  std::vector<Vertex*> v;
Vertex_list v;
//Vertex* cur{nullptr};
/*
 begin() - end();
*/
public:

Shape(){}
//~Shape(){}
void add(Point p){v.add(p);}
void trace(std::ostream &os){
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

Vertex*operator[](int i){
   //if(i<size)     // size должен быть определен у vertex_list, т.к. за точки отвечает vertex_list
    //   return v->ccv();
   int cnt=0;
   Vertex* pv=v->v();
   while (cnt<i) {
       pv=pv->cv();
   cnt++;
   }
    return pv;}
};









}
#endif // BASE_GRAPH_H
