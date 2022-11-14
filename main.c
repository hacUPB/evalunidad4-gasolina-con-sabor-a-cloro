#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

int buffer = 0 ;
int turno;
char letra;
char infocuenta[20];
sem_t empty,full;  
sem_t sem_prod;
sem_t sem_con;
pthread_mutex_t mutex; 


void* productor(void* data)
{
       while(1){  
        sem_wait(&empty);  
        for (size_t i = 0; i < 9; i++)
	    {
            pthread_mutex_lock(&mutex);
			
            printf( "que ocpion desea elegir A:abrir una cuenta \n ");
			scanf("%c",&letra);
            buffer++;
            printf(" El turno del cliente %d pra la solicitud %c\n ", buffer, letra) ;
            pthread_mutex_unlock(&mutex);
			
	    }  
        sem_post(&full);        
        return NULL;
    }  
}
void* consumidor(void* data)
{
	
       while(1)
        {
        sem_wait(&empty); 
        for (size_t i = 0; i < 9; i++)
	    {
            pthread_mutex_lock(&mutex);
            printf( " la caja va a atender %d \n ",buffer);  
            buffer--;
            printf(" rellene la informacion para abrir la cuenta \n ") ;
			scanf("%s" ,infocuenta);
			printf("el nombre de su cuenta sera %s \n ", infocuenta);
            pthread_mutex_unlock(&mutex);
			
	    }    
        
        sem_post(&full);        
        return NULL;
    	}	
		
       
}


int main(int argc, char** argv)
{
    
	
		    pthread_t thrd_prod , thrd_cons;  

    pthread_mutex_init( &mutex , NULL );     
    
    sem_init (&empty, 0, 5);            
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