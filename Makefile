rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

SRCS := $(call rwildcard,src/,*.cpp)
GCC_FLAGS := -std=c++23
INCLUDE := -I./src/ -I../my-lib/include/
LIBS := SDL2 SDL2_image SDL2_ttf SDL2_mixer

all:
	g++ -o game $(SRCS) $(INCLUDE) $(GCC_FLAGS) -g `pkg-config --cflags --libs $(LIBS)`

windows:
	g++ -o game.exe $(SRCS) $(INCLUDE) $(GCC_FLAGS) -static `pkg-config --cflags --static --libs $(LIBS)`