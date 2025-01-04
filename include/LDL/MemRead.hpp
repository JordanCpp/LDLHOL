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

#ifndef LDL_MemRead_hpp
#define LDL_MemRead_hpp

class LDL_MemoryReader : public LDL_Reader
{
public:
	LDL_MemoryReader();
	void Reset(uint8_t* buffer, size_t total);
	size_t Read(void* dest, size_t bytes);
private:
	uint8_t* _buffer;
	size_t   _total;
	size_t   _position;
};

#ifdef LDL_IMPLEMENTATION
LDL_MemoryReader::LDL_MemoryReader() :
	_buffer(NULL),
	_total(0),
	_position(0)
{
}

void LDL_MemoryReader::Reset(uint8_t* buffer, size_t total)
{
	LDL_ASSERT(buffer != NULL);
	LDL_ASSERT(total > 0);

	_buffer = buffer;
	_total  = total;
}

size_t LDL_MemoryReader::Read(void* dest, size_t bytes)
{
	size_t result = 0;

	if (_position + bytes <= _total)
	{
		LDL_BytesCopy(dest, &_buffer[_position], bytes);
		_position += bytes;

		result = bytes;
	}

	return result;
}
#endif

#endif
