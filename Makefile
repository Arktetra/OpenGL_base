# This uses Bash shell...

CC = g++

LDFLAGS = src/lib/libglfw3.dll.a -lglfw3
DEPFLAGS = -MP -MD

INCDIRS = src/includes		# can be a list
INCGLAD = src/includes/GLAD/glad.c
OPT = -O1

CFLAGS = -std=c++17 -Wall -Wextra -g $(foreach D, $(INCDIRS), -I$(D)) $(OPT) $(DEPFLAGS)

APPNAME = app 
EXT = .cpp
SRCDIR = src
PFDIR = src/platform
BUILDDIR = build
DEPDIR = dep
IMGUI_DIR = src/includes/imgui
IMGUI_BACKEND_DIR = $(IMGUI_DIR)/backends
IMGUI_SRC = $(IMGUI_DIR)/imgui.cpp $(IMGUI_DIR)/imgui_demo.cpp $(IMGUI_DIR)/imgui_draw.cpp $(IMGUI_DIR)/imgui_tables.cpp $(IMGUI_DIR)/imgui_widgets.cpp 
IMGUI_BACKEND_SRC = $(IMGUI_BACKEND_DIR)/imgui_impl_glfw.cpp $(IMGUI_BACKEND_DIR)/imgui_impl_opengl3.cpp

SRCFILES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp, $(BUILDDIR)/%.obj, $(SRCFILES))

# for dir in
PFFILES = $(wildcard $(PFDIR)/*.cpp)
OBJECTS += $(patsubst $(PFDIR)/%.cpp, $(BUILDDIR)/%.obj, $(PFFILES))
DEPFILES = $(patsubst $(SRCDIR)/%.cpp, $(DEPDIR)/%.d, $(SRCFILES))
DEPFILES += $(patsubst $(PFDIR)/%.cpp, $(DEPDIR)/%.d, $(PFFILES))
OBJECTS += $(patsubst $(IMGUI_DIR)%.cpp, $(BUILDDIR)/%.obj, $(IMGUI_SRC))
OBJECTS += $(patsubst $(IMGUI_BACKEND_DIR)%.cpp, $(BUILDDIR)/%.obj, $(IMGUI_BACKEND_SRC))

all: $(APPNAME)

$(APPNAME): $(OBJECTS)
	$(CC) $(INCGLAD) -o $@ $^ $(LDFLAGS)

-include $(DEPFILES)

$(BUILDDIR)/%.obj: $(PFDIR)/%.cpp Makefile
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILDDIR)/%.obj: $(SRCDIR)/%.cpp Makefile
	$(CC) $(FLAGS) -c -o $@ $<

$(BUILDDIR)/%.obj: $(IMGUI_DIR)/%.cpp
	$(CC) $(FLAGS) -c -o $@ $<
	
$(BUILDDIR)/%.obj: $(IMGUI_BACKEND_DIR)/%.cpp
	$(CC) $(FLAGS) -c -o $@ $<

debug:
	$(warning SRCFILES = $(SRCFILES))
	$(warning OBJECTS = $(OBJECTS))

clean:
	rm $(BUILDDIR)/*.obj
	rm $(DEPDIR)/*.d

print:
	$(warning SRCFILES = $(SRCFILES))
	$(warning OBJECTS = $(OBJECTS))
	$(warning PFFILES = $(PFFILES))
	$(warning PFOBJECTS = $(PFOBJECTS))
	$(warning IMGUI_SRC = $(IMGUI_SRC))
