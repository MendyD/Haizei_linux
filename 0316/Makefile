CC = gcc
SHDIR = ./common
CFLAGS = -Wall -lpthread -lm -I $(SHDIR)
#CFLAGS = 形式


OBJS = master.o common.o 

all : pihealthd
	@echo "Finish!"

pihealthd : $(OBJS)
	@$(CC) -o $@ $(CFLAGS) $(OBJS)

#.o依赖于.c
$(OBJS) : %.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@
#伪目标防止原本有clean
.PHONY: clean

clean:
	@rm -fr *.o pihealthd
	@rm -fr $(SHDIR)/common.o
	@echo "Clean Done!"

