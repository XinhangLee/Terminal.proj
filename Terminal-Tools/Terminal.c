//
// Created by lixh1 on 24-12-28.
//
#include "Terminal.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <stdlib.h>

char *ANSI[7] =
    {"\033[31m","\033[34m","\033[32m","\033[1m","\033[3m","\033[4m","\033[0m"};

void Init(char *output[HEIGHT]) {
    for (int i = 0; i < HEIGHT; i++) {
        output[i] = (char *)malloc(100 * sizeof(*output[i]));
        memset(output[i], ' ', WIDTH);
        output[i][WIDTH] = '\0';
    }
}
void Init_elem(Element *elem) {
    elem->content.str[0] = '\0';
    elem->nature.have_or_not[0] = 0;
    elem->nature.have_or_not[1] = 1;
    elem->nature.have_or_not[2] = 1;
    elem->nature.have_or_not[3] = 1;
    elem->nature.have_or_not[4] = 0;
    elem->nature.have_or_not[5] = 0;
    elem->nature.have_or_not[6] = 0;
    elem->nature.have_or_not[7] = 0;
    elem->nature.nature_content.src_content[0] = '\0';
    elem->size.height = 0;
    elem->size.width = 0;
}

void Input(char html[]) {
    int i = 0;
    int c;
    while ((c = getchar()) != EOF) {
        if (c != '\n') {
            html[i++] = (char)c;
        }
    }
    html[i] = '\0';
}

char * Skip_blanks(char * str) {
    while (*str == ' ') {
        str++;
    }
    return str;
}
char * Nature_check(char *html, Nature *nature) {
    if (strncmp(html,"em",2) == 0) {
        nature->have_or_not[em] = 1;
        html += 2;
    }
    else if (strncmp(html,"i",1) == 0) {
        nature->have_or_not[i] = 1;
        html += 1;
    }
    else if (strncmp(html,"u",1) == 0) {
        nature->have_or_not[u] = 1;
        html += 1;
    }
    else if (strncmp(html,"color",5) == 0) {
        nature->have_or_not[color] = 1;
        html += 7;
        if (strncmp(html,"red",3) == 0) {
            nature->nature_content.nature_content[color] = red;
            html += 4;
        }
        else if (strncmp(html,"green",5) == 0) {
            nature->nature_content.nature_content[color] = green;
            html += 6;
        }
        else if (strncmp(html,"blue",4) == 0) {
            nature->nature_content.nature_content[color] = blue;
            html += 5;
        }
    }
    return html;
}
int Strlen(const char *str) {
    int count = 0;
    while (str[count] != '<') {
        count++;
    }
    return count;
}
void Toupper(char *html) {
    char *str = html;
    while (*str) {
        if (*str >= 'a' && *str <= 'z') {
            *str = (char)toupper(*str);
        }
        str++;
    }
}
char *ANSIcode(const Nature *nature) {
    char *result = calloc(20, sizeof(*result));
    if (result == NULL) {
        return NULL;
    }
    result[0] = '\0';
    if (nature->have_or_not[color]) {
        strcat(result, ANSI[nature->nature_content.nature_content[color]]);
    }
    if (nature->have_or_not[em]) {
        strcat(result, ANSI[3]);
    }
    if (nature->have_or_not[i]) {
        strcat(result, ANSI[4]);
    }
    if (nature->have_or_not[u]) {
        strcat(result, ANSI[5]);
    }
    return result;
}
void HandleIt(const Element *elem, char *output[HEIGHT], const int *row, const int len) {
    char *temp = ANSIcode(&elem->nature);
    if (temp) {
        output[*row][0] = '\0';
        strcat(output[*row], temp);
        strcat(output[*row], elem->content.str);
        strcat(output[*row], ANSI[6]);
        strcat(output[*row], output[i] + len);
        free(temp);
    }
    *row++;
}
char * Render_h (char *html, char *output[HEIGHT], const int *row) {
    Element h;
    Init_elem(&h);
    h.name = 0;
    html = html + 2;
    html = Skip_blanks(html);
    while (*html != '>') {
        html = Nature_check(html,&h.nature);
        html = Skip_blanks(html);
    }//现在html -> '>'.

    html +=1;//html -> 内容部分第一个字符。
    int len = Strlen(html);
    strncpy(h.content.str,html,len);
    h.content.str[len] = '\0';
    Toupper(h.content.str);
    HandleIt(&h,output,row,len);
    html += len + 4;
    return html;
}
char * Render_p (char *html, char *output[HEIGHT], int *row) {

}
char * Render_img (char *html, char *output[HEIGHT], int *row) {

}
char * Render_div (char *html, char *output[HEIGHT], int *row) {

}
void Render(char *html, char *output[HEIGHT], int *row) {
    while (*html != '\0') {
        if (strncmp(html, "<h", 2) == 0) {
            html = Render_h(html, output, row);
        }
        else if (strncmp(html, "<p", 2) == 0) {
            html = Render_p(html, output, row);
        }
        else if (strncmp(html, "<i", 2) == 0) {
            html = Render_img(html, output, row);
        }
        else if (strncmp(html, "<d", 2) == 0) {
            html = Render_div(html, output, row);
        }
    }
}



void Print(char *output[HEIGHT]) {
    for (int i = 0; i < HEIGHT; i++) {
        printf("%s", output[i]);
        printf("\n");
        free(output[i]);
    }
}