BUILDDIR    := objs
TARGETDIR   := bin

all: directories
	gcc gnu.c -o ./bin/gnu
	gcc array.c -o ./bin/array
	gcc threads.c -l pthread -o ./bin/threads
	gcc conds.c dlist.c -l pthread -o ./bin/cond

clean:
	@$(RM) -rf $(BUILDDIR) @$(RM) -rf $(TARGETDIR)

directories:
	@mkdir -p $(TARGETDIR)
	@mkdir -p $(BUILDDIR)

.PHONY: all clean