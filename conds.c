#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include <pthread.h>
#include <unistd.h>
#include <assert.h>

#include "dlist.h"

typedef struct {
    pthread_cond_t cond_var;
    pthread_mutex_t lock;
    int flag;

    long id;
    long value;      // value assigned by main thread
} condition;

condition *condition_new (void) {

    condition *cond =  (condition *) malloc (sizeof (condition));
    if (cond) {
        pthread_mutex_init(&cond->lock, NULL);
        pthread_cond_init(&cond->cond_var, NULL);
        cond->flag = 0;

        cond->value = 0;
    }

    return cond;

}

DoubleList *workers = NULL;

// used for master thread
int done = 0;
pthread_mutex_t global_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t global_cond = PTHREAD_COND_INITIALIZER;

void *worker(void *args) {

    const long myid = (long)args;

    // create shared data
    condition *cond = condition_new ();
    cond->id = myid;

    // add to global list -> share data
    dlist_insert_after (workers, dlist_end (workers), cond);

    sleep (1);

     /* Wait for flag to be set */
    pthread_mutex_lock(&cond->lock);

    // we're going to manipulate done and use the cond, so we need the mutex
    pthread_mutex_lock( &global_mutex );

    // done++;
    // printf( "[thread %d] done is now %d. Signalling cond.\n", myid, done );

    // wait up the main thread (if it is sleeping) to test the value of done  
    pthread_cond_signal( &global_cond ); 
    pthread_mutex_unlock( & global_mutex );

    while (!cond->flag)
        pthread_cond_wait(&cond->cond_var, &cond->lock);

    // do stuff
    printf ("\nid: %ld - value assigned by main thread is: %ld\n", myid, cond->value);

    pthread_mutex_unlock (&cond->lock);

    free (cond);

    pthread_exit(NULL);     // we are done here!
}


const size_t NUMTHREADS = 20;

int count = 0;

// check
// https://stackoverflow.com/questions/37019144/control-each-thread-by-its-own-condition-variable-c
// https://stackoverflow.com/questions/1136371/why-is-a-while-loop-needed-around-pthread-wait-conditions

int main (int argc, char **argv) {

    puts( "[thread main] starting" );

    workers = dlist_init (NULL, NULL);

    pthread_t threads[NUMTHREADS];

    for( int t=0; t<NUMTHREADS; t++ ) {
        pthread_create( &threads[t], NULL, worker, (void*)(long)t );
        // sleep (1);
    }
        

    // we're going to test "done" so we need the mutex for safety
    pthread_mutex_lock( &global_mutex );

    // are the other threads still busy?
    while( done < NUMTHREADS ) {
      printf( "[thread main] done is %d which is < %d so waiting on cond\n", 
	      done, (int)NUMTHREADS );
      
      /* block this thread until another thread signals cond. While
	 blocked, the mutex is released, then re-aquired before this
	 thread is woken up and the call returns. */ 
      pthread_cond_wait( & global_cond, & global_mutex ); 
      
      puts( "[thread main] wake - cond was signalled." ); 

        // assign a value to worker
        while (workers->size > 0) {
            condition *worker_cond = (condition *) dlist_remove_element (workers, NULL);
            if (worker_cond) {
                pthread_mutex_lock(&worker_cond->lock);
                worker_cond->flag = 1;
                worker_cond->value = worker_cond->id;
                // count++;
                pthread_cond_signal(&worker_cond->cond_var);
                pthread_mutex_unlock(&worker_cond->lock);
            }
        }
        
      
      /* we go around the loop with the lock held */
    }
  
    printf( "[thread main] done == %d so everyone is done\n", (int)NUMTHREADS );
  
    pthread_mutex_unlock( & global_mutex );

    return 0;

}