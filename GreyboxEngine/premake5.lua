workspace "GreyboxEngine"
	architecture "x64"
	configurations
	{
	"Debug",
	"Release",
	"Dist"
	}
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"	
	
IncludeDir = {}
IncludeDir["GLFW"] = "GreyboxEngine/3rdParty/GLFW/include"
IncludeDir["Glad"] = "GreyboxEngine/3rdParty/Glad/include"
IncludeDir["ImGui"] = "GreyboxEngine/3rdParty/imgui"

include "GreyboxEngine/3rdParty/GLFW"
include "GreyboxEngine/3rdParty/Glad"
include "GreyboxEngine/3rdParty/imgui"

project "GreyboxEngine"
    location "GreyboxEngine"
    kind "SharedLib"
    language "C++"
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
    buildoptions { "/utf-8" }
    
    pchheader "gbepch.h"
    pchsource "GreyboxEngine/src/gbepch.cpp"
    
    files
    {
        "%{prj.name}/include/**.h",
        "%{prj.name}/src/**.cpp"
    }
    
    includedirs 
    {
        "%{prj.name}/3rdParty/spdlog/include/",
        "%{prj.name}/include/",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}"
    }
    
    links
    {
        "GLFW",
        "GLAD",
        "ImGui",
        "opengl32.lib"
    }
    
    filter "system:windows"
        systemversion "latest"
        
    defines
    {
        "GBE_BUILD_DLL", 
        "GBE_PLATFORM_WINDOWS",
        "GLFW_INCLUDE_NONE"
    }
    
    postbuildcommands
    {
        ("{copy} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
    }
    
    filter "configurations:Debug"
        defines "GBE_DEBUG"
        buildoptions "/MDd"
        symbols "On"
    filter "configurations:Release"
        defines "GBE_RELEASE"
        buildoptions "/MD"
        symbols "On"
    filter "configurations:Dist"
        defines "GBE_DIST"
        buildoptions "/MD"
        symbols "On"
project "Sandbox"
    location "Sandbox"
        kind "ConsoleApp"
        language "C++"
        targetdir ("bin/" .. outputdir .. "/%{prj.name}")
        objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
        buildoptions { "/utf-8" }
         
        files
        {
            "%{prj.name}/include/**.h",
            "%{prj.name}/src/**.cpp"
        }
        
        includedirs
        {
            "GreyboxEngine/3rdParty/spdlog/include/",
            "GreyboxEngine/include",
            "%{prj.name}/include/"
        }
        
        links
        {
            "GreyboxEngine"
        }
        
        filter "system:windows"
            systemversion "latest"
            
        defines
        {
            "GBE_PLATFORM_WINDOWS",
        }
        
        filter "configurations:Debug"
            defines "GBE_DEBUG GBE_ENABLE_ASSERTS"
            buildoptions "/MDd"
            symbols "On"
        filter "configurations:Release"
            defines "GBE_RELEASE"
            buildoptions "/MD"
            symbols "On"
        filter "configurations:Dist"
            defines "GBE_DIST"
            buildoptions "/MD"
            symbols "On"