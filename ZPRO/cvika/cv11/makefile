TARGET = main
OBJS = $(patsubst %.cpp,%.o,$(wildcard *.cpp))
OBJSC = $(patsubst %.o,%.cpp,$(wildcard *.cpp))
CFLAGS +=-std=c++17 -pedantic -Wall
CFLAGS += -O2

	
bin: $(TARGET)
	@echo "Build was finished succesfully!"
	@echo "Running file $(TARGET):"
	@echo "\e[1;35m"
	@./$(TARGET)

$(OBJS):  %.o: %.cpp
	@clear
	@echo "Building..."	 
	@$(CXX) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS) 
	@$(CXX) $(OBJS) $(LDFLAGS) -o $@

	@rm -rf $(OBJS)

# clean_obj:
# 	rm -rf $(OBJS)
clean:
	@clear
	@rm -rf $(OBJS) $(TARGET)
	@echo "\e[1;33mBuild was cleaned!"