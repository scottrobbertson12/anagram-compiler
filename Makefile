PROGRAM_NAME=$(shell [ -r config/program ] && cat config/program)
LIBRARY_NAME=$(shell [ -r config/library ] && cat config/library)
INCLUDE_DIR=include
COMP_LIBS=$(shell [ -r config/libs ] && cat config/libs)

SOURCES=$(wildcard src/**/*.c src/*.c)
OBJECTS=$(patsubst src/%.c,obj/%.o,$(SOURCES))

CFLAGS=-I$(INCLUDE_DIR) -std=c11
DEBUG_CFLAGS=-Wall -Wextra -g -I$(INCLUDE_DIR) $(CFLAGS) -pedantic -coverage
RELEASE_CFLAGS=-O3 $(CFLAGS)
LDFLAGS=$(patsubst %,-l%,$(COMP_LIBS))

all: obj $(PROGRAM_NAME) $(LIBRARY_NAME)

obj:
	mkdir obj

$(PROGRAM_NAME): $(OBJECTS) main/main.c
	@gcc $(DEBUG_CFLAGS) -o $@ $^ $(LDFLAGS)
	@echo LINK $@

release-prog: $(OBJECTS) main/main.c
	@gcc $(RELEASE_CFLAGS) -o $(PROGRAM_NAME) $^ $(LDFLAGS)
	@echo RELEASE $(PROGRAM_NAME)


$(LIBRARY_NAME): $(OBJECTS) main/lib.c
	@gcc $(CFLAGS) -shared -fPIC -o lib$@.so $^
	@echo LINK $@

test: $(OBJECTS) main/test.c
	@gcc $(CFLAGS) -o $@ $^
	@echo LINK $@

obj/%.o: src/%.c
	@mkdir $(dirname $@) -pv 2>/dev/null || true
	@gcc $(CFLAGS) -g -fPIC -c -o $@ $^
	@echo CC $^

clean: 
	@rm -rf $(PROGRAM_NAME) $(LIBRARY_NAME) $(OBJECTS)
	@echo CLEAN
	
memcheck: $(PROGRAM_NAME)
	@valgrind ./$(PROGRAM_NAME)
