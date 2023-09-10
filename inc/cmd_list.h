 #ifndef CMD_LIST_H
#define CMD_LIST_H
#include <cstdint>

#include <cstdio>
#include "point.h"
//#pragma pack(push, 1)
namespace  command
{


// for POD- type
template <typename T>
void write(uint8_t* d, const T&t)
{
 for(size_t i=0;i<sizeof(T);++i)
 {
   *(d+i)=*(reinterpret_cast<const uint8_t*>(&t)+i) ;
        }
}

//template<typename T>
// T read (const uint8_t *b)
//{
//
//  T t= *reinterpret_cast<T*>(b);
// return t;
//}

template <typename T>
void read(const uint8_t* d, T &t)
{
  t=*reinterpret_cast<const T*>(d);// copy POD-object

}




 template<const char>
void write (uint8_t* d, const char *c)
{
while(c&&*c!='\0')
{
*d=*c;
 d++;c++;
}
*d='\0';
	}

 template<char>
 void read(const uint8_t* d, char* c)
{
 while(d&&*d!='\0')
 {
	 *c=*d;
	 c++;d++;
 }
 }



struct cmd
{
   enum cmd_tp:unsigned {none_cmd,cfg_cmd,start_cmd,stop_cmd,pause_cmd,line_cmd,circle_cmd};

cmd_tp type_;
 cmd():type_(cmd::none_cmd){}
explicit cmd(cmd_tp c):type_(c){}
 virtual ~cmd(){}
cmd(const cmd& c):type_(c.type_){}
cmd& operator=(const cmd&c)
{ if(&c==this) return*this;
   type_=c.type_;
   return *this;
	}

 cmd_tp type() const {return type_;}

virtual void write(uint8_t* b)
{
//  for(size_t i=0;i<sizeof (type_);++i)
//  {
//   b[i]=*(reinterpret_cast<uint8_t*>(&type_)+i);
//  }

 ::command::write(b,type_);
}
virtual void read(const uint8_t*d)
{
//type_=*reinterpret_cast<const cmd_tp*>(d);
  ::command::read(d,type_);
 //type_=::command::read<>(d);
}
};
//void  serialize(unt8_t * b) // Запись данных
//cmd deserialize(const uint8_t* b)  //

struct cfg_param:cmd
{

	int max_x;
	int max_y;

 cfg_param(int x,int y):cmd(cfg_cmd),max_x(x),max_y(y){}


void write(uint8_t *d)
{
 ::command::write(d,type_);
 ::command::write(d+sizeof(cmd_tp),max_x);
 ::command::write(d+sizeof(cmd_tp)+sizeof(int),max_y);

}

void read(const uint8_t* d)
{
	::command::read(d,type_);
	   ::command::read(d+sizeof(cmd_tp),max_x);
	   ::command::read(d+sizeof(cmd_tp)+sizeof(max_x),max_y);
 }
};


struct c_line:cmd
{

Point nxt_point;
c_line(Point p):cmd(cmd::line_cmd),nxt_point(p){}
c_line():nxt_point(-1,-1){}
c_line(const c_line& c):cmd(c),nxt_point(c.nxt_point){}
c_line& operator=(const c_line& l)
{ if(this==&l) return *this;
  nxt_point=l.nxt_point;
  type_=l.type_;
	return*this;
	}

~c_line(){}
void write(uint8_t* d)
{
// cmd::write(d);
//uint8_t* ch=d+sizeof (cmd_tp);
// for(size_t i=0;i<sizeof(Point);++i)
// {
//   *(ch+i)=(*reinterpret_cast<uint8_t*>(&nxt_point)+i);
// }
 ::command::write(d,type_);
   command::write(d+sizeof(cmd_tp),nxt_point);
}

void read(const uint8_t* d)
{
// cmd::read(d);
// nxt_point=*reinterpret_cast<const Point*>(d+sizeof (cmd_tp));

//	type_=::command::read(d);

 //  ::command::read(d,type_);
//	 nxt_point=::command::read(d+sizeof(cmd_tp));

 ::command::read(d,type_);
   ::command::read(d+sizeof (cmd_tp),nxt_point);
}

};

struct c_circle:public cmd
{

Point c_;
int r_;
    // возможно направление обхода
c_circle():c_(-1,-1),r_(-1) {}
c_circle(Point p, int r):cmd(cmd::circle_cmd),c_(p),r_(r){}
 ~c_circle(){}
c_circle(const c_circle& c):cmd(c),c_(c.c_),r_(c.r_){}
c_circle& operator=(const c_circle& c)
{ if(&c==this) return *this;
  type_=c.type_;
  c_=c.c_;
  r_=c.r_;
  return *this;
  }

void write(uint8_t* d)
{
//   cmd::write(d);
//   uint8_t* ch=d+sizeof (cmd_tp);
// // пишем точку
//   for(size_t i=0;i<sizeof(Point);++i)
//   {
//     *(ch+i)=(*reinterpret_cast<uint8_t*>(&c_)+i);
//   }
//    ch=ch+sizeof (Point);

//  for(size_t i=0;i<sizeof (r_);++i)
//  {
//    *(ch+i)=*reinterpret_cast<uint8_t*>(&r_);
//  }
     ::command::write(d,type_);
      ::command::write(d+sizeof(cmd_tp),c_);
      ::command::write(d+sizeof(cmd_tp)+sizeof(Point),r_);
}

void read(const uint8_t* d)
{

//type_=read(d);

   ::command::read(d,type_);
// c_=read(d+sizeof(cmd_tp));

// r_=read(d+sizeof(cmd_tp)+sizeof(c_));
 ::command::read(d+sizeof(cmd_tp),c_);

   ::command::read(d+(sizeof (cmd_tp)+sizeof(c_)),r_);


}




};




}



#endif
