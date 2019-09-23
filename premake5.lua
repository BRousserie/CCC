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
    kind "SharedLib"
    language "C++"
	staticruntime "off"
	
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
		cppdialect "C++17"
		systemversion "latest"
		
		defines
		{
			"CCC_PLATFORM_WINDOWS",
			"CCC_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}
		
		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Garage/\"")
		}
		
    filter "configurations:Debug"
        defines "CCC_DEBUG"
		runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "CCC_RELEASE"
		runtime "Release"
        optimize "On"
		
	filter "configurations:Dist"
		defines "CCC_DIST"
		runtime "Release"
		optimize "On"
	
	
	
project "Garage"
	location "Garage"
    kind "ConsoleApp"
    language "C++"
	staticruntime "off"
	
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
        symbols "On"

    filter "configurations:Release"
        defines { "CCC_RELEASE" }
		runtime "Release"
        optimize "On"
		
	filter "configurations:Dist"
		defines { "CCC_DIST" }
		runtime "Release"
		optimize "On"
	