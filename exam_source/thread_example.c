#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

// 创建两个线程以供使用
pthread_t tid[2];

// 多线程要执行的函数，args为待传递进来的参数列表
void *thread_function(void *args)
{
    // 线程 id 使用 unsigned long 类型来表述
    unsigned long i = 0;
    // 获取当前线程 id
    pthread_t id = pthread_self();
    // 对参数格式化输出
    printf("传进来的参数为：%s", (char *)args);
    if (pthread_equal(id, tid[0]))
    {
        printf("\n 第一个线程正在执行，id为 %ld \n", id);
    }
    else
    {
        printf("\n 第二个线程正在执行，id为 %ld \n", id);
    }
    return NULL;
}

int main(int argc, char *args)
{
    int i = 0;
    int err;

    for (; i < 2; i++)
    {
        err = pthread_create(&(tid[i]), NULL, &thread_function, "hello,name");
        if (err != 0)
        {
            printf("\n创建线程失败了！ [%s]", strerror(err));
        }
        else
        {
            printf("\n创建线程成功了，id 为 [%ld]\n", tid[i]);
        }
    }

    sleep(5);
    return 0;
}