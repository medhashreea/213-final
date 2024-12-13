CC := clang
CFLAGS := -o -fsanitize=address
TARGETS := window

all: $(TARGETS)

clean:
	rm -f $(TARGETS)

%: %.c
	@echo Compiling $<
	$(CC) $(CFLAGS) -o $@ $<
	@echo
