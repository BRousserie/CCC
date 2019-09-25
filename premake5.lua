workspace "CCC"
	architecture "x64"
	startproject "Garage"
	
    configurations 
	{ 
		"Debug", 
		"Release", 
		"Dist" 
	}

outputdir = "%{cfg.buildcfg}"

IncludeDir = {}
IncludeDir["GLFW"] = "CCC/vendor/GLFW/include"
IncludeDir["Glad"] = "CCC/vendor/Glad/include"
IncludeDir["imgui"] = "CCC/vendor/imgui"
IncludeDir["glm"] = "CCC/vendor/glm"

group "Dependencies"
	include "CCC/vendor/GLFW"
	include "CCC/vendor/Glad"
	include "CCC/vendor/imgui"

group ""
project "CCC"
	location "CCC"
    kind "StaticLib"
    language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "CCCpch.h"
	pchsource "CCC/src/CCCpch.cpp"
	
    files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",		
		"%{prj.name}/vendor/glm/glm/**.inl",		
	}
	
	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}
	
	includedirs
	{ 
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.glm}"
	}
	
	links
	{
		"GLFW",
		"Glad",
		"imgui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"
		
		defines
		{
			"CCC_PLATFORM_WINDOWS",
			"CCC_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}
		
    filter "configurations:Debug"
        defines "CCC_DEBUG"
		runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "CCC_RELEASE"
		runtime "Release"
        optimize "on"
		
	filter "configurations:Dist"
		defines "CCC_DIST"
		runtime "Release"
		optimize "on"
	
	
	
project "Garage"
	location "Garage"
    kind "ConsoleApp"
    language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
    files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp" 
	}
	
	includedirs
	{ 
		"CCC/vendor/spdlog/include",
		"CCC/src",
		"CCC/vendor",
		"%{IncludeDir.glm}"
	}
	
	links
	{
		"CCC"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"
		
		defines
		{
			"CCC_PLATFORM_WINDOWS"
		}
		
    filter "configurations:Debug"
        defines { "CCC_DEBUG" }
		runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines { "CCC_RELEASE" }
		runtime "Release"
        optimize "on"
		
	filter "configurations:Dist"
		defines { "CCC_DIST" }
		runtime "Release"
		optimize "on"
	