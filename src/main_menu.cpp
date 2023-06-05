#include "main_menu.h"
#include "own_fl_widgets.h"
#include <Fl/Fl_Box.H>
#include "window.h"
namespace Graph {


//void  item::draw(int x,int y) const
//{

// // int ofnt=fl_font();
// // int osz=fl_size();
//    int ofl=fl_color();

// }


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

void menu::add(item &&it, const char* pth)
{
  add(new item(std::move(it)),pth);

}

//void menu::draw(int x, int y) const
//{

//}

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

//*******************************************************
//********************* Menu

// drawing menu
// defines to size the Widget to fit all elements

Menu::~Menu()
{
 //   std::cout<<"delete menu for "<<menu_->name()<<"\n";

    if(submenu_)
{  submenu_->hide();
    own->detach(*submenu_);
 Menu* it=submenu_;
 submenu_=nullptr;
 delete it;

}
 //   hide();
  //  own->detach(*this);
//Menu*it=this;

          //     submenu_=nullptr;


}
void Menu::create(Point p, int w, int h)
{
    pw=new fl_empty(p,w,h);// FL_Box
     set_widget_size(menu_);
   //  pw->box(FL_UP_BOX);
    pw->user_data(this);
}

void Menu::set_widget_size( const item* it)
{
  if(!it) {
      resize(0,0);
      return;

      }
    int wd=0;
     int ht=0;
    for(const item*cur=it ;cur;cur=cur->next())
  {
   if(orient==orientation::vertical)
       wd=(wd< (cur->width()*9))?cur->width()*9:wd;
    else
        wd+=cur->width()*9;
     }
 // height:
  if(orient==orientation::vertical)
  { wd+=wd/3;
     ht=it->size()*20;
      } else
    ht=20;

 resize(wd,ht);

}
void Menu::draw_item(Point o,const item* it) const
{
    int ofl=fl_color();
    fl_color(Fl_Color(FL_BLACK));
     fl_draw(it->name(),o.x()+5,o.y()+15);
     fl_color(ofl);
}
void Menu:: draw() const
{
Point o=loc;
 const item* cur=menu_;
  fl_rectf(loc.x(),loc.y(),w(),h(),FL_GRAY);
// fl_rectf(loc.x(),loc.y()-1,w()-1,h()-1,FL_GRAY);
 // рисуем box

for(;cur;cur=cur->next())
{
 int wdth= fl_width(cur->name())+10;

if(curent_item.active_==cur) { // curent_active не изменяется если:
    // При собьтии Fl_Leave   submenu_visible && положение курсора уходит на submenu_
    //
    fl_rectf(o.x(),o.y(),wdth-2,18,FL_GREEN);

} else
      fl_rectf(o.x(),o.y(),wdth-2,18,FL_GRAY);

 draw_item(o ,cur);
 if(orient==orientation::vertical)
 {
  o.y()+=20;
 } else
 {
  o.x()+=wdth;
 }
}
//if(submenu_ ){
//    if(dynamic_cast<Menu*>(submenu_)->curent_item.status==submenu_visible)//&& curent_item.active_ && curent_item.status==submenu_visible)
//    dynamic_cast<Menu*>(submenu_)->draw();
//}
}

int Menu::handle(int e)
{


    switch (e)
    {
     case FL_LEAVE:

//  if(curent_item.active_&& submenu_){ // если есть submenu_ то возможно переход на submenu_, и убирать его не надо
//        std::cout<<"leave "<<curent_item.active_->name()<<"  item\n";

//   if(orient==orientation::vertical && submenu_) // если меню вертикальное, убрать submenu
//     { // куда уходим? на submenu_ или нет
//        std::cout<< curent_item.active_->name()<<" will be close\n";
//          own->detach(*submenu_);
//          delete submenu_;
//          submenu_=nullptr;
//      }

 // break;
  // }else  // если submenu_ не активно
//    if(orient==orientation::horisontal && submenu_)
//        break;
//    else
    { // curent_item.clear();
        if(curent_item.active_ && curent_item.status==status_menu::submenu_visible)
        {
            // проверить что в границах submenu_
       if(submenu_){
         int x_ps=Fl::event_x();
          int y_ps=Fl::event_y();
       if(x_ps > submenu_->loc.x()-5  && x_ps<submenu_->loc.x()+submenu_->w())
       {
          if(y_ps> submenu_->loc.y()-2 && y_ps< submenu_->loc.y()+submenu_->h())
              break;
        }
     //  delete submenu_;
     clear();
//         submenu_->clear();
       submenu_=nullptr;
//       submenu_->hide();
       }
    }else
          curent_item.clear();
 // при оставлении меню, если это не меню первого уровня, нужно уничтожать это меню,
    // возможно при выходе из меню посылать сигнал родителю, что бы он решал уничтожать submenu или нет
     pw->redraw();
    }   break;

    case FL_MOVE:
    {
     int dx=Fl::event_x();//-loc.x();
     int dy=Fl::event_y();
     int wd=loc.x();
     int hd=loc.y() ;
     const item* cur = menu_;
    for(;cur;cur=cur->next())
    {
         if(orient==vertical)
         { if(dy>hd && dy< hd+20)
             {

     break;
             }
            hd+=20;

         }
         else
         {
             if(dx>wd && dx <wd+cur->width()*9){

                break;
         }


          wd+=cur->width()*9;


         }
    }
 if(cur &&(cur!=curent_item.active_)){
     curent_item.orig=orient==orientation::vertical?Point(wd+w(),hd):Point(wd,hd+20);
     if(submenu_) // если submenu
     {
      clear();
//          delete submenu_;
//         submenu_=nullptr;
        // break;

     if(cur->state()==item::as_menu)
    {
       curent_item.set_state(cur,status_menu::submenu_visible);
   submenu_=create_submenu(curent_item.orig,curent_item.active_);
 }  }else
  { //if(cur==curent_item.active_) break;
      if(strcmp(cur->name(),"quit")==0)
      {  std::cout << e<<" handle \n";
       if(curent_item.active_)
           std::cout<<"active name ="<<curent_item.active_->name()<<"\n";
      if(cur)
       std::cout<<" curent elem name = "<<cur->name()<<"\n\n";
        }
              curent_item.set_state(cur,status_menu::active);
         //     break;
     }
   own->redraw();
 }

 }


        break;
    case FL_RELEASE:

   std::cout<<"submenu position :"<<curent_item.orig.x()<<", "<<curent_item.orig.y()<<"\n";

 if(curent_item.active_ ){
      if(curent_item.active_->state()==item::as_menu && !submenu_)
 { std::cout<<"create menu for "<<curent_item.active_->name()<<"\n";
    curent_item.set_state(curent_item.active_,submenu_visible);
  submenu_=create_submenu(curent_item.orig,curent_item.active_);

} else if(curent_item.active_->state()==item::as_menu && submenu_)
      {
     //     delete submenu_;
        clear();
      //  clear();
        submenu_=nullptr;
        curent_item.set_state(curent_item.active_,active);
      }

else {
    std::cout<<"here call callback function for "<<curent_item.active_->name()<<"\n";
     item*it= const_cast<item*>(curent_item.active_);
             //const_cast<item*>(curent_item.active_)
       clear_all();
      it->callback();
   // clear();  // здесь должны очистить текущее меню т.е. до верхнего уровня

  //  it->callback();
    break;
}
}
 own->redraw();


// {
// if(curent_item.active_&&curent_item.active_->state()==item::as_item)

 // закрыть всю цепочку меню,

//    }

        break;

    }
    return e;
}
// создать меню из it->submenu(); или it  уже  submenu
// привязать к окну : own->attach(*submenu_);
Menu* Menu::create_submenu(Point o, const item* it)
{ if(!it || it->state()!=item::as_menu)
            return nullptr;
std::cout<<"create menu for " <<it->name()<<"\n";
   Menu* m=new Menu(o,static_cast<const menu*>(it)->submenu(),this,vertical);
    //m->curent_item.set_state(m->menu_,curent_item.status);

   own->attach(*m);
  // own->set_active(*m,FL_PUSH);
//   submenu_=m;
   return m;
}

void Menu::set_submenu(Point o, const item *it)
{//1. Можно удалить старое и создать новое,
  // 2. Изменить размер и положение виджета
 // Variant 2
    if(it)
  std::cout<<"set submenu for "<<it->name()<<"\n";
if(it&&it->state()==item::as_menu && static_cast<const menu*>(it)->submenu())
{ const item* pit=static_cast<const menu*>(it)->submenu();

//submenu_->clear();
   // submenu_->hide();

// submenu_->loc=o;//(loc.x()-o.x(),loc.y()-o.y());
//submenu_->set_widget_size(pit);
//submenu_->menu_=pit;
//submenu_->show();
//} else {
//submenu_->hide();
//submenu_->set_widget_size(nullptr);
//submenu_->menu_=nullptr;

}

}

