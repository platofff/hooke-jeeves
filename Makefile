ifeq ($(origin CC), undefined)
   CC = cc
endif
CFLAGS = -lm -Wall -Wextra -Wpedantic -Werror -std=c99 -O3
TARGET = nearest_line_func
all: $(TARGET)

$(TARGET): src/hnj.c src/$(TARGET).c include/func.h
	$(CC) $(CFLAGS) -Iinclude -o $(TARGET) src/hnj.c src/$(TARGET).c
	strip $(TARGET)

clean:
	$(RM) $(TARGET)
