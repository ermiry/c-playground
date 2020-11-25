TARGETDIR   := bin

all: directories
	gcc gnu.c -o ./bin/gnu
	gcc array.c -o ./bin/array
	gcc threads.c -l pthread -o ./bin/threads
	gcc wait.c -l pthread -o ./bin/wait
	gcc conds.c dlist.c -l pthread -o ./bin/cond
	gcc gray.c -lm -o ./bin/gray
	gcc root.c -lm -o ./bin/root
	gcc fetch.c -l curl -o ./bin/fetch
	gcc sanitize.c -l curl -o ./bin/sanitize

clean:
	@$(RM) -rf $(BUILDDIR) @$(RM) -rf $(TARGETDIR)

directories:
	@mkdir -p $(TARGETDIR)

.PHONY: all clean