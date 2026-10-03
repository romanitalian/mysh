BIN = mysh

compile:
	clang main.c -o $(BIN)

cc:
	rm -f $(BIN) && make compile

r:
	make cc && ./$(BIN)
