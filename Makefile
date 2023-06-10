CC = g++
CFLAGS = -Wall -Wextra -std=c++17 -Ofast
LIBS = -lm -lpthread -lX11

SRCS = main.cc 
OBJS = $(SRCS:.cc=.o)
EXEC = a

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC) $(LIBS)

%.o: %.cc prewitt_filter.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	echo rm -f $(OBJS) $(EXEC)

