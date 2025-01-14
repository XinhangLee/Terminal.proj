#include <stdio.h>

#include "Terminal-Tools/Terminal.h"

int WIDTH, HEIGHT;

int main() {
    printf("Please enter the width of the window you expected:\n");
    scanf("%d", &WIDTH);
    printf("Please enter the height of the window you expected:\n");
    scanf("%d", &HEIGHT);
    char inputPath[256];
    printf("Please create a file which contains your input of orders.\n"
            "Please enter the path to the source file:\n"
            "Your input may like this:\n"
            "D:\\cpl\\filework\\browserinterminal\\cases\\heart.in\n");
    scanf("%s", inputPath);
    freopen(inputPath, "r", stdin);

    char *output[HEIGHT], *out[HEIGHT];
    char html[10005];
    int row = 0;

    Init(output,out);
    Input(html);

    Render(html,output,&row);

    Print(out);

    fclose(stdin);
    return 0;
}