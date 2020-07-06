# 构建所有程序
all: te pc

# 构建生产者消费者程序
pc: producer_consumer.o 
	@# 因为用到了 semaphore.h 需要添加 -pthread 参数
	@gcc -pthread -o pc producer_consumer.o

# 编译生产者消费者源码
producer_consumer.o: producer_consumer.c
	@gcc -c producer_consumer.c

# 运行生产者消费者程序
run_pc: pc
	@./pc
	
# 构建线程示例程序
te: thread_example.o
	@gcc -pthread -o te thread_example.o

# 编译线程示例源码
thread_example.o: thread_example.c
	@gcc -c thread_example.c

# 运行线程示例程序
run_te: te
	@./te

# 定义一些伪目标
.PHONE: clean all
clean:
	@rm *.o

f_buffer.o: f_buffer.cpp
	g++ -o f_buffer.o f_buffer.cpp
