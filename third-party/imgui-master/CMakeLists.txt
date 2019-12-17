#file(GLOB_RECURSE SRC_FILES *.cpp *.h)
file(GLOB SRC_FILES
	imgui.cpp
	imgui.h
	imgui_draw.cpp
	imgui_widgets.cpp
	imgui_demo.cpp
	imgui_demo.hpp
		imgui_impl_opengl3.cpp
		imgui_impl_opengl3.h
		imgui_impl_sdl.cpp
		imgui_impl_sdl.h
)
add_library(imgui ${SRC_FILES})
