workspace "Mandelbrot"
	configurations { "Debug", "Release" }
	platforms { "Win32", "Win64"}

project "proj"
	kind "ConsoleApp"
	language "C++"
	files { "**.h", "**.cpp" }

	linkoptions {
		--"/NODEFAULTLIB:libcmt.lib"
	}
	includedirs {
	-- add include dirs here
		"$(GLFW)/include",
		"$(GMP)"
	}
	libdirs {
	--add lib dirs here
		"$(GLFW)/lib-vc2019",
		"$(GMP)/.libs"
	}
	links {
	-- premake doesn't support lib ends with '.a', so add it in source
		"opengl32", "glu32", "glfw3"
	}
	configuration "Release"
		flags { optimize "Speed" }
		targetdir "bin/release"

	configuration "vs*"
		vectorextensions "SSE2"
		buildoptions { "-wd4996 -wd4828", "/utf-8" }
		defines { "_CRT_SECURE_NO_WARNINGS" }

	configuration "Debug"
		symbols "On"
		defines "_DEBUG"
		targetdir "bin/debug"

	
-- libgmp.dll.a;opengl32.lib;glu32.lib;glfw3.lib;