if exist echecs.exe (
    del /f echecs.exe
)
gcc -Iheaders -Iheaders\logic .\*.c .\code\game_logic\*.c
ren a.exe echecs.exe
echecs