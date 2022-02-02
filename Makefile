
CC = g++
CFILES = $(shell find src/ -type f -name '*.cpp')
OFILES = $(CFILES:.cpp=.o)

TARGET = build/rci

.PHONY = clean test all

$(TARGET): $(OFILES)
	@echo [LD] $(TARGET)
	@$(CC) $(OFILES) -o $@

%.o: %.cpp
	@echo [CC] $@
	@$(CC) -I include/ -c $< -o $@

clean:
	@echo [CLEAN]
	@rm $(OFILES) $(TARGET)

all: clean $(TARGET)

