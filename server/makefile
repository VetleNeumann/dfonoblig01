objects = server.o utils.o

oblig_server : $(objects)
	cc -o oblig_server $(objects)

server.o: defs.h

.PHONY : clean
clean :
	rm oblig_server $(objects)