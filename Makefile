# Компилятор и флаги
CXX := g++
CXXFLAGS := -std=c++17 -O0 -Wall -Wextra -Weffc++ -Werror=vla \
            -D_DEBUG -ggdb3 -fstack-protector -fno-omit-frame-pointer \
            -pie -fPIE

SANITIZER_FLAGS := -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr

# Исходные файлы
SRCS := akinator.cpp akinator_func.cpp stack_operations.cpp stack_protection.cpp dump.cpp file_work.cpp
OBJS := $(SRCS:.cpp=.o)

# Имя исполняемого файла
TARGET := akinator

# Правило по умолчанию
all: $(TARGET)

# Сборка исполняемого файла
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(CXXFLAGS) $(SANITIZER_FLAGS)

# Компиляция объектных файлов
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Очистка
clean:
	rm -f $(OBJS) $(TARGET)

# Пересборка
rebuild: clean all

# Отладочная информация
debug:
	@echo "Sources: $(SRCS)"
	@echo "Objects: $(OBJS)"
	@echo "Target: $(TARGET)"

.PHONY: all clean rebuild debug