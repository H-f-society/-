//
//  EightQueen.c
//  
//
//  Created by tujunfeng on 19/4/9.
//
//

#include <stdio.h>
#define SIZE_MAP 8
int map[SIZE_MAP][SIZE_MAP];
int num;
void solve(int row);
void printMap(int row);
int check(int row,int column);

int check(int row,int column){
    int i;
    for (i=row-2; i>=0; i--) {
        if (map[i][column-1]==1) {
            return 0;
        }
        if (i-row+column>=0 && map[i][i-(row-column)]==1) {
            return 0;
        }
        if (row+column-i-2<=SIZE_MAP-1 && map[i][row+column-i-2]==1) {
            return 0;
        }
    }
    return 1;
}

void printMap(int row){
    int i,j;
    printf("the No.%d answer:\n",++num);
    for (i=0; i<row; i++) {
        for (j=0; j<row; j++) {
            printf("%d ",map[i][j]);
        }
        printf("\n");
    }
}
void solve(int row){
    int i;
    for (i=1; i<=SIZE_MAP; i++) {
        map[row-1][i-1]=1;
        if (check(row,i)) {
            if (row==8) {
                printMap(SIZE_MAP);
            }
            else{
                solve(row+1);
            }
        }
        map[row-1][i-1]=0;
    }
}

int main(){
    solve(1);
    return 0;
}
