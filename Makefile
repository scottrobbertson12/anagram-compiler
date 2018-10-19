PROGRAM_NAME=$(shell [ -r config/program ] && cat config/program)
LIBRARY_NAME=$(shell [ -r config/library ] && cat config/library)
INCLUDE_DIR=include
COMP_LIBS=$(shell [ -r config/libs ] && cat config/libs)

SOURCES=$(wildcard src/**/*.c src/*.c)
OBJECTS=$(patsubst src/%.c,obj/%.o,$(SOURCES))

CFLAGS=-Wall -g -I$(INCLUDE_DIR)
LDFLAGS=$(patsubst %,-l%,$(COMP_LIBS))

all: $(PROGRAM_NAME) $(LIBRARY_NAME)

$(PROGRAM_NAME): $(OBJECTS) main/main.c
	@gcc $(CFLAGS) -o $@ $^ $(LDFLAGS)
	@echo LINK $@

$(LIBRARY_NAME): $(OBJECTS) main/lib.c
	@gcc $(CFLAGS) -shared -fPIC -o lib$@.so $^
	@echo LINK $@

test: $(OBJECTS) main/test.c
	@gcc $(CFLAGS) -o $@ $^
	@echo LINK $@

obj/%.o: src/%.c
	@mkdir $(dirname $@) 2>/dev/null || true
	@gcc $(CFLAGS) -fPIC -c -o $@ $^
	@echo CC $^

clean: 
	@rm -rf $(PROGRAM_NAME) $(LIBRARY_NAME) $(OBJECTS)
	@echo CLEAN
	
memcheck: $(PROGRAM_NAME)
	@valgrind ./$(PROGRAM_NAME)
