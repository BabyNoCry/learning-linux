.PHONY:all
all:Client Server

Client:Client.cc
	g++ -o $@ $^
Server:Server.cc
	g++ -o $@ $^
.PHONY:clean
clean:
	rm -f Server Client 
