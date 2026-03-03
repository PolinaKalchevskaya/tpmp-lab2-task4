CC = gcc
CFLAGS = -I./include -Wall -Wextra
TARGET = bin/task4
OBJDIR = obj
SRCDIR = src
INCDIR = include

SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SOURCES))

all: $(TARGET)

$(TARGET): $(OBJECTS) | bin
	$(CC) $(OBJECTS) -o $@
	@echo "Build complete: $(TARGET)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCDIR)/*.h | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

bin:
	mkdir -p bin

clean:
	rm -f $(OBJDIR)/*.o $(TARGET)
	@echo "Clean complete"

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
