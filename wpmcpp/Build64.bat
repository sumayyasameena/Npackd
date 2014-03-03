call Compile64.bat

ren wpmcpp_release.map Npackd64-%version%.map
if %errorlevel% neq 0 goto error

"%qt%\bin\lrelease.exe" ..\..\wpmcpp.pro
if %errorlevel% neq 0 goto error

mkdir zip

copy ..\..\wpmcpp_es.qm zip\npackdg_es.qm
if %errorlevel% neq 0 goto error

copy ..\..\wpmcpp_ru.qm zip\npackdg_ru.qm
if %errorlevel% neq 0 goto error

copy ..\..\wpmcpp_fr.qm zip\npackdg_fr.qm
if %errorlevel% neq 0 goto error

copy ..\..\wpmcpp_de.qm zip\npackdg_de.qm
if %errorlevel% neq 0 goto error

cd ..\..

copy LICENSE.txt build\64\zip

copy CrystalIcons_LICENSE.txt build\64\zip
if %errorlevel% neq 0 goto error

copy build\64\release\wpmcpp.exe build\64\zip\npackdg.exe
if %errorlevel% neq 0 goto error

"%mingw%\bin\strip.exe" build\64\zip\npackdg.exe
if %errorlevel% neq 0 goto error

rem creating .zip
cd build\64\zip
"%sevenzip%\7z" a ..\Npackd64-%version%.zip *
if %errorlevel% neq 0 goto error
cd ..\..\..

rem creating .msi
"%ai%\bin\x86\AdvancedInstaller.com" /edit wpmcpp64.aip /SetVersion %version%
"%ai%\bin\x86\AdvancedInstaller.com" /build wpmcpp64.aip
if %errorlevel% neq 0 goto error

:error

