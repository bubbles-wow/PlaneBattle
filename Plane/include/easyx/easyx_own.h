#pragma once
#ifndef EASYX_OWN_H
#define EASYX_OWN_H

#include <map>
#include <string>

#include <graphics.h>

/**
 * @brief 绘制透明背景图片
 * @param x 图片左上角的x坐标
 * @param y 图片左上角的y坐标
 * @param srcimg 图片
 * @see https://blog.csdn.net/Solahalo/article/details/127598433
 */
void transparentimage3(int x, int y, IMAGE *srcimg);
void transparentimage3(int x, int y, int width, int height, IMAGE *srcimg, int srcX, int srcY);

#endif // !EASYX_OWN_H
