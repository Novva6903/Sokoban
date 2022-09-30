#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

void printMenu(){
    puts("   _aaaaaaaa  _aaaaaa_     _a   _a_  _aaaaaa_  >aaaaaaaaa_     _aaaaaaaa aaa____");
    puts("  aaa    aaa aaa    aaa   aaa _aaa> aaa    aaa   aaa    aaa   aaa    aaa aaa>>>aa_");
    puts("  aaa    a>  aaa    aaa   aaaaaa>   aaa    aaa   aaa    aaa   aaa    aaa aaa   aaa");
    puts("  aaa        aaa    aaa  _aaaaa>    aaa    aaa  _aaa___aa>    aaa    aaa aaa   aaa");
    puts(">aaaaaaaaaaa aaa    aaa >>aaaaa_    aaa    aaa >>aaa>>>aa_  >aaaaaaaaaaa aaa   aaa");
    puts("         aaa aaa    aaa   aaaaaa_   aaa    aaa   aaa    aa_   aaa    aaa aaa   aaa");
    puts("   _a    aaa aaa    aaa   aaa >aaa_ aaa    aaa   aaa    aaa   aaa    aaa aaa   aaa");
    puts("_aaaaaaaa>   >aaaaaa>    aaa   >a>  >aaaaaa>  _aaaaaaaaa>    aaa    a>   >a   a>");
    puts("                          >");
    puts("");
    puts("1. Game");
    puts("2. View Score");
    puts("0. Exit");
    printf(">> ");
}

void pressEnter(){
    char enter[500];
    scanf("%[^\n]", enter); getchar();
}

int startX, startY;
int goals;
int goalX[3], goalY[3];
char map[10][9];
char map2[10][9];
bool sekip = false;

int move;
char input;
int currY, currX;
char inputName[101];

void readMap(int pilih){
    FILE *fp;
    switch (pilih){
        case 1:
            fp = fopen("map1.txt", "r");
            break;
        case 2:
            fp = fopen("map2.txt", "r");
            break;
        case 3:
            fp = fopen("map3.txt", "r");
            break;
        
        default:
            break;
    }
    fscanf(fp, "%d %d\n%d\n", &startX, &startY, &goals);
    for (int i = 0; i < goals; i++){
        fscanf(fp, "%d %d\n", &goalX[i], &goalY[i]);
    }
    int j = 0;
    while (!feof(fp)){
        fscanf(fp, "%[^\n]\n", map[j]);
        j++;
    }
    fclose(fp);
}

void copyMap(){
    int i = 0;
    while (true){
        if (map[i][0] == NULL) break;
        else strcpy(map2[i], map[i]);
        i++;
    }
}

void printMap(){
    int i = 0;
    while (true){
        printf("%s\n", map2[i]);
        if (map2[i][0] == NULL) break;
        i++;
    }
}

void Reset(){
    map[startY][startX] = 12;
    for (int i = 0; i < goals; i++){
        map[goalY[i]][goalX[i]] = 15;
    }
    copyMap();
    move = 0;
    currY = startY;
    currX = startX;
}

