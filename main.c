#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include<pthread.h>
#include<semaphore.h>
#define N 10

void *klient(void *);
void *fryzjer();
void printQueue(int , int , int , int );
//void waitTime(int );

sem_t poczekalnia;
sem_t fotel;
sem_t poduszka;
sem_t strzyzenie;

pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;

int zakonczono, klienci, krzesla, rezygnacje, sukcesy, wolne;
int mode;           //0-normalny; 1-debug

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
    printf("Program uruchomiony. Wartość parametru mode: %d\n", mode);
    //tid is for thread id
    pthread_t ftid;
    pthread_t tid[N];
    int i, x;
    //int Liczba[N];
    rezygnacje=0;
    printf("Maksymalna liczba klientow to 10\n");
    printf("Podaj liczbe klientow i krzesel\n");

    scanf("%d", &x);
    klienci=x;
    scanf("%d", &x);
    krzesla=x;

    wolne=krzesla;

    if(krzesla > N){
        printf("Maksymalna liczba klientow to: %d\n", N);
        //system("PAUSE");
        return 0;
    }

    if(klienci>krzesla)
        rezygnacje=klienci-krzesla;
    wolne=krzesla;

    //sem_int(wskaznik na semafor, 
    //flaga nie wspierana przez LinuxThreads, 
    //początkowa wartość semafora, oznacza ile procesów mozemy w nim umieścić)

    sem_init(&poczekalnia, 0, krzesla);
    sem_init(&fotel, 0,1);
    sem_init(&poduszka, 0,0);
    sem_init(&strzyzenie, 0,0);

    //Utworzenie procesu fryzjera f(ryzjer)t(hread)id
    pthread_create(&ftid, NULL, fryzjer, NULL);

    //Utworzenie procesów klientow
    for(i=0; i<klienci; i++){
        pthread_create(&tid[i], NULL, klient, (void*)(i+1));
        usleep(100);
    }

    //Po zakończeniu scalenie procesów klientow
    for(i=0; i<klienci; i++){
        pthread_join(tid[i], NULL);
    }
    zakonczono=1;
    //Po zakończeniu pobudka fryzjera i scalenie jego procesu
    sem_post(&poduszka);
    pthread_join(ftid, NULL);
    //system("PAUSE");
    return 0;
}

void *klient(void *number){
    int num=(int*)number;
    
    if((krzesla-num+1)>0){

        sem_wait(&poczekalnia);
        int empty=0;

        pthread_mutex_lock(&mutex);
        wolne--;
        pthread_mutex_unlock(&mutex);
        printQueue(rezygnacje, krzesla-wolne, krzesla, empty);

        //printf("Res: %d, WRoom: %d/%d [in: %d]\n",rezygnacje, krzesla-wolne, krzesla, empty);
        sleep(1);
        sem_wait(&fotel);
        sem_post(&poczekalnia);

        pthread_mutex_lock(&mutex);
        wolne++;
        pthread_mutex_unlock(&mutex);
        printQueue(rezygnacje, krzesla-wolne, krzesla, num);

        //printf("Res: %d, WRoom: %d/%d [in: %d]\n",rezygnacje, krzesla-wolne, krzesla, num); 
        sem_post(&poduszka);
        sem_wait(&strzyzenie);
        sem_post(&fotel);
        printQueue(rezygnacje, krzesla-wolne, krzesla, empty);
        //printf("Res: %d, WRoom: %d/%d [in: %d]\n",rezygnacje, krzesla-wolne, krzesla, empty);

        pthread_mutex_lock(&mutex);
        sukcesy++;
        pthread_mutex_unlock(&mutex);
    }
    if(mode==0){
    } else if (mode==1){

    }
    //sleep(3);
}

void printQueue(int rez, int zaj, int all, int in){
    if(mode==0){
        printf("Res: %d, WRoom: %d/%d [in: %d]\n"
                ,rez, zaj, all, in);
    } else if(mode==1){
        int i=0;
        printf("Klienci czekający:");
        for(i=in; i<zaj+in; i++)
            printf(" %d", i);
        printf("\n");
        printf("Klienci którzy zdezygnowali:");
        for(i=10;i<all+rez; i++)
            printf(" %d", i+1);
        printf("\n");
    }
}

void *fryzjer(){
    while(!zakonczono){ 
        sem_wait(&poduszka);
        if(!zakonczono){
            sleep(1);
            sem_post(&strzyzenie);
        } else{
            printf("Fryzjer zakonczyl prace\n");
        }
    } 
}

//void waitTime(int sec){
//    int len=1;
//    sleep(len);
//}