CC=gcc
CFLAGS=-O3 -std=c99 -w
TARGET=qxcrypt
all: $(TARGET) $(KEYGEN)

$(TARGET): qxcrypt.c
	$(CC) qxcrypt.c $(CFLAGS) -o $(TARGET)

clean:
	$(RM) $(TARGET)
