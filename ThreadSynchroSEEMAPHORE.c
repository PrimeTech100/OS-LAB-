#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>

#define BUFF_SIZE 2
#define FULL 0
#define EMPTY 0
char buffer[BUFF_SIZE];
int nextIn = 0;
int nextOut = 0;

sem_t empty_sem_mutex; //producer semaphore
sem_t full_sem_mutex; 

void produce(int item)
{
  int value;
  sem_wait(&empty_sem_mutex); //get the mutex to fill the buffer

  buffer[nextIn] = item;
  nextIn = (nextIn + 1) % BUFF_SIZE;
  printf("Producing %d \n",item);
  if(nextIn==FULL)
    {
      sem_post(&full_sem_mutex);
      sleep(1);
    }
  sem_post(&empty_sem_mutex);

}
//*********************producer
void * Producer()
{
  int i;
  for(i = 0; i < 5; i++)
    {
      produce(i);
    }
}

void consume()
{
  int item;

  sem_wait(&full_sem_mutex); // gain the mutex to consume from buffer

  item = buffer[nextOut];
  nextOut = (nextOut + 1) % BUFF_SIZE;
  printf("\t...Consuming %d \n",item);
  if(nextOut==EMPTY) //its empty
    {
      
 sem_post(&empty_sem_mutex);
sleep(1);

    }

  sem_post(&full_sem_mutex);
}
//***********************************consumer
void * Consumer()
{
  int i;
  for(i = 0; i < 5; i++)
    {
      consume();
    }
}


//*****************main()******

void main()
{
  pthread_t ptid,ctid;
  //initialize the semaphores

  sem_init(&empty_sem_mutex,0,1);
  sem_init(&full_sem_mutex,0,0);

  //creating producer and consumer threads

  pthread_create(&ptid, NULL,Producer, NULL);
  pthread_create(&ctid, NULL,Consumer, NULL);
    
  
  //exit the main thread

  pthread_exit(NULL);
 
}
#include &lt;pthread.h&gt;
#include &lt;stdio.h&gt;
#include &lt;semaphore.h&gt;
#include&lt;unistd.h&gt;

#define BUFF_SIZE 2
#define FULL 0
#define EMPTY 0
char buffer[BUFF_SIZE];
int nextIn = 0;
int nextOut = 0;

sem_t empty_sem_mutex; 
sem_t full_sem_mutex; 

void produce(int item)
{
int value;
sem_wait(&amp;empty_sem_mutex); 

buffer[nextIn] = item;
nextIn = (nextIn + 1) % BUFF_SIZE;
printf(&quot;Producing %d \n&quot;,item);
if(nextIn==FULL)
{
sem_post(&amp;full_sem_mutex);

sleep(5);
}
sem_post(&amp;empty_sem_mutex);

}

void * Producer()
{
int i;
for(i = 0; i &lt; 5; i++)
{
produce(i);
}
}

void consume()
{
int item;

sem_wait(&amp;full_sem_mutex); 

item = buffer[nextOut];
nextOut = (nextOut + 1) % BUFF_SIZE;
printf(&quot;\t...Consuming %d \n&quot;,item);
if(nextOut==EMPTY) //its empty
{

sem_post(&amp;empty_sem_mutex);
sleep(1);

}

sem_post(&amp;full_sem_mutex);
}

void * Consumer()
{
int i;
for(i = 0; i &lt; 5; i++)
{
consume();
}
}



void main()
{
pthread_t ptid,ctid;


sem_init(&amp;empty_sem_mutex,0,1);
sem_init(&amp;full_sem_mutex,0,0);



pthread_create(&amp;ptid, NULL,Producer, NULL);

pthread_create(&amp;ctid, NULL,Consumer, NULL);



pthread_exit(NULL);

}