worker_ms_demo:worker_main.o worker_ms.o
				g++ worker_main.o worker_ms.o -o worker_ms_demo	`mysql_config --cflags --libs`
main.o:main.cpp
				g++ -c main.cpp `mysql_config --cflags --libs`
worker_ms.o:worker_ms.h worker_ms.cpp
				g++ -c worker_ms.cpp `mysql_config --cflags --libs`
