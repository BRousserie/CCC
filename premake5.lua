workspace "CCC"
	architecture "x64"
	
    configurations 
	{ 
		"Debug", 
		"Release", 
		"Dist" 
	}

outputdir = "%{cfg.buildcfg}"

project "CCC"
	location "CCC"
    kind "SharedLib"
    language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
    files 
	{
		"%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp" 
	}
	
	includedirs
	{ 
		"CCC/vendor/spdlog/include" 
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		
		defines
		{
			"CCC_PLATFORM_WINDOWS",
			"CCC_BUILD_DLL"
		}
		
		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Garage")
		}
		
    filter "configurations:Debug"
        defines "CCC_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "CCC_RELEASE"
        optimize "On"
		
	filter "configurations:Dist"
		defines "CCC_DIST"
		optimize "On"
	
	
	
project "Garage"
	location "Garage"
    kind "ConsoleApp"
    language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
    files 
	{
		"%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp" 
	}
	
	includedirs
	{ 
		"%{prj.name}/vendor/spdlog/include",
		"CCC/src"
	}
	
	links
	{
		"CCC"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		
		defines
		{
			"CCC_PLATFORM_WINDOWS"
		}
		
    filter "configurations:Debug"
        defines { "CCC_DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "CCC_RELEASE" }
        optimize "On"
		
	filter "configurations:Dist"
		defines { "CCC_DIST" }
		optimize "On"
	