#include "main_menu.h"
#include "own_fl_widgets.h"
#include <Fl/Fl_Box.H>
#include "window.h"
namespace Graph {


void  item::draw(int x,int y) const
{

 // int ofnt=fl_font();
 // int osz=fl_size();
    int ofl=fl_color();
 //  fl_rectf(x,y,size()*8,20,FL_GRAY);
    fl_color(FL_BLACK);
    fl_draw(txt.c_str(),x,y);
  fl_color(ofl);
 }


const char* item::elem_name(const char *path, char *buf)
{
 const char *ch=path;
 char* c_buf=buf;
 while(ch&&*ch!='\0'&&*ch!='/')
     *c_buf++=*ch++;

// while(ch && *ch++=='/')
 if(*ch=='/')
     ch++ ;
   return ch;
}

//******************************************

void menu::add(item *it, const char *path)
{
   item *cur=this;
   item* previos=this;

 while(path&&*path!='\0')
 {
     char buf[24]={0};
     int cnt=cur->size();
  path=elem_name(path,buf);
  for(int i=0;i<cnt;++i)
  {
      if(strcmp(cur->name(),buf)==0)
      { if(cur->state()!=item::as_menu) // расширить cur до меню, при создании menu, первый элемент всегда типа menu, а остальные должны иметь parent()
          {
              menu* new_m=new menu(std::move(*cur) );
            //  new_m->submenu(it);
         delete  cur;
             cur=new_m;
          if(new_m->parent())
          {   item *par=new_m->parent();
                    par->next(new_m);
                // cur=par->next();
           if(new_m->next())
           {
             new_m->next()->parent(new_m);
           }
          }//else  // а если у нас родителя нет,т.е. первый пункт меню, сюда не попадем
            if(cur->parent()!=previos)
           static_cast<menu*>(previos)->submenu_=cur;
           }

 if(static_cast<menu*>(cur)->submenu())
 {
     previos=cur;
    cur= static_cast<menu*>(cur)->submenu();
    break;
 } else
 {
   static_cast<menu*>(cur)->submenu(it);
     return;
  }

      }
      previos=cur;
      cur=cur->next();
  }

 }
 cur->add(it);
}

void menu::draw(int x, int y) const
{

}

//item& menu::operator[](int i)
//{
//    i=i<sz-1?i:sz-1;
//menu* it=this;
//    for(int k=0;k<i;k++)
//   it=it->next();
//     // return *( next_+i);
//    return *it;
//}

//const item& menu::operator[](int i) const
//{
//i=i<sz-1?i:sz-1;
//const menu* it=this;
//    for(int k=0;k<i;k++)
//   it=it->next_;
//     // return *( next_+i);
//    return *it;
//}




//item* menu::find(const char *path,item* it) // принимает меню в котором ищет, path
//{
//  if(!it&&(!path||*path=='\0'||*path==' '))
//      return it;  // nullptr
//// если it пустой, а path пустой, значит нашли

//  char buf[24]={0}; // magic_number!!! #define path_elem=24 or const int max_len_elem=24;
//const char *ch_p=path;
//int idx=0;
//while(ch_p && *ch_p!='\\'&& *ch_p!='\0')
//{
// buf[idx++]=*ch_p;
// ch_p++;
//}
//// проверить, что it->name!= buf
// // если равен, ищем в нутри it, если нет, ищем по меню
//if(it) // ищем в глубину ->next()
//{
//  find(++ch_p ,it->next());

//} else // ищем в ширину
//{ // проверить себя
//  menu* cur=this;
//// while(true)
//for(int i=0;i<sz;++i)
//  { // std::cout<<"cur["<<i<<"]="<<(*cur)[i].name()<<"\n";
//    if(strcmp((*cur)[i].name(),buf)==0)
//     {
//         return find(++ch_p,&cur[i]);
//     }
//  //if(!cur->next()) return cur;
//    // cur=cur->next();
//    }

//}

// return nullptr;
//}

//*********************************
item* menu_bar::parser_path(const char* name )
{ //tool/create/simple
    // первую подстроку до разделителя
  //int lavel=idx; //
std::string s;
const char *ch=name;

while(ch && (*ch!='\\') )
{
 s+=*ch;
 ch++;
}
 // lavel++;
 item* cur=nullptr;
 // if(idx==0)  ищем в массиве
 for(size_t sz=0;sz<arr.size();++sz)
 {
   if(strcmp(s.c_str(),arr[sz]->name())==0)
   {
    cur= arr[sz];
    break;
   } }

  // parser(ch,cur)
 // проходить по текущему
 // возвращать ,nullpr если значение не найдено в векторе
  // возвращать указатель на значение в векторе, если idx==0
  //  возвращать указатель на элемент, за которым следует вставить item если idx>0
 // при вставке, next() найденного элемента указывает на вставляемый, а next() вставляемого присваивается next() найденного
 if(cur)
 {
   //parser_path(ch,lavel);
 ;
 }

 return cur;
}

item* menu_bar::parser_path(const char *name, item *it) // it==nullptr
{ // проверяем что есть что искать
    if(!name||*name=='\0')
         return it;  // путь закончен
  const char *ch=name;
   char buf[32]={0};
   int idx=0;
  item *cur=it;
   while(*ch != '\\'&& *ch !='\0')
   {
      buf[idx++] =*ch++;
   }


    if(cur)  // если есть эдемент где искать, ищем в нем
  {
    while(true)
    {
      if(strcmp(buf,cur->name())==0)
      {
        return parser_path(ch,cur);
      } else
       {  if(!cur->next())
          {
              return cur->next();
          }
          cur=cur->next();
        }
    } // доходит до конца списка, и вернет последний элемент,не nullptr

  }
  else  // ищем в vector<>  если есть что искать
 {
   for(size_t sz=0;sz<arr.size();++sz)
   {
      if(strcmp(buf,arr[sz]->name())==0)
      {
          return parser_path(ch, arr[sz]);
      }
   }

  }

    return cur;
}

int menu_bar::parser(item* it)
{

    return it->size()<<3;
 }

