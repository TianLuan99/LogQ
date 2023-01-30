CC = g++ -std=c++11

FLAGS = -O2 -Wall -Wextra

all: main_server main_client

main_server: main_server.cpp qserver/qserver.cc
	$(CC) $(FLAGS) main_server.cpp qserver/qserver.cc -o main_server

main_client: main_client.cpp qclient/qclient.cc
	$(CC) $(FLAGS) main_client.cpp qclient/qclient.cc -o main_client

clean:
	rm -rf main_server main_client