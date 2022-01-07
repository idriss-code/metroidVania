program_CXX_SRCS = $(wildcard *.cpp) $(wildcard Scene/*.cpp) $(wildcard menu/*.cpp) \
$(wildcard menuItem/*.cpp) $(wildcard core/*.cpp) $(wildcard util/*.cpp) $(wildcard Eni/*.cpp) \
$(wildcard Item/*.cpp) $(wildcard level/*.cpp) $(wildcard Map/*.cpp) $(wildcard MapElement/*.cpp)
program_CXX_OBJS = ${program_CXX_SRCS:.cpp=.o}
program_C_SRCS = $(wildcard gfx/*.c)
program_C_OBJS = ${program_C_SRCS:.c=.o}
program_OBJS = $(addprefix $(OBJ_DIR)/,$(program_CXX_OBJS) $(program_C_OBJS))
program_INCLUDE_DIRS = /usr/include/SDL2
program_LIBRARY_DIRS =
program_LIBRARIES = SDL2 SDL2_mixer SDL2_ttf SDL2_image

CPPFLAGS = $(foreach includedir,$(program_INCLUDE_DIRS),-I$(includedir))
LDFLAGS = $(foreach librarydir,$(program_LIBRARY_DIRS),-L$(librarydir))
LDLIBS = $(foreach library,$(program_LIBRARIES),-l$(library))

MKDIR_P = mkdir -p
BIN_DIR = bin
OBJ_DIR = obj
OUT_DIR = $(BIN_DIR) $(OBJ_DIR)
program_NAME = $(BIN_DIR)/main

LINK.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) $(TARGET_ARCH)

.PHONY: all clean distclean directories

all: directories $(program_NAME)

directories: ${OUT_DIR}

${OUT_DIR}:
	${MKDIR_P} ${OUT_DIR}

$(program_NAME): $(program_OBJS)
	$(LINK.cc) $(program_OBJS) -o $(program_NAME) $(LDLIBS)

$(OBJ_DIR)/%.o: %.cpp %.h
	${MKDIR_P} ${dir $@}
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c -o $@ $<

$(OBJ_DIR)/%.o: %.cpp
	${MKDIR_P} ${dir $@}
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c -o $@ $<

$(OBJ_DIR)/%.o: %.c %.h
	${MKDIR_P} $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

clean:
	@- $(RM) $(program_NAME)
	@- $(RM) $(program_OBJS)

distclean: clean