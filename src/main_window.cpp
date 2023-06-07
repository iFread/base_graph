 #include "main_window.h"
#include "modal_window.h"
#include <fstream>

namespace Graph
{
void cb_quit_win(Address ,Address adr)
{  window * win =&reference_to<window>(adr);
  win->hide();
  delete win;
 exit(0);
      }


 void main_window::cb_open_win()  //
{

}
  void main_window:: cb_save_file(Address, Address adr)
 {
      main_window& win= reference_to<main_window>(adr);

     // func<main_window> f(&main_window::save_file);
    //my_functor fu(win,&main_window::open_file);
    my_functor<main_window> f1(win,&main_window::save_file);
    // save_window;
    //  save_window
        save_window*w=new save_window({300,300},800,600,"save_window",f1);
//  w->hide();
//  w->set_modal();
//  w->show();
  while(w->shown()&&w->visible())
  {
    Fl::wait();
  }
  delete w;
  }

 void main_window::open_win(Address, Address us)
 {
   main_window& win= reference_to<main_window>(us);


  //  func<main_window> f(&main_window::open_file);
 my_functor<main_window> f1(win,&main_window::open_file);
   new_open*  w=new new_open({200,200},800,600,"open_file",f1);
//   w->hide();
//   w->set_modal();
//   w->show();
  while(w->shown()&&w->visible())
  {
    Fl::wait();
   }
   delete w;
  // здесь открытие файла



 }
// открытие файла
 void main_window::open_file(const char* fl)
 {
     // добавить новый файл в stack_file
curent_file.list.clear();
     path=std::string(fl);
  std::ifstream fin(path);
 if(!fin)
 {
  std::cerr<<"Cann't open file "<<path<<"\n";
   // возможно создание модального окна ошибка открытия файла
  return;
 }
 curent_file.read_list(fin);
 fin.close();

redraw();
 }
//*******************сохранение файла****************************/

 void main_window::save_file(const char *fl)
 { // в окне должен быть доступен источник, откуда сохраняются данные
   // 2. в окне должен быть определен указатель текущего файла, и должен быть определен статус файла,
     // если файл, был сохранен на диск, и указатель текущего файла установлен, то для поля save callback() = сохранение текущего файла
     //
  std::ofstream fout(fl);
 if(!fout) return;
 curent_file.write_list(std::cout);
  curent_file.write_list(fout);
fout.close();
  }

main_window::main_window(Point p,int w,int h,const char* ttl):window(p,w,h,ttl),m(create_menu()),panels(new VLayout(Point(20,60))),//Point(20,150)))//,main_menu(new Menu(p,nullptr,orientation::horisontal))
scrl(new Scroll(Point(150,50),600,500)),
   can(new Canvas(Point(150,100),1000,1000))
{

 main_menu=new Menu(Point{0,0},m,nullptr,orientation::horisontal);
//curent_file.list.push_back(new line(Point(100,100),Point(200,200)));

 attach(*main_menu);
 attach(*panels);
 attach(*scrl);
 scrl->attach(*can);//Canvas(Point(0,0),1000,1000));
 create_panel(Point(20,150),(*scrl)[0]);
 static_cast<Canvas*>(&(*scrl)[0])->set_file(&curent_file);
}

main_window::~main_window()
{
    detach(*main_menu);
    delete m;
    delete main_menu;
    delete panels;
    delete scrl;
    delete can;


}

VLayout*main_window::create_panel(Point p, Widget &w)
{
 //VLayout *panels=new VLayout(p);
// добавить кнопки
//make_functor(static_cast<Canvas&>(w), &Canvas::set_tool,shape_type::sh_none_t);
    panels->attach( Button(Point(10,10),70,20,"line"));
    (*panels)[0].callback([](Address,Address adr){reference_to<Canvas>(adr).set_tool(shape_type::sh_line_t);},&w);
 panels->attach(Button(Point(10,10),70,20,"polyline"));

 (*panels)[1].callback([](Address,Address adr){reference_to<Canvas>(adr).set_tool(shape_type::sh_polyline_t);},&w);
 panels->attach(Button(Point(10,10),70,20,"rectangle"));
 (*panels)[2].callback([](Address,Address adr){reference_to<Canvas>(adr).set_tool(shape_type::sh_rectangle_t);},&w);
  panels->attach(Button(Point(10,10),70,20,"polygon"));
  (*panels)[3].callback([](Address,Address adr){reference_to<Canvas>(adr).set_tool(shape_type::sh_polygon_t);},&w);

  panels->attach(Button(Point(10,10),70,20,"circle"));
  (*panels)[panels->size()-1].callback([](Address,Address adr){reference_to<Canvas>(adr).set_tool(shape_type::sh_circle_t);},&w);




return panels;
 }

menu* main_window::create_menu() noexcept
{ //
 menu* m = nullptr;
 try{
     m= new menu(item("file") );
      m->add(item("tools"));
      m->add(item("help"));

     m->add(item("new"),"file");
     m->add(item("open",&main_window::open_win,this),"file");
     m->add(item("save"),"file");
     m->add(item("save as",&main_window::cb_save_file,this),"file");
     m->add(item("quit", cb_quit_win,this),"file");


     m->add(item("shapes"),"tools");
     m->add(item("line"),"tools/shapes");
     m->add(item("lines"),"tools/shapes");
     m->add(item("rectangle"),"tools/shapes");
     m->add(item("polygon"),"tools/shapes");
     m->add(item("circle"),"tools/shapes");

     m->add(item("about"),"help");
     m->add(item("contacts"),"help");
  } catch(std::exception& e)
  {
   std::cerr<<e.what()<<"\n";
 }
 return m;
}

}

