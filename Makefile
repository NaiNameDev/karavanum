CXX = g++
STD = -std=c++20
FLGS = -O3 -flto
DEF = -DGLM_FORCE_INTRINSICS -DGLM_FORCE_DEFAULT_ALIGNED_GENTYPES -DGLM_ENABLE_EXPERIMENTAL
LIBS = -I./include -lglfw ./lib/glad/libglad.a
SRC = main.cpp src/engine/*.cpp
PREC_PATH = ./include/engine/precompile_headers.hpp

a.elf: main.cpp ./lib/glad/libglad.a
	$(CXX) $(STD) $(FLGS) $(DEF) $(SRC) -include $(PREC_PATH) -o a.elf $(LIBS)

.PHONY = ctdbg gen_prec

ctdbg: main.cpp ./lib/glad/libglad.a
	$(CXX) $(STD) $(FLGS) $(DEF) $(SRC) -include $(PREC_PATH) -o a.elf $(LIBS)
	./a.elf
	rm a.elf

gen_prec: ./include/engine/ ./lib/glad/
	echo "#pragma once" > ./include/engine/precompile_headers.hpp
	grep -r "#include" | awk -F':' '{print $$2}' | grep -vE "\"|engine|win" | tr -d "*" | tr -d " " | grep ^[#] | sort -u >> $(PREC_PATH)
	g++ ./include/glad/glad.c -c -o ./lib/glad/libglad.a -I./include/
	$(CXX) $(STD) $(FLGS) $(DEF) -x c++-header $(PREC_PATH) -I./include
