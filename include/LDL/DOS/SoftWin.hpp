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

#ifndef LDL_DOS_SoftWin_hpp
#define LDL_DOS_SoftWin_hpp

class LDL_WindowSoftware
{
public:
	LDL_WindowSoftware(LDL_Result* result, const LDL_Vec2i& pos, const LDL_Vec2i& size, const char* title, int mode = LDL_WindowMode::Fixed);
	~LDL_WindowSoftware();
	bool Running();
	void Present();
	void PollEvents();
	const LDL_Vec2i& Size();
	const LDL_Vec2i& Pos();
	bool GetEvent(LDL_Event& event);
	bool WaitEvent(LDL_Event& event);
	void StopEvent();
	const char* Title();
	void Title(const char* title);
	void* NativeHandle();
	void Update();
	uint8_t GetBpp();
	LDL_Surface* GetScreen();
private:
	LDL_Result*      _Result;
	uint8_t LDL_FAR* _Video;
	LDL_MainWindow   _MainWindow;
	LDL_Palette      _Palette;
	LDL_Surface      _Screen;
};

#ifdef LDL_IMPLEMENTATION
LDL_WindowSoftware::LDL_WindowSoftware(LDL_Result* result, const LDL_Vec2i& pos, const LDL_Vec2i& size, const char* title, int mode) :
	_Result(result),
	_MainWindow(result, pos, size, title, mode),
	_Screen(size, size, &_Palette)
{
	_Video = (uint8_t LDL_FAR*)0xA0000000L;

	union REGS regs;

	regs.h.ah = 0x00;
	regs.h.al = 0x13;
	int86(0x10, &regs, &regs);
}

LDL_WindowSoftware::~LDL_WindowSoftware()
{
}

bool LDL_WindowSoftware::Running()
{
	return _MainWindow.Running();
}

void LDL_WindowSoftware::Present()
{
	size_t           count  = _Screen.Size().x * _Screen.Size().y * _Screen.Bpp();
	uint8_t LDL_FAR* pixels = _Screen.Pixels();
	LDL_Palette* palette    = _Screen.Palette();

	if (_Palette.Empty())
	{
		_Palette.Assign(palette);

		outp(0x03c8, 0);

		for (size_t i = 0; i < _Palette.Max; i++)
		{
			LDL_Color color = _Palette.Get(i);

			outp(0x03c9, color.r >> 2);
			outp(0x03c9, color.g >> 2);
			outp(0x03c9, color.b >> 2);
		}
	}

	for (size_t i = 0; i < count; i++)
	{
		_Video[i] = pixels[i];
	}
}

void LDL_WindowSoftware::PollEvents()
{
	_MainWindow.PollEvents();
}

const LDL_Vec2i& LDL_WindowSoftware::Size()
{
	return _MainWindow.Size();
}

const LDL_Vec2i& LDL_WindowSoftware::Pos()
{
	return _MainWindow.Pos();
}

bool LDL_WindowSoftware::GetEvent(LDL_Event& event)
{
	return _MainWindow.GetEvent(event);
}

bool LDL_WindowSoftware::WaitEvent(LDL_Event& event)
{
	return _MainWindow.WaitEvent(event);
}

void LDL_WindowSoftware::StopEvent()
{
	_MainWindow.StopEvent();
}

const char* LDL_WindowSoftware::Title()
{
	return _MainWindow.Title();
}

void LDL_WindowSoftware::Title(const char* title)
{
	_MainWindow.Title(title);
}

void* LDL_WindowSoftware::NativeHandle()
{
	return NULL;
}

void LDL_WindowSoftware::Update()
{
	_MainWindow.Update();
}

uint8_t LDL_WindowSoftware::GetBpp()
{
	return 1;
}

LDL_Surface* LDL_WindowSoftware::GetScreen()
{
	return &_Screen;
}

#endif

#endif