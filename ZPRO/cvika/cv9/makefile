TARGET = main
OBJS = $(patsubst %.cpp,%.o,$(wildcard *.cpp))
CFLAGS +=-std=c++17 -pedantic -Wall
CFLAGS += -O2
CC = g++

bin: $(TARGET)

$(OBJS):  %.o: %.cpp
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS) 
	$(CC) $(OBJS) $(LDFLAGS) -o $@

	rm -rf $(OBJS)

# clean_obj:
# 	rm -rf $(OBJS)
clean:
	rm -rf $(OBJS) $(TARGET)