 #include "modal_window.h"
#include <Fl/Fl_Button.H>
#include <unistd.h>
#include <dirent.h>
#include <cstdio>
#include <sys/stat.h>
#include <fcntl.h>
#include <algorithm>

namespace Graph {

open_window::open_window(Point o,int w,int h,window& parent):window(o,w,h,"open"), // создаем окно, нужен родитель?
    b_ok(new Button(Point(w-100,h-45),70,20,"open")),b_cancel(new Button( Point(w-100,h-25),70,20,"Cancel")),
    b_up(new Button(Point(w/4*3+10,10),30,30,"Up")),
  list(new Simple_table(Point((w-20)/4,50),w/4*3,h-110)), //Simple_list( Point o,x,y,..const std::vector<item>& v)
  bx(new Out_Box(Point((w-20)/4,10),(w-20)/4*2,30)),
    own(&parent)
{
attach(*b_ok);
attach(*b_cancel);
//list->move((w-20)/4,10);
attach(*b_up);
attach(*list);
attach(*bx);

//bx->put(list->value());
b_cancel->callback([](Address,Address adr){
open_window* w=&reference_to<open_window>(adr);//.hide();
w->hide();
//  delete w;
},this);


b_up->callback([](Address,Address adr){
open_window& w=reference_to<open_window>(adr);
w.set_new_path("..");
},this);

char buf[256]={0};
path=std::string(getcwd(buf,256));
set_new_path(buf);
}


 file_type open_window::get_type(struct stat &type)
{  file_type res= ukn_t;
   if(S_ISDIR(type.st_mode))
        res= file_type::dir_t;
   else   if(S_ISREG(type.st_mode))
            res=  file_type::file_t;
   else  if(S_ISBLK(type.st_mode))
       res=  file_type::blc_t;
   else if(S_ISCHR(type.st_mode))
       res=  file_type::chr_t;

        return res;// open_window::file_type::ukn_t;
}
void open_window::set_items(const char* pth)
{
 DIR* dr;
 dirent *dir;

 dr=opendir(pth);
 if(!dr)
     return;
list->clear();
 // если путь корректен
 path=pth; // записываем новый путь


 while((dir=readdir(dr)))
{struct stat st;
   if(lstat(std::string(path+'/'+dir->d_name).c_str(),&st)!=0)
 {   //  stat(dir->d_name,&st);
     list->set_item(dir->d_name,file_type::ukn_t,0);
 char* error=strerror(errno);
     std::cout<<error<<"\n"<<dir->d_name<<"\n";
   }else
         list->set_item(dir->d_name,get_type(st),st.st_blocks);
 }

closedir(dr);
dr=nullptr;
bx->put(path);
list->sort_item();
 redraw();
}


void open_window::set_active(Item &it)
{
  active=&it;
   if(it.type()==file_type::file_t)
   {
       b_ok->content().deactivate();
   } if(it.type()==file_type::dir_t)
{       b_ok->content().activate();
b_ok->callback(cb_open,this);
  }
}

void open_window::cb_open(Address, Address a)
{

 open_window& win=reference_to<open_window>(a);
 std::string s=win.path+'/'+win.active->name();
 win.set_items(s.c_str());

}

void open_window::cb_open_file(Address, Address a)
{

}


//*************************************
// protected :::
void open_window::set_new_path(const char* n_path)
{ //1. selected
      // проверить если переданный path совпадает с именем selected добавить имя к пути
std::string new_path=path; // копируем установленный путь


    if(!n_path) return; // если путь не корректен,

    if(active&& strcmp(n_path,active->name().c_str())==0)
  {
   new_path=new_path+'/'+std::string(active->name());
   }
   // path=path+ '/'+selected.name
    // 2 button_up
    else  if(strcmp(n_path,"..")==0)  // убрать из path последний элемент
     {
       int pos=0,cnt=0; // если в пути только '/' менять ничего не будем

       const char* ch=new_path.data();
      while(ch&&*ch!='\0') // пробегаем по массиву
     {
      if(*ch=='/')
          pos=cnt;
        cnt++;
        ch++;
      }
      // обрезание
// std::cout"
     (pos==0)?
              new_path="/"                // вышли в
              :new_path=std::string(new_path.data(),pos);


     //
     } else new_path=n_path;
   //3 // проверить корректность пути можно в set_items
// просто передаем путь
     set_items(new_path.c_str());
 }


}
