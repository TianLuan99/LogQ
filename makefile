CC = g++ -std=c++11

FLAGS = -O2 -Wall -Wextra

all: main_server main_client

main_server: main_server.cpp qserver/server.cc
	$(CC) $(FLAGS) main_server.cpp qserver/server.cc -o main_server

main_client: main_client.cpp qclient/client.cc
	$(CC) $(FLAGS) main_client.cpp qclient/client.cc -o main_client

clean:
	rm -rf main_server main_client