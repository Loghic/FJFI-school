TARGET = main
OBJS = $(patsubst %.cpp,%.o,$(wildcard *.cpp))
CFLAGS +=-std=c++17 -pedantic -Wall
CFLAGS += -O2


bin: $(TARGET)

$(OBJS):  %.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS) 
	$(CXX) $(OBJS) $(LDFLAGS) -o $@

	rm -rf $(OBJS)

# clean_obj:
# 	rm -rf $(OBJS)
clean:
	rm -rf $(OBJS) $(TARGET)