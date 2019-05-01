#include<stdio.h>
#include<math.h>
#include<pthread.h>
#include<stdlib.h>


#define NUM_THREADS 4
#define ITERATIONS 1000

// Declarar funciones
int create_thread(pthread_t * thread, void * function, void *arg);
void *leibniz(void *threadid);

double result = 0.0;

int main(){
  pthread_t threads[NUM_THREADS];
  long i;
  int rc;

  // CREATE
  for( i = 0; i < NUM_THREADS; i++ )
  {
    printf("Creando hilo...\n");
    fflush(stdout);
    create_thread(&threads[i], leibniz, (void *)i);
  }

  // JOIN
  for( i = 0; i < NUM_THREADS; i++ )
  {
    rc = pthread_join(threads[i], NULL);
    if(rc)
    {
      perror("No puedo cerrar hilo");
      exit(-1);
    }
  }
  printf("Pi %f\n", result);
  exit(0);

}

void *leibniz( void *threadid )
{
  double local = 0.0;
  int size = ITERATIONS/NUM_THREADS;
  int start = (long)threadid * size;
  int end = ( (long) threadid + 1 ) * size;
  int i;
  int test = (long)threadid;
  printf("---------- \n");
  printf("threadid = %d \n", test);
  printf("---------- \n");
  printf("Size = %d \n", size);
  printf("Start = %d \n", start);
  printf("End = %d \n", end);
  printf("---------- \n");
  for( i = start; i < end; i++ )
  {
    if ( i%2 == 0 ){
      local += 1 * ( 1.0 / ( 2 * i + 1 ) );
    } else {
      local += -1 * ( 1.0 / ( 2 * i + 1 ) );
    }
    
  }
  result += local*4;
}

int create_thread(pthread_t * thread, void * function, void *arg)
{
    int r = pthread_create(thread, NULL, function, arg);

    if (r != 0)
    {
        perror("No puedo crear hilo");
        return 0;
    }   
    return 1;
}