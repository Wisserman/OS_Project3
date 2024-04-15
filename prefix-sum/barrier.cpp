#include "barrier.h"

#include <semaphore.h>

namespace synchronization
{
    // Provides a reusable barrier
    class barrier {
    private:
        // Declare your variables here
    int numThreads, threadCount;
    sem_t count_sem, lock_sem;

    public:

        // Constructor
        barrier(int numberOfThreads)
        {
            numThreads = numberOfThreads;
            threadCount = 0;
            sem_init(&count_sem, 0, 1);
            sem_init(&lock_sem, 0, 0);
        }

        // Destructor
        ~barrier()
        {
            sem_destroy(&count_sem);
            sem_destroy(&lock_sem);
        }

        // Function to wait at the barrier until all threads have reached the barrier
        void arriveAndWait(void)
        {
            sem_wait(&count_sem);
            threadCount++;
            sem_post(&count_sem);

            if (threadCount == numThreads)
                sem_post(&lock_sem);

            sem_wait(&lock_sem);
            sem_post(&lock_sem);
        }
    };

}