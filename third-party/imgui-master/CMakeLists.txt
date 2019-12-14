#file(GLOB_RECURSE SRC_FILES *.cpp *.h)
file(GLOB SRC_FILES
	imgui.cpp
	imgui.h
	imgui_draw.cpp
	imgui_widgets.cpp
)
add_library(imgui ${SRC_FILES})
