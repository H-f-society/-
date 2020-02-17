//
//  TestArray.c
//  
//
//
//

#include <stdio.h>
#include <stdlib.h>
typedef struct Array{
    int *base;
    int dim;
    int *bounds;
    int *constants;
}Array;

void InitalArray(Array *A){
    int i;
    int elemTotal=1;
    printf("input the dim\n");
    scanf("%d",&A->dim);
    A->bounds=(int *)malloc(A->dim*sizeof(int));
    if (!A->bounds) {
        printf("create bounds is failed\n");
        exit(0);
    }
    for (i=0; i<A->dim; i++) {
        scanf("%d",(A->bounds)+i);
        elemTotal*=A->bounds[i];
    }
    A->base=(int *)malloc(sizeof(int)*elemTotal);
    if (!A->base) {
        printf("not enough memory create Array is failed\n");
        exit(0);
    }
    for(i=1;i<=elemTotal;i++){
        A->base[i]=i;
    }
    A->constants=(int *)malloc(A->dim*sizeof(int));
    if (!A->constants) {
        printf("create constants is failed\n");
        exit(0);
    }
    A->constants[A->dim-1]=1;
    for (i=A->dim-2; i>=0; i--) {
        A->constants[i]=A->constants[i+1]*A->bounds[i+1];
        printf("constants[%d]=%d\n",i,A->constants[i]);
    }
    printf("the total of elem is %d",elemTotal);
}

int locate(Array *A){
    int ind;
    int i;
    int off=0;
    printf("dim=%d\n",A->dim);
    for (i=0; i<A->dim; i++) {
        printf("input the No.%d mark of the Atom\n",i+1);
        scanf("%d",&ind);
        if(ind<0||ind>=A->bounds[i]){
            printf("exceeds the bound\n");
            exit(0);
        }
        off+=ind*A->constants[i];
    }
    printf("the location is %d\n",off);
    return off;
            
}

void Value(Array *A){
    int e;
    int result;
    result=locate(A);
    e=*(A->base+result);
    printf("the number is %d\n",e);
}

void DestroyArray(Array *A){
    free(A->base);
    free(A->bounds);
    free(A->constants);
}


int main(){
    Array array;
    InitalArray(&array);
    Value(&array);
  
    
    
}

