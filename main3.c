#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define N 10

typedef struct node node;
typedef struct queue queue;

struct node{
    int num;
    node *next;
};

struct queue{
    node *head;
    node *tail;
};


void *klient(void *);
void *fryzjer();
int pop(queue *);
int push(queue *, int , pthread_mutex_t);
void printQueue(int, int, int, int, char *);
void testQueue();

pthread_cond_t poczekalnia, fotel;
//pthread_mutex_t mutex[N];
pthread_mutex_t locker=PTHREAD_MUTEX_INITIALIZER;

int zakonczono, klienci, krzesla, rezygnacje, wolne;
int mode;

queue *q;

int main(int argc, char *argv[]){

    mode=0;
    char *param="-debug";
    if(argc>2){
        printf("Zbyt wiele argumentów\n");
        return -1;
    }
    if(argc==2 && strcmp(argv[1], param)!=0){
        printf("Nie rozpoznano parametru: %s\n", argv[1]);
        return-1;
    }
    if(argc==2 && strcmp(argv[1], param)==0){
        mode=1;
    }

    int x;
    rezygnacje=0;
    printf("Maksymalna liczba klientow to 10\n");
    printf("Podaj liczbe klientow i krzesel\n");

    scanf("%d", &x);
    klienci=x;
    scanf("%d", &x);
    krzesla=x;
    printf("Test\n");

    if(krzesla>N){
        printf("Maksymalna liczba krzesel to: %d", N);
        return 0;
    }

    if(klienci > krzesla){
        rezygnacje=klienci-krzesla;
    }
    wolne=krzesla;

    pthread_cond_init(&poczekalnia, NULL);
    pthread_cond_init(&fotel, NULL);

    pthread_t ftid;
    pthread_t tid[N];

    q=malloc(sizeof(queue));
    q->head=NULL;
    q->tail=NULL;

    zakonczono=0;

    for(x=0; x< klienci; x++){
        //mutex[x]=PTHREAD_MUTEX_INITIALIZER;
        pthread_create(&tid[x], NULL, klient, (void*)(x+1));
        usleep(100);
    }

    sleep(1);

    pthread_create(&ftid, NULL, fryzjer, NULL);

    for(x=0; x<klienci; x++){
        pthread_join(tid[x], NULL);
        //printf("Wątek %d zakończył prace\n", x+1);
    }
    zakonczono=1;

    pthread_cond_signal(&fotel);
    pthread_join(ftid, NULL);
    //testQueue(q);

    return 0;
}

void testQueue(queue *q){

    int i=0;
    for(i=0; i<10; i++){
        //push(q, i);
        printf("Pushed element: %d\n", i);
    }
    printf("\n");
    for(i=0; i<10; i++){
        int val=pop(q);
        printf("Pushed element: %d\n", val);
    }
}

int pop(queue *q){
    //rintf("Inside pop\n");
    if(q->head==NULL)
        return -1;
    //printf("q->head not NULL\n");
    pthread_mutex_lock(&locker);
    //printf("mutex locked\n");
    int val=q->head->num;
    //printf("val=q->head->num\n");
    node *temp=q->head;
    //printf("node *temp=q->head;\n");
    q->head=q->head->next;
    //printf("q->head=q->head->next;\n");
    free(temp);
    //printf("free(temp)\n");
    pthread_mutex_unlock(&locker);
    //printf("mutex unlocked\n");

    pthread_cond_signal(&poczekalnia);
    //printf("condt_signaled\n");

    return val;
}

int push(queue *q, int val, pthread_mutex_t mutex){
    node *new = malloc(sizeof(node));
    if(new==NULL)
        return -1;

    new->num=val;
    new->next=NULL;
    if(q->tail!=NULL)
        q->tail->next=new;

    q->tail=new;
    if(q->head==NULL)
        q->head=new;

    pthread_cond_wait(&poczekalnia, &mutex);;

    return 0;
}

void*klient(void *number){
    int num=(int *)number;
    int empty=0;

    if((krzesla-num+1)>0){

        pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;

        //printf("Umieszczono wątek %d w kolejce\n", num);
        printQueue(rezygnacje, num, krzesla, empty, "Przyszedł");

        pthread_mutex_lock(&locker);
        wolne--;
        pthread_mutex_unlock(&locker);

        push(q, num, mutex); //condt wait


        pthread_mutex_lock(&locker);
        wolne++;
        pthread_mutex_unlock(&locker);

        printQueue(rezygnacje, krzesla-wolne, krzesla, num, "Wszedł");

        usleep(200);
        //printf("Zdjęto wątek %d z kolejki\n", num);
        pthread_cond_wait(&fotel, &mutex);

        //printf("Zakończono strzyżenie klienta %d\n", num);
    }
}

void *fryzjer(){
    int empty=0;
    while(!zakonczono){
        //printf("!zakończono\n");
        int val=pop(q);
        //printf("Zdjęto klienta %d z kolejki\n", val);
        //printf("Wybudzono fryzjera. Strzyżenie\n");
        sleep(3);
        pthread_cond_signal(&fotel);

        printQueue(rezygnacje, krzesla-wolne, krzesla, empty, "Wyszedł");
             zakonczono=1;
    }
}

void printQueue(int rez, int zaj, int all, int in, char *msg){
    printf("Res: %d, WRoom: %d/%d [in: %d] <--- %s\n", rez, zaj,all, in, msg);
}