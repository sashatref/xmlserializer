call "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\bin\vcvars32.bat"

@Echo off

Set Folder=Builds

If Exist "%Folder%\*.*" (
rem	rd "%Folder%\" /s /q
)

mkdir "%Folder%"

cd %Folder%


qmake ..\Sources\TinyXml.pro "CONFIG+=build_all"
nmake


del /f /s /q *.res
del /f /s /q *.manifest
del /f /s /q *.exp
del /f /s /q *.ilk
del /f /s /q *_manifest.rc
del /f /s /q ui_*.h
del /f /s /q Makefile.Debug
del /f /s /q Makefile.Release
del /f /s /q Makefile
rd "debug" /s /q
rd "release" /s /q

pause