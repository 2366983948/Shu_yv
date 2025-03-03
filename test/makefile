# 定义编译器
CXX = g++

# 定义编译选项
CXXFLAGS = -Wall -g

# 定义目标文件
TARGET = myprogram

# 定义源文件
SRCS = main.cpp

# 定义目标文件
OBJS = $(SRCS:.cpp=.o)

# 默认目标
all: $(TARGET)

# 链接目标文件生成可执行文件
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# 编译源文件生成目标文件
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 清理生成的文件
clean:
	rm -f $(OBJS) $(TARGET)