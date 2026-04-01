@echo off
echo ====================================================
echo  [VERSATIL] Compilador Portatil Ativado!
echo ====================================================
set PATH=%CD%\w64devkit\bin;%PATH%

echo.
echo [1] Gerando os arquivos do CMake usando Ninja...
cmake -G "Ninja" -B build_sfml -S .

echo.
echo [2] Compilando o executavel C++...
cmake --build build_sfml

echo.
echo ====================================================
if exist build_sfml\Runner2DGame.exe (
    echo  COMPILACAO CONCLUIDA COM SUCESSO!
    echo  Pode rodar o jogo com: .\build_sfml\Runner2DGame.exe
) else (
    echo  FALHA NA COMPILACAO.
)
echo ====================================================
pause
