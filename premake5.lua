workspace "Mandelbrot"
	configurations { "Debug", "Release" }

project "proj"
	kind "ConsoleApp"
	language "C++"
	files { "**.h", "**.cpp" }

	configuration "vs*"
		flags "EnableSSE2"
		buildoptions { "-wd4996", "/utf-8" }
		defines { "_CRT_SECURE_NO_WARNINGS" }

	configuration "not vs*"
		buildoptions { "-fno-strict-aliasing", "-Wno-multichar" }
	configuration {"not vs*", "windows"}
		buildoptions { "-static-libgcc" }

	configuration "Debug"
		flags "Symbols"
		defines "_DEBUG"
		targetdir "bin/debug"

	configuration "Release"
		flags { "OptimizeSpeed" }
		targetdir "bin/release"

-- libgmp.dll.a;opengl32.lib;glu32.lib;glfw3.lib;