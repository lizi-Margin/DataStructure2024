@echo off
setlocal enabledelayedexpansion

rem 循环创建文件夹
for /l %%i in (31, 1, 399) do (
    mkdir %%i
)

echo 文件夹创建完成！
