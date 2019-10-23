APUE := $(shell dirname $(shell pwd))

INCS=$(APUE)/apue.3e/include
LIBS=-L$(APUE)/apue.3e/lib -lapue
CFLAGS=-I$(INCS) $(LIBS)

objs=devzero shm slock

all : $(objs)
	mv $(objs) $(APUE)/bin

# %.o : %.c

clean:
	cd $(APUE)/bin && rm $(objs)
