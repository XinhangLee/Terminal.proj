//
// Created by lixh1 on 24-12-28.
//

#ifndef TERMINAL_H
#define TERMINAL_H

extern int WIDTH;
extern int HEIGHT;
//structures

enum NAME{h,p,img,dive};
enum NATURE{color,direction,align_items,justify_content,src,em,i,u};//{0：颜色，1：方向，2：竖排，3：横排，4：画面内容，5：加粗，6：斜体，7：下划线}
enum COLOR{red,green,blue};
enum DIRECTION{row,column};//方向。
enum LAYOUT{start,center,end,space_evenly};//布局。
extern char *ANSI[7];
//红，绿，蓝，粗，斜，下，重置。

typedef struct elem Element;
typedef struct size Size;
typedef union nature_content Nature_content;
typedef struct nature Nature;
typedef struct children Children;
typedef union content Content;

struct size {
    int height[2];
    int width[2];//[0]:记录是否是定义好的：0:否，1:是    //[1]:记录数据
};

union nature_content {
    int nature_content[4];
    char src_content[505];
};

struct nature {
    int have_or_not[8];//对应8个属性，有的话存1，否则存0；
    Nature_content nature_content;
};

struct children {
    int children_number;
    Element *children[10];//this is an array which contains several points.
};

union content {
    char str[52];
    Children child;
};

struct elem {
    enum NAME name;
    Nature nature;
    Content content;
    Size size;
};


//functions


void Init(char *output[], char *out[]);
void Init_elem(Element *elem);

void Input(char html[]);

char * Skip_blanks(char * str);
int Strlen(const char *str);
int str_to_int(char *str, int len);
char * Nature_check(char *html, Element *elem);
void Toupper(const char *str);
char *ANSIcode(const Nature *nature);
int Blank_width(const Element *elem);
int Blank_height(const Element *elem);
void Handle_str(const Element *elem, char *output[], const int *row, int len);
void Handle_img(const Element *elem, char *output[], int *row);
void Handle_div(Element *elem, char *output[], int *row);
char * Render_h (char *html, char *output[], int *row);
char * Render_p (char *html, char *output[], int *row);
char * Render_img (char *html, char *output[], int *row);
void Inherit(const Element *father, Element *child);
void Update(Element *father, const Element *child);
char * Memory_child(Element *elem, char html[]);
char * Render_div (char *html, char *output[], int *row);
void Render(char *html, char *output[], int *row);

void Print(char *output[]);

void Executive();
void Entrance();
void Mode();
void Continue();
#endif //TERMINAL_H
