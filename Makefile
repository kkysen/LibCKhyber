CC := gcc

LTO = -flto
OPT := -O3 -march=native $(LTO)
WARNINGS := all error extra
NO_WARNINGS := unused-parameter unused-function
MACROS := _POSIX_C_SOURCE=201810L _XOPEN_SOURCE=700 _DEFAULT_SOURCE=1
DMACROS := $(MACROS:%=-D %)

CPPFLAGS := $(INC_FLAGS) $(DMACROS) -MMD -MP
CFLAGS := -std=c11 -g -ggdb $(WARNINGS:%=-W%) $(NO_WARNINGS:%=-Wno-error=%) $(OPT) $(DMACROS)

LFLAGS := -g $(LTO)
LDFLAGS := -lm -lbfd

AR := gcc-ar
RANLIB := gcc-ranlib

MKDIR_P := mkdir -p



MAIN := Khyber
EXE := LibCKhyber
LIB := Khyber

BIN_DIR := bin
SRC_DIR := src
TEST_DIR := test

TEST_ARGS :=

EXE := $(BIN_DIR)/$(MAIN)
TEST := $(BIN_DIR)/test$(MAIN)
LIB := $(BIN_DIR)/lib$(MAIN).a

SRCS := $(shell find $(SRC_DIR) -name *.cpp -or -name *.c -or -name *.s)
OBJS := $(SRCS:$(SRC_DIR)%=$(BIN_DIR)%.o)
TEST_OBJS := $(filter $(BIN_DIR)/$(TEST_DIR)/%,$(OBJS))
LIB_OBJS := $(filter-out $(TEST_OBJS),$(OBJS))
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIR) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

.PHONY: all
all: $(EXE) $(TEST) $(LIB)

.PHONY: run
run: $(EXE)
	./$(EXE)

.PHONY: test
test: $(TEST)
	./$(TEST) $(TEST_ARGS)

.PHONY: valgrind
valgrind: $(TEST)
	valgrind --leak-check=full --show-leak-kinds=all ./$(TEST) $(TEST_ARGS)

.PHONY: lib
lib: $(LIB)

.PHONY: debug
debug:
	echo $(TEST_OBJS)
	echo $(LIB_OBJS)

$(EXE): $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $@ $(LDFLAGS)

$(TEST): $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $@ $(LDFLAGS)

$(LIB): $(LIB_OBJS)
	# TODO filter out test files from OBJS
	$(AR) rc $(LIB) $^
	$(RANLIB) $(LIB)

# assembly
$(BIN_DIR)/%.s.o: $(SRC_DIR)/%.s
	$(MKDIR_P) $(dir $@)
	$(AS) $(ASFLAGS) -c $< -o $@

# c source
$(BIN_DIR)/%.c.o: $(SRC_DIR)/%.c
	$(MKDIR_P) $(dir $@)
	$(CPP) $(CPPFLAGS) $< -MF $(@:.o=.d) -MT $@ > /dev/null
#	$(filter-out -I$(<D),$(CPPFLAGS))
	$(CC) $(CFLAGS) -c $< -o $@

# c++ source
$(BIN_DIR)/%.cpp.o: $(SRC_DIR)/%.cpp
	$(MKDIR_P) $(dir $@)
	$(CPP) $(INC_FLAGS) -MMD -MP $< -MF $(@:.o=.d) -MT $@ > /dev/null
	$(CXX) $(CXXFLAGS) -c $< -o $@


.PHONY: clean
clean:
	$(RM) -r $(BIN_DIR)

-include $(DEPS)
