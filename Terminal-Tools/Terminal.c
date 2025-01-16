//
// Created by lixh1 on 24-12-28.
//
#include "Terminal.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *ANSI[7] =
    {"\033[31m", "\033[32m", "\033[34m", "\033[1m", "\033[3m", "\033[4m", "\033[0m"};

void Init(char *output[], char *out[]) {
    for (int i = 0; i < HEIGHT; i++) {
        output[i] = (char *)malloc((WIDTH + 100) * sizeof(*output[i]));//防止有大量的转义符撑爆output。
        memset(output[i], ' ', WIDTH);
        memset(output[i] + WIDTH, '\0', 100);
        out[i] = output[i];
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
    if (elem->name == img) {
        elem->nature.nature_content.src_content[0] = '\0';
    } else {
        elem->nature.nature_content.nature_content[0] = 0;
        elem->nature.nature_content.nature_content[1] = 0;
        elem->nature.nature_content.nature_content[2] = 0;
        elem->nature.nature_content.nature_content[3] = 0;
    }
    if (elem->name == dive) {
        elem->content.child.children_number = 0;
    }
    elem->size.height[0] = 0;
    elem->size.height[1] = 0;
    elem->size.width[0] = 0;
    elem->size.width[1] = 0;
}

void Input(char html[]) {
    int i = 0;
    int c;
    while ((c = getchar()) != EOF) {
        if (c != '\n' && c != '\t' && c != '\r') {
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
int Strlen(const char *str) {
    int count = 0;
    while (str[count] != '<' && str[count] != '"' && str[count] != '>') {
        count++;
    }
    return count;
}
int str_to_int(char *str, const int len) {
    *(str + len) = '\0';
    return atoi(str);
}
char * Nature_check(char *html, Element *elem) {
    if (elem->name == img) {
        if (strncmp(html,"src",3) == 0) {
            elem->nature.have_or_not[src] = 1;
            html += 5;
            int len = Strlen(html);
            strncpy(elem->nature.nature_content.src_content, html, len);
            elem->nature.nature_content.src_content[len] = '\0';
            html += len + 1;//html -> " 下一位。
        }
        else if (strncmp(html,"width",5) == 0) {
            html += 7;
            int len = Strlen(html);
            elem->size.width[1] = str_to_int(html,len);
            html += len + 1;
        }
    }else {
        if (strncmp(html,"em",2) == 0) {
            elem->nature.have_or_not[em] = 1;
            html += 2;
        }
        else if (strncmp(html,"i",1) == 0) {
            elem->nature.have_or_not[i] = 1;
            html += 1;
        }
        else if (strncmp(html,"u",1) == 0) {
            elem->nature.have_or_not[u] = 1;
            html += 1;
        }
        else if (strncmp(html,"color",5) == 0) {
            elem->nature.have_or_not[color] = 1;
            html += 7;
            if (strncmp(html,"red",3) == 0) {
                elem->nature.nature_content.nature_content[color] = red;
                html += 4;
            }
            else if (strncmp(html,"green",5) == 0) {
                elem->nature.nature_content.nature_content[color] = green;
                html += 6;
            }
            else if (strncmp(html,"blue",4) == 0) {
                elem->nature.nature_content.nature_content[color] = blue;
                html += 5;
            }
        }
    }
    if (elem->name == dive) {
        if (strncmp(html,"direction",9) == 0) {
            html += 11;
            if (strncmp(html,"row",3) == 0) {
                elem->nature.nature_content.nature_content[direction] = row;
                html += 4;
            }
            else if (strncmp(html,"column",6) == 0) {
                elem->nature.nature_content.nature_content[direction] = column;
                html += 7;
            }
        }
        else if (strncmp(html,"align-items",11) == 0) {
            html += 13;
            if (strncmp(html,"start",5) == 0) {
                elem->nature.nature_content.nature_content[align_items] = start;
                html += 6;
            }
            else if (strncmp(html,"center",6) == 0) {
                elem->nature.nature_content.nature_content[align_items] = center;
                html += 7;
            }
            else if (strncmp(html,"end",3) == 0) {
                elem->nature.nature_content.nature_content[align_items] = end;
                html += 4;
            }
            else if (strncmp(html,"space-evenly",12) == 0) {
                elem->nature.nature_content.nature_content[align_items] = space_evenly;
                html += 13;
            }
        }
        else if (strncmp(html,"justify-content",15) == 0) {
            html += 17;
            if (strncmp(html,"start",5) == 0) {
                elem->nature.nature_content.nature_content[justify_content] = start;
                html += 6;
            }
            else if (strncmp(html,"center",6) == 0) {
                elem->nature.nature_content.nature_content[justify_content] = center;
                html += 7;
            }
            else if (strncmp(html,"end",3) == 0) {
                elem->nature.nature_content.nature_content[justify_content] = end;
                html += 4;
            }
            else if (strncmp(html,"space-evenly",12) == 0) {
                elem->nature.nature_content.nature_content[justify_content] = space_evenly;
                html += 13;
            }
        }
        else if (strncmp(html,"w",1) == 0) {
            html += 3;
            elem->size.width[0] = 1;
            int len = Strlen(html);
            elem->size.width[1] = str_to_int(html,len);
            html += len + 1;
        }
        else if (strncmp(html,"h",1) == 0) {
            html += 3;
            elem->size.height[0] = 1;
            int len = Strlen(html);
            elem->size.height[1] = str_to_int(html,len);
            html += len + 1;
        }
    }
    return html;
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
char * ANSIcode(const Nature *nature) {
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
int Blank_width(const Element *elem) {
    int width = 0;
    for (int j = 0; j < elem->content.child.children_number; j++) {
        width += elem->content.child.children[j]->size.width[1];
    }
    return elem->size.width[1] - width;
}
int Blank_height(const Element *elem) {
    int height = 0;
    for (int i = 0; i < elem->content.child.children_number; i++) {
        height += elem->content.child.children[i]->size.height[1];
    }
    return elem->size.height[1] - height;
}
void Row_J_Start(const Element *elem, char *output[], int *rows) {
    int r = *rows,  count = 0;
    while (count < elem->content.child.children_number) {
        if (elem->content.child.children[count]->name == h || elem->content.child.children[count]->name == p) {
            Handle_str(elem->content.child.children[count], output, &r, elem->content.child.children[count]->size.width[1]);
            output[*rows] += elem->size.width[1] - elem->content.child.children[count]->size.width[1];
            *rows = r;
        }
        else if (elem->content.child.children[count]->name == img) {
            Handle_img(elem->content.child.children[count], output, &r);
            while (*rows < r) {
                output[*rows] += elem->size.width[1] - elem->content.child.children[count]->size.width[1];
                *rows += 1;
            }
        }
        else if (elem->content.child.children[count]->name == dive){
            Handle_div(elem->content.child.children[count], output, &r);
            while (*rows < r) {
                output[*rows] += elem->size.width[1] - elem->content.child.children[count]->size.width[1];
                *rows += 1;
            }
        }
        count += 1;
        if (elem->nature.nature_content.nature_content[align_items] == space_evenly) {
            if (count != elem->content.child.children_number) {
                int height = Blank_height(elem);
                int temp = height / (elem->content.child.children_number + 1);
                while (temp--) {
                    output[*rows] += elem->size.width[1];
                    *rows += 1;
                    r++;
                }
            }
        }
    }
}
void Row_J_CenterAndEvenly(const Element *elem, char *output[], int *rows) {
    int r = *rows, count = 0;
    while (count < elem->content.child.children_number) {
        if (elem->content.child.children[count]->name == h || elem->content.child.children[count]->name == p) {
            output[r] += (elem->size.width[1] - elem->content.child.children[count]->size.width[1]) / 2;
            Handle_str(elem->content.child.children[count], output, &r, elem->content.child.children[count]->size.width[1]);
            output[*rows] += elem->size.width[1] - elem->content.child.children[count]->size.width[1] - (elem->size.width[1] - elem->content.child.children[count]->size.width[1]) / 2;
            *rows = r;
        }
        else if (elem->content.child.children[count]->name == img) {
            int r1 = r, h = elem->content.child.children[count]->size.height[1];
            while (h--) {
                output[r1++] += (elem->size.width[1] - elem->content.child.children[count]->size.width[1]) / 2;
            }
            Handle_img(elem->content.child.children[count], output, &r);
            while (*rows < r) {
                output[*rows] += elem->size.width[1] - elem->content.child.children[count]->size.width[1] - (elem->size.width[1] - elem->content.child.children[count]->size.width[1]) / 2;
                *rows += 1;
            }
        }
        else if (elem->content.child.children[count]->name == dive){
            int r1 = r, h = elem->content.child.children[count]->size.height[1];
            while (h--) {
                output[r1++] += (elem->size.width[1] - elem->content.child.children[count]->size.width[1]) / 2;
            }
            Handle_div(elem->content.child.children[count], output, &r);
            while (*rows < r) {
                output[*rows] += elem->size.width[1] - elem->content.child.children[count]->size.width[1] - (elem->size.width[1] - elem->content.child.children[count]->size.width[1]) / 2;
                *rows += 1;
            }
        }
        count += 1;
        if (elem->nature.nature_content.nature_content[align_items] == space_evenly) {
            if (count != elem->content.child.children_number) {
                int height = Blank_height(elem);
                int temp = height / (elem->content.child.children_number + 1);
                while (temp--) {
                    output[*rows] += elem->size.width[1];
                    *rows += 1;
                    r++;
                }
            }
        }
    }
}
void Row_J_End(const Element *elem, char *output[], int *rows) {
    int r = *rows, count = 0;
    while (count < elem->content.child.children_number) {
        if (elem->content.child.children[count]->name == h || elem->content.child.children[count]->name == p) {
            output[r] += elem->size.width[1] - elem->content.child.children[count]->size.width[1];
            Handle_str(elem->content.child.children[count], output, &r, elem->content.child.children[count]->size.width[1]);
            *rows = r;
        }
        else if (elem->content.child.children[count]->name == img) {
            int h = elem->content.child.children[count]->size.height[1];
            while (h--) {
                output[*rows] += elem->size.width[1] - elem->content.child.children[count]->size.width[1];
                *rows += 1;
            }
            Handle_img(elem->content.child.children[count], output, &r);
        }
        else if (elem->content.child.children[count]->name == dive) {
            int h = elem->content.child.children[count]->size.height[1];
            while (h--) {
                output[*rows] += elem->size.width[1] - elem->content.child.children[count]->size.width[1];
                *rows += 1;
            }
            Handle_div(elem->content.child.children[count], output, &r);
        }
        count += 1;
        if (elem->nature.nature_content.nature_content[align_items] == space_evenly) {
            if (count != elem->content.child.children_number) {
                int height = Blank_height(elem);
                int temp = height / (elem->content.child.children_number + 1);
                while (temp--) {
                    output[*rows] += elem->size.width[1];
                    *rows += 1;
                    r++;
                }
            }
        }
    }
}
void Row_J(const Element *elem, char *output[], int *rows) {
    if (elem->nature.nature_content.nature_content[justify_content] == start) {
        Row_J_Start(elem, output, rows);
    }
    else if (elem->nature.nature_content.nature_content[justify_content] == center
            || elem->nature.nature_content.nature_content[justify_content] == space_evenly) {
        Row_J_CenterAndEvenly(elem, output, rows);
    }
    else if (elem->nature.nature_content.nature_content[justify_content] == end) {
        Row_J_End(elem, output, rows);
    }
}
void Col_AI_Start(const Element *elem, char *output[], const int *rows) {
    int count = 0;
    while (count < elem->content.child.children_number) {
        int r = *rows;
        if (elem->content.child.children[count]->name == h || elem->content.child.children[count]->name == p) {
            Handle_str(elem->content.child.children[count], output, &r, elem->content.child.children[count]->size.width[1]);
        }
        else if (elem->content.child.children[count]->name == img) {
            Handle_img(elem->content.child.children[count], output, &r);
        }
        else if (elem->content.child.children[count]->name == dive){
            Handle_div(elem->content.child.children[count], output, &r);
        }
        int num = elem->size.height[1] - elem->content.child.children[count]->size.height[1];
        while (num--) {
            output[r] += elem->content.child.children[count]->size.width[1];
            r += 1;
        }
        count += 1;
        if (elem->nature.nature_content.nature_content[justify_content] == space_evenly)
            if (count != elem->content.child.children_number) {
                int rrr = *rows, temp = Blank_width(elem) / (elem->content.child.children_number + 1);
                int *h1 = malloc(sizeof(int));
                *h1 = elem->size.height[1];
                while ((*h1)--) {
                    output[rrr++] += temp;
                }
                free(h1);
            }
    }
}
void Col_AI_CenterAndEvenly(const Element *elem, char *output[], const int *rows) {
    int count = 0;
    while (count < elem->content.child.children_number) {
        int r = *rows, temp3 = (elem->size.height[1] - elem->content.child.children[count]->size.height[1]) / 2;
        while (temp3--) {
            output[r++] += elem->content.child.children[count]->size.width[1];
        }
        if (elem->content.child.children[count]->name == h || elem->content.child.children[count]->name == p) {
            Handle_str(elem->content.child.children[count], output, &r, elem->content.child.children[count]->size.width[1]);
        }
        else if (elem->content.child.children[count]->name == img) {
            Handle_img(elem->content.child.children[count], output, &r);
        }
        else if (elem->content.child.children[count]->name == dive){
            Handle_div(elem->content.child.children[count], output, &r);
        }
        int temp4 = elem->size.height[1] - elem->content.child.children[count]->size.height[1]
                    - (elem->size.height[1] - elem->content.child.children[count]->size.height[1]) / 2;
        while (temp4--) {
            output[r++] += elem->content.child.children[count]->size.width[1];
        }
        count += 1;
        if (elem->nature.nature_content.nature_content[justify_content] == space_evenly) {
            if (count != elem->content.child.children_number) {
                int rrr = *rows, temp = Blank_width(elem) / (elem->content.child.children_number + 1);
                int *h1 = malloc(sizeof(int));
                *h1 = elem->size.height[1];
                while ((*h1)--) {
                    output[rrr++] += temp;
                }
                free(h1);
            }
        }
    }
}
void Col_AI_End(const Element *elem, char *output[], const int *rows) {
    int count = 0;
    while (count < elem->content.child.children_number) {
        int r = *rows;
        int num = elem->size.height[1] - elem->content.child.children[count]->size.height[1];
        while (num--) {
            output[r++] += elem->content.child.children[count]->size.width[1];
        }
        if (elem->content.child.children[count]->name == h || elem->content.child.children[count]->name == p) {
            Handle_str(elem->content.child.children[count], output, &r, elem->content.child.children[count]->size.width[1]);
        }
        else if (elem->content.child.children[count]->name == img) {
            Handle_img(elem->content.child.children[count], output, &r);
        }
        else if (elem->content.child.children[count]->name == dive) {
            Handle_div(elem->content.child.children[count], output, &r);
        }
        count += 1;
        if (elem->nature.nature_content.nature_content[justify_content] == space_evenly) {
            if (count != elem->content.child.children_number) {
                int rrr = *rows, temp = Blank_width(elem) / (elem->content.child.children_number + 1);
                int *h1 = malloc(sizeof(int));
                *h1 = elem->size.height[1];
                while ((*h1)--) {
                    output[rrr++] += temp;
                }
                free(h1);
            }
        }
    }
}
void Handle_str(const Element *elem, char *output[],int *row, const int len) {
    char *temp = ANSIcode(&elem->nature);
    if (temp) {
        char *str = malloc((WIDTH + 50) * sizeof(*str));
        memset(str, '\0', WIDTH + 50);
        if (temp[0]) {
            strcat(str, temp);
            strcat(str, elem->content.str);
            strcat(str, ANSI[6]);
        } else {
            strcat(str, elem->content.str);
        }
        size_t lens = strlen(str);
        strcat(str, output[*row] + len);
        strcpy(output[*row], str);
        output[*row] = output[*row] + lens;
        (*row)++;
        free(temp);
        free(str);
    }
}
void Handle_img(const Element *elem, char *output[], int *row) {
    int count = elem->size.height[1];
    char *temp = elem->nature.nature_content.src_content;
    while (count--) {
        char *str = malloc(200 * sizeof(*str));
        memset(str, '\0', 200);
        strncpy(str, temp, elem->size.width[1]);
        strcat(str, output[*row] + elem->size.width[1]);
        strcpy(output[*row], str);
        output[*row] = output[*row] + elem->size.width[1];
        *row += 1;
        temp = temp + elem->size.width[1];
        free(str);
    }
}
void Handle_div(Element *elem, char *output[], int *rows) {
    if (elem->nature.nature_content.nature_content[direction] == row) {//方向：row
        if (elem->nature.nature_content.nature_content[align_items] == start) {//竖直：start  ->  right.
            int height = Blank_height(elem);
            Row_J(elem,output,rows);
            while (height--) {
                output[(*rows)++] += elem->size.width[1];
            }
        }
        else if (elem->nature.nature_content.nature_content[align_items] == center) {//竖直:center
            int height = Blank_height(elem);
            int temp = height / 2;
            while (temp--) {
                output[(*rows)++] += elem->size.width[1];
            }
            Row_J(elem,output,rows);
            int temp2 = height - height / 2;
            while (temp2--) {
                output[(*rows)++] += elem->size.width[1];
            }
        }
        else if (elem->nature.nature_content.nature_content[align_items] == end) {//竖直：end
            int height = Blank_height(elem);
            while (height--) {
                output[(*rows)++] += elem->size.width[1];
            }
            Row_J(elem,output,rows);
        }
        else if (elem->nature.nature_content.nature_content[align_items] == space_evenly) {//竖直：evenly
            int height = Blank_height(elem);
            int temp0 = height / (elem->content.child.children_number + 1);
            while (temp0--) {
                output[(*rows)++] += elem->size.width[1];
            }
            Row_J(elem,output,rows);
            int temp1 = height / (elem->content.child.children_number + 1);
            int temp2 = height - temp1 * elem->content.child.children_number;
            while (temp2--) {
                output[(*rows)++] += elem->size.width[1];
            }
        }
    }
    else if (elem->nature.nature_content.nature_content[direction] == column) {//方向：column
        if (elem->nature.nature_content.nature_content[align_items] == start) {//竖直：start
            if (elem->nature.nature_content.nature_content[justify_content] == start) {//水平：start
                int width = Blank_width(elem);
                Col_AI_Start(elem,output,rows);
                int *h1 = malloc(sizeof(*h1));
                *h1 = elem->size.height[1];
                while ((*h1)--) {
                    output[(*rows)++] += width;
                }
                free(h1);
            }
            else if (elem->nature.nature_content.nature_content[justify_content] == center) {//水平：center
                int width = Blank_width(elem);
                int temp = width / 2, rr = *rows;
                int *h1 = malloc(sizeof(int));
                *h1 = elem->size.height[1];
                while ((*h1)--) {
                    output[rr] += temp;
                    rr += 1;
                }
                free(h1);
                Col_AI_Start(elem,output,rows);
                h1 = malloc(sizeof(int));
                *h1 = elem->size.height[1];
                while ((*h1)--) {
                    output[(*rows)++] += width - temp;
                }
                free(h1);
            }
            else if (elem->nature.nature_content.nature_content[justify_content] == end) {
                int width = Blank_width(elem), rsv = *rows;
                int *h1 = malloc(sizeof(int));
                *h1 = elem->size.height[1];
                while ((*h1)--) {
                    output[(*rows)++] += width;
                }
                free(h1);
                Col_AI_Start(elem,output,&rsv);
            }
            else if (elem->nature.nature_content.nature_content[justify_content] == space_evenly) {
                int width = Blank_width(elem), rsv = *rows;
                int temp = width / (elem->content.child.children_number + 1);
                int rr = rsv;
                int *h1 = malloc(sizeof(int));
                *h1 = elem->size.height[1];
                while ((*h1)--) {
                    output[rr++] += temp;
                }
                free(h1);
                Col_AI_Start(elem,output,&rsv);
                h1 = malloc(sizeof(int));
                *h1 = elem->size.height[1];
                while ((*h1)--) {
                    output[(*rows)++] += width - temp * elem->content.child.children_number;
                }
                free(h1);
            }
        }
        else if (elem->nature.nature_content.nature_content[align_items] == center
                    || elem->nature.nature_content.nature_content[align_items] == space_evenly) {//竖直：center||evenly
            if (elem->nature.nature_content.nature_content[justify_content] == start) {//水平：start
                int width = Blank_width(elem);
                Col_AI_CenterAndEvenly(elem,output,rows);
                int *h1 = malloc(sizeof(int));
                *h1 = elem->size.height[1];
                while ((*h1)--) {
                    output[(*rows)++] += width;
                }
                free(h1);
            }
            else if (elem->nature.nature_content.nature_content[justify_content] == center) {//水平：center
                int width = Blank_width(elem);
                int temp = width / 2, rr = *rows;
                int *h1 = malloc(sizeof(int));
                *h1 = elem->size.height[1];
                while ((*h1)--) {
                    output[rr++] += temp;
                }
                free(h1);
                Col_AI_CenterAndEvenly(elem,output,rows);
                h1 = malloc(sizeof(int));
                *h1 = elem->size.height[1];
                while ((*h1)--) {
                    output[(*rows)++] += width - temp;
                }
                free(h1);
            }
            else if (elem->nature.nature_content.nature_content[justify_content] == end) {
                int width = Blank_width(elem), rsv = *rows;
                int *h1 = malloc(sizeof(int));
                *h1 = elem->size.height[1];
                while ((*h1)--) {
                    output[(*rows)++] += width;
                }
                free(h1);
                Col_AI_CenterAndEvenly(elem,output,&rsv);
            }
            else if (elem->nature.nature_content.nature_content[justify_content] == space_evenly) {
                int width = Blank_width(elem), rsv = *rows;
                int temp = width / (elem->content.child.children_number + 1);
                int rr = rsv;
                int *h1 = malloc(sizeof(int));
                *h1 = elem->size.height[1];
                while ((*h1)--) {
                    output[rr++] += temp;
                }
                free(h1);
                Col_AI_CenterAndEvenly(elem,output,&rsv);
                h1 = malloc(sizeof(int));
                *h1 = elem->size.height[1];
                while ((*h1)--) {
                    output[(*rows)++] += width - temp * elem->content.child.children_number;
                }
                free(h1);
            }
                    }
        else if (elem->nature.nature_content.nature_content[align_items] == end) {//竖直：end
            if (elem->nature.nature_content.nature_content[justify_content] == start) {//水平：start
                int width = Blank_width(elem);
                Col_AI_End(elem, output, rows);
                int *h1 = malloc(sizeof(int));
                *h1 = elem->size.height[1];
                while ((*h1)--) {
                    output[*rows] += width;
                    *rows += 1;
                }
                free(h1);
            }
            else if (elem->nature.nature_content.nature_content[justify_content] == center) {//水平：center
                int width = Blank_width(elem);
                int temp = width / 2, rr = *rows;
                int *h1 = malloc(sizeof(int));
                *h1 = elem->size.height[1];
                while ((*h1)--) {
                    output[rr++] += temp;
                }
                free(h1);
                Col_AI_End(elem, output, rows);
                h1 = malloc(sizeof(int));
                *h1 = elem->size.height[1];
                while ((*h1)--) {
                    output[(*rows)++] += width - temp;
                }
                free(h1);
            }
            else if (elem->nature.nature_content.nature_content[justify_content] == end) {
                int width = Blank_width(elem), rsv = *rows;
                int *h1 = malloc(sizeof(int));
                *h1 = elem->size.height[1];
                while ((*h1)--) {
                    output[(*rows)++] += width;
                }
                free(h1);
                Col_AI_End(elem, output, &rsv);
            }
            else if (elem->nature.nature_content.nature_content[justify_content] == space_evenly) {
                int width = Blank_width(elem), rsv = *rows;
                int temp = width / (elem->content.child.children_number + 1);
                int rr = rsv;
                int *h1 = malloc(sizeof(int));
                *h1 = elem->size.height[1];
                while ((*h1)--) {
                    output[rr++] += temp;
                }
                free(h1);
                Col_AI_End(elem, output, &rsv);
                h1 = malloc(sizeof(int));
                *h1 = elem->size.height[1];
                while ((*h1)--) {
                    output[(*rows)++] += width - temp * elem->content.child.children_number;
                }
                free(h1);
            }
        }
    }
}
char * Render_h (char *html, char *output[], int *row) {
    Element h;
    h.name = 1;
    Init_elem(&h);
    html += 2;
    html = Skip_blanks(html);
    while (*html != '>') {
        html = Nature_check(html,&h);
        html = Skip_blanks(html);
    }//现在html -> '>'.

    html +=1;//html -> 内容部分第一个字符。
    int len = Strlen(html);
    h.size.width[1] = len;
    h.size.height[1] = 1;
    strncpy(h.content.str,html,len);
    h.content.str[len] = '\0';
    Toupper(h.content.str);
    Handle_str(&h,output,row,len);
    html += len + 4;
    return html;
}
char * Render_p (char *html, char *output[], int *row) {
    Element p;
    p.name = 1;
    Init_elem(&p);
    html += 2;
    html = Skip_blanks(html);
    while (*html != '>') {
        html = Nature_check(html,&p);
        html = Skip_blanks(html);
    }//现在html -> '>'.

    html += 1;//html -> 内容部分第一个字符。
    int len = Strlen(html);
    p.size.width[1] = len;
    p.size.height[1] = 1;
    strncpy(p.content.str,html,len);
    p.content.str[len] = '\0';
    Handle_str(&p,output,row,len);
    html += len + 4;
    return html;
}
char * Render_img (char *html, char *output[], int *row) {
    Element img;
    img.name = 2;
    Init_elem(&img);
    html += 4;
    html = Skip_blanks(html);
    while (*html != '>') {
        html = Nature_check(html,&img);
        html = Skip_blanks(html);
    }//现在html -> '>'.

    int lens = (int)strlen(img.nature.nature_content.src_content);
    img.size.height[1] = lens / img.size.width[1];
    Handle_img(&img, output, row);
    html += 7;
    return html;
}
void Inherit(const Element *father, Element *child) {
    child->nature.have_or_not[color] = father->nature.have_or_not[color];
    child->nature.have_or_not[em] = father->nature.have_or_not[em];
    child->nature.have_or_not[i] = father->nature.have_or_not[i];
    child->nature.have_or_not[u] = father->nature.have_or_not[u];
    child->nature.nature_content.nature_content[color] = father->nature.nature_content.nature_content[color];
}
void Update(Element *father, const Element *child) {
    if (father->nature.nature_content.nature_content[direction] == column) {
        if (child->size.height[1] > father->size.height[1]) {
            father->size.height[1] = child->size.height[1];
        }
        if (father->size.width[0] == 0) {
            father->size.width[1] += child->size.width[1];
        }
    }
    else {
        if (child->size.width[1] > father->size.width[1]) {
            father->size.width[1] = child->size.width[1];
        }
        if (father->size.height[0] == 0) {
            father->size.height[1] += child->size.height[1];
        }
    }
}
void Free_Children(const Element *father) {
    for (int i = 0; i < father->content.child.children_number; i++) {
        if (father->content.child.children[i]->name == dive) {
            Free_Children(father->content.child.children[i]);
        }
        free(father->content.child.children[i]);
    }
}
char * Memory_child(Element *elem, char html[]) {
    if (elem->name == h || elem->name == p) {
        while (*html != '>') {
            html = Nature_check(html,elem);
            html = Skip_blanks(html);
        }//现在html -> '>'.

        html +=1;//html -> 内容部分第一个字符。
        int len = Strlen(html);
        elem->size.width[1] = len;
        elem->size.height[1] = 1;
        strncpy(elem->content.str,html,len);
        elem->content.str[len] = '\0';
        if (elem->name == h) {
            Toupper(elem->content.str);
        }
        html += len + 4;//html -> '<'
    }
    else if (elem->name == img) {
        while (*html != '>') {
            html = Nature_check(html,elem);
            html = Skip_blanks(html);
        }//现在html -> '>'.

        int lens = (int)strlen(elem->nature.nature_content.src_content);
        elem->size.height[1] = lens / elem->size.width[1];
        html += 7;
    }
    else if (elem->name == dive) {
        while (*html != '>') {
            html = Nature_check(html,elem);
            html = Skip_blanks(html);
        }//html -> '>'

        html += 1;
        html = Skip_blanks(html);
        while (strncmp(html,"</",2) != 0) {
            html = Skip_blanks(html);

            elem->content.child.children[elem->content.child.children_number] = malloc(sizeof(Element));
            if (strncmp(html,"<h",2) == 0) {
                elem->content.child.children[elem->content.child.children_number]->name = 0;
                html += 2;
            }
            else if (strncmp(html,"<p",2) == 0) {
                elem->content.child.children[elem->content.child.children_number]->name = 1;
                html += 2;
            }
            else if (strncmp(html,"<img",4) == 0) {
                elem->content.child.children[elem->content.child.children_number]->name = 2;
                html += 4;
            }
            else if (strncmp(html,"<div",4) == 0) {
                elem->content.child.children[elem->content.child.children_number]->name = 3;
                html += 4;
            }
            Init_elem(elem->content.child.children[elem->content.child.children_number]);
            //html -> 'name' 后一位的 ' '.
            Skip_blanks(html);
            Inherit(elem,elem->content.child.children[elem->content.child.children_number]);
            html = Memory_child(elem->content.child.children[elem->content.child.children_number], html);
            Update(elem,elem->content.child.children[elem->content.child.children_number]);
            elem->content.child.children_number += 1;
            html = Skip_blanks(html);
        }
        //html -> '<' from '</div>'
        html += 6;
    }
    return html;
}
char * Render_div (char *html, char *output[], int *row) {
    Element div;
    div.name = 3;
    Init_elem(&div);
    html += 4;
    html = Skip_blanks(html);
    while (*html != '>') {
        html = Nature_check(html,&div);
        html = Skip_blanks(html);
    }//html -> '>'

    html += 1;
    html = Skip_blanks(html);
    while (strncmp(html,"</",2) != 0) {
        html = Skip_blanks(html);

        div.content.child.children[div.content.child.children_number] = malloc(sizeof(Element));
        if (strncmp(html,"<h",2) == 0) {
            div.content.child.children[div.content.child.children_number]->name = 0;
            html += 2;
        }
        else if (strncmp(html,"<p",2) == 0) {
            div.content.child.children[div.content.child.children_number]->name = 1;
            html += 2;
        }
        else if (strncmp(html,"<img",4) == 0) {
            div.content.child.children[div.content.child.children_number]->name = 2;
            html += 4;
        }
        else if (strncmp(html,"<div",4) == 0) {
            div.content.child.children[div.content.child.children_number]->name = 3;
            html += 4;
        }
        Init_elem(div.content.child.children[div.content.child.children_number]);
        //html -> 'name' 后一位的 ' '.
        Skip_blanks(html);
        Inherit(&div,div.content.child.children[div.content.child.children_number]);
        html = Memory_child(div.content.child.children[div.content.child.children_number], html);
        Update(&div,div.content.child.children[div.content.child.children_number]);
        div.content.child.children_number += 1;
        html = Skip_blanks(html);
    }
    Handle_div(&div, output, row);
    Free_Children(&div);
    return html;
}
void Render(char *html, char *output[], int *row) {
    html = Skip_blanks(html);
    while (*html != '\0') {
        if (strncmp(html, "<h", 2) == 0) {
            html = Render_h(html, output, row);
        }
        else if (strncmp(html, "<p", 2) == 0) {
            html = Render_p(html, output, row);
        }
        else if (strncmp(html, "<img", 4) == 0) {
            html = Render_img(html, output, row);
        }
        else if (strncmp(html, "<div", 4) == 0) {
            html = Render_div(html, output, row);
            html += 6;
        }
        html = Skip_blanks(html);
    }
}

void Print(char *output[]) {
    for (int i = 0; i < HEIGHT; i++) {
        printf("%s", output[i]);
        printf("\n");
        free(output[i]);
    }
}

void Executive()
{
    char *output[HEIGHT], *out[HEIGHT];
    char html[10005];
    int row = 0;

    Init(output, out);
    Input(html);

    Render(html, output, &row);

    Print(out);
    fflush(stdout);
}
void Entrance()
{
    freopen("D:\\cpl\\filework\\browserinterminal\\Execution\\Entrance", "r", stdin);
    scanf("%d", &WIDTH);
    scanf("%d", &HEIGHT);
    Executive();
    freopen("CON", "r", stdin);
}
void Mode()
{
    freopen("D:\\cpl\\filework\\browserinterminal\\Execution\\Mode", "r", stdin);
    scanf("%d", &WIDTH);
    scanf("%d", &HEIGHT);
    Executive();
    freopen("CON", "r", stdin);
}
void Continue()
{
    freopen("D:\\cpl\\filework\\browserinterminal\\Execution\\Continue", "r", stdin);
    scanf("%d", &WIDTH);
    scanf("%d", &HEIGHT);
    Executive();
    freopen("CON", "r", stdin);
}