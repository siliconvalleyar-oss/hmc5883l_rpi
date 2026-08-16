# ==============================================================================
# Makefile for Raspberry Pi HMC5883L SPI Application
# Target: bin/App (ARM native on Raspberry Pi)
# ==============================================================================

SHELL := /bin/bash

# Compiler and tools
CXX      ?= g++
AR       ?= ar
STRIP    ?= strip

# Compiler flags
CXXSTD   := c++17
WARNINGS := -Wall -Wextra -Wpedantic -Wshadow -Wformat=2
OPTIMIZE := -O2

# Architecture detection
ARCH     := $(shell uname -m)
ifeq ($(ARCH),x86_64)
    ARCH_FLAGS := -m64
    ARCH_MSG   := x86_64
else ifeq ($(ARCH),i686)
    ARCH_FLAGS := -m32
    ARCH_MSG   := "x86 (32-bit)"
else ifeq ($(ARCH),aarch64)
    ARCH_FLAGS :=
    ARCH_MSG   := "aarch64 (ARM 64-bit)"
else ifeq ($(ARCH),armv7l)
    ARCH_FLAGS :=
    ARCH_MSG   := "armv7l (ARM 32-bit)"
else ifeq ($(ARCH),armv6l)
    ARCH_FLAGS :=
    ARCH_MSG   := "armv6l (ARM 32-bit)"
else
    ARCH_FLAGS :=
    ARCH_MSG   := $(ARCH)
endif

# Cross-compilation support
ifneq ($(CROSS_COMPILE),)
    CXX := $(CROSS_COMPILE)g++
endif

# Directories
SRC_DIR   := src
INC_DIR   := include
OBJ_DIR   := obj
BIN_DIR   := bin
CONF_DIR  := config
DOCS_DIR  := docs

# Stub mode for desktop builds without bcm2835
USE_STUB  ?= 0
ifeq ($(USE_STUB),1)
    LIBS     := -lpthread
else
    LIBS     := -lbcm2835 -lpthread
endif

# Source files
SRCS      := $(shell find $(SRC_DIR) -name '*.cpp' -type f)
OBJS      := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

# Include paths
INCLUDES  := -I$(INC_DIR)

# Compiler and linker flags
CXXFLAGS  := $(WARNINGS) $(OPTIMIZE) $(ARCH_FLAGS) $(INCLUDES) -std=$(CXXSTD) -MMD -MP
LDFLAGS   := $(ARCH_FLAGS) $(LIBS)

# Add HAS_BCM2835 define based on stub mode
ifeq ($(USE_STUB),1)
    CXXFLAGS += -DHAS_BCM2835=0
else
    CXXFLAGS += -DHAS_BCM2835=1
endif

# Target executable
TARGET    := $(BIN_DIR)/App

# Phony targets
.PHONY: all clean distclean run install docs size check arch

# Default target
all: $(TARGET)

# Create directories
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

# Link executable
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) $^ $(LDFLAGS) -o $@
	@printf 'Built: %s (%s)\n' $(TARGET) '$(ARCH_MSG)'

# Compile source files to object files (mirroring src/ structure)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean targets
clean:
	rm -rf $(OBJ_DIR)
	@echo "Cleaned object files."

distclean: clean
	rm -f $(TARGET)
	@echo "Cleaned binary."

# Run the application (requires root)
run: all
	@echo "Running $(TARGET)..."
	sudo $(TARGET)

# Install dependencies
install:
	@echo "Installing dependencies..."
	sudo apt-get update
	sudo apt-get install -y g++ make libbcm2835-dev

# Show architecture info
arch:
	@echo "Host architecture: $(ARCH_MSG)"
	@echo "Compiler: $(CXX)"
	@echo "Flags: $(ARCH_FLAGS)"

# Show binary size
size: $(TARGET)
	@echo "Binary size:"
	ls -lh $(TARGET)

# Dependency files
-include $(OBJS:.o=.d)
