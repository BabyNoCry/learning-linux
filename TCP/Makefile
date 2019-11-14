.PHONY:all
all:Client Server
CC=g++

Client:Client.cc
	$(CC) -o $@ $^
erver:Server.cc
	$(CC) -o $@ $^

.PHONY:clean
clean:
	rm -f Server Client 
