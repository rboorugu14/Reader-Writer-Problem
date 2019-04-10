#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>
#include <semaphore.h>


sem_t rlock,wlock;
int value = 0,rcount = 0;

void *writer(void *a)
{
int b;
b=((int)a);
sem_wait(&wlock);
value++;
printf("\nValue written by %d is %d\nThe number of readers inside while writing: %d\n",b,value,rcount);
sleep(1);
sem_post(&wlock);
}
void *reader(void *a1)
{
int b1;
int rc=0;
b1=((int)a1);
sem_wait(&rlock);
rc++;
if(rc==1)
{
sem_wait(&wlock);
}
sem_post(&rlock);
printf("\n%d readers are inside\nValue read by %d is %d\n",rc,b1,value);
sleep(1);
sem_wait(&rlock);
rc--;
if(rc==0)
{
sem_post(&wlock);
}
sem_post(&rlock);
}

int main()
{
int i,m,n;
pthread_t rtid[100], wtid[100];

sem_init(&rlock,0,1);
sem_init(&wlock,0,1);

printf("\nEnter number of reader threads required: ");
scanf("%d",&m);
printf("\nEnter number of writer threads required: ");
scanf("%d",&n);

for(i=1;i<=m;i++)
{
pthread_create(&rtid[i], NULL, reader, (void*)i);
}
for(i=1;i<=n;i++){
pthread_create(&wtid[i], NULL, writer,(void*)i);
}
for(i=1;i<=m;i++)
{
pthread_join(rtid[i],NULL);
}
for(i=1;i<=n;i++){
pthread_join(wtid[i],NULL);
}
}
