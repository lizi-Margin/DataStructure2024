@echo off
setlocal enabledelayedexpansion

set "source_dir=C:\Users\33149\Desktop\DS2024\pack\Database"
set "destination_dir=C:\Users\33149\Desktop\DS2024\pack\Database"

for /l %%i in (10,1,20) do (
    set /a "new_folder=%%i+10"
    xcopy /s /e /i "%source_dir%\%%i" "%destination_dir%\!new_folder!"
)

echo Done.
pause
