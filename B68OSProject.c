#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>
#include <fcntl.h>

pthread_mutex_t rlock;
pthread_mutex_t wlock;
int value = 0,rcount = 0;

void *writer(void *a)
{
int b;
b=((int)a);
pthread_mutex_lock(&wlock);
value++;
printf("\nValue written by %d is %d\nThe number of readers inside while writing: %d\n",b,value,rcount);
sleep(1);
pthread_mutex_unlock(&wlock);
}
void *reader(void *a1)
{
int b1;
int rc=0;
b1=((int)a1);
pthread_mutex_lock(&rlock);
rc++;
if(rc==1)
{
pthread_mutex_lock(&wlock);
}
pthread_mutex_unlock(&rlock);
printf("\n%d readers are inside\nValue read by %d is %d\n",rc,b1,value);
pthread_mutex_lock(&rlock);
rc--;
if(rc==0)
{
pthread_mutex_unlock(&wlock);
}
pthread_mutex_unlock(&rlock);
}

int main()
{
int i,m,n;
pthread_t rtid[100], wtid[100];

pthread_mutex_init(&rlock,NULL);
pthread_mutex_init(&wlock,NULL);

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
