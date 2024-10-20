#pragma comment(lib, "MSIMG32.LIB")

#include <easyx/easyx_own.h>

void transparentimage3(int x, int y, IMAGE *srcimg)
{
	transparentimage3(x, y, srcimg->getwidth(), srcimg->getheight(), srcimg, 0, 0);
}

void transparentimage3(int x, int y, int width, int height, IMAGE *srcimg, int srcX, int srcY)
{
	HDC srcDC = GetImageHDC(srcimg);
	HDC dstDc = GetImageHDC(nullptr); // 获取设备上下文
	BLENDFUNCTION bf = {AC_SRC_OVER, 0, 255, AC_SRC_ALPHA};
	AlphaBlend(dstDc, x, y, width, height, srcDC, srcX, srcY, width, height, bf);
}
