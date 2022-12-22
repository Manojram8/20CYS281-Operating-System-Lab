#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_THREADS 4
#define NUM_ELEMENTS 8

int array[NUM_ELEMENTS] = {1, 2, 3, 4, 5, 6, 7, 8};
char *results[NUM_THREADS];

void *sum_array(void *threadid) {
  int start = (int threadid * (NUM_ELEMENTS / NUM_THREADS);
  int end = start + (NUM_ELEMENTS / NUM_THREADS);
  int sum = 0;
  for (int i = start; i < end; i++) {
    sum += array[i];
  }
  char result[32];
  sprintf(result, "Thread %d sum: %d\n", (int)threadid, sum);
  results[(int)threadid] = strdup(result);
  return NULL;
}

int main(int argc, char *argv[]) {
  pthread_t threads[NUM_THREADS];
  int sum = 0;
  for (int i = 0; i < NUM_THREADS; i++) {
    pthread_create(&threads[i], NULL, sum_array, (void*)i);
  }
  for (int i = 0; i < NUM_THREADS; i++) {
    pthread_join(threads[i], NULL);
    printf("%s", results[i]);
    sum += atoi(results[i] + strlen("Thread 0 sum: "));
  }
  printf("Total sum: %d\n", sum);
  return 0;
}
