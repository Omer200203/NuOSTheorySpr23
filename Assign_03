#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include<time.h>
#include <errno.h>
#include <signal.h>
#define SizeOfGrid 15
#define ThreadsNumber 10
#define GenerationsNumber 15

int Grid[SizeOfGrid][SizeOfGrid];
pthread_mutex_t Grid_MUTEX;
pthread_cond_t Grid_CONDITION;

void *calculate(void *arg) {
    int ID = *((int*)arg);
    int Start = ID * (SizeOfGrid / ThreadsNumber);
    int End = (ID + 1) * (SizeOfGrid / ThreadsNumber);

    for (int Generation = 0; Generation < GenerationsNumber; Generation++) {
        for (int i = Start; i < End; i++) {
            for (int j = 0; j < SizeOfGrid; j++) {
                int Neighbors = 0;
                for (int x = i-1; x <= i+1; x++) {
                    for (int y = j-1; y <= j+1; y++) {
                        if (x == i && y == j) continue;
                        if (x >= 0 && x < SizeOfGrid && y >= 0 && y < SizeOfGrid && Grid[x][y] == 1) {
                            Neighbors++;
                        }
                    }
                }

                if (Grid[i][j] == 1 && (Neighbors < 2 || Neighbors > 3)) {
                    Grid[i][j] = 0;
                } else if (Grid[i][j] == 0 && Neighbors == 3) {
                    Grid[i][j] = 1;
                }
            }
        }

        pthread_mutex_lock(&Grid_MUTEX);
        if (ID == 0) {
            pthread_cond_broadcast(&Grid_CONDITION);
        } else {
            while (pthread_cond_wait(&Grid_CONDITION, &Grid_MUTEX) != 0);
        }
        pthread_mutex_unlock(&Grid_MUTEX);

        if (ID == 0) {
            printf("****Generation Number %d****\n", Generation);
            for (int i = 0; i < SizeOfGrid; i++) {
                for (int j = 0; j < SizeOfGrid; j++) {
                    printf("%c", (Grid[i][j] == 1 ? 'O'  : ' '));
                }
                printf("\n");
            }
        }
    }
    return NULL;
}

int main() {

    clock_t Starting, Ending;
    double TotalTime;
    
    Starting = clock();
    for (int i = 0; i < SizeOfGrid; i++) {
        for (int j = 0; j < SizeOfGrid; j++) {
            Grid[i][j] = rand() % 2;
        }
    }

    pthread_mutex_init(&Grid_MUTEX, NULL);
    pthread_cond_init(&Grid_CONDITION, NULL);

    pthread_t threads[ThreadsNumber];
    int thread_IDS[ThreadsNumber];
    for (int i = 0; i < ThreadsNumber; i++) {
        thread_IDS[i] = i;
        pthread_create(&threads[i], NULL, calculate, &thread_IDS[i]);
    }
    
    Ending = clock();
    TotalTime = ((double) (Ending - Starting)) / CLOCKS_PER_SEC;
    printf("Time Taken with %d Threads: %f",ThreadsNumber,TotalTime);

    int Finish = 0;
    struct timespec Time;
    while (!Finish) {
        pthread_mutex_lock(&Grid_MUTEX);
        clock_gettime(CLOCK_REALTIME, &Time);
        Time.tv_sec += 1;  
        int Returns = pthread_cond_timedwait(&Grid_CONDITION, &Grid_MUTEX, &Time);
        if (Returns == ETIMEDOUT) {
            Finish = 1;
            for (int i = 0; i < ThreadsNumber; i++) {
                if (pthread_kill(threads[i], 0) == 0) {
                    Finish = 0;
                    break;
                }
            }
        }
        pthread_mutex_unlock(&Grid_MUTEX);
    }
    
    for (int i = 0; i < ThreadsNumber; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&Grid_MUTEX);
    pthread_cond_destroy(&Grid_CONDITION);

    return 0;
}
