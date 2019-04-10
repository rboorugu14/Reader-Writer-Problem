# Reader-Writer-Problem

The READER-WRITER problem(B68OSProject.c) i have written is based on pthreads, mutexes and conditional variables. In this code the readers have priority over writers so all the read statements print once and write statements print all at once.
And in my code the number of reader threads and writer threads are taken from the user and the maximum threads i have given are 100. You can increase them by changing the array size in the main() method.
In the screenshot you can see that the value read by readers is '0' because i have initialised the lavue as '0'. If you want the initial value to be different you can change and after all the read functions run then the write function increments the value.
The file SEMproject.c is based on semaphores
