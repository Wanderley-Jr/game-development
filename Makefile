rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

SRCS := $(call rwildcard,src/,*.cpp)

all:
	g++ -lSDL2_image -g -o game $(SRCS) -std=c++23 -I../my-lib/include/ `pkg-config --cflags --libs sdl2 SDL2_image`
