#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>

#define N 10
#define producer_num 7
#define consumer_num 5

typedef int semaphore;
typedef int item;

item buffer[N] = {0};
item id = 0;

int in = 0, out = 0;
semaphore empty = N, full = 0, mutex = 1, producer_mutex = 1;

/**
 * 生产者进程函数
 */
void *producer_func(void *args)
{
    while (true)
    {
        while (producer_mutex == 1)
        {
            producer_mutex = 0;
            printf("生产者生产了一个产品，id 为 [%d]\n", id++);
        }
        producer_mutex = 1;

        while (empty <= 0)
        {
            printf("缓冲区满了！\n");
            sleep(1);
        }
        empty--;

        while (mutex == 1)
        {
            mutex = 0;
            buffer[in] = id;
            in = (in + 1) % N;
        }
        mutex = 1;
        full++;

        sleep(1);
    }
}

/**
 * 消费者进程函数
 */
void *consumer_func(void *args)
{
    while (true)
    {
        while (full <= 0)
        {
            printf("\t\t\t\t\t缓冲区空了！\n");
            sleep(1);
        }
        full--;

        while (mutex == 1)
        {
            mutex = 0;
            printf("\t\t\t\t\t消费者用了一个产品，id 为 [%d]\n", buffer[out]);
            buffer[out] = 0;
            out = (out + 1) % N;
        }
        mutex = 1;
        empty++;
        sleep(1);
    }
}

int main(int argc, char *args[])
{
    unsigned long producer_thread_id[producer_num] = {};
    unsigned long consumer_thread_id[consumer_num] = {};
    pthread_t thread_pool[producer_num + consumer_num];

    for (int i = 0; i < producer_num; i++)
    {
        int err = pthread_create(&(producer_thread_id[i]), NULL, &producer_func, NULL);
        if (err != 0)
        {
            printf("\n生产者进程创建失败！\n");
        }
        else
        {
            thread_pool[i] = producer_thread_id[i];
            // printf("生产者进程创建成功～ id 为 %lu\n", producer_thread_id[i]);
        }
    }
    for (int i = 0; i < consumer_num; i++)
    {
        int err = pthread_create(&(consumer_thread_id[i]), NULL, &consumer_func, NULL);
        if (err != 0)
        {
            printf("\n消费者进程创建失败！\n");
        }
        else
        {
            thread_pool[i] = consumer_thread_id[i + producer_num];
            // printf("消费者进程创建成功～ id 为 %lu\n", consumer_thread_id[i]);
        }

        for (int i = 0; i < producer_num + consumer_num; i++)
        {
            if (pthread_join(thread_pool[i], NULL) == -1)
            {
                printf("线程 %lu 运行失败！\n", thread_pool[i]);
            }
        }
    }
    return 0;
}