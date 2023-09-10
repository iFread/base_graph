#ifndef TEMPLATE_HEAP_H
#define TEMPLATE_HEAP_H

#include <unistd.h>
#include <vector>
#include "../base_graph.h"

namespace algo {
// следует определить компаратор для типов данных

class comp
{
public:
    bool operator()(const Graph::Shape& sh1,const Graph::Shape& sh2)
    {
        return sh1.limit_x().x()<sh2.limit_x().x();
    }
};


// реализует мин_кучу
//


template <typename T, class Comp=comp()> // ,size_t sz> сразу задавать размер данных, чтобы избегать перераспределения памяти
class heap
{
 std::vector<T> vec;
 Comp  c;
 template<typename Iter>
 struct Iterator
 {
     friend  class heap<Iter,Comp>;

     using iterator_type = Iter;
     using reference = iterator_type&;
     using pointer = iterator_type*;
     using value_type = iterator_type;

 value_type value;
 private:

 private:
  //   Iterator(value_type &val):value(val){}
     Iterator(value_type val):value( val){}
 public:
     Iterator(const Iterator& it):value(it.value) {}
     Iterator& operator=(const Iterator& it)
     {
       if(this==&it) return *this;
       this->value=it.value;
       return *this;
     }

     operator bool()
     {
       if(value) return true;
       return false;
      }

     iterator_type operator*(){return value;}

 };
public:

 using iterator=Iterator<T>;
 using citerator = Iterator<const T>;


 // нужен компаратор для элементов
public:
 heap():c(Comp{}){}
 heap(size_t sz):vec(sz,T{}){}
 size_t size() const{return vec.size();}
void insert(const T &t);
iterator  extract();// извлечь корень,

private:
void sift_up(size_t idx_elem);
void sift_down(size_t idx_elem);
};

}



#include "m_heap.hpp"




#endif
