hdrs = ipc.h
opts = -g -c
p_src = producer.c ipc.c
p_obj = producer.o ipc.o
a_src = haveA.c ipc.c
a_obj = haveA.o ipc.o
b_src = haveB.c ipc.c
b_obj = haveB.o ipc.o
c_src = haveC.c ipc.c
c_obj = haveC.c ipc.o
all:	haveA	haveB	haveC producer
haveA:		$(a_obj)
	gcc $(a_obj) -o haveA
haveA.o: 	$(a_src) $(hdrs)
	gcc $(opts) $(a_src) -lrt
haveB:		$(b_obj)
	gcc $(b_obj) -o haveB
haveB.o: 	$(b_src) $(hdrs)
	gcc $(opts) $(b_src) -lrt
haveC:		$(c_obj)
	gcc $(c_obj) -o haveC
haveC.o: 	$(c_src) $(hdrs)
	gcc $(opts) $(c_src) -lrt
producer: 	$(p_obj)
	gcc $(p_obj) -o producer
producer.o: 	$(p_src) $(hdrs)
	gcc $(opts) $(p_src) -lrt
clean:
	rm haveA haveB haveC producer *.o 

