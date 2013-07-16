dofile("plugin.lua")
dofile("embed.lua")

embed "scripts"
embed "behaviors"

-- Maratis Adventure Game Engine
solution "Mage"

    plugins {
        "MEvent",
        "MSaveFile",
        "MScriptExt",
        "MScriptableBehaviour",
        "MEmbedFile"
    }

 
    configurations { "Debug", "Release" }
    language "C++"
    
    -- make sure we can search and link properly
    libdirs { os.getenv("MSDKDIR") .. "/SDK/MCore/Libs",
          os.getenv("MSDKDIR") .. "/SDK/MEngine/Libs" }
    includedirs { os.getenv("MSDKDIR") .. "/SDK/MCore/Includes",
              os.getenv("MSDKDIR") .. "/SDK/MEngine/Includes",
              "scripts", "behaviors" }

    --targetprefix ""
    
    -- OS defines
    if os.is("windows") then
        defines { "WIN32" }
    end

    configuration "Debug"
        defines { "DEBUG" }
        flags { "Symbols" }

    configuration "Release"
        defines { "NDEBUG" }
        flags { "Optimize" } 
        
    loadplugins()

    project "Mage"
        kind "SharedLib"
        language "C++"

        -- include all the files, including Maratis SDK ones
        files {
            "src/**.cpp",
            "include/**.h",
            "**.md",
            os.getenv("MSDKDIR") .. "SDK/**.h"
        }
        includedirs { "include" }
        targetdir "bin"
        targetprefix ""

        -- split the files up a bit nicer inside Visual Studio
        vpaths { 
            ["MCore/*"] = os.getenv("MSDKDIR") .. "/SDK/MCore/Includes/**.h",
            ["MEngine/*"] = os.getenv("MSDKDIR") .. "/SDK/MEngine/Includes/**.h",
            ["MAGE/*"] = { "**.h", "**.cpp" },
            ["Doc/*"] = { "**.md" }
        }
        -- link to Maratis
        links { "MCore", "MEngine" }
        linkplugins() 

