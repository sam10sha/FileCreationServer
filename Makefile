CC	= gcc
WALL	= -ansi -Wall

SRC_DIR	= src
OBJ_DIR	= obj
LIB_DIR	= lib
BIN_DIR	= bin

CLIENT		= $(BIN_DIR)/client
LIBCREATOR_SO	= $(LIB_DIR)/libCreator.so
CLIENT_CREATE_O	= $(OBJ_DIR)/client_create.o
CLIENT_CREATE_H = $(SRC_DIR)/client_create.h
CLIENT_CREATE_C	= $(SRC_DIR)/client_create.c
MAIN_C		= $(SRC_DIR)/main.c

RPATH	= .:../lib:lib




client: $(CLIENT)

$(CLIENT): $(LIBCREATOR_SO) $(MAIN_C) | $(BIN_DIR)
	$(CC) $(MAIN_C) -Llib -lCreator -o $@ $(WALL) -Wl,-rpath,$(RPATH)

$(LIBCREATOR_SO): $(CLIENT_CREATE_O) | $(LIB_DIR)
	$(CC) -shared $^ -o $@

$(CLIENT_CREATE_O): $(CLIENT_CREATE_H) $(CLIENT_CREATE_C) | $(OBJ_DIR)
	$(CC) -c $(CLIENT_CREATE_C) -o $@ $(WALL) -fPIC


$(SRC_DIR):
	mkdir -p $@

$(OBJ_DIR):
	mkdir -p $@

$(LIB_DIR):
	mkdir -p $@

$(BIN_DIR):
	mkdir -p $@


clean:
	rm -f $(OBJ_DIR)/*.o $(LIB_DIR)/*.so $(BIN_DIR)/client
