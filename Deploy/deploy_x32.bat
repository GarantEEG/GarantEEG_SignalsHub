@echo off
cls
chcp 1251 >nul



rem Output directory
set OutputPath="%cd%\x32"

rem GarantEegStreamer.exe and GarantEegStreamer.pdb path
set BinariesPath="%cd%\..\build\release_x32"

rem Dependencies VC runtime dlls path
set DependenciesPath="%cd%\..\Dependencies\bin\x32"

rem Dependencies LSL dlls path
set DependenciesLSLPath="%cd%\..\libs\x32"

rem Qt (msvc2015 x32) path
set QtPath="C:\Qt\5.11.0\msvc2015\"

echo Clear output directory...
rmdir /S /Q %OutputPath%
mkdir %OutputPath%

echo Copy executable file in to run directory...
copy /Y %BinariesPath%\GarantEegStreamer.exe %OutputPath%

echo Copy PDB file in to run directory...
copy /Y %BinariesPath%\GarantEegStreamer.pdb %OutputPath%

echo Copy VC runtime dependencies in to run directory...
copy /Y %DependenciesPath%\*.dll %OutputPath%

echo Copy LSL dependencies in to run directory...
copy /Y %DependenciesLSLPath%\*.dll %OutputPath%

echo Going to Qt directory...
C:
cd %QtPath%\bin

echo Calling windeployqt...
windeployqt -dir "%OutputPath%" %OutputPath%\GarantEegStreamer.exe --release

echo Copy absent libraries
cd %QtPath%\qml
xcopy /Y /O /X /E /H /K QtGraphicalEffects %OutputPath%\QtGraphicalEffects\
xcopy /Y /O /X /E /H /K QtQml %OutputPath%\QtQml\
xcopy /Y /O /X /E /H /K QtQuick %OutputPath%\QtQuick\
xcopy /Y /O /X /E /H /K "QtQuick.2" "%OutputPath%\QtQuick.2\"

echo End...