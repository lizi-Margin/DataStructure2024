@echo off
setlocal enabledelayedexpansion

rem 设置文件名和要复制的行数
set "filename=toursite_table.csv"
set /a "num_lines=100"

rem 使用 find /v /c "" 命令获取文件总行数
for /f %%a in ('find /v /c "" ^< "%filename%"') do set "total_lines=%%a"

rem 使用 set /a 命令计算要跳过的行数
set /a "skip_lines=%total_lines%-%num_lines%-1"

rem 使用 for /f 命令读取文件的最后一行
for /f %%b in ('more +%skip_lines% "%filename%"') do (
    echo %%b
    rem 复制指定数量的行
    for /l %%c in (1,1,%num_lines%) do (
        echo %%b
    )
)