  // пройти по элеметам menu

void menu_bar::create(Point p, int w, int h)
{
    pw=new fl_empty(p,w,h);
    pw->box(FL_DOWN_BOX);
    pw->user_data(this);


}
Widget& menu_bar::create()
{
    return *this;
}

void menu_bar::draw()
{
  int dx=Fl::event_x();
     int wd=0;

    for(size_t i=0;i<arr.size();i++)
    {

   if(arr[i]==active)
    fl_rectf(loc.x()+wd-2,loc.y(),parser( arr[i])+4,20,FL_BLUE);
   else
       fl_rectf(loc.x()+wd-2,loc.y(),parser( arr[i])+4,20,FL_GRAY);

  arr[i]->draw(loc.x()+wd,loc.y()+15 );
  wd+=parser(arr[i]);
   }
  // здесь отрисовка виджета
     if(pt) pt->content().redraw();
 }

int menu_bar::handle(int ev)
{
    switch (ev)
    {
       case FL_LEAVE:
        if(active){
            active=nullptr;
           pw->redraw();
        }
      //  std::cout<<" leave in widget\n" ;
        break;
    case FL_MOVE:
    {
     int dx=Fl::event_x();//-loc.x();
  int wd=0;
    for(size_t i=0;i<arr.size();++i)
     {
    if(dx>loc.x()+wd && dx <loc.x()+wd+parser( arr[i])) {
     { if( active!=arr[i]){
           active= arr[i];
           pw->redraw();}

       }

    }
 wd+=parser(arr[i]);

}

    }
  break;
 case FL_PUSH:
      // обработка события меню
        // если меню активно, handle() передается ему
     switch (Fl::event_button())
        {
          case FL_LEFT_MOUSE:
         if(pt && Fl::belowmouse()!=&pt->content())
         {
              printf("unfocus events\n");
        //  pt->hide();
              if(pt ) {own->detach(*pt);
                    delete pt;
                pt=nullptr;
                return ev;
              }
         } else
         {  // здесь событие уходит в submenu

    //      std::cout<<"in widget cliced\n";
          }
 // при нажатии, пункт меню,
         if(active)
           { //std::cout<<"new creating widget\n";
          //   menu_bar* bar=new menu_bar(loc+100);
               Button *b=new Button(loc+100,70,20,"new button");
            const item* it=active ;
            //  own->attach(*bar);
            for(;it->next();){
               it=it->next();
                std::cout<<it->name()<<"\n";

             // bar->add(*it,active->name());
             // pt=bar;
           } //b->attach(*own);
             own->attach(*b);
             own->set_active(*this,FL_PUSH);
             pt=b;

             //b->content().take_focus();

             b->show();
            own->redraw();
//
           // Fl::pushed(&b->content());
            }


            break;

        }
        break;
    }

 return ev;
}



// if(pt->x()<dx && pt->x()+pt->w()>dx && pt->y()<dy && pt->y()+pt->h()>dy)
 //pw->redraw();
//  std::cout<<"handle in sub_menu\n";

// path=="item_name_lavel1/item_name_lavel2/item_name_lavel3"
//

/* Если Paht не существует, или не коректен ???
 * 1. Можно использовать только корректный path : ==> file/blabla/quit  == file/quit если   blabla не найдено
 Место для вставки: вставлять в конец начало или по индексу ????
  допустим функция будет иметь вид add(item it, const char* path, index i=255)
// где index отвечает за положение в списке :::
         если индекс >= размеру списка вставка в конец,
              индекс ==0 вставка в начало,
              иначе вставка по номеру, т.е. сдвигая элементы по индексу



 */
void menu_bar::add(item *it, const char *path, unsigned char ind) // file, view, help
{
//   if(!path)
//    {
//      // arr.push_back(new item(it.name()));

//       resize(pw->w()+parser(&it)+4,20);
//    }
//     else
//    {
//     for(size_t i=0;i<arr.size();++i) {
//      item* cur=
//               parser_path(path, arr[i]);
//        if(cur) {
//             cur->add(it);
//             return;
//        }
//     }   //arr[0].add(*new item(it));

//   }
    if(menu_)
        static_cast<menu*>(menu_)->add(it,path);
     else
     {   menu_=new menu(std::move(*it));
    delete it;}
// std::cout<<"pw->size() =="<<pw->w()<<"\n";
}
//size_menu++;


}

