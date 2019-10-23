APUE := $(shell dirname $(shell pwd))

INCS=$(APUE)/apue.3e/include
LIBS=-L$(APUE)/apue.3e/lib -lapue
CFLAGS=-I$(INCS) $(LIBS) -g

objs=pollmsg sendmsg bindunix

all : $(objs)
	mv $(objs) $(APUE)/bin

# %.o : %.c

clean:
	cd $(APUE)/bin && rm $(objs)
