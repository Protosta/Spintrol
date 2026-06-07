@echo off

jlink.exe -device SPC1169_128K -if SWD -speed 10000 -autoconnect 1 -CommandFile .\download.jlink