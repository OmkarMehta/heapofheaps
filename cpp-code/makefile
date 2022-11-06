SRC_DIR = .

SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,%.o,$(SRC_FILES))
EXE = main.exe


$(info OBJS = "$(OBJS)")

# OBJS = hello-world.o

include ../generic.mk
# Directory-specific rules: