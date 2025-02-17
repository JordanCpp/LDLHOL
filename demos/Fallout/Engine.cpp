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

#include "Engine.hpp"
#include <stdio.h>

Engine::Engine(const LDL_Vec2i& size) :
	_paletteLoader(&_byteReader, "data/COLOR.PAL"),
	_window(&_result, LDL_Vec2i(0,0), size, "", LDL_WindowMode::Fixed),
	_render(&_window, _paletteLoader.Result()),
	_frmReader(&_byteReader),
	_spriteLoader(&_frmReader, _paletteLoader.Result()),
	_spriteManager(&_spriteLoader)
{
}

Engine::~Engine()
{
}

void Engine::Run()
{
	if (_result.Ok())
	{
		LDL_Event report;

		while (_window.Running())
		{
			_fpsCounter.Start();

			while (_window.GetEvent(report))
			{
				if (report.Type == LDL_Event::IsQuit)
				{
					_window.StopEvent();
				}
			}

			_render.Begin();

			Sprite* sprite = _spriteManager.GetSprite("data/art/critters/HANPWRAA.FRM");
			_render.Draw(sprite->GetFrame(0, 0)->GetImage(), LDL_Vec2i(5, 10));
			_render.Draw(sprite->GetFrame(0, 0)->GetImage(), LDL_Vec2i(70, 10));

			_render.End();

			if (_fpsCounter.Calc())
			{
				_window.Title(_convert.Convert(_fpsCounter.Fps()));
				_fpsCounter.Clear();
			}

			_window.PollEvents();
		}
	}
	else
	{
		printf("%s\n", _result.Message());
	}
}
