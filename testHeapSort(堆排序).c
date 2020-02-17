//
//  testHeapSort.c
//  
//
//  Created by tujunfeng on 2019/7/23.
//

#include <stdio.h>
#include <stdlib.h>

void heapAdjust(int *num,int s,int m);
void heapSort(int *num,int s,int m);

void heapAdjust(int *num,int s,int m){
    int i,temp;
    temp=num[s];
    for(i=s*2+1;i<=m;i*=2){
        if(i+1<=m && num[i+1]>num[i])
            i++;
        if (temp>num[i])
            break;
        num[s]=num[i];
        s=i;
    }
    num[s]=temp;
}

void headSort(int *num,int m){
    int i,temp;
    for (i=(m+1)/2-1; i>=0; i--) {
        heapAdjust(num,i,m);
        
    }
    for (i=m; i>0;) {
        printf("%d ",num[0]);
        temp=num[i];
        num[i]=num[0];
        num[0]=temp;
        heapAdjust(num,0,--i);
    }
    
}

int main(){
    int i;
    int num[] = {98, 48, 777, 63, 57, 433, 23, 1112, 1,45};
    headSort(num,9);
    printf("\n");
    for (i=0; i<10; i++) {
        printf("%d ",num[i]);
    }
}
 
