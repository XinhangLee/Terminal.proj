#include <stdio.h>

#include "Terminal-Tools/Terminal.h"

int main() {

    char output[10][51];
    char html[10005];

    Init(output);
    Input(html);

    Tender(html,output);

    Print(output);

    // printf("\033[31m\033[36mHello World\n");
    // printf("Hello C!\033[0m\n");
    // printf("end!");


    return 0;
}