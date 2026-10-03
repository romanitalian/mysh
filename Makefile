# Output binary name
BIN = mysh

.PHONY: all compile clean test run cc r

# Default: build the shell
all: compile

# Compile main.c into $(BIN)
compile:
	clang main.c -o $(BIN)

# Force rebuild (remove binary, then compile)
cc:
	rm -f $(BIN) && $(MAKE) compile

# Remove build artifacts
clean:
	rm -f $(BIN) mm

# Smoke test: build and run the example script
test: compile
	./$(BIN) examples/hello.sh

# Build and start interactive shell
run: compile
	./$(BIN)

# Force rebuild, then start interactive shell
r: cc
	./$(BIN)
