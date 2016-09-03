CC := g++-4.8
FLAGS := -std=c++11 -w -g
INC_DIR := include
SRC_DIR := src
BUILD_DIR := build
BIN_DIR := bin
DATA_DIR := data
INCLUDE := -I./$(INC_DIR)

$(BIN_DIR)/main: $(BUILD_DIR)/AgendaUI.o $(BUILD_DIR)/AgendaService.o $(BUILD_DIR)/Storage.o $(BUILD_DIR)/Date.o $(BUILD_DIR)/Meeting.o $(BUILD_DIR)/User.o $(BUILD_DIR)/Agenda.o
	@mkdir -p $(BIN_DIR)
	$(CC) $(FLAGS) $(INCLUDE) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $(FLAGS) $(INCLUDE) -c -o $@ $<


clean:
	@rm -f *.o
	@rm -f *.gch
	@rm -f main
