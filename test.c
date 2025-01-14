#include <stdio.h>
#include "Terminal-Tools/Terminal.h"

int WIDTH, HEIGHT;

int main() {
    Entrance();
    printf("                  Your Choice:  ");
    fflush(stdout);
    int choice = 0;
    scanf("%d", &choice);
    while (choice == 1) {
        int mode = 0;
        Mode();
        printf("                  Enter Mode:  ");
        scanf("%d", &mode);
        printf("\n");
        if (mode == 1) {
            printf("                 Enter Width:  ");
            scanf("%d", &WIDTH);
            printf("\n");
            printf("                 Enter Height:  ");
            scanf("%d", &HEIGHT);
            printf("\n");
            printf("Please Enter Your Code Here:");
            printf("(Remember to tap 'Enter'->'Ctrl'+'Z'->'Enter' to EOF.)\n");
            Executive();

        }
        else if (mode == 2) {
            printf("Please enter the width of the window you expected:  ");
            scanf("%d", &WIDTH);
            printf("\n");
            printf("Please enter the height of the window you expected:  ");
            scanf("%d", &HEIGHT);
            printf("\n");
            char inputPath[256];
            printf("Please create a file which contains your input of orders.\n"
            "Please enter the path to the source file:\n"
            "Your input may like this:\n"
            "D:\\cpl\\filework\\browserinterminal\\cases\\heart.in\n");
            scanf("%s", inputPath);
            freopen(inputPath, "r",stdin);
            Executive();
            freopen("CON", "r", stdin);
        }
        Continue();
        printf("           Please Enter Your Choice:  ");
        scanf("%d", &choice);
        printf("\n");
    }


    // system("pause");
    return 0;
}

