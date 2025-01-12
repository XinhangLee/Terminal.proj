#include "Terminal-Tools/Terminal.h"

int main() {

    char *output[HEIGHT], *out[HEIGHT];
    char html[10005];
    int row = 0;

    Init(output,out);
    Input(html);

    Render(html,output,&row);

    Print(out);
    // char str[17] = "\033[31mHello World!";
    // printf("\033[31m\033[36mHello World\n");
    // printf("Hello C!\033[0m\n");
    // printf("end!\n");
    // printf("%s",str);

    return 0;
}