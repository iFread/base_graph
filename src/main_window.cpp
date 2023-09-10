 #include "main_window.h"
#include "modal_window.h"
#include "convert_form.h"
#include <fstream>
#include "m_heap.h"

namespace Graph
{
void cb_quit_win(Address ,Address adr)
{  window * win =&reference_to<window>(adr);
  win->hide();
  delete win;
 exit(0);
      }

//***********************File
File::File(const char* pth):path(pth)
{ // пытаемся открыть path, если не получается заменяем пустой строкой,
    // если получается заполняем list
  std::ifstream fin(path);
if(!fin)
{ std::cerr<<"can not open "<<path<<", create empty File object\n";
    path="";
    return;
 }
 list.clear();
 read_list(fin);


}

Shape* File::read(std::istream &is)
{
      unsigned char tp=0;
      size_t sz=0;
       is>>tp>>sz;
// то что считывается далее, зависит от типа

std::vector<Point> vec;
int x=0,y=0;
Shape *res=nullptr;
for(size_t i=0;i<sz;++i)
{
   is>>x>>y;
   vec.push_back(Point(x,y));
}


    switch (tp)
  {
        case '1':
                   // считать две точки
   res=new line(vec[0],vec[1]);
        break;


case '2':
           // считать
    res=new lines(vec[0]); // polyline
case '4':
   if(!res)
       res=new polygon(vec[0]);

for(size_t i=1;i<vec.size();++i)
  res->add(vec[i]);
           break;

    case '3':
res=new rectangle(vec[0],vec[2]);
        break;

       case '5':
{
   res=new circle(vec[0],vec[1].x()-vec[0].x()) ;
    }        
           break;
    case '6':

    res=new arc(vec[0],vec[2],vec[3]);
        break;

   case '7':
    { int a=std::abs(vec[0].x()-vec[1].x());
        int b=std::abs(vec[0].y()-vec[1].y());

        res =new ellipse(Point(vec[0].x()-a,vec[0].y()-b),vec[1]);
     }   break;
    default:
    res=nullptr;
    }
    return res;
 }



//****************==>File header и реализацию в  свой файла
//main_window


// открытие файла
 void main_window::open_file(const char* fl)
 {
     // добавить новый файл в stack_file
 curent_file.list.clear();
 curent_file.path=std::string(fl);
  std::ifstream fin(curent_file.path);
 if(!fin)
 {
  std::cerr<<"Cann't open file "<<path<<"\n"<<"Create empty File object\n";
   // возможно создание модального окна ошибка открытия файла
 path="";
  return;
 }
 curent_file.read_list(fin);
 fin.close();

can->update();
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

 // разложение файла на линии
    void main_window::convertion(const char* fl) // текущий path
    {
        File f(fl);
// пройти по списку и каждую фигуру разлогаем на линии
     // найти подстроку с именем файла
    size_t pos_beg=f.path.find_last_of('/')+1; // ищем послледнне вхождение символа '/', и точки
     size_t pos_end=f.path.find_first_of('.');
    // копировать подстроку
    std::string out_path=std::string(f.path.data()+pos_beg,f.path.data()+pos_end)+"_convert.txt";
 std::ofstream fout(out_path);
 if(!fout)
  {   std::cerr<<"cannot open file"<<out_path<<"\n";
     return;}
 // создаем файл для вывода данных

 using Point = command::Point ;

 //auto cmp= [](const Shape*sh,const Shape*s2){return sh->limit_x().x()<s2->limit_x().x();};
// using compare=cmp; ;
algo::comp cmp;
 algo::heap<Shape* ,algo::comp> hp;
 for(size_t i=0;i<f.list.size();++i)
    {
    //   Shape& sh= f.list[i];
 hp.insert(&f.list[i]);
//       Point  moveTo(sh[0].x(),sh[0].y(),100); // получаем первую точку,

//      // u_int8_t  buf[64]={0};
//       command::c_line ln(moveTo);

// std::cout<<"move To shape : "<<"("<<ln.nxt_point.x_<<", "<<ln.nxt_point.y_<<", "<<ln.nxt_point.z_<<")\n";
     // разложение фигуры на команды
     //   f.list[i].trace(std::cout);
       // f.list[i].trace(fout);


 }
 while(hp.size())
 {
   auto it=hp.extract();
   if(it)
   {
     convert_shape(fout, *(*it));
   }
 }
 std::cout<<"end\n";


//       convert_shape(fout,sh);




    }
// требует cmd_file.h
    void main_window::convert_shape(std::ostream& os,const Shape &sh)
    {
        using Point = command::Point;
    // для каждой вершины фигуры формируем c_line() или c_circle, или c_arc() для дуги
     // и записываем в файл
        for(int i=0;i<sh.size();++i)
        {

      int z=i==0?100:0;
            Point p(sh[i].x()*100,sh[i].y()*100,z);
            command::c_line cl(p);
     trace_cmd(os,cl);
             std::cout<<" next vertex : "<<"("<<cl.nxt_point.x_<<", "<<cl.nxt_point.y_<<", "<<cl.nxt_point.z_<<")\n";
             if((sh.type()==Shape::close_line||sh.get_shape_type()==shape_type::sh_rectangle_t)&& i==sh.size()-1)
              {
                command::c_line cz(Point(sh[0].x()*100,sh[0].y()*100));
               trace_cmd(os,cz);
                std::cout<<" last vertex : "<<"("<<cz.nxt_point.x_<<", "<<cz.nxt_point.y_<<", "<<cz.nxt_point.z_<<")\n";
                  }
        }
    }

    void main_window::trace_cmd(std::ostream &s,const command::cmd&c)
    {
        using command::cmd ;
    s<<c.type()<<" ";
    switch (c.type_)
    {
     case cmd::cfg_cmd:
     {
     const command::cfg_param &prm=reinterpret_cast<const command::cfg_param&>(c);
       s<<prm.max_x<<" "<<prm.max_y<<"\n";
     }
        break;
     case cmd::line_cmd:
{ const command::c_line &ln=reinterpret_cast<const command::c_line&>(c);
        s<<ln.nxt_point.x_<<" "<<ln.nxt_point.y_<<" "<<ln.nxt_point.z_<<"\n";

    }
        break;
     case cmd::circle_cmd:
{ const command::c_circle &cr=reinterpret_cast<const command::c_circle&>(c);
       s<<cr.c_.x_<<" "<<cr.c_.y_<<" "<<cr.c_.z_<<" "<<cr.r_<<"\n";

    }
        break;
    default:

        break;
    }
    }

// callbacks
 void main_window::cb_save_file(Address, Address a)
 {
   main_window& w=reference_to<main_window>(a);
    if(!w.curent_file.path.empty())
      w.save_file(w.curent_file.path.c_str());
  }



 void main_window:: cb_save_new_file(Address, Address adr)
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

void main_window::cb_open_win(Address, Address us)
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


void main_window::cb_convertion(Address,Address a)
{
   main_window& w=reference_to<main_window>(a);

   base_convert cvrt({200,200},800,600);

   while(cvrt.shown())
   {
     Fl::wait();
   }
   if(!w.curent_file.path.empty())
    w.convertion(w.curent_file.path.c_str());
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
 //
 create_panel(Point(20,150),(*scrl)[0]);

  static_cast<Canvas*>(&(*scrl)[0])->set_file(&curent_file);
 //curent_file.list.push_back(new ellipse({100,100},{250,120}));
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

 panels->attach(Button(Point(10,10),70,20,"arc"));
 (*panels)[panels->size()-1].callback([](Address,Address a){reference_to<Canvas>(a).set_tool(shape_type::sh_arc_t);},&w);

 panels->attach(Button(Point(10,10),70,20,"ellipse"));
 (*panels)[panels->size()-1].callback([](Address,Address a){reference_to<Canvas>(a).set_tool(shape_type::sh_ellipse_t);},&w);

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
     m->add(item("open",&main_window::cb_open_win,this),"file");
     m->add(item("save",&main_window::cb_save_file,this),"file");
     m->add(item("save as",&main_window::cb_save_new_file,this),"file");
     m->add(item("quit", cb_quit_win,this),"file");


     m->add(item("shapes"),"tools");

     m->add(item("line"),"tools/shapes");
     m->add(item("lines"),"tools/shapes");
     m->add(item("rectangle"),"tools/shapes");
     m->add(item("polygon"),"tools/shapes");
     m->add(item("circle"),"tools/shapes");

       m->add(item("convert",&main_window::cb_convertion,this),"tools");

     m->add(item("about"),"help");
     m->add(item("contacts"),"help");
  } catch(std::exception& e)
  {
   std::cerr<<e.what()<<"\n";
 }
 return m;
}

}

