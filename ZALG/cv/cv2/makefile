TARGET = main
OBJS = $(patsubst %.cpp,%.o,$(wildcard *.cpp))
OBJSC = $(patsubst %.o,%.cpp,$(wildcard *.cpp))
CFLAGS +=-std=c++17 -pedantic -Wall
CFLAGS += -O2

	
bin: $(TARGET)
	@echo "Build was finished succesfully!"
	@echo "Running file $(TARGET):"
	@echo "\033[0m"
	@echo "\033[1;35m"
	@./$(TARGET)

$(OBJS):  %.o: %.cpp
	@clear
	@echo "\033[1;34m"
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
	@echo "\033[1;33mBuild was cleaned!"