void game(){
    Reset();
    bool exit = false;
    sekip = false;
    strcpy(inputName, "");
    while (true){
        system("cls");
        bool goal = false;
        printf("Move: %d\n", move);
        printMap();
        printf("Move [%c %c %c %c]\n", (char)27, char(24), char(25), char(26));
        puts("Exit [ESC]");
        puts("Reset [Space]");
        if (exit) break;
        input = getch();
        switch (input){
        case 75:
            if (map2[currY][currX-1] != '@' && map2[currY][currX-1] != '#'){
                map2[currY][currX-1] = 12;
                for (int i = 0; i < goals; i++){
                    if (currY == goalY[i] && currX == goalX[i]) goal = true;
                }
                if (goal) map2[currY][currX] = 15;
                else map2[currY][currX] = ' ';
                currX--;
                move++;
            }
            else if (map2[currY][currX-1] == '@' && map2[currY][currX-2] != '#'){
                map2[currY][currX-2] = '@';
                for (int i = 0; i < goals; i++){
                    if (currY == goalY[i] && currX-1 == goalX[i]){
                        map[goalY[i]][goalX[i]] = 12;
                        break;
                    }
                }
                map2[currY][currX-1] = 12;
                for (int i = 0; i < goals; i++){
                    if (currY == goalY[i] && currX == goalX[i]) goal = true;
                }
                if (goal) map2[currY][currX] = 15;
                else map2[currY][currX] = ' ';
                for (int i = 0; i < goals; i++){
                    if (currY == goalY[i] && currX-2 == goalX[i]){
                        map[goalY[i]][goalX[i]] = '@';
                        break;
                    }
                }
                currX--;
                move++;
            }
            break;
        case 72:
            if (map2[currY-1][currX] != '@' && map2[currY-1][currX] != '#'){
                map2[currY-1][currX] = 12;
                for (int i = 0; i < goals; i++){
                    if (currY == goalY[i] && currX == goalX[i]) goal = true;
                }
                if (goal) map2[currY][currX] = 15;
                else map2[currY][currX] = ' ';
                currY--;
                move++;
            }
            else if (map2[currY-1][currX] == '@' && map2[currY-2][currX] != '#'){
                map2[currY-2][currX] = '@';
                for (int i = 0; i < goals; i++){
                    if (currY-1 == goalY[i] && currX == goalX[i]){
                        map[goalY[i]][goalX[i]] = 12;
                        break;
                    }
                }
                map2[currY-1][currX] = 12;
                for (int i = 0; i < goals; i++){
                    if (currY == goalY[i] && currX == goalX[i]) goal = true;
                }
                if (goal) map2[currY][currX] = 15;
                else map2[currY][currX] = ' ';
                for (int i = 0; i < goals; i++){
                    if (currY-2 == goalY[i] && currX == goalX[i]){
                        map[goalY[i]][goalX[i]] = '@';
                        break;
                    }
                }
                currY--;
                move++;
            }
            break;
        case 80:
            if (map2[currY+1][currX] != '@' && map2[currY+1][currX] != '#'){
                map2[currY+1][currX] = 12;
                for (int i = 0; i < goals; i++){
                    if (currY == goalY[i] && currX == goalX[i]) goal = true;
                }
                if (goal) map2[currY][currX] = 15;
                else map2[currY][currX] = ' ';
                currY++;
                move++;
            }
            else if (map2[currY+1][currX] == '@' && map2[currY+2][currX] != '#'){
                map2[currY+2][currX] = '@';
                for (int i = 0; i < goals; i++){
                    if (currY+1 == goalY[i] && currX == goalX[i]){
                        map[goalY[i]][goalX[i]] = 12;
                        break;
                    }
                }
                map2[currY+1][currX] = 12;
                for (int i = 0; i < goals; i++){
                    if (currY == goalY[i] && currX == goalX[i]) goal = true;
                }
                if (goal) map2[currY][currX] = 15;
                else map2[currY][currX] = ' ';
                for (int i = 0; i < goals; i++){
                    if (currY+2 == goalY[i] && currX == goalX[i]){
                        map[goalY[i]][goalX[i]] = '@';
                        break;
                    }
                }
                currY++;
                move++;
            }
            break;
        case 77:
            if (map2[currY][currX+1] != '@' && map2[currY][currX+1] != '#'){
                map2[currY][currX+1] = 12;
                for (int i = 0; i < goals; i++){
                    if (currY == goalY[i] && currX == goalX[i]) goal = true;
                }
                if (goal) map2[currY][currX] = 15;
                else map2[currY][currX] = ' ';
                currX++;
                move++;
            }
            else if (map2[currY][currX+1] == '@' && map2[currY][currX+2] != '#'){
                map2[currY][currX+2] = '@';
                for (int i = 0; i < goals; i++){
                    if (currY == goalY[i] && currX+1 == goalX[i]){
                        map[goalY[i]][goalX[i]] = 12;
                        break;
                    }
                }
                map2[currY][currX+1] = 12;
                for (int i = 0; i < goals; i++){
                    if (currY == goalY[i] && currX == goalX[i]) goal = true;
                }
                if (goal) map2[currY][currX] = 15;
                else map2[currY][currX] = ' ';
                for (int i = 0; i < goals; i++){
                    if (currY == goalY[i] && currX+2 == goalX[i]){
                        map[goalY[i]][goalX[i]] = '@';
                        break;
                    }
                }
                currX++;
                move++;
            }
            break;
        case 27:
            char exit[100];
            strcpy(exit, "");
            while (true){
                puts("Are you sure want to exit (y|n)?");
                printf(">> ");
                scanf("%[^\n]", exit); getchar();
                if (strcmp(exit, "y") == 0){
                    sekip = true;
                    return;
                }
                else if (strcmp(exit, "n") == 0) break;
            }
            break;
        case 32:
            Reset();
            break;

        default:
            break;
        }
        for (int i = 0; i < goals; i++){
            if (map[goalY[i]][goalX[i]] == '@' && i == goals-1){
                exit = true;
                break;
            }
            else if (map[goalY[i]][goalX[i]] == '@') continue;
            else break;
        }
    }
    puts("You win");
    printf("You use %d move(s)", move);
    pressEnter();
    while(true){
        printf("Input Name: ");
        scanf("%[^\n]", inputName); getchar();
        int len = strlen(inputName);
        if (len >= 3 && len <= 30) break;
        else puts("Name's length must between 3 and 30");
    }
}

