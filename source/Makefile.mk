
CXXFLAGS	+= -I$(PROJECT_DIR)/source
VPATH 	+=   $(PROJECT_DIR)/source

-include $(PROJECT_DIR)/source/app/Makefile.mk

OBJ += $(OBJ_DIR)/app.o
OBJ += $(OBJ_DIR)/main.o
