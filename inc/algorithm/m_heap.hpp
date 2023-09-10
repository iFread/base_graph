#ifndef MY_HEAP_HPP
#define MY_HEAP_HPP

#include "m_heap.h"

namespace algo {

template <typename T,class Comp>
void heap<T,Comp>::insert(const T &t)
{
vec.push_back(t);
sift_up(vec.size()-1); // обменять местами с родителем
 }

// извлечь корень, и вернуть
template <typename T,class Comp>
 typename heap<T,Comp>::iterator
  heap<T,Comp>:: extract()
{
    if(vec.empty()) return iterator(nullptr);
 iterator res(*vec.data());//std::remove_reference<T>(vec[0]));
 vec[0]=vec[vec.size()-1]; // последнее значение в корень и sift_down
vec.pop_back(); // удалить элемент из вектора
 sift_down(0);
 return res;
 }

// реализуем min_heap, значит потомки больше родителя
template <typename T ,class Comp>
void heap<T,Comp> ::sift_up(size_t idx)
{
                                         //  -1: 0: 1
 while(idx>0 && c(*vec[idx],*vec[(idx-1)/2]))  // пока не достигли нуля, и Компоратор с элементом и родителем положительный
 { // обмениваем местами
 T tmp=vec[idx]; // swap с родителем
 vec[idx]=vec[(idx-1)/2];
 vec[(idx-1)/2]=tmp;
 idx=(idx-1)/2;    //ставим индекс родителя
  }
}
template <typename T ,class Comp> // просеивание вниз,
void heap<T,Comp> ::sift_down(size_t idx)
{ // если левый или правый потомок, на сравнении дают true , например при Comp = less, min_heap, при Comp==grater= max_heap
    while(idx*2+2<=vec.size()  && (c(*vec[idx*2+1],*vec[idx])||c(*vec[idx*2+2],*vec[idx])))
    { // если левый потомок Comp правого, меняем с ним, иначе с правым
    if(c(*vec[idx*2+1],*vec[idx*2+2]))
    {
        T tmp=vec[idx*2+1];
        vec[idx*2+1]=vec[idx];
        vec[idx]=tmp;
        // ставим индекс левого потомка
        idx=(idx*2+1);

    }
    else
     {
        T tmp=vec[idx*2+2];
        vec[idx*2+2]=vec[idx];
        vec[idx]=tmp;
    idx=(idx*2+2);
    }
    }



}





}



#endif
