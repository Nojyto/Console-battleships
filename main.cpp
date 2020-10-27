#include <stdio.h>
#include <algorithm>
#include <time.h>

char playerMap[10][10], computerMap[10][10];

void generateComputerMap()
{
    srand(time(NULL));

    for(int i = 5; i > 0; i--){
        start:
        char pos;
        int x = rand() % 9, y = rand() % 9;

        rand() % 2 ? pos = 'h' : pos = 'v';

        if(x + i > 9 || y + i > 9 || computerMap[y][x] == 'O') goto start;

        switch (pos){
            case 'h':
                for(int j = 0; j < i; j++){
                    if(computerMap[y][x] == 'O')
                        goto start;
                    y++;
                }
                for(int j = 0; j < i; j++){
                    computerMap[y][x] = 'O';
                    y--;
                }
                break;
            case 'v':
                for(int j = 0; j < i; j++){
                    if(computerMap[y][x] == 'O')
                        goto start;
                    x++;
                }
                for(int j = 0; j < i; j++){
                    computerMap[y][x] = 'O';
                    x--;
                }
                break;
            default:
                goto start;
        }
    }
}

void getInput()
{
    char pos;
    int x, y;

    for(int i = 5; i > 0; i--){
        start:
        system("cls");
        printf("  ");
        for(int i = 0; i < 10; i++)
            printf("%i ", i);

        for(int i = 0; i < 10; i++){
            printf("\n%i ", i);
            for(int j = 0; j < 10; j++){
                printf("%c ", playerMap[i][j]);
            }
        }

        printf("\nPlace your %i ship (h/v, x, y): ", i);
        scanf("%c %i %i", &pos, &x, &y);

        if((pos != 'h' && pos != 'v') || x > 9 || x < 0 || x + i > 9 || y > 9 || y < 0 || y + i > 9 )
            goto start;

        if(pos == 'h'){
            for(int j = 0; j < i; j++){
                playerMap[y][x] = 'O';
                y++;
            }
        }
        if(pos == 'v'){
            for(int j = 0; j < i; j++){
                playerMap[y][x] = 'O';
                x++;
            }
        }
    }

}

void printScreen()
{
    system("cls");

    printf("  ");
    for(int i = 0; i < 10; i++)
        printf("%i ", i);

    for(int i = 0; i < 10; i++){
        printf("\n%i ", i);
        for(int j = 0; j < 10; j++){
            if(computerMap[i][j] == 'X' || computerMap[i][j] == '*')
                printf("%c ", computerMap[i][j]);
            else
                printf("  ");
        }
    }

    printf("\n\n  ");
    for(int i = 0; i < 10; i++)
        printf("%i ", i);

    for(int i = 0; i < 10; i++){
        printf("\n%i ", i);
        for(int j = 0; j < 10; j++){
            printf("%c ", playerMap[i][j]);
        }
    }
}

int main()
{
    int x, y;

    getInput();
    generateComputerMap();

    while(true){
        for(int i = 0; i < 10; i++)
            for(int j = 0; j < 10; j++)
                if(playerMap[i][j] == 'O')
                    goto playerStart;
        goto GameOver;

        playerStart:
        printScreen();
        printf("\n\nInput coordinates: ");
        scanf("%i%i", &x, &y);

        switch(computerMap[y][x]){
            case 'O':
                computerMap[y][x] = 'X';
                goto playerStart;
            case 'X': case '*':
                goto playerStart;
            default:
                computerMap[y][x] = '*';
        }

        for(int i = 0; i < 10; i++)
            for(int j = 0; j < 10; j++)
                if(computerMap[i][j] == 'O')
                    goto computerStart;
        goto GameOver;

        computerStart:
        printScreen();

        x = rand() % 9;
        y = rand() % 9;

        switch(playerMap[y][x]){
            case 'O':
                playerMap[y][x] = 'X';
                goto computerStart;
            case 'X': case '*':
                goto computerStart;
            default:
                playerMap[y][x] = '*';
        }

    }

    GameOver:

    printf("\nGame Over.\n");
}
