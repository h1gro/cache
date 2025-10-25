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
-fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr

CXX = g++
LDFLAGS = -lgtest -lgtest_main -lpthread
BUILD   = build

lfu: src/LFU.cpp include/LFU.hpp
	$(CXX) $(CXXFLAGS) src/LFU.cpp -o $(BUILD)/lfu

lfu_tests: src/LFU_tests.cpp include/LFU.hpp
	$(CXX) $(CXXFLAGS) src/LFU_tests.cpp $(LDFLAGS) -o $(BUILD)/lfu_tests

lru: src/LRU.cpp include/LRU.hpp
	$(CXX) $(CXXFLAGS) src/LRU.cpp -o $(BUILD)/lru

lru_tests: src/LRU_tests.cpp include/LRU.hpp
	$(CXX) $(CXXFLAGS) src/LRU_tests.cpp $(LDFLAGS) -o $(BUILD)/lru_tests

lru_test: lru_tests
	./lru_tests

lfu_test: lfu_tests
	./lfu_tests

clean:
	rm -f lru_tests lru lfu_tests lfu *.o

.PHONY: test clean
