#ifndef TEMPLATE_RB_TREE_H
#define TEMPLATE_RB_TREE_H
#include <stdint.h>
#include <iostream>


class Shape;
template <typename T>
class Compare {

  public:
    bool operator() (const T &obj1, const T& obj2) {
        return obj1<obj2;
   }

};

template <>
class Compare<Shape&> {


public:
    bool operator() ( const Shape& obj1,const Shape& obj2) {
        return true;
   }

};


template <typename T,  class Comp= std::less<T> >
class rbtree {

    template<class U>  // T =type & то U = type &
    struct Node{
     enum color_node:unsigned char{red,black};
     Node<U>* parent,*left,*right;
     color_node c;
     U* data;
     bool own;

    public:
      Node<U>():parent(nullptr),left(nullptr),right(nullptr),c(Node<U>::black){}
      explicit Node<U>(const U & u,color_node cl=Node<T>::red):parent(nullptr),left(nullptr),right(nullptr),c(cl),data(new U ),own(true){*data=u;}
       explicit Node<U>(U *u,color_node cl=Node<T>::red):parent(nullptr),left(nullptr),right(nullptr),c(cl),data(u){ }
     ~Node(){
         delete left;delete right;
         if(own)
             delete data;
     }
    };


template<typename  Iter>
  class Iterator
{

    //  friend  class Node<T>;
      friend class rbtree<T,Comp>;
  public:
 // определяем псевдонимы
 typedef Iter iterator_type ;
 typedef std::input_iterator_tag iterator_category;
 typedef ptrdiff_t difference_type ;  // int
 typedef iterator_type value_type;
 typedef iterator_type& reference ;
 typedef iterator_type* pointer ;

 iterator_type *value;
 private:
 Iterator(iterator_type *t):value(t){}
 // публичный конструктор копирования
  public:
 Iterator(const Iterator& i):value(i.value){}
 Iterator& operator=(const Iterator& i)
 {
    if(this==&i) return *this;
    value=i.value;
    return *this;
 }
// методы
 bool operator==(const Iterator &other)
 {
     return value==other.value;
 }
 bool operator!=(const Iterator &other)
 {
     return !(*this==other);
 }

   T  operator*()
 {
    return     *value->data;

 }
// реализует обход дерева с лева на право
 Iterator& operator++()
 {
     if(!value->parent)
         value=nullptr;
     else if(value->parent->right==value)
         value=value->parent;
     else
     {
       value=value->parent;
        if(value->right)
        { value=value->right;
            while(value->left)
                value=value->left;
        }
     }
     return *this;
 }

 Iterator& greater_than( )
 {
      if(value->right)
     {      value=value->right;
          while(value->left)
               value=value->left;
           return *this;
      }
   else // если сами с права идем наверх пока не встретим левый переход
  {        while(value->parent && value->parent->right==value)
                value=value->parent;  //
      if(!value->parent) // если достигли корня, конец
           value=nullptr;
       if(value)
       value=value->parent;
    }
       return *this;


 }


};


 Node<T> *root;
  Comp  cmp; // компаратор для сравления
public:
  typedef Iterator<Node<T>> iterator ;
  typedef Iterator< const Node<T>> const_iterator ;

 using key_type =T;

 iterator begin()
 {
   Node<T>* l = root;
   while(l->left)
   {
     l=l->left;
   }
   return iterator(l);
 }
 iterator end()
 {
     return nullptr;
 }
 // вернуть итератор на первый элемент меньше или равный key
 iterator lower_bound( const key_type& key)
 {
  Node<T> *n=root;
 // Node<T> *p=root; // родитель
  while(n){
  if(cmp(key, *n->data)&&n->left) // key  меньше data , идем в лево, если можно
      n=n->left;
   else  // значение key больше или равно узла больше
    { if(cmp(*n->data,key))  // значение узла в дереве меньше key
      {     if(n->right && cmp(*n->data,key)) // если справа что то есть
             {   n=n->right; // идем в право
              continue;}
         }
      // и проверяем
      return iterator(n);
  }

  }
  return iterator(root);
 // return nullptr;
 }
public:
rbtree():rbtree(Comp()){}
  rbtree( const Comp &c ):root(nullptr) ,cmp(c){}
~rbtree(){   delete root; }
 //template<typename  cmp,class C>
 // class Iter - инкапсуляция указателя на ноду
Node<T>* search(const T &key);
void insert(T &&  dd);
void insert(const T &dd);
void insert(T *dd);

void show_tree() const;

 void remove(const T & t)
{   remove(search(t));
}


protected:
void show(Node<T>* p,int l=0) const
{
    const std::string red("\033[0;31m");
       const std::string reset("\033[0m");
    if(p)
    {
        show(p->left,l + 1);
        for(int i = 0;i< l;i++) std::cout<<"   ";
           if(p->c==Node<T>::red)
                 std::cout <<red;
       else
            std::cout <<reset;
       std::cout<<*p->data<< std::endl;
        show(p->right,l + 1);
     }
    std::cout<<reset;
}

void correct(Node<T>* n);

void remove(Node<T>* dd) ; // искать по ключу, а не по Node


