-- premake5.lua
workspace "CostaBarcodes-Locations-Portable"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "CostaBarcodes-Locations-Portable"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
include "Walnut/WalnutExternal.lua"

include "CostaBarcodes-Locations-Portable"