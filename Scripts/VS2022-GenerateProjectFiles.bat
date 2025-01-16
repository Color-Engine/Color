:: You must have premake5.exe on your PATH environment variable before you will be able to execute this script.
@echo off
pushd %~dp0\..\
call premake5.exe vs2022
popd
pause
