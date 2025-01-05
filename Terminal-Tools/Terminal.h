//
// Created by lixh1 on 24-12-28.
//

#ifndef TERMINAL_H
#define TERMINAL_H

#define WIDTH 51
#define HEIGHT 10

//structures

enum NAME{h,p,img};
enum NATURE{color,em,i,u};
enum COLOR{red,green,blue};

typedef struct size {
    int height;
    int width;
} Size;

typedef struct information {
    enum NAME name;
    enum NATURE nature;
    enum COLOR color;
    Size size;
} Information;


//functions

void Init(char[HEIGHT][WIDTH]);

void Input(char[]);

void Tender(char[], char[HEIGHT][WIDTH]);



void Print(char[HEIGHT][WIDTH]);

#endif //TERMINAL_H
