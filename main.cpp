#include <iostream>
#include <ctime>
#include <unistd.h>
#include "base_graph.h"
//#include "window.h"
#include "base_gui.h"
#include "math_primitives.h"
#include "group_widgets.h"
#include "own_gui_widgets.h"
#include "base_tools.h"
#include "main_menu.h"
#include "item_list.h"
#include "modal_window.h"
#include "u_item.h"
#include "main_window.h"



using namespace std;

using namespace::math;
class B;
class A{

protected:
   char name;
public:
 A():name('a'){}
 A(const A& a):name(a.name){}
 A(const B& b):name('A'){}
 void foo(){std::cout<<"field name ="<<name<<"\n";}

};

void tst_sort();

void show_area(area_t ar);

void tst_rbtree();

int common_tests();

int tst_menu();
int tst_submenu();
int tst_main_window();

static void cb_quit( Graph::Address add,Graph::Address add2)
{
 Graph::window *win =  &Graph::reference_to<Graph::window>(add2);
// Graph::window* win =static_cast<Graph::window*>(add2);
   win->hide();
 // delete win;
 exit(0);
}

// void cb_open(Graph::Address,Graph::Address adr)
// {
//     Graph::window &win=Graph::reference_to<Graph::window>(adr);
//   Graph::func<Graph::open_window> f(&Graph::window::set_path);
//     Graph::window*m_win=new Graph::open_window(Point{200,200},780,600,win,&f);//&Graph::window::set_path);

//    m_win->hide();
//    m_win->set_modal();

//    m_win->show();
//     while (m_win->shown()) {
//   Fl::wait();

//     }
//     delete m_win;
// }

int main()
{


//tst_sort();
   //tst_rbtree();
// common_tests();
//  return tst_menu();
 //  return tst_submenu();
  return tst_main_window();
    return 0;
    }

int tst_main_window()
{
    using namespace Graph;
    main_window *win =new main_window({100,100},800,600,"common test");


   int res=gui_run();
   return res;
}

int tst_submenu()
{
    using namespace Graph;
{
    window*win= new  Graph::window  (Point{100,100},800,600,"test_submenu");
  Out_Box bx({200,200},100,20);
  win->attach(bx);

//Graph::window *winM=new Graph::window({100,100},500,600,"open");
 // Graph::open_window win_open({100,100},500,600,"open");
  menu m(new item("file"));
   m.add(new item("view"));
   m.add(new item("property"));
   m.add(new item("help"));
   // m["file"]["open"].callback("cb")
  // m.add(new Graph::item("open",cb_open,&win),"file");
   m.add(new Graph::item("new"),"file");
    m.add(new Graph::item("save"),"file");
     m.add(new Graph::item("quit",cb_quit,&win),"file");
     m.add(new Graph::item("save_as"),"file/save");
      m.add(new Graph::item("save_curent"),"file/save");
    m.add(new Graph::item("about"),"help");
    m.add(new Graph::item("version"),"help");
    m.add(new Graph::item("constacts"),"help");

  Menu m_menu({10,0},&m,nullptr,orientation::horisontal);
win->attach(m_menu);


//Graph::Button* b_ok=new Graph::Button({10,10},70,20,"Ok");
//Graph::Button* b_cancl=new Graph::Button({90,10},70,20,"Cancel");
//winM->set_modal();
//winM->hide();
//winM->attach(*b_ok);
//winM->attach(*b_cancl);

////Graph::Out_Box* bx=reinterpret_cast<Graph::Out_Box*>(adr);

//b_ok->callback([](Graph::Address,Graph::Address ad)
//{
//Graph::Out_Box& b= Graph::reference_to<Graph::Out_Box>(ad);

//b.put("Ok");
////b.content().parent()->hide();

//},&bx);

//b_cancl->callback([](Graph::Address,Graph::Address ad)
//{
//Graph::Out_Box& b= Graph::reference_to<Graph::Out_Box>(ad);

//b.put("Cancel");


//},&bx);



int ret= Graph::gui_run();
 delete  win;
return ret;
    }
    return 0;
    }

int tst_menu()
{
  Graph::window*win= new  Graph::window  (Point{100,100},800,600,"test_menu");
    Graph:: menu_bar menu({10,0});
     win->attach(menu);
      menu.add(new Graph::item("file"));
       menu.add(new Graph::item("view"));  // menu add ("file view tool help"
     menu.add(new Graph::item("open"),"file");
       menu.add(new Graph::item("property")); // menu.add("open,new, ",), menu.add( item*,"file"), menu add(submenu *sb, "file")
       menu.add(new Graph::item("help"));
  menu.add(new Graph::item("new"),"file");
   menu.add(new Graph::item("save"),"file");
    menu.add(new Graph::item("quit"),"file");
  menu.add(new Graph::item("version"),"help");
  menu.add(new Graph::item("about"),"help");

          menu.add(new Graph::item("text_edit"),"view");
              menu.add(new Graph::item("panels"),"view");
                  menu.add(new Graph::item("text_editor"),"property");
  win->attach(Graph::Button({ 1, 100},80,20,"transform"));
                  Graph::gui_run();
    delete win;
                  return 0;
}


void tst_sort()
{

srand(time(0));
char arr[100];

for(int i=0;i<100;++i)
{
  arr[i]= 'a'+rand()%27;
}

for(int i=0;i<100;++i)
{
 std::cout<<arr[i]<<" ";
}
std::cout<<"\n";
Graph::sort(arr,arr+100,[](int a,int b){return a<b;});

for(int i=0;i<100;++i)
{
 std::cout<<arr[i]<<" ";
}

 std::cout<<"\n";



}

