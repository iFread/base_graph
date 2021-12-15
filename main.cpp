
#include <iostream>
//#include "Graph.h"
#include <Fl/Fl_Window.H>
//#include "window.h"
#include <exception>
#include "base_gui.h"
#include <vector>
#include "base_data.h"
#include "my_timer.h"

//#include <gtk/gtk.h>

//using namespace:: Graph_lib;
//int main(int argv, char * argc[])
//{
//try{
//   // Fl_Window window(640,480,"Test");
//_Window win(640,480,"Test");

//  // line ln1(point(110,10),point (210,310));
//   // line ln2(point (210,310),point (255,155));
//   // line ln3(point(255,155),point(110,10));
//    //ln1.draw();
// lines grd;
//// lns.add_line(point(110,10),point(210,310));
////lns.add_line(point(210,310),point (255,155));
// // win.attach(ln1);
// int x_size=win.x_max();
//int y_size=win.y_max();
//int x_grid=80;
//int y_grid=40;
//int count=0;
//for(int xx=x_grid;xx<x_size;xx+=x_grid)
//{
//  grd.add_line(point(xx,0),point(xx,y_size));
////win.attach(grd[count]);
////count++;
//}
// //win.attach(grd);
//// lines grd2;
//for(int y=y_grid;y<y_size;y+=y_grid)
//{
//  grd.add_line(point(0,y),point(x_size,y));
//}

// win.attach(grd);
//  win.show();


//    return  gui_main();
//   }
//    catch(std::exception &ex)
//        {
//        return 1;
//        }
//}
int two_lines();
void lines_use();
void test_axis();


void test_line();
void test_timer();
void test_poli();
void test_flrect();

int main(int argv,char* argc[])
{

  // Fl_Window win(640,480,"Test2");
//std::vector<Line*> vec;

//int w=80;
//int h=40;
// for(int i=0;i<640;i+=w)
// {
//   vec.push_back(new Line(Point(i,0),Point(i,480)));
// }
//win.end();
// for(int i=0;i<480;i+=h)
// {
//     vec.push_back( new Line(Point(0,i),Point(640,i)));
// }
//   Line ln(Point(10,10),Point(win.w(),win.h()));

// ln.draw();
//two_lines();
 //win.show();
// return  Fl::run();
//lines_use();
 //test_axis();
  //  std::cout<<"Hello_World\n";
 // test_line();
   //test_poli();
   test_flrect();
    return 0;
}
void test_flrect()
{
    Fl_Window win(640,480,"Test rectangle");
Point<int> x(100,100);
    Rectangle rect(x,100,100);


    win.show();
  Fl::run();

}

void test_poli()
{ Fl_Window win(600,400,"Use_lines");
    Point<int> x(100,100);
Point<int> y(200,200);
Point<int> z(100,300);
Pologon plg;
plg.add(x);
plg.add(y);
plg.add(z);

plg.add(Point<int>(50,150));

win.show();
Fl::run();
}


void test_timer()
{


}

void test_line()
{
 int a;

 a= std::rand()%100+1;
int fa=100.,fb=50.;


std::vector<line_t> vec;
my_timer t1;
for(int i=0;i<10000;i++)
{
   a= std::rand()%200+1;
fa=fa+a/a;
fb=fb-a/a;
vec.push_back(line_t(point_t{(float)fa-fb,(float)fb+fa},point_t{float(fa-fb),float(fb-fa)}));

}
std::cout<<t1.elapsed()<<std::endl;
    line_t ln(point_t{1,1},point_t{4,3});
ln.print();
}

void test_axis()
{
   Fl_Window win(600,400,"Test Axis");

   Point<int> x(40,370);
  Axis ax(x,500,5);
  ax.set_color(Color::red);
 // ax.change_point(2,Point(100,100));
 // ax.set_style(Line_style(Line_style::dot ));
// ax.change_line(3);
 ax.change_line(10);

 Lines op1(Lines::OneLines,{100,100},{150,202});
 op1.add_point({250,250},{300,250});
 op1.set_style(Line_style::dashdot);
  win.show();

  Fl::run();

}

void lines_use()
{
    Fl_Window win(600,400,"Use_lines");
Point<int> x(100,100);
  Lines lns(Lines::ClosedLines,x,{200,100});
  lns.add_point({150,150},{50,150});//Point(150,150),Point(50,150));
 lns.set_color(Color::dark_yellow);
 win.show();
Fl::run();
}


int two_lines()
{
  Fl_Window win(600,400,"Two lines");
   Point<int> x(100,100);
 //Line horisontal;//(x,Point(200,100));
 //horisontal.setLine(x,Point(200,100));
 //Line vertical(Point(150,50),Point(150,150));
 Lines lns(Lines::OneLines,x,Point<int>(200,200));
 lns.add_point(Point<int>(150 ,150));
   win.show();
return Fl::run();
}


/*


Line oneLine;
oneLine.setLine(Point(20,2),Point(200,400));
Lines lns1;
for(int i=w;i<640;i+=w)
{
   lns1.add_point(Point(i,0),Point(i,480));
}
for(int i=h;i<480;i+=h)
{
  lns1.add_point(Point(0,i),Point(640,i));
}
lns1.set_style(Line_style::dot);
Lines lns(Lines::PolyLines);
lns.add_point(Point(100,100),Point(200,10));
lns.set_color(Color::blue);
lns.add_point(Point(300,100),Point(210,300));
lns.add_point(Point(210,300));
lns.add_point(Point(0,0),Point(640,480));

*/
