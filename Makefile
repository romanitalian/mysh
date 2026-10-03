BIN = mysh

.PHONY: all compile clean test run cc r

all: compile

compile:
	clang main.c -o $(BIN)

cc:
	rm -f $(BIN) && $(MAKE) compile

clean:
	rm -f $(BIN) mm

test: compile
	./$(BIN) examples/hello.sh

run: compile
	./$(BIN)

r: cc
	./$(BIN)
