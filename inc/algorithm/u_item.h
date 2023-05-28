 #ifndef _UNIVERSAL_ITEM_H
#define _UNIVERSAL_ITEM_H

#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <vector>

namespace Graph
{
 class Iclonable
 {
 public:
     virtual Iclonable* clone()=0;
     virtual~ Iclonable(){}
//     Iclonable(const Iclonable& )=delete;
//     Iclonable(Iclonable&& cl){}
 };

// for simple classes
 template <typename T>
 struct  Resource:public Iclonable
{
T  data_;

public:


 Resource(const Resource& r):data_(  T(r.data_)){ } // какой move? copy?
// Resource(Resource &&r):data_(std::move(r.data_)){std::cout<<"move Resource \n";r.data_=nullptr;}  // а если не указатель
 //explicit Resource(T &&t): data_(new T(std::move(t))) {}
 explicit Resource(const T& t): data_( T(t)) {}  // copy ctor
//template< size_t sz>
//Resource( char*ch,size_t sz):data_(new char[sz]) {
//    std::cout<<"stpoint\n";
//   strncpy(data_,ch,sz);
//    std::cout<<"stend\n";

//}

//Iclonable*clone()
// для char* clone должен возвращать указатель
Iclonable* clone() {return  new Resource(*this);}

~Resource(){}//delete  data_;}
};


template <>
 struct Resource< char *>:public Iclonable
{
char* data_;  //
const size_t sz_;
public:
  Resource(const char* ch,size_t sz):data_(new char[sz]),sz_(sz)
{
  std::cout<<"ch="<<ch<<"\n"  ;
 memcpy(data_,ch,sz);//,strlen(ch)+1);
 data_[sz-1]='\0';
// std::cout<<"size = "<<strlen(ch)<<"\n";

}


//template< char*>
  Resource (const Resource& res):data_(new char[res.sz_]),sz_(res.sz_){
      std::cout<<"copy "<<res.data_<<" in array "<<sz_<<"\n";
      memcpy(data_,res.data_,sz_); } //Resource(res.data_, res.sz_)  {}    //data_(new char[strlen(res.data_)]){}
Iclonable* clone() {return new Resource (*this );}
//Resource(const Resource& res):Resource(res.data_){}    //data_(new char[strlen(res.data_)]){}

~Resource(){delete [] data_;}
};



class U_Resource
{
Iclonable* data_;
public:
 U_Resource():data_(nullptr){}
 U_Resource(const U_Resource& cl):data_(cl.data_->clone()){ }

//  template<typename T>
//   U_Resource(T &&t):data_(new Resource<T>(t)){}

 template<typename T>
 explicit U_Resource(T t):data_(new Resource<T>(t)){}

//  template<>
// explicit  U_Resource::U_Resource(const char* ch);


 //template<typename T>
// U_Resource(U_Resource &&t):data_(new Resource<T>(std::move(t.data_))){}
   ~U_Resource(){  delete data_;}

  template< typename T1>
  T1* cast()
  {
   Resource<T1> * tmp=dynamic_cast<Resource<T1>* >(data_);
 if(tmp)
     return &dynamic_cast<Resource<T1>*>(data_)->data_;
 return nullptr;
  }


};

// template <const char*>
template <>
inline U_Resource:: U_Resource (const char *ch):data_(new Resource< char*>(ch,strlen(ch)+1)){}

template<>
 inline   char* U_Resource::cast<char>()
  {
 Resource<char*> *tmp=dynamic_cast< Resource<char*>*>(data_);
if(tmp)
    return dynamic_cast<Resource<char*>*>(data_)->data_;
return nullptr;//std::string{};
  }

// в подобном подходе следует оперделять key-value, что бы добавляемые значения были доступны по какому то ключу


//class Item
//{
// std::vector<U_Resource> vec;

//};

 template <typename T >
 bool less(const T &t1,const T &t2)
 {
     return  t1<t2 ;  // t1<t2
 }


 template <typename T, typename Comp>
 int partition(T* t1,T*t2,Comp cmp=less<T>) //
 {
   int l=0;
   int r=t2-t1;

   T* pivot=t1;
int i=l+1; // элементы меньше опорного,
int j=0;  // элементы больше опорного, пока пустые
 for(;i<=r;i++)
 {   // если встретили элемент меньше опорного , ставим его на место j,
     if(cmp(*(t1+i),*pivot))
     {
         j++; // передвигаем j
// меняем местами,
         T tmp=*(t1+i);
         *(t1+i)=*(t1+j);  // элемент с индексом j
     *(t1+j)=tmp;

      }
  } // после цикла меняем местами опорный элемент с j-тым

 T tmp=*(t1+j);
 *(t1+j)=*pivot;
 *pivot=tmp;
 return j;
 }
 template <typename T, typename Comp  > // непрерывная последовательность
 void sort(T* l,T* r,Comp cmp = less<T>)
 {
   if((r-l)<=0) return;

   int m=partition(l,r,cmp);
  sort(l,l+m,cmp);
  sort(l+m+1,r,cmp);
  }

}



#endif
