MAIN := Khyber



CC := gcc

LTO := -flto
OPT := -O0 -march=native $(LTO)
WARNINGS := all error extra
NO_ERRORS := unused-parameter unused-function
MACROS := _POSIX_C_SOURCE=201810L _XOPEN_SOURCE=700 _DEFAULT_SOURCE=1
DMACROS := $(MACROS:%=-D %)

INC_DIRS := .
INC_FLAGS := $(addprefix -I,$(INC_DIRS))
CPPFLAGS := ${INC_FLAGS} $(DMACROS) -MMD -MP
CFLAGS := -std=c11 -g -ggdb $(WARNINGS:%=-W%) $(NO_ERRORS:%=-Wno-error=%) $(OPT) $(DMACROS) ${INC_FLAGS}

LFLAGS := -g $(LTO)
LDFLAGS := -lm -lbfd

AR := gcc-ar
RANLIB := gcc-ranlib

MKDIR_P := mkdir -p

VALGRIND := valgrind --leak-check=full --show-leak-kinds=all



BIN_DIR := bin
SRC_DIR := src
TEST_DIR := test

TEST_ARGS :=

EXE := $(BIN_DIR)/$(MAIN)
TEST := $(BIN_DIR)/$(MAIN).test
LIB := $(BIN_DIR)/lib$(MAIN).a

SRCS := $(shell find $(SRC_DIR) -name "*.cpp" -or -name "*.c" -or -name "*.s")
OBJS := $(SRCS:$(SRC_DIR)%=$(BIN_DIR)%.o)
TEST_OBJS := $(filter $(BIN_DIR)/$(TEST_DIR)/%,$(OBJS))
LIB_OBJS := $(filter-out $(TEST_OBJS),$(OBJS))
DEPS := $(OBJS:.o=.d)

.PHONY: all
all: $(LIB) $(TEST) $(EXE)

.PHONY: debug
debug:
	echo $(INC_DIRS)

.PHONY: lib
lib: $(LIB)

.PHONY: test
test: $(TEST)
	./$(TEST) $(TEST_ARGS)

.PHONY: valgrind
valgrind: $(TEST)
	$(VALGRIND) ./$(TEST) $(TEST_ARGS)

.PHONY: run
run: $(EXE)
	./$(EXE)

$(LIB): $(LIB_OBJS)
	$(AR) rc $(LIB) $^
	$(RANLIB) $(LIB)

$(TEST): $(LIB) $(TEST_OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $@ $(LDFLAGS) -L$(BIN_DIR) -l$(MAIN)

$(EXE): $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $@ $(LDFLAGS)

# assembly
$(BIN_DIR)/%.s.o: $(SRC_DIR)/%.s
	$(MKDIR_P) $(dir $@)
	$(AS) $(ASFLAGS) -c $< -o $@

# c source
$(BIN_DIR)/%.c.o: $(SRC_DIR)/%.c
	$(MKDIR_P) $(dir $@)
	$(CPP) $(CPPFLAGS) $< -MF $(@:.o=.d) -MT $@ > /dev/null
	$(CC) $(CFLAGS) -c $< -o $@

# c++ source
$(BIN_DIR)/%.cpp.o: $(SRC_DIR)/%.cpp
	$(MKDIR_P) $(dir $@)
	$(CPP) $(INC_FLAGS) -MMD -MP $< -MF $(@:.o=.d) -MT $@ > /dev/null
	$(CXX) $(CXXFLAGS) -c $< -o $@


.PHONY: clean
clean:
ifeq ($(BIN_DIR), $(SRC_DIR))
	$(RM) $(OBJS) $(DEPS) $(EXE) $(TEST) $(LIB)
else
	$(RM) -r $(BIN_DIR)
endif

-include $(DEPS)
