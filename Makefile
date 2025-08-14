CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
DEBUG_FLAGS = -g -O0 -DDEBUG
RELEASE_FLAGS = -O3
TARGET = primal

all: $(TARGET)

debug: CXXFLAGS += $(DEBUG_FLAGS)
debug: $(TARGET)

release: CXXFLAGS += $(RELEASE_FLAGS)
release: $(TARGET)

$(TARGET): main.cpp src/alignment_result.cpp src/iupac_handler.cpp src/scoring.cpp src/traceback.cpp src/local_aligner_core.cpp
	$(CXX) $(CXXFLAGS) -Iinclude -o $(TARGET) main.cpp src/alignment_result.cpp src/iupac_handler.cpp src/scoring.cpp src/traceback.cpp src/local_aligner_core.cpp

clean:
	rm -f $(TARGET) *.o

run: $(TARGET)
	./$(TARGET)

debug-run: debug
	gdb ./$(TARGET)

install-deps-mac:
	brew install gcc make

install-deps-ubuntu:
	sudo apt-get update
	sudo apt-get install build-essential gdb

install: $(TARGET)
	@echo "Installing $(TARGET) to $(DESTDIR)$(PREFIX)/bin..."
	@mkdir -p $(DESTDIR)$(PREFIX)/bin
	@cp $(TARGET) $(DESTDIR)$(PREFIX)/bin/
	@chmod +x $(DESTDIR)$(PREFIX)/bin/$(TARGET)
	@echo "Installation complete"

uninstall:
	@echo "Removing $(TARGET) from $(DESTDIR)$(PREFIX)/bin..."
	@rm -f $(DESTDIR)$(PREFIX)/bin/$(TARGET)
	@echo "Uninstallation complete"

ifeq ($(OS),Windows_NT)
    PREFIX ?= /usr/local
else ifeq ($(shell uname),Darwin)
    PREFIX ?= /usr/local
else
    PREFIX ?= /usr/local
endif

.PHONY: all debug release clean run debug-run install-deps-mac install-deps-ubuntu install uninstall
