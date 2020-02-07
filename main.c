#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<time.h>

#define SIZE 60

typedef struct _array{
    int * arr;
    int size;
}array;

static pthread_mutex_t lock=PTHREAD_MUTEX_INITIALIZER;

void print_arr(array *arr);
void arr_init(array *arr,int init_val);



/*
param is array pointer
travel array in -> this direcction
*/
void* direction_1(void* param);


/*
param is array pointer
travel array in <- this direcction
*/
void* direction_2(void* param);



int main(int argc,char ** argv){
    array arr;
    arr.arr=malloc(sizeof(int)*SIZE);
    arr.size=SIZE;



    pthread_t thread1,thread2;

    pthread_create(&thread1,NULL,direction_1,&arr);
    pthread_create(&thread2,NULL,direction_2,&arr);
    
    
    pthread_join(thread2,NULL);
    pthread_join(thread1,NULL);
    

    return 0;
}


/*
param is array pointer
travel array in -> this direcction
*/
void* direction_1(void* param){
    array * _arr=(array*) param;
    for (size_t i = 0; i < _arr->size/2; i++)
    {
            _arr->arr[i]=1;
      
        pthread_mutex_lock(&lock);              
        print_arr(_arr);
        pthread_mutex_unlock(&lock);
    
    }
    pthread_exit(0);
}

/*
param is array pointer
travel array in <- this direcction
*/
void* direction_2(void* param){
 array * _arr=(array*) param;
    for (size_t i = _arr->size; i >= _arr->size/2; i--)
    {
        _arr->arr[i]=1;

        pthread_mutex_lock(&lock);              
        print_arr(_arr);
        pthread_mutex_unlock(&lock);
    }
    pthread_exit(0);
}


void print_arr(array *_arr){
    for (size_t i = 0; i < _arr->size; i++)
    {
        printf("%d ",_arr->arr[i]);
    }
    printf("\n");
}


void arr_init(array *_arr,int init_val){
    for (size_t i = 0; i <_arr->size ; i++)
    {
        _arr->arr[i]=init_val;
    }
    
}

