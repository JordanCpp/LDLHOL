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

#ifndef LDL_UtilGL_hpp
#define LDL_UtilGL_hpp

int LDL_SelectTextureSize(const LDL_Vec2i& size);
void LDL_Normalize(const LDL_Color& color, GLclampf& r, GLclampf& g, GLclampf& b);
GLuint LDL_CreateTexture(GLsizei width, GLsizei heigth, GLint format);
void LDL_DeleteTexture(GLint id);
void LDL_DrawQuad(const LDL_Vec2i& dstPos, const LDL_Vec2i& dstSize, const LDL_Vec2i& srcPos, const LDL_Vec2i& srcSize, size_t textureSize);

#ifdef LDL_IMPLEMENTATION
const int LDL_TextureCount = 12;
const int LDL_TextureSizes[LDL_TextureCount] = { 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536 };

int LDL_SelectTextureSize(const LDL_Vec2i& size)
{
	int w = size.x;
	int h = size.y;

	for (int i = 0; i < LDL_TextureCount; i++)
	{
		if (w <= LDL_TextureSizes[i] && h <= LDL_TextureSizes[i])
		{
			return (int)LDL_TextureSizes[i];
		}
	}

	return 0;
}

void LDL_Normalize(const LDL_Color& color, GLclampf& r, GLclampf& g, GLclampf& b)
{
	r = color.r / 255.0f;
	g = color.g / 255.0f;
	b = color.b / 255.0f;
}

GLuint LDL_CreateTexture(GLsizei width, GLsizei heigth, GLint format)
{
	GLuint result = 0;

	LDL_GL_CHECK(glGenTextures(1, (GLuint*)&result));

	LDL_GL_CHECK(glEnable(GL_TEXTURE_2D));

	LDL_GL_CHECK(glBindTexture(GL_TEXTURE_2D, (GLuint)result));

	LDL_GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
	LDL_GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

	LDL_GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, format, width, heigth, 0, format, GL_UNSIGNED_BYTE, NULL));

	LDL_GL_CHECK(glDisable(GL_TEXTURE_2D));

	return result;
}

void LDL_DeleteTexture(GLint id)
{
	LDL_GL_CHECK(glDeleteTextures(0, (GLuint*)&id));
}

void LDL_DrawQuad(const LDL_Vec2i& dstPos, const LDL_Vec2i& dstSize, const LDL_Vec2i& srcPos, const LDL_Vec2i& srcSize, size_t textureSize)
{
	GLfloat x = (GLfloat)dstPos.x;
	GLfloat y = (GLfloat)dstPos.y;
	GLfloat w = (GLfloat)dstSize.x;
	GLfloat h = (GLfloat)dstSize.y;

	GLfloat cx = (GLfloat)srcPos.x;
	GLfloat cy = (GLfloat)srcPos.y;
	GLfloat cw = (GLfloat)srcSize.x;
	GLfloat ch = (GLfloat)srcSize.y;

	GLfloat dcx = cx / textureSize;
	GLfloat dcy = cy / textureSize;

	GLfloat dcw = (cx + cw) / textureSize;
	GLfloat dch = (cy + ch) / textureSize;

	glBegin(GL_QUADS);
	glTexCoord2f(dcx, dcy); glVertex2f(x, y);
	glTexCoord2f(dcw, dcy); glVertex2f(x + cw + (w - cw), y);
	glTexCoord2f(dcw, dch); glVertex2f(x + cw + (w - cw), y + ch + (h - ch));
	glTexCoord2f(dcx, dch); glVertex2f(x, y + ch + (h - ch));
	glEnd();
}
#endif

#endif
