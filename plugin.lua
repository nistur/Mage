local _plugins = {}

local function plugin(name)
    local dir = "ext/" .. name

    local projfile = dir .. "/proj-static.lua"
    local includedir = dir .. "/include"
    local linkdir = dir .. "/bin"
    local def = "M" .. name:gsub("^M",""):gsub("(%u)", "_%1"):upper() .. "_STATIC"
    return projfile, includedir, linkdir, def
end

function plugins(toadd)
    for i,v in ipairs(toadd) do
        _plugins[#_plugins+1] = v
        local projfile, includedir, linkdir, def = plugin(v)

        includedirs { includedir }
        libdirs { linkdir }
        defines { def }
    end
end

function loadplugins()
    for i,v in ipairs(_plugins) do
        local projfile = plugin(v)
        dofile(projfile)
    end
end


function linkplugins()
    for i,v in ipairs(_plugins) do
        links { v }
    end
end

