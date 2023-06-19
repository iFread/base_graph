 #ifndef BASE_TOOL_H_
#define  BASE_TOOL_H_
#include "base_graph.h"
#include "algorithm/t_rb_tree.h"
#include <vector>
/*
  Инструмнент может иметь собственные Shape, или нет:
Вариант 1. Может: например при модификации фигуры, инструмент получает копию и модифицирует ее,
     Для отображения должна бьть вызвана draw() инструмента

 Вариант 2: Если добавлять фигуру непосредственно в canvas, и затем удалять ее???
  -- Если в canvas фигуры хранятся в виде двоичной кучи?


*/
namespace Graph {
template <typename T>
// Not RAII
class ref_list
{ // ref_list<Shape*>
 // T ptr;  //  Если T = Type*
std::vector<T*> vec;   // std::vector<Shape**> vec
std::vector<T*> own;


public:
ref_list(){} // вывод Type будет в конструкторе, или в push_back// но вектор, уже будет типа T

~ref_list()
{
  for(auto *el:vec)
      delete el;
}
//void push_back(T &t) { vec.push_back(&t); } // что за бред, если сунуть переменную, будет жопа// если T=Type* std::vector<Type*> v
void push_back(T* t) {own.push_back(t);vec.push_back(t);}
void push_back(T& t) { vec.push_back(&t);}

void remove(T *t)
{
  for(size_t i=0;i<vec.size();++i)
  {    if(vec[i]==t)
       vec.erase(vec.begin()+i);
    }
  for(size_t j=0;j<own.size();++j)
 {
    if(own[j]==t)
    {
        own.erase(own.begin()+j);
    //     delete t;
    }
  }
}
void remove(T& t)
{
  remove(&t);
}

T& operator[](int i){ return *vec[i];}
  const T& operator[](int i) const {return *vec[i];}
size_t size() const {return vec.size();}
void clear(){vec.clear();
             for (size_t i=0;i<own.size() ;++i)
             {
                 delete own[i];
             }
                   own.clear();
            }
};

}


struct  Point;
namespace Graph {

class Shape;

class Canvas;
  // intrface

// следует опраделить proxy-class для хранения указателей на фигуру
class base_tool {

public:
    enum   tool_type:uint8_t{none_t,selected_t,creating_t,transform_t};

    base_tool(tool_type tp):current(nullptr),tp_(tp){}
   virtual ~base_tool(){}//if(current) delete current;}

    virtual void action(Canvas* c,int ev)=0; // нужен ли здесь Canvas* p_can //
  // Для дальнейшего определения функций
    //  virtual int handle(int e)=0;
   // virtual void draw()=0;
    tool_type type()const {return tp_;}

virtual void draw(Point p) const;
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
 current указывает на фигуру которая  находится в canvas
*/



class creat_tool:public base_tool
 {
   // указатель на функцию создания фигуры
 using creat_ptr= Shape*(*)(Point);
 //этапы создания фигуры,
enum stage_tool:uint8_t {none_sh, modify_sh,ready_sh};
public:
    creat_tool():base_tool(tool_type::creating_t){}
   ~creat_tool() { }
    void set_shape(creat_ptr ptr); //create=ptr ;
 // ac
  void action(Canvas *c,int ev); // Widget *w ???
protected:  // virtual in base class??
//  void capche(Shape* cur);
 // void free(Shape *cur);

private:
                 //   action() {      // Возможно определить статический флаг, для вызова action
                                            //   if(create) current =create(Point p); // если функция установлена
                                           //..модификация созданной фигуры
   creat_ptr create{nullptr};                                         // if(current)  // после вызова функ
   stage_tool stage{none_sh};                                         // Canvas *can->add(current); // добавление фигуры в канву}
};
//
// функции для создания фигур
// ********************************************************************
//Shape* get_line(Point p);
//Shape* get_rectangle(Point p);
//Shape* get_polyline(Point p);// {return new lines(p);}
//Shape* get_polygon(Point p);
//Shape* get_circle(Point p);

//***********************************************************************

/*
  в первую очередь:
     1. Все модификации над фигурой происходят только после ее захвата, (capche(Shape*)/insert(Shape*))
     2. При наведении на фигуру она подсвечивается
       // т.е. нужно проверить попадает ли текущая точка(курсор) на какую либо фигуру
        // сортировка фигур (или указателей на фигуры ):  1. представить фигуру бинарным деревом
                                                             (как производить обход фигуры при change(Point), если ее вершины меняются ???)
                                                          2. Определить экстренумы фигуры, (и хранить отсортированный массив экстренумов) // дерево
                                                               или создавать такой массив, при выборе transform_tool  //дерево
                                                           при изменении фигуры как просеивать это дерево ??? (поиск фигуры удаление из массива, и добавление снова)
                                                           // а при изменении группы фигур (поиск каждой фигуры, удаление, добавление)
*/


template <typename  T>
class Comparator {
public:
    bool operator() (T obj1, T obj2)// const Shape& obj1,const Shape& obj2) {
  {      return obj1<obj2;
   }

};

template <>
class Comparator<Shape>
{public:
    bool operator()(Shape *sh1, Shape *sh2)
    {

//     if(sh1->limit_x()==sh2->limit_x())
//           return sh1->limit_y()<sh2->limit_y();
        return sh1->limit_x()<sh2->limit_x();
     }

};

class select_tool //:public base_tool
{
public:
   enum sh_state:uint8_t {none_state,modify_state,ready_state} ;
private:
     ref_list<Shape> vec;
     rbtree<Shape* ,Comparator<Shape>> tr;//(Comparator<Shape>);
    // Shape *curs; // прямоугольная область
     sh_state current_state{none_state};
public:
    select_tool();
   void add(Shape*sh)   {sh->vertex_visible(true);
                         sh->set_vertex(Color::red,3);
                          vec.push_back(*sh);
                        }
   void remove(Shape* sh)  //
   { sh->vertex_visible(false);
   }
   size_t size() const{ return vec.size();}
    virtual void action(Canvas* c,int ev); // считает фигуры которые попали в область курсора,
  // virtual void draw(Point p) const; // здесь не нужен
    ~select_tool(){    // if(curs) delete curs;
                            vec.clear();
                                      }
    bool isEmpty()const {return vec.size()==0;}
    void clear(){
               if(!isEmpty())
                   for(size_t i=0;i<vec.size();++i)
                     remove(&vec[i]);
                      vec.clear();
                    //  current_state=select_tool::none_state;

                }
    Shape& operator[](int i) {i=i<(int)vec.size()?i:vec.size(); return vec[i];}
    void set_state(sh_state st){current_state=st;}
    sh_state state() const{return current_state;}
     void search_under_cursor(Shape* cursor);

     void init_tree(Canvas* s); // std::vector<Shape*>& v ;
       // искать фигуры которые попадают в область курсора
protected:
};


class transform_tool:public base_tool {
// перенести в базовый класс
   enum stage_modify:uint8_t {none_md,cur_md,ready_md };
 enum modify_type:uint8_t {mode_none_t,mode_move_t,mode_rotat_t, mode_change_t, mode_remove_t}; // типы модификации фигуры, движение, вращение, изменение вершины, удаление вершины(для типов )
   rbtree<Shape* ,Comparator<Shape>> tr;//(Comparator<Shape>);
ref_list<Shape*> list;
 //std::vector<Shape> tr;
public:
transform_tool(Canvas *can);//:base_tool(tool_type::transform_t),curs(nullptr)//new rectangle(can->loc(),can->loc()))
    //{       init_tree(can);    }
   void action(Canvas *c, int ev);
 ~transform_tool() { //tr.clear();//list.clear();//delete tr ;
          if(curs) delete curs;      }

 void draw(Point p) const;
 protected:
   void init_tree(Canvas* s); // доступ к фигурам
   void search_under(Shape* cursor);
   inline void clear_list(){for(size_t i=0;i<list.size();++i) free(list[i]); list.clear(); }

   void search_under2(Shape* cursor);
      void search_under3(Shape* cursor);
   // курсор
   void init_cursor(Point p); // для инициализации нужны две точки,
        //  обычное состояние курсора - прамоугольник 2 * 2
private:
   bool isAcross(Shape* sh,Shape* cur);


private:
  stage_modify stage{none_md}; // нет модификации никакой фигуры
  modify_type m_type{mode_none_t};
 Shape *curs; // в последствии заменить на объект cursor
};


}






#endif
