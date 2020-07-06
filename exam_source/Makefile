pc: producer_consumer.o 
	@# 因为用到了 semaphore.h 需要添加 -pthread 参数
	@gcc -pthread -o pc producer_consumer.o

producer_consumer.o: producer_consumer.c
	@gcc -c producer_consumer.c

run_pc: pc
	@./pc
	

te: thread_example.o
	@gcc -pthread -o te thread_example.o

thread_example.o: thread_example.c
	@gcc -c thread_example.c

run_te: te
	@./te

clean:
	@rm pc producer_consumer.o