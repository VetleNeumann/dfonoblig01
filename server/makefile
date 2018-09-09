objects = server.o utils.o

server : $(objects)
	cc -o server $(objects)

server.o: defs.h

.PHONY : clean
clean :
	rm server $(objects)