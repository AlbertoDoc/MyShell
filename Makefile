TARGET_EXEC := myshell

CC = gcc

OBJS = errors.o systemfunctions.o myshell.o

.o:	.c $*.h
	$(CC) -c $*.c

all:	$(TARGET_EXEC)

$(TARGET_EXEC):	$(OBJS)
	$(CC) $^ -o $@

.PHONY:	clean all

clean:
	$(RM) *.o $(TARGET_EXEC)