 // рекурсивня функия
void Menu:: clear_all()
{  clear();
  if(parent) {
       parent->clear_all();

}
}
void Menu::clear()
{

    if(submenu_) {
     submenu_->hide();
  // submenu_->clear();
     Menu* it=submenu_;
 own->detach(*it);
        submenu_=nullptr;
//std::cout<<"delete "<<it->menu_->name()<<"\n";
        delete it;  }


}

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
    pw->box(FL_UP_BOX);
    pw->user_data(this);


}
Widget& menu_bar::create()
{
    return  *this;
}

void menu_bar::draw() const
{
//fl_rect(pw->x()-1,pw->y()+1,pw->w()+1,pw->h()+1,FL_BLACK);
 Point orig=loc;

  item* cur=menu_;
     for(int i=0;i<menu_->size();i++,cur=cur->next())
    {
         double wdth= fl_width(cur->name());
   if(menu_curent.active==cur)
   {  fl_rectf(orig.x(),orig.y(),wdth+10,20,FL_GREEN);
    if(menu_curent.flag==menu_bar::submunu_visible)
       draw_submenu(orig,menu_curent.active);
    }
       else
         fl_rectf(orig.x(),orig.y(),wdth+10,20,FL_GRAY);
   draw_item(Point(orig.x(),orig.y()),cur);

    orig.x()=orig.x()+wdth+10;
   }
//     if(menu_curent.active && (menu_curent.flag==menu_bar::submunu_visible))//||menu_curent.flag==menu_bar::menu_active))
//     {
//       draw_submenu({100,100},menu_curent.active);
//      std::cout<<"active name ->"<<menu_curent.active->name()<<"\n";
//     }
 }

void menu_bar::draw_item(Point o, const item *it) const
{
      int ofl=fl_color();
    fl_color(Fl_Color(FL_BLACK));
     fl_draw(it->name(),o.x()+5,o.y()+15);
     fl_color(ofl);
}

void menu_bar::draw_submenu(Point o, const item *it) const
{
   //const item* c=it->state()==item::as_menu?static_cast<const menu*>(it):it;

   int hd= it->state()==item::as_menu?static_cast<const menu*>(it)->submenu()->size()*20:20;//it->size()*20;
   // определить ширину виджета, (можно определять ширину при добавлении item) ширина должна учитывать возможность быстрого доступа
   // т.е.  item->name() " + space +" "Ctrl+ O" // комбинация быстрого доступа
    int wd=150;
  fl_rectf(o.x(),o.y()+20,wd,hd,FL_GREEN);
  if(it->state()==item::as_menu)
  { const item* m=static_cast<const menu*>(it)->submenu();
    for(int hd=0;m;m=m->next())
     {// double wdth=fl_width(m->name());

         draw_item(Point(o.x(),o.y()+hd+20),m);

      hd+=20;
     }


  }

}

int menu_bar::handle(int ev)
{ Point o=loc; // при движении по меню устанавливаем o в начало нового элемента
    switch (ev)
    {
       case FL_LEAVE:
        if(menu_curent.active){
           if(menu_curent.flag==submunu_visible)
      {     break;
        } else {     menu_curent.clear();
             pw->redraw();}

        }

        break;
    case FL_MOVE:
    {
     int dx=Fl::event_x();//-loc.x();

     int wd=0;
    for(item* cur = menu_;cur;cur=cur->next())
    {
    if(dx>loc.x()+wd && dx <loc.x()+wd+(cur->width()*9)) {
       if(menu_curent.active!=cur){
      // status_menu m=menu_curent.flag;
 if(pt)
      pt->content().label(cur->name());

       if(menu_curent.flag==menu_bar::submunu_visible)
          menu_curent.set_state(cur,menu_bar::submunu_visible);
        else
           menu_curent.set_state(cur,menu_active);
       pw->redraw();
own->redraw();

}
 break;
    }
 wd+=cur->width()*9;

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
              menu_curent.clear();
                return ev;
              }
         } else
         {  // здесь событие уходит в submenu

    //      std::cout<<"in widget cliced\n";
          }
 // при нажатии, пункт меню,
         if(menu_curent.active)
           { //std::cout<<"new creating widget\n";
          //   menu_bar* bar=new menu_bar(loc+100);
               Button *b=new Button(loc+100,70,20,menu_curent.active->name());
            const item* it=menu_curent.active ;
           menu_curent.flag=menu_bar::submunu_visible;
            //  own->attach(*bar);
           const item *sub= it->state()==item::as_menu?static_cast<const menu*>(it)->submenu():it->next();
           for(;sub;){
                std::cout<<sub->name()<<"\n";
                sub=sub->next();

             // bar->add(*it,active->name());
             // pt=bar;
           } //b->attach(*own);
             own->attach(*b);
             own->set_active(*this,FL_PUSH);
            if(pt) delete pt;
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

 if(!path){ resize(w()+it->width()*9 ,20);
  std::cout<<"width widget more  "<<it->width()<<"\n";
 }
     if(menu_)
        static_cast<menu*>(menu_)->add(it,path);
     else
     {   menu_=new menu( std::move(*it)) ;
        delete it;
    }



}
//size_menu++;


}

