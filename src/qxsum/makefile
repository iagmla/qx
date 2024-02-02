CC=gcc
CFLAGS=-O3 -std=c99 -w
TARGET=qxsum
all: $(TARGET) $(KEYGEN)

$(TARGET): qx_sum.c
	$(CC) qx_sum.c $(CFLAGS) -o $(TARGET)

clean:
	$(RM) $(TARGET)
