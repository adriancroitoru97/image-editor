CC=gcc
CFLAGS=-Wall -Wextra -std=c99

TARGETS=image_editor

build: $(TARGETS)

image_editor: image_editor.c functions.c
	$(CC) $(CFLAGS) image_editor.c functions.c -o image_editor

clean:
	rm -f $(TARGETS)