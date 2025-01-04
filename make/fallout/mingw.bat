call "C:\Downloads\codeblocks-8.02mingw-setup\MinGW\mingwvars.bat"

g++ -Wall -Wextra -Werror -pedantic-errors -o mingw_fallout.exe -O2 -s ..\..\demos\Fallout\*.cpp -I..\..\include -DLDL_SUPPORT_SOFTWARE -lgdi32 -lopengl32 -lwinmm

pause