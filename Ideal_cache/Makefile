.PHONY: all clean release debug

CONFIG ?= debug

CXX = g++
BUILD = build

CXXFLAGS := -D _DEBUG -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations \
-Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts \
-Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal \
-Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op \
-Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self \
-Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 \
-Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override \
-Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast \
-Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast \
-Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow \
-flto-odr-type-merging -fno-omit-frame-pointer -Wstack-usage=8192 -pie -fPIE -Werror=vla \
-fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero, \
integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr

RELEASE_CXXFLAGS = -std=c++17 -O2 -Wall -Wextra -DNDEBUG

ifeq ($(CONFIG), release)
    CXXFLAGS  = $(RELEASE_CXXFLAGS)
    BUILD_DIR = $(BUILD)/release
else
    CXXFLAGS  = $(DEBUG_CXXFLAGS)
    BUILD_DIR = $(BUILD)/debug
endif

LDFLAGS = -lgtest -lgtest_main -lpthread

all: ideal_cache ideal_cache_tests

ideal_cache: src/Ideal_cache.cpp include/Ideal_cache.hpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) src/Ideal_cache.cpp -o $(BUILD_DIR)/ideal_cache

ideal_cache_tests: src/Ideal_cache_tests.cpp include/Ideal_cache.hpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) src/Ideal_cache_tests.cpp $(LDFLAGS) -o $(BUILD_DIR)/ideal_cache_tests

debug:
	$(MAKE) CONFIG=debug

release:
	$(MAKE) CONFIG=release

clean:
	rm -rf $(BUILD)

