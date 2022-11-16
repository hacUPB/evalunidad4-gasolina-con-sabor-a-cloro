#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int buffer [10] ;
int count = 0;
char letra = 'A';
int infocuenta;
sem_t empty,full;  
sem_t sem_prod;
sem_t sem_con;
pthread_mutex_t mutex; 


void* productor(void* data)
{
       while(1){  
        sem_wait(&empty);  
        
	    
            pthread_mutex_lock(&mutex);
			
            printf( "bienvenido al banco tome su turno \n ");
			buffer[count] = count + 1;
            printf(" su turno es  %d,%c\n ", buffer[count], letra) ;
            count++;
             sleep(3);
            pthread_mutex_unlock(&mutex);
			
	     
        sem_post(&full);        
        
    }  
    
}
void* consumidor(void* data)
{
	
       while(1)
        {
            int y;
         int infocuenta=rand()%100000;
        sem_wait(&full); 
        
	    
            pthread_mutex_lock(&mutex);
            printf( " la caja va a atender %d,%c \n ",buffer[count] , letra);  
            y = buffer[count - 1];
            count--;
            printf("el numero de su cuenta sera  %d \n ", infocuenta);
            printf("se libero el turno %d\n",y);
            pthread_mutex_unlock(&mutex);
            
			
	       
        
        sem_post(&empty);        
        
    	}	
        
		
       
}


int main(int argc, char** argv)
{
    
	srand(time(NULL));
    
	pthread_t thrd_prod , thrd_cons;  

    pthread_mutex_init( &mutex , NULL );     
    
    sem_init (&empty, 0, 10);            
    sem_init (&full, 0, 0);        
    
    if( pthread_create( &thrd_prod , NULL, productor ,  NULL ) != 0 )  {
		printf( "thread create failed." );
	}
        
	if( pthread_create( &thrd_cons , NULL, consumidor ,   NULL ) != 0 ) {
		printf( "thread create failed." );  
	}
       

     
    if( pthread_join( thrd_prod , NULL ) != 0 )  
        printf( " wait thread failed.");  
    if( pthread_join( thrd_cons , NULL ) != 0 )  
        printf( " wait thread failed.");  
    sem_destroy (&full);            
    sem_destroy(&empty);            
    pthread_mutex_destroy( &mutex );          
    return 0;  
	
	
}