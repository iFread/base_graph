#ifndef GUI_ATTRIBUTES_H
#define GUI_ATTRIBUTES_H
// определяет общие атрибуты для программы :
// Цвет, тип линий, характеристики текста и шрифты
// возможно продолжить
#include <stdint.h>
 #include <FL/fl_draw.H>
//#include <Fl/Fl.H>
//#include <Fl/Fl_Window.H>


namespace Graph
{



enum orientation:uint8_t {vertical, horisontal};



struct Color {
    enum Color_type :uint  {
        red=FL_RED, blue=FL_BLUE, green=FL_GREEN,
        yellow=FL_YELLOW, white=FL_WHITE, black=FL_BLACK,
        magenta=FL_MAGENTA, cyan=FL_CYAN, grey=FL_GRAY0,dark_red=FL_DARK_RED,
        dark_green=FL_DARK_GREEN, dark_yellow=FL_DARK_YELLOW, dark_blue=FL_DARK_BLUE,
        dark_magenta=FL_DARK_MAGENTA, dark_cyan=FL_DARK_CYAN,
    };
    enum Transparency:uint8_t { invisible = 0, visible=255 };

    Color(Color_type cc) :c(Fl_Color(cc)), v(visible) { }
    Color(Color_type cc, Transparency vv) :c(Fl_Color(cc)), v(vv) { }
    Color(int cc) :c(Fl_Color(cc)), v(visible) { }
    Color(Transparency vv) :c(Fl_Color()), v(vv) { }

    int as_int() const { return c; }
    char visibility() const { return v; }
    void set_visibility(Transparency vv) { v=vv; }
private:
 Fl_Color c;
 unsigned char v;	// 0 or 1 for now
};


struct Line_style {
    enum Line_style_type:uint8_t {
        solid=FL_SOLID,      //_______
        dash=FL_DASH,       // - - - -
        dot=FL_DOT,         // .......
        dashdot=FL_DASHDOT,			// - . - .
        dashdotdot=FL_DASHDOTDOT,	// -..-..
    };
    Line_style(Line_style_type ss) :s(ss), w(0) { }
    Line_style(Line_style_type lst, int ww) :s(lst), w(ww) { }
    Line_style(int ss) :s(ss), w(0) { }

    int width() const { return w; }
    int style() const { return s; }
    void set_vertex(bool vert){v=vert;}
    bool vertex_visible()const {return v;}
private:
    char s;
    int w;
    bool v{false}; // отображает верщины
};

struct Vertex_style{
private:
    Color c;
  uint8_t sz;
public:
  Vertex_style(Color col=Fl_Color(),uint8_t o=3):c(col),sz(o){}
 // Vertex_style(Color col):c(col),r(1){}
  int v_r() const {return sz;}
 int v_color() const {return c.as_int();}
 void set_vertex_style(Color cl, int s=3){c=cl;sz=s;}
};

class Font {
public:
    enum Font_type:uint8_t {
        helvetica=FL_HELVETICA,
        helvetica_bold=FL_HELVETICA_BOLD,
        helvetica_italic=FL_HELVETICA_ITALIC,
        helvetica_bold_italic=FL_HELVETICA_BOLD_ITALIC,
        courier=FL_COURIER,
        courier_bold=FL_COURIER_BOLD,
        courier_italic=FL_COURIER_ITALIC,
        courier_bold_italic=FL_COURIER_BOLD_ITALIC,
        times=FL_TIMES,
        times_bold=FL_TIMES_BOLD,
        times_italic=FL_TIMES_ITALIC,
        times_bold_italic=FL_TIMES_BOLD_ITALIC,
        symbol=FL_SYMBOL,
        screen=FL_SCREEN,
        screen_bold=FL_SCREEN_BOLD,
        zapf_dingbats=FL_ZAPF_DINGBATS
    };

    Font(Font_type ff) :f(ff) { }
    Font(int ff) :f(ff) { }

    int as_int() const { return f; }
private:
    int f;
};

}

#endif // GUI_ATTRIBUTES_H
