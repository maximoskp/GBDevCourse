GBDK = ../../tools/gbdk_linux64/gbdk

CC = $(GBDK)/bin/lcc

SRC = main.c
ROM = build/game.gb

all: $(ROM)

$(ROM): $(SRC)
	mkdir -p build
	$(CC) -o $(ROM) $(SRC)

run: $(ROM)
	java -jar ../../tools/emulators/Emulicious/Emulicious.jar $(ROM)

clean:
	rm -rf build
