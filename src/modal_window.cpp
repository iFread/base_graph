 #include "modal_window.h"
#include <Fl/Fl_Button.H>
#include <unistd.h>
#include <dirent.h>
#include <cstdio>
#include <sys/stat.h>
#include <fcntl.h>
#include <algorithm>

 namespace Graph {
//void cb_open_file(Address, Address a)
//{
// open_window& win=reference_to<open_window>(a);
// // вывать основную функцию для которой все это затевалось:
// // открыть файл который находится в active
//}

// base_modal_window :



// modal_window

 void modal_window::init()
 {
      b_ok->set_position(Point(w()-80,h()-60));
        attach(*b_up);
        attach(*list);
        attach(*c_path);
// init()
        b_cancel->callback([](Address,Address ad){
            std::cout<<"hide win\n";
            reference_to<window>(ad).hide();
          },this);

        b_up->callback([](Address,Address adr){
        modal_window& w=reference_to<modal_window>(adr);
        w.set_new_path("..");
        },this);

        b_ok->callback([](Address, Address a){
         modal_window& w=reference_to<modal_window>(a);
         // w.open_file();
         w.action();

        },this);
  //  base_func *f=make_functor(b_ok->content(),&b_ok->content().callback);
list->set_callback(*this,&modal_window::action);

//        },this);
visible(true);
        char buf[128]={0};
        path=std::string(getcwd(buf,128));
        set_new_path(buf);
 }

 void modal_window::set_new_path(const char *n_path)
 {
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

 void modal_window::set_items(const char* pth)
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
    }
     else
          list->set_item(dir->d_name,get_type(&st),st.st_blocks);
  }

 closedir(dr);
 dr=nullptr;
 c_path->put(path);
 list->sort_item();
  redraw();
 }

 file_type modal_window::get_type(struct stat *type)
{  file_type res= ukn_t;
   if(!type) return res;

     if(S_ISDIR(type->st_mode))
        res= file_type::dir_t;
   else   if(S_ISREG(type->st_mode))
            res=  file_type::file_t;
   else  if(S_ISBLK(type->st_mode))
       res=  file_type::blc_t;
   else if(S_ISCHR(type->st_mode))
       res=  file_type::chr_t;

        return res;// open_window::file_type::ukn_t;
}

 void modal_window::action()
 {
    active=list->select();
    if(!active) return;
     if(active->type()==file_type::dir_t) // если передан каталог
     {
       set_items(std::string(path+"/"+active->name()).c_str());
     //  list->select(nullptr); //clear selected in list

     }
      else  // пытаемся открыть, файл:: т.е. передаем путь вызвавшему окну
      {
//       std::string s=path+"/"+active->name();
//     //   main_window& win=reference_to<main_window>(own);
//       // (*futh)(win,s.c_str());
// // my_functor<main_window> *f =static_cast<my_functor<main_window >*>(fun);//(s.c_str());
//  my_functor<window> *f =static_cast<my_functor<window >*>(fun);
//  if(f) (*f)(s.c_str());
//    this-> hide();
// // visible(false);
   b_cancel->content().do_callback();
  }
 }


 // new_open

 void new_open::init()
 {
    // modal_window::init();
     attach(fl_name);



     //  Item* it=list->get_select();
   // list->callback([](Address,Address adr)
//std::cout<< list->get_select()->name();
  //{
    // new_open& win=reference_to<new_open>(adr);
     // if(win.active)
       //   win.fl_name.put("Hello_World");//win.active->name());
   // },this);
 //    fl_name.put(std::string("Helo_world"));

 }
 // открытие файла, если dir_t вызывать обработку
void new_open::action()
{  active=list->select();

    if(!active) return;
// будем проверять на double_click

    fl_name.put(active->name()) ;

if(Fl::event_clicks())
{
    if(active->type()==file_type::dir_t)
    {
       modal_window::action();
    } else
      { // проверить что файл соответствует, и вызвать функцию открытия файла, передав полный path
        // например проверить формат файла
      std::string s=path+'/'+active->name();
     // my_functor<window> *f =static_cast<my_functor<window >*>(fun);
      if(fun)
           (*fun)(s.c_str());
      b_cancel->content().do_callback();
 }
}


}
//*********************************

void save_window:: init()
{
    attach(fl_name);

}


void save_window::action()
{   // 0. проверить что элемент не выбран,
        //если выбран элемент и это каталог, -modal_window::action();
        // если выбран файл, и fl_name!=empty() выбор игнорируется
    //1. получить имя файла из fl_name и передать полный путь в callback функцию
     active=list->select();
        if(active&&active->type()==file_type::dir_t)
         {
          modal_window::action();
        } else
         {
             std::string file=fl_name.get_string();
             if(file.empty())  {
              // вывод модального окна с ошибкой, не задано имя файла, и вернуться к истокам ???
                 std::cout<<"Error, undefined file name \n";
                 return;
              }
            // иниче вызываем установленную функцию
             if(fun) {
               std::string s=path+'/'+file ;
                 (*fun)(s.c_str());
        }
             b_cancel->content().do_callback();

        }

    // проверка на соответствие имени : буквы,цифры, подчеркивания, формат


}



 // open_window:
open_window::open_window(Point o, int w, int h, window& parent,func<main_window> *f ):window(o,w,h,"open"), // создаем окно, нужен родитель?  void (window::*f)(const char *)
    b_ok(new Button(Point(w-100,h-45),70,20,"open")),b_cancel(new Button( Point(w-100,h-25),70,20,"Cancel")),
    b_up(new Button(Point(w/4*3+10,10),30,30,"Up")),
  list(new Simple_table(Point((w-20)/4,50),w/4*3,h-110)), //Simple_list( Point o,x,y,..const std::vector<item>& v)
  bx(new Out_Box(Point((w-20)/4,10),(w-20)/4*2,30)),
  fl_name(new Out_Box(Point(w/2,h-45),w/4,20)),
  own(&parent),futh(f)
{
attach(*b_ok);
attach(*b_cancel);
//list->move((w-20)/4,10);
attach(*b_up);
attach(*list);
attach(*bx);
attach(*fl_name);

//bx->put(list->value());
b_cancel->callback([](Address,Address adr){
open_window* w=&reference_to<open_window>(adr);//.hide();
w->hide();
 // delete w;
},this);


b_up->callback([](Address,Address adr){
open_window& w=reference_to<open_window>(adr);
w.set_new_path("..");
},this);

b_ok->callback([](Address, Address a){
 open_window& w=reference_to<open_window>(a);
 w.open_file();

},this);

char buf[128]={0};
path=std::string(getcwd(buf,128));
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
   }
    else
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

 fl_name->put(active->name());
  } else if(it.type()==file_type::dir_t)
       fl_name->put("");
}


void open_window::open_file()
{
 if(active->type()==file_type::dir_t) // если передан каталог
 {
  set_items(std::string(path+"/"+active->name()).c_str());
 }
  else  // пытаемся открыть, файл:: т.е. передаем путь вызвавшему окну
  {
   std::string s=path+"/"+active->name();
    main_window& win=reference_to<main_window>(own);
    (*futh)(win,s.c_str());

      b_cancel->content().do_callback();
      }

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
