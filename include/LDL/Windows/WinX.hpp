/*
Boost Software License - Version 1.0 - August 17th, 2003

Permission is hereby granted, free of charge, to any person or organization
obtaining a copy of the software and accompanying documentation covered by
this license (the "Software") to use, reproduce, display, distribute,
execute, and transmit the Software, and to prepare derivative works of the
Software, and to permit third-parties to whom the Software is furnished to
do so, all subject to the following:

The copyright notices in the Software and this entire statement, including
the above license grant, this restriction and the following disclaimer,
must be included in all copies of the Software, in whole or in part, and
all derivative works of the Software, unless such copies or derivative
works are solely in the form of machine-executable object code generated by
a source language processor.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
*/

#ifndef LDL_Windows_WinX_hpp
#define LDL_Windows_WinX_hpp

#if defined(_WIN32)
#define STRICT
#undef UNICODE
#undef _UNICODE

#ifdef NOMINMAX
#include <windows.h>
#else
#define NOMINMAX
#include <windows.h>
#undef NOMINMAX
#endif

#if !defined INVALID_ATOM
#define INVALID_ATOM ((ATOM)0)
#endif

#if !defined INVALID_FILE_ATTRIBUTES
#define INVALID_FILE_ATTRIBUTES ((DWORD)-1)
#endif

#if !defined VK_OEM_1
#define VK_OEM_1 0xBA
#endif

#if !defined VK_OEM_2
#define VK_OEM_2 0xBF
#endif

#if !defined VK_OEM_3
#define VK_OEM_3 0xC0
#endif

#if !defined VK_OEM_4
#define VK_OEM_4 0xDB
#endif

#if !defined VK_OEM_5
#define VK_OEM_5 0xDC
#endif

#if !defined VK_OEM_6
#define VK_OEM_6 0xDD
#endif

#if !defined VK_OEM_7
#define VK_OEM_7 0xDE
#endif

#if !defined VK_OEM_PLUS
#define VK_OEM_PLUS 0xBB
#endif

#if !defined VK_OEM_COMMA
#define VK_OEM_COMMA 0xBC
#endif

#if !defined VK_OEM_MINUS
#define VK_OEM_MINUS 0xBD
#endif

#if !defined VK_OEM_PERIOD
#define VK_OEM_PERIOD 0xBE
#endif

#if !defined WM_MOUSEWHEEL
#define WM_MOUSEWHEEL 0x020A
#endif

#if !defined WM_MOUSEHWHEEL
#define WM_MOUSEHWHEEL 0x020E
#endif
#endif

#endif
