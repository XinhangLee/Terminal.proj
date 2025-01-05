//
// Created by lixh1 on 24-12-28.
//
#include "Terminal.h"

#include <stdio.h>
#include <string.h>


void Init(char output[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        memset(output[i], ' ', WIDTH - 1);
        output[i][WIDTH - 1] = '\0';
    }
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


void Tender(char html[], char output[HEIGHT][WIDTH]) {

}


void Print(char output[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        printf("%s", output[i]);
        printf("\n");
    }
}