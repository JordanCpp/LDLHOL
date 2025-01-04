#define LDL_IMPLEMENTATION
#define LDL_SUPPORT_SOFTWARE
#include "LDL/LDL.hpp"

void Vec2iTest()
{
	LDL_Vec2i vec;
	LDL_TEST_EQUAL(vec.x == 0);
	LDL_TEST_EQUAL(vec.y == 0);

	LDL_Vec2i vec2(100, 200);
	LDL_TEST_EQUAL(vec2.x == 100);
	LDL_TEST_EQUAL(vec2.y == 200);
}

void ResultTest()
{
	LDL_Result result;
	LDL_TEST_EQUAL(result.Ok() == true);
	LDL_TEST_EQUAL(LDL_CharsEqual(result.Message(), "") == true);

	result.Message("Message");
	LDL_TEST_EQUAL(result.Ok() == false);
	LDL_TEST_EQUAL(LDL_CharsEqual(result.Message(), "Message") == true);

	result.Message("Message", "Detail");
	LDL_TEST_EQUAL(result.Ok() == false);
	LDL_TEST_EQUAL(LDL_CharsEqual(result.Message(), "MessageDetail") == true);

	result.Clear();
	LDL_TEST_EQUAL(result.Ok() == true);
	LDL_TEST_EQUAL(LDL_CharsEqual(result.Message(), "") == true);
}

void WindowTest()
{
	LDL_Result result;
	LDL_Window window(&result, LDL_Vec2i(1, 2), LDL_Vec2i(320, 200), "window test");
	LDL_TEST_EQUAL(result.Ok()     == true);
	LDL_TEST_EQUAL(window.Pos().x  == 1);
	LDL_TEST_EQUAL(window.Pos().y  == 2);
	LDL_TEST_EQUAL(window.Size().x == 320);
	LDL_TEST_EQUAL(window.Size().y == 200);
	LDL_TEST_EQUAL(window.Title()  != NULL);
	LDL_TEST_EQUAL(LDL_CharsEqual(window.Title(), "window test") == true);
}

void RenderTest()
{
	LDL_Result result;
	LDL_Window window(&result, LDL_Vec2i(1, 2), LDL_Vec2i(320, 200), "window test");
	LDL_Render render(&window);
}

void ColorTest()
{
	LDL_Color color1;
	LDL_TEST_EQUAL(color1.r == 0);
	LDL_TEST_EQUAL(color1.g == 0);
	LDL_TEST_EQUAL(color1.b == 0);
	LDL_TEST_EQUAL(color1.a == 255);

	LDL_Color color2(1, 2, 3);
	LDL_TEST_EQUAL(color2.r == 1);
	LDL_TEST_EQUAL(color2.g == 2);
	LDL_TEST_EQUAL(color2.b == 3);
	LDL_TEST_EQUAL(color2.a == 255);

	LDL_Color color3(1, 2, 3, 4);
	LDL_TEST_EQUAL(color3.r == 1);
	LDL_TEST_EQUAL(color3.g == 2);
	LDL_TEST_EQUAL(color3.b == 3);
	LDL_TEST_EQUAL(color3.a == 4);
}

void AlphaTest()
{
	LDL_Alpha alpha1;
	LDL_TEST_EQUAL(alpha1.IsAlpha() == false);

	LDL_Alpha alpha2(LDL_Color(1, 2, 3, 4));
	LDL_TEST_EQUAL(alpha2.IsAlpha() == true);
	LDL_TEST_EQUAL(alpha2.Color().r == 1);
	LDL_TEST_EQUAL(alpha2.Color().g == 2);
	LDL_TEST_EQUAL(alpha2.Color().b == 3);
	LDL_TEST_EQUAL(alpha2.Color().a == 4);
	LDL_TEST_EQUAL(alpha2.Index()   == 1);

	LDL_Alpha alpha3(1);
	LDL_TEST_EQUAL(alpha3.IsAlpha() == true);
	LDL_TEST_EQUAL(alpha3.Color().r == 1);
	LDL_TEST_EQUAL(alpha3.Color().g == 0);
	LDL_TEST_EQUAL(alpha3.Color().b == 0);
	LDL_TEST_EQUAL(alpha3.Color().a == 255);
	LDL_TEST_EQUAL(alpha3.Index()   == 1);
}

void ConverterTest()
{
	LDL_Converter conv;

	LDL_TEST_EQUAL(LDL_CharsEqual(conv.Convert(12845), "12845") == true);
	LDL_TEST_EQUAL(LDL_CharsEqual(conv.Convert(-12845), "-12845") == true);
}

int main()
{
	Vec2iTest();
	ResultTest();
	ColorTest();
	AlphaTest();
	WindowTest();
	RenderTest();
	ConverterTest();

	return 0;
}