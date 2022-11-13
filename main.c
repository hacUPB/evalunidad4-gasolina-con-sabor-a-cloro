#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

int buffer[10];
int turno;
char letra;
sem_t sem_prod;
sem_t sem_con;

void* productor(void* data)
{
        if ( buffer[9] ){
			sem_wait(&sem_prod);
		}else {
			sem_post(&sem_prod);
		}
		pthread_exit(NULL);
}

void* consumidor(void* data)
{
        for(int i = 0 ; i > 10 ; i++){
			if(buffer[i]  == 0 ){
				sem_wait(&sem_con);
				break;
			}else{
				sem_post(&sem_con);
				break;
			}
		}
		printf("A: abrir una cuenta \n");
		scanf("%c" ,&letra);
		for (int i= 0 ; i < 10 ; i++){
			if (buffer [i] == 0){
				turno = i;
				printf("Su turno es %d %c", (turno + 1), letra);
				
			}break;
		}
		pthread_exit(NULL);
		
       
}


int main(int argc, char** argv)
{
        pthread_t prod;
        pthread_t con;

        sem_init(&sem_prod,0,5);
        sem_init(&sem_con,0,0);

        pthread_create(&prod,NULL,productor,NULL);
        pthread_create(&con,NULL,consumidor,NULL);

        pthread_join(con,NULL);
        return 0;
}