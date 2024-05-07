@echo off

rd /s /q "./.vscode"
rd /s /q "./.idea"
rd /s /q "./build"
rd /s /q "./cmake-build-debug"

echo 删除完成！
pause
