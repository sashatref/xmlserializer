call "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\bin\vcvars32.bat"

msbuild Sources\TinyXml2.vcxproj /p:configuration=Release
msbuild Sources\TinyXml2.vcxproj /p:configuration=Debug

pause