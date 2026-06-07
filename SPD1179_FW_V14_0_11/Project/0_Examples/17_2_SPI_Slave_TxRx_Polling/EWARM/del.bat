del *.dep

del /f /s /q settings\*
rd settings

for /d /r "Debug\" %%i in (*) do (rd /q /s "%%i" 2>nul)
del /q /a "Debug\*.*"
rd Debug