void menuSatu(){
    int pilih;
    while(true){
        system("cls");
        puts("1. Level 1");
        puts("2. Level 2");
        puts("3. Level 3");
        puts("0. Exit");
        printf(">> ");
        scanf("%d", &pilih); getchar();
        if (pilih == 0) return;
        readMap(pilih);
        game();
        if (sekip) return;
        if (pilih == 1){
            FILE *fp = fopen("score1.txt", "a");
            fprintf(fp, "%s#%d\n", inputName, move);
            fclose(fp);
        }
        else if (pilih == 2){
            FILE *fp = fopen("score2.txt", "a");
            fprintf(fp, "%s#%d\n", inputName, move);
            fclose(fp);
        }
        else if (pilih == 3){
            FILE *fp = fopen("score3.txt", "a");
            fprintf(fp, "%s#%d\n", inputName, move);
            fclose(fp);
        }
    }
}

void merge(char name[][101], int arr[], int left, int mid, int right){
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];
    char Lname[n1][101], Rname[n2][101];

    for(int i=0;i<n1;i++){
        L[i] = arr[left+i];
        strcpy(Lname[i], name[left+i]);
    }
    for(int i=0;i<n2;i++){
        R[i] = arr[mid+i+1];
        strcpy(Rname[i], name[mid+i+1]);
    }

    int i=0;
    int j=0;
    int k=left;

    while(i<n1&&j<n2){
        if(L[i] <= R[j]){
            arr[k] = L[i];
            strcpy(name[k], Lname[i]);
            i++;
        }
        else{
            arr[k] = R[j];
            strcpy(name[k], Rname[j]);
            j++;
        }
        k++;
    }

    while(i<n1){
        arr[k] = L[i];
        strcpy(name[k], Lname[i]);
        i++;
        k++;
    }

    while(j<n2){
        arr[k] = R[j];
        strcpy(name[k], Rname[j]);
        j++;
        k++;
    }

    return;
}

void mergeSort(char name[][101], int arr[], int left, int right){
    if(left < right){
        int mid = left + (right-left) / 2;
        mergeSort(name, arr, left, mid);
        mergeSort(name, arr, mid+1, right);
        merge(name, arr, left, mid, right);
    }
}

void menuDua(){
    system("cls");
    char playerName[1001][101];
    int score[1001];
    puts("Level 1");
    FILE *l1 = fopen("score1.txt", "r");
    if (!l1) puts("No Data\n");
    else{
        int i = 0;
        while(!feof(l1)){
            fscanf(l1, "%[^#]#%d\n", playerName[i], &score[i]);
            i++;
        }
        mergeSort(playerName, score, 0, i-1);
        puts("####################################################################");
        puts("| No. | Name                                               | Score |");
        puts("####################################################################");
        for (int j = 0; j < i; j++){
            printf("| %3d | %-51s| %5d |\n", j+1, playerName[j], score[j]);
        }
        puts("####################################################################\n");
    }
    puts("Level 2");
    FILE *l2 = fopen("score2.txt", "r");
    if (!l2) puts("No Data\n");
    else{
        int i = 0;
        while(!feof(l2)){
            fscanf(l2, "%[^#]#%d\n", playerName[i], &score[i]);
            i++;
        }
        mergeSort(playerName, score, 0, i-1);
        puts("####################################################################");
        puts("| No. | Name                                               | Score |");
        puts("####################################################################");
        for (int j = 0; j < i; j++){
            printf("| %3d | %-51s| %5d |\n", j+1, playerName[j], score[j]);
        }
        puts("####################################################################\n");
    }
    puts("Level 3");
    FILE *l3 = fopen("score3.txt", "r");
    if (!l3) puts("No Data\n");
    else{
        int i = 0;
        while(!feof(l3)){
            fscanf(l3, "%[^#]#%d\n", playerName[i], &score[i]);
            i++;
        }
        mergeSort(playerName, score, 0, i-1);
        puts("####################################################################");
        puts("| No. | Name                                               | Score |");
        puts("####################################################################");
        for (int j = 0; j < i; j++){
            printf("| %3d | %-51s| %5d |\n", j+1, playerName[j], score[j]);
        }
        puts("####################################################################\n");
    }
    pressEnter();
}

int main(){
    int pilih;
    do {
        system("cls");
        printMenu();
        scanf("%d", &pilih); getchar();
        switch (pilih){
        case 1:
            menuSatu();
            break;
        case 2:
            menuDua();
            break;
        
        default:
            break;
        }
    } while (pilih != 0);
    puts("Thank you for playing");
    return 0;
}