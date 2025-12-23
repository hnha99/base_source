VERSION=1.0.0
NAME_MODULE = demo

PROJECT_DIR = $(PWD)
OBJ_DIR=${PROJECT_DIR}/build

CROSS_COMPILE ?= 
CXX = $(CROSS_COMPILE)g++
CC = $(CROSS_COMPILE)gcc
AR = $(CROSS_COMPILE)ar
STRIP = $(CROSS_COMPILE)strip

-include $(PROJECT_DIR)/Makefile.conf
-include $(PROJECT_DIR)/Makefile.libs.conf
-include $(PROJECT_DIR)/source/Makefile.mk

OPTIMIZE = -Wall -g -s -O2
CXXFLAGS += $(FLAG_HAVE) $(OPTIMIZE)
LDFLAGS += -Wall -Wl,-gc-sections -lpthread -lm -lrt -lstdc++

.PHONY : all create clean install

all: create $(OBJ_DIR)/$(NAME_MODULE)
	@echo $(GREEN) "--------- Project build $(NAME_MODULE) ---------" $(NONE)

create:
	@echo Create build dir...
	mkdir -p $(OBJ_DIR)

clean:
	@echo $(YELLOW) ---------- CLEAN PROJECT ---------- $(NONE)
	@rm -rf $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c
	@echo $(BLUE) CC $< $(NONE)
	$(CC) -c -o $@ $< $(CXXFLAGS)

$(OBJ_DIR)/%.o: %.cpp
	@echo $(BLUE) CXX $< $(NONE)
	$(CXX) -c -o $@ $< $(CXXFLAGS) -std=c++11

$(OBJ_DIR)/$(NAME_MODULE): $(OBJ)
	@echo $(BLUE) ---------- BUILD PROJECT ---------- $(NONE)
	$(CXX) -o $@ $^ $(LDFLAGS) $(LDLIBS)
	@echo $(GREEN)"-- Compiling '$(NAME_MODULE)' done --"$(NONE)


