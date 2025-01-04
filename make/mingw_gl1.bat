call "C:\Downloads\codeblocks-8.02mingw-setup\MinGW\mingwvars.bat"

g++ -Wall -Wextra -Werror -pedantic-errors -o mingw_gl1_%1.exe -O2 -s %2%1.cpp -I..\include -DLDL_SUPPORT_OPENGL1 -lgdi32 -lopengl32 -lwinmm