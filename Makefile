# Recursive wildcard
#
# Example:
#	$(call rwildcard,src,*.c *.h)
#	Finds all the .c and .h files in src
#
# Credits to https://stackoverflow.com/a/18258352
rwildcard = $(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

main = $(call rwildcard,.,*.c)

objmain = $(main:.c=.o)

CC = gcc
CFLAGS = -Wextra -Wall -O1
CLIBS = `sdl2-config --cflags --libs` -lSDL2_image

main: $(objmain)
	mkdir -p build && $(CC) -o build/$@ $^ -Wextra -O -Wall --enable-checking -g `sdl2-config --cflags --libs` -lSDL2_image

.PHONY: clean
clean:
	rm -f $(objmain) main