   void rotate_left(Node<T>* n);


   void rotate_right(Node<T>*n);

   void correct_db(Node<T>* parent_db, Node<T>* db) ;

};

//*****************************************************8

template <typename T,class Comp>
using type_ = rbtree<T,Comp>;

template <typename T,class Comp>
using ret_type = typename rbtree<T,Comp>::template Node<T> ;


template <typename T,class Comp>
void rbtree<T,Comp>::show_tree() const
{
    show(root,0);
}

 template <typename T, class Comp >
typename rbtree<T,Comp>::template Node<T>* rbtree<T,Comp> :: search(const T & key) // возвращать данные хранимые по ключу или, если такого ключа нет ??

 {
   Node<T>* l=root;
   while(l)
   {
       if( cmp(key,*l->data))
          l=l->left;
        else {
           if(cmp(*l->data,key))
            l=l->right;
            else if(!cmp(*l->data,key)&&!cmp(key,*l->data))
                         return l;
       }
   }
   return l;
 }

template <typename T,class Comp>
void rbtree<T,Comp>::insert(const T& dd)
{
 if(root)
 {
   Node<T>* l=root;
   Node<T>*p =root;

   while(l)
   {
     p=l;
    l=(cmp(dd,*l->data))?l->left:l->right; //Comp(l->data,dd)?l->right:nullptr;
      }
   l=new Node<T>(dd);
   l->parent=p;
    // смотрим откуда пришли
   ( cmp(*l->data,*p->data))?p->left=l:p->right=l;
   correct(l);
    } else
        root=new Node<T>(dd,Node<T>::black);
 }


template <typename T,class Comp>
void rbtree<T,Comp>::insert(T *dd)
{
 if(root)
 {
   Node<T>* l=root;
   Node<T>*p =root;

   while(l)
   {
     p=l;
    l=(cmp(*dd,*l->data))?l->left:l->right; //Comp(l->data,dd)?l->right:nullptr;
      }
   l=new Node<T>(dd);
   l->parent=p;
    // смотрим откуда пришли
   ( cmp(*l->data,*p->data))?p->left=l:p->right=l;
   correct(l);
    } else
        root=new Node<T>(dd,Node<T>::black);
 }



//************************************************************

template <typename T,class Comp>
void  rbtree<T,Comp>::remove(typename rbtree<T,Comp>::template Node<T>* dd)//typename rbtree<T,Comp>::template Node<T>* dd)
{  if(!dd) return  ;
    if( (!(dd->left && dd->right)) && (dd->left || dd->right) )
      {
            Node<T>* ch=(dd->left)?dd->left:dd->right;

             (dd->parent->left==dd) ? dd->parent->left=ch:dd->parent->right=ch;
                //dd->parent-> left  или  right
               ch->parent=dd->parent;
               dd->left=dd->right=nullptr;
            ch->c=dd->c;
               T key=*dd->data;
                delete dd;
            return ;//key;
        }
       if(dd->left&&dd->right)
        {  // ближайшая - самая левая вершина в правом поддереве
           Node<T>* ch= dd->right;
           while(ch->left){ // идем пока идется в лево
            //if(ch->left){
              ch=ch->left;
              }
      T key=*dd->data;
       dd->data=ch->data;
               remove(ch);
       return ;//key;
       } // нет, детей
         // если вершина черная , можут нарушится свойства дерева
       if(!(dd->right|| dd->left))
       {  if(dd->c==Node<T>::red)
           {    T key=*dd->data;
            (dd==dd->parent->left)?dd->parent->left=nullptr:dd->parent->right=nullptr;
             delete dd;
           // c=nullptr; // зануляем указатель для родителя удаленной вершины
                    return ;//key;
           } else  // удаление черной вершины
            {
               Node<T>* double_black=nullptr;
               Node<T>* d_parent=dd->parent;
               //->parent = nullptr;//->parent; // узел вместо удаляемой черной вершины
              T key=*dd->data;
              // указатель родителя указывает на самого себя
              (dd==d_parent->left)?d_parent->left=double_black:d_parent->right=double_black;
               delete dd; //19 здесь реально удалена вершина
                   dd=double_black; // занулили указатель на нее
                 correct_db(d_parent,double_black);
                      //  case 1 когда вершина корень
                       return ;//key; // если корень все хорошо
             }
         }
   }

template <typename T,class Comp>
void rbtree<T,Comp>::correct(typename rbtree<T,Comp>::template Node<T> *n)
{
   if(!(n&& n->parent&&n->parent->c==Node<T>::red)) return;
   Node<T>*p =n->parent; // родитель не может быть корнем , т.к. красный
   Node<T>*pp=p->parent; // дед, может быть корнем
   Node<T>* d=nullptr; // дядя
 d=(p==pp->left)?pp->right:pp->left;

 if(d&&d->c==Node<T>::red) { // если дядя красный
   p->c=d->c=Node<T>::black;
   if(pp->parent) // если не корень
       pp->c=Node<T>::red;

// Вызов рекурсии здесь ???
      correct(pp);
 } else
  {
     if(d==pp->right) // если дядя правый
     { // предварительная проверка элемента
         if(p->right==n) // и элемент правый
           {
            rotate_left(p);
            p=p->parent;
             }
         rotate_right(pp);
     p->c=(p->c==Node<T>::black)?Node<T>::red:Node<T>::black;
      pp->c=(pp->c==Node<T>::black)?Node<T>::red:Node<T>::black;
    // проверить, что дошли до корня, и если нужно установить новый  корень
      if(!p->parent) { root=p;  p->c=Node<T>::black;  }
       } else  // дядя левый, действуем симметрично
       {
         if(p->left==n)
         {
           rotate_right(p);
          p=p->parent;
         }
         rotate_left(pp);
         // корректируем цвета и проверяем достигли ли корня
         p->c=(p->c==Node<T>::black)?Node<T>::red:Node<T>::black;
         pp->c=(pp->c==Node<T>::black)?Node<T>::red:Node<T>::black;
         if(!p->parent) {root=p; p->c=Node<T>::black; }
         }
        }
    }

template <typename T,class Comp>
void rbtree<T,Comp>::correct_db(typename rbtree<T,Comp>::template Node<T>* parent_db,typename rbtree<T,Comp>::template Node<T>* db)
{
    if(db==root) return;
    Node<T>* b=(parent_db->left==db)?parent_db->right:parent_db->left;
    if(b->c==Node<T>::red) // если брат красный
    {
        (b==parent_db->left)?rotate_right(parent_db):rotate_left(parent_db);
         parent_db->parent->c=Node<T>::black; // красим деда, ,бывшего брата
         parent_db->c=Node<T>::red; // и отца

         if(!b->parent) // если брат стал корнем
             root=b;
         // брат изменился , его нужно проверить
          b= parent_db->left==db?parent_db->right:parent_db->left;
         // теперь брат черный

    }
       if( (!(b->right || b->left)) || ((b->left && b->right) && b->left->c==Node<T>::black && b->right->c==Node<T>::black))
    {
           b->c=Node<T>::red;
          if(b->parent->c==Node<T>::red)
           {   b->parent->c=Node<T>::black;
             return;
           }
           else // если отец черный
           { // считаем, что он дважды черный,
             correct_db(b->parent->parent,b->parent) ;
             }
           // сюда попадаем если у b есть дети, и они не черные, по крайней мере 1
       } else
       { if(db==parent_db->left) // брат правый,
           {  // здесь у черного брата есть как минимум один ребенок красный,
             // или оба красные, но нам нужен правый
              // if(b->left && b->left->c==Node<T>::red) // если есть левый, проверим наличие правого,
                //{
                   //if((b->right) && b->right->c!=Node<T>::red) // если есть правый ребенок, но он не красный
                  if((!b->right) || b->right->c!=Node<T>::red)
                   {  // т.к. если правого, нет он всяко не красный
                     rotate_right(b);
                       // перекрасить b - он стал правым ребенком брата
                     b->c=Node<T>::black;
                     b->parent->c=Node<T>::red;
                     // теперь востановить брата
                     b=b->parent; // его правый ребенок красный
                    }
           //
                    rotate_left(parent_db);
                   if(b->right) b->right->c=Node<T>::black;
                    b->c=parent_db->c;
                    parent_db->c=Node<T>::black;

                  return; // двойная чернота ушла
              } else // симметрично если брат левый
           {
               //if(b->right&& b->right->c==Node<T>::red) // если есть правый красный, проверям наличие левого красного
               //{
                   if(!(b->left) || b->left->c!=Node<T>::red)
                   {rotate_left(b);
                     b->c=Node<T>::black ;
                     b->parent->c=Node<T>::red;
                   b=b->parent; // востанавливаем брата
                   }
                   rotate_right(parent_db);
             if(b->left) b->left->c=Node<T>::black;
             b->c=parent_db->c;
             parent_db->c=Node<T>::black;
             //  }
               return;
           }
       }

}

template <typename T,class Comp>
void rbtree<T,Comp>::rotate_left(typename rbtree<T,Comp>::template Node<T>* n)
{
    Node<T>* cn=n->right;
     cn->parent=n->parent;  // указатель на родителя , cn может быть корнем
   // проверить это, и если cn не корень, меняем указатель его родителя, на нужную вершину
     if(n->parent) {
       if(n->parent->left==n)
           n->parent->left=cn;
        else
           n->parent->right=cn;
     }
     n->right=cn->left;
     if(cn->left) {   // если у cn что то есть слева, для этого левого, родителем становится n
         cn->left->parent=n;
     }
     n->parent=cn;
     cn->left=n;
}
template <typename T,class Comp>
void rbtree<T,Comp>::rotate_right(typename rbtree<T,Comp>::template Node<T>* n)
{ Node<T>* cn=n->left;
    cn->parent=n->parent;
    if(n->parent) // проверка если не корень, меняем у него указатели
    {   if(n->parent->left==n)
          n->parent->left=cn;
        else n->parent->right=cn;
     }
    n->left=cn->right;
    if(cn->right)
        cn->right->parent=n;
    n->parent=cn;
    cn->right=n;
}







#endif
