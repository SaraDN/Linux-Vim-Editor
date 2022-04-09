build:
	gcc editor.c -o editor -Wall -Im -g
run:
	./editor
clean:
	rm -rf p*.o
