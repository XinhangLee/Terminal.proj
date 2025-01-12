//
// Created by lixh1 on 24-12-28.
//

#ifndef TERMINAL_H
#define TERMINAL_H

#define WIDTH 50
#define HEIGHT 10
//structures

enum NAME{h,p,img,dive};
enum NATURE{color,direction,align_items,justify_content,src,em,i,u};//{0：颜色，1：方向，2：横排，3：竖排，4：画面内容，5：加粗，6：斜体，7：下划线}
enum COLOR{red,green,blue};
enum DIRECTION{row,column};//方向。
enum LAYOUT{start,center,end,space_evenly};//布局。
extern char *ANSI[7];
//红，蓝，绿，粗，斜，下，重置。

typedef struct size {
    int height;
    int width;
} Size;

typedef union nature_content {
    int nature_content[4];
    char src_content[200];
} Nature_content;

typedef struct nature {
    int have_or_not[8];//对应8个属性，有的话存1，否则存0；
    Nature_content nature_content;
} Nature;

typedef union content {
    char str[52];
    struct elem *children[10];//this is an array which contains several points.
} Content;

typedef struct elem {
    enum NAME name;
    Nature nature;
    Content content;
    Size size;
} Element;


//functions


void Init(char *output[HEIGHT]);
void Init_elem(Element *elem);

void Input(char html[]);

char * Skip_blanks(char * str);
char * Nature_check(char *html, Nature *nature);
int Strlen(const char *str);
void Toupper(char *str);
char *ANSIcode(const Nature *nature);
void HandleIt(const Element *elem, char *output[HEIGHT], const int *row, int len);
char * Render_h (char *html, char *output[HEIGHT], const int *row);
char * Render_p (char *html, char *output[HEIGHT], int *row);
char * Render_img (char *html, char *output[HEIGHT], int *row);
char * Render_div (char *html, char *output[HEIGHT], int *row);
void Render(char *html, char *output[HEIGHT], int *row);

void Print(char *output[HEIGHT]);

#endif //TERMINAL_H
