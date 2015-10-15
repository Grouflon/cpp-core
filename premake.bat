@echo off
premake\premake5.exe --file=premake.lua vs2012
if %ERRORLEVEL% NEQ 0 PAUSE