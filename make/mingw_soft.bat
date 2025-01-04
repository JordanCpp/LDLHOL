call "C:\Downloads\codeblocks-8.02mingw-setup\MinGW\mingwvars.bat"

g++ -Wall -Wextra -Werror -pedantic-errors -o mingw_soft_%1.exe -O2 -s %2%1.cpp -I..\include -DLDL_SUPPORT_SOFTWARE -lgdi32 -lopengl32 -lwinmm