int common_tests()
{  Graph::window win(Point{100,100},800,600,"test");

        Graph::HLayout ln({ 10,  70});

        Graph::VLayout vln({10,10});

      win.attach(ln);


      Graph::Scroll scrl({230,70},550,500);


       win.attach(scrl);

       scrl.attach(Graph::Canvas  ({150,50},1000 ,1000));

      ln.attach(Graph::VLayout ({10,210}));
       Graph::reference_to<Graph::VLayout>(&ln[0]).attach(Graph::Button({10,200},70,20,"line"));
       Graph::reference_to<Graph::VLayout>(&ln[0]).attach(Graph::Button({10,200},70,20,"polyline"));
        Graph::reference_to<Graph::VLayout>(&ln[0]).attach(Graph::Button({10,200},70,20,"rectangle"));
       Graph::reference_to<Graph::VLayout>(&ln[0]).attach(Graph::Button({10,200},70,20,"polygon"));
      Graph::reference_to<Graph::VLayout>(&ln[0]).attach(Graph::Button({10,200},70,20,"circle"));


      vln.attach(Graph::Button({0,10},70,20,"move+"));
      vln.attach(Graph::Button({0,10},70,20,"move-"));



       ln.attach(Graph::Button({ 0, 0},80,20,"transform")); //bt);
        ln.attach(vln);



      vln[0].callback([](Graph::Address,Graph::Address adr){
          Graph:: Canvas& p=Graph::reference_to<Graph::Canvas>(adr);
           //p.set_tool(Graph::get_line);
      p.move(10,10);
      },&scrl[0]);
      vln[1].callback([](Graph::Address,Graph::Address adr){
          Graph:: Canvas& p=Graph::reference_to<Graph::Canvas>(adr);
           //p.set_tool(Graph::get_line);
      p.move(-10,-10);
      },&scrl[0]);
      //vln.add(Graph::Button ({0,10},90,20,"hello2"));
      Graph::Layout& l=Graph::reference_to<Graph::Layout>(&ln[0]);

      Graph::Button& btn=Graph::reference_to<Graph::Button>(&ln[1]);

      btn.callback([](Graph::Address,Graph::Address adr){
          Graph:: Canvas& p=Graph::reference_to<Graph::Canvas>(adr);
    //  p.set_tool(new Graph::transform_tool(&p));
      },&scrl[0]);

      l[0].callback([](Graph::Address,Graph::Address adr){
            Graph:: Canvas& p=Graph::reference_to<Graph::Canvas>(adr);
    //    p.set_tool( Graph::get_line);
      p.set_tool(Graph::shape_type::sh_line_t);
        //p.move(-10,-10);
      },&scrl[0]);
      l[1].callback([](Graph::Address,Graph::Address adr){
            Graph:: Canvas& p=Graph::reference_to<Graph::Canvas>(adr);
    //    p.set_tool( Graph::get_polyline);
      p.set_tool(Graph::shape_type::sh_polyline_t);
         //p.move(-10,-10);
      },&scrl[0]);


      //Graph::reference_to<Graph::Layout>(&ln[0])[1].
       l[2].callback([](Graph::Address,Graph::Address adr){
        Graph:: Canvas& p=Graph::reference_to<Graph::Canvas>(adr);
        //p.move(10,10);
    //   p.set_tool(Graph::get_rectangle);
       p.set_tool(Graph::shape_type::sh_rectangle_t);
       //p.content().redraw();
       },&scrl[0]);

       l[3].callback([](Graph::Address,Graph::Address adr){
        Graph:: Canvas& p=Graph::reference_to<Graph::Canvas>(adr);
        //p.move(10,10);
  //     p.set_tool(Graph::get_polygon);
       p.set_tool(Graph::shape_type::sh_polygon_t);

       //p.content().redraw();
       },&scrl[0]);
       l[4].callback([](Graph::Address,Graph::Address adr){
        Graph:: Canvas& p=Graph::reference_to<Graph::Canvas>(adr);
        //p.move(10,10);
   //    p.set_tool(Graph::get_circle);
       p.set_tool(Graph::shape_type::sh_circle_t);
       //p.content().redraw();
       },&scrl[0]);




       return    Graph::gui_run();




}


void tst_rbtree()
{ using namespace Graph ;

    window win(Point {100,100},800,600,"test rbtree");
    Graph::Scroll scrl({230,70},550,500);
     win.attach(scrl);
     scrl.attach(Graph::Canvas  ({150,50},1000 ,1000));
Canvas &can= reference_to<Canvas>(&scrl[0]);

Point p1={10,10};
for(int i=0;i<10000;i++)
{
    can.add(new rectangle(p1,{p1.x()+20,p1.y()+30}));
    p1={p1.x()+22,p1.y()};
   if(i&& i%50==0)
      p1={10,p1.y()+50};
}
 can.set_tool(Graph::shape_type::sh_none_t);

int res= Graph::gui_run();
}



void show_area(area_t ar)
{
    switch (ar)
    {
    case LEFT:
        std::cout<<"left";
        break;
    case RIGHT:
        std::cout<<"right";
        break;
    case INTER:
        std::cout<<"inter";
        break;
    case ORIGIN:
        std::cout<<"ORIGIN";
        break;
    case DESTINATION:
        std::cout<<"Destination";
        break;
    case BEYOND:
        std::cout<<"Beyond";
        break;

    case BEHIND:
        std::cout<<"BEHIND";
        break;

    default:
        std::cout<<"none";
    }
    std::cout<<"\n";
}


