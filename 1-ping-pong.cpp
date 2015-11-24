#include <iostream>
#include <semaphore.h>

#include <cstdio>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>

#define N 50

using namespace std;

sem_t sema1;
sem_t sema2;

void* ping(void* arg);
void* pong(void* arg);

int main()
{
    pthread_t p1_tid;
    pthread_t p2_tid;

    sem_init(&sema1, NULL, 1);
    sem_init(&sema2, NULL, 0);

    if(pthread_create(&p1_tid, NULL, ping, NULL) != 0)
    {
        perror("Thread ping");
        return EXIT_FAILURE;
    }

    if(pthread_create(&p2_tid, NULL, pong, NULL) != 0)
    {
        perror("Thread pong");
        return EXIT_FAILURE;
    }

    pthread_join(p1_tid, NULL);
    pthread_join(p2_tid, NULL);

    pthread_detach(p1_tid);
    pthread_detach(p2_tid);

    return EXIT_SUCCESS;
}

void* ping(void *arg)
{
    for(int i = 0; i < N; i++)
    {
        sem_wait(&sema1);
        std::cout << "Ping-";
        sem_post(&sema2);
    }

    pthread_exit(NULL);
}

void* pong(void *arg)
{
    for(int i = 0; i < N; i++)
    {
        sem_wait(&sema2);
        std::cout << "Pong\n";
        sem_post(&sema1);
    }

    pthread_exit(NULL);
}
