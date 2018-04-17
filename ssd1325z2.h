/******************************************************************************
 * SSD1325Z2 - Library for SSD1325Z2 OLed Driver based on libohiboard
 * Copyright (C) 2018 Marco Giammarini
 *
 * Authors:
 *  Marco Giammarini <m.giammarini@warcomeb.it>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 ******************************************************************************/

#ifndef __WARCOMEB_SSD1325Z2_H
#define __WARCOMEB_SSD1325Z2_H

#define WARCOMEB_SSD1325Z2_LIBRARY_VERSION     "1.0.0"
#define WARCOMEB_SSD1325Z2_LIBRARY_VERSION_M   1
#define WARCOMEB_SSD1325Z2_LIBRARY_VERSION_m   0
#define WARCOMEB_SSD1325Z2_LIBRARY_VERSION_bug 0
#define WARCOMEB_SSD1325Z2_LIBRARY_TIME        0

#include "libohiboard.h"
#include "GDL/gdl.h"

/*
 * The user must define these label...
 * The name of the define is:
 *     #define WARCOMEB_SSD1325Z2_HEIGHT         xx
 *     #define WARCOMEB_SSD1325Z2_WIDTH          xx
 */
#ifndef __NO_BOARD_H
#include "board.h"
#endif

#if !defined(WARCOMEB_SSD1325Z2_HEIGHT) | !defined(WARCOMEB_SSD1325Z2_WIDTH)
#error "You must define height and width of display!"
#else
// Every byte represent 2 pixel...
#define WARCOMEB_SSD1325Z2_BUFFERDIMENSION (WARCOMEB_SSD1325Z2_WIDTH*WARCOMEB_SSD1325Z2_HEIGHT/2)
#endif

#if defined(WARCOMEB_SSD1325Z2_HEIGHT) & ((WARCOMEB_SSD1325Z2_HEIGHT < 16) | (WARCOMEB_SSD1325Z2_HEIGHT > 80))
#error "The height must be between 16 and 128!"
#endif

#if defined(WARCOMEB_SSD1325Z2_WIDTH) & ((WARCOMEB_SSD1325Z2_WIDTH < 16) | (WARCOMEB_SSD1325Z2_WIDTH > 128))
#error "The width must be between 16 and 128!"
#endif

/**
 * A usefull enum that define all the possbile color for each pixel.
 */
typedef enum _SSD1325Z2_GrayScale
{
	SSD1325Z2_GRAYSCALE_0  = 0,
	SSD1325Z2_GRAYSCALE_1  = 1,
	SSD1325Z2_GRAYSCALE_2  = 2,
	SSD1325Z2_GRAYSCALE_3  = 3,
	SSD1325Z2_GRAYSCALE_4  = 4,
	SSD1325Z2_GRAYSCALE_5  = 5,
	SSD1325Z2_GRAYSCALE_6  = 6,
	SSD1325Z2_GRAYSCALE_7  = 7,
	SSD1325Z2_GRAYSCALE_8  = 8,
	SSD1325Z2_GRAYSCALE_9  = 9,
	SSD1325Z2_GRAYSCALE_10 = 10,
	SSD1325Z2_GRAYSCALE_11 = 11,
	SSD1325Z2_GRAYSCALE_12 = 12,
	SSD1325Z2_GRAYSCALE_13 = 13,
	SSD1325Z2_GRAYSCALE_14 = 14,
	SSD1325Z2_GRAYSCALE_15 = 15,
} SSD1325Z2_GrayScale;

typedef enum _SSD1325Z2_Product
{
	SSD1325Z2_PRODUCT_RAYSTAR_REX012864F   = 0x0001 | GDL_MODELTYPE_SSD1325,
} SSD1325Z2_Product;

typedef struct SSD1325Z2_Device
{
    GDL_Device gdl;                         /**< Common part for each device */

#if defined WARCOMEB_GDL_PARALLEL

#elif defined WARCOMEB_GDL_I2C

    Gpio_Pins rstPin;            /**< Reset pin used for start-up the display */

#elif defined WARCOMEB_GDL_SPI

#endif

    /** Buffer to store display data */
    uint8_t buffer [WARCOMEB_SSD1325Z2_BUFFERDIMENSION];

} SSD1325Z2_Device, *SSD1325Z2_DeviceHandle;

/**
 *
 */
void SSD1325Z2_init (SSD1325Z2_DeviceHandle dev);

/**
 *
 *
 * @param[in] dev The handle of the device
 * @param[in] xPos The x position
 * @param[in] yPos The y position
 * @param[in] color The color of the pixel
 * @return
 */
GDL_Errors SSD1325Z2_drawPixel (SSD1325Z2_DeviceHandle dev,
                                uint8_t xPos,
                                uint8_t yPos,
							    SSD1325Z2_GrayScale color);

/**
 * The function print a line in the selected position with the selected
 * color.
 *
 * @param[in] dev The handle of the device
 * @param[in] xStart The starting x position
 * @param[in] yStart The starting y position
 * @param[in] xStop The ending x position
 * @param[in] yStop The ending y position
 * @param[in] color The color of the line
 */
void SSD1325Z2_drawLine (SSD1325Z2_DeviceHandle dev,
                         uint8_t xStart,
                         uint8_t yStart,
                         uint8_t xStop,
                         uint8_t yStop,
					     SSD1325Z2_GrayScale color);

/**
 * The function print a horizontal line from the selected position with
 * the selected width and color.
 *
 * @param[in] dev The handle of the device
 * @param[in] xStart The starting x position
 * @param[in] yStart The starting y position
 * @param[in] width The width of the line
 * @param[in] color The color of the line
 */
void SSD1325Z2_drawHLine (SSD1325Z2_DeviceHandle dev,
                          uint8_t xStart,
                          uint8_t yStart,
                          uint8_t width,
                          SSD1325Z2_GrayScale color);

/**
 * The function print a vertical line from the selected position with
 * the selected height and color.
 *
 * @param[in] dev The handle of the device
 * @param[in] xStart The starting x position
 * @param[in] yStart The starting y position
 * @param[in] height The height of the line
 * @param[in] color The color of the line
 */
void SSD1325Z2_drawVLine (SSD1325Z2_DeviceHandle dev,
                          uint8_t xStart,
                          uint8_t yStart,
                          uint8_t height,
                          SSD1325Z2_GrayScale color);

/**
 * The function draw a rectangle. It can be fill or not.
 *
 * @param[in] dev The handle of the device
 * @param[in] xStart The starting x position
 * @param[in] yStart The starting y position
 * @param[in] width The ending x position
 * @param[in] height The ending y position
 * @param[in] color The color of the rectangle
 * @param[in] isFill If TRUE the rectangle will be fill
 */
void SSD1325Z2_drawRectangle (SSD1325Z2_DeviceHandle dev,
                              uint16_t xStart,
                              uint16_t yStart,
                              uint16_t width,
                              uint16_t height,
							  SSD1325Z2_GrayScale color,
                              bool isFill);

/**
 * The function print a char in the selected position with the selected
 * color and size.
 * The starting point is the top-left corner of the char.
 *
 * @param[in] dev The handle of the device
 * @param[in] xPos The x position
 * @param[in] yPos The y position
 * @param[in] c The char to be draw
 * @param[in] color The foreground color of the char
 * @param[in] background The background color of the char
 * @param[in] size The size for the char, if 0 use default dimension
 * @return GDL_ERRORS_WRONG_POSITION if the dimension plus position of the char
 *         exceeds the width or height of the display, GDL_ERRORS_OK otherwise.
 */
GDL_Errors SSD1325Z2_drawChar (SSD1325Z2_DeviceHandle dev,
                               uint16_t xPos,
                               uint16_t yPos,
                               uint8_t c,
							   SSD1325Z2_GrayScale color,
                               SSD1325Z2_GrayScale background,
                               uint8_t size);

/**
 * The function print a string from the selected position with the selected
 * color and size.
 * The starting point is the top-left corner of the first char.
 *
 * @param[in] dev The handle of the device
 * @param[in] xPos The x position
 * @param[in] yPos The y position
 * @param[in] text A pointer to the string
 * @param[in] color The foreground color of the string
 * @param[in] background The background color of the string
 * @param[in] size The size for every char of the string, if 0 use default dimension
 * @return GDL_ERRORS_WRONG_POSITION if the dimension plus position of the string
 *         exceeds the width or height of the display, GDL_ERRORS_OK otherwise.
 */
GDL_Errors SSD1325Z2_drawString (SSD1325Z2_DeviceHandle dev,
                                 uint16_t xPos,
                                 uint16_t yPos,
                                 const uint8_t* text,
                                 SSD1325Z2_GrayScale color,
                                 SSD1325Z2_GrayScale background,
                                 uint8_t size);

/**
 * The function print a picture from an array of pixel, in the selected
 * position.
 * Every pixel can be described from 1 or 4 because this OLED driver accept
 * only 16-level of color.
 * The starting point is the top-left corner of the picture.
 *
 * @param[in] dev The handle of the device
 * @param[in] xPos The x position
 * @param[in] yPos The y position
 * @param[in] width The picture dimension along the x axis
 * @param[in] height The picture dimension along the y axis
 * @param[in] picture The array of picture to be printed
 * @param[in] pixelType The number of bit for each pixel. This value represent the
 *                      number of color
 * @return GDL_ERRORS_WRONG_POSITION if the dimension plus position of the picture
 *         exceeds the width or height of the display, GDL_ERRORS_WRONG_VALUE if
 *         some value are wrong, GDL_ERRORS_OK otherwise.
 */
GDL_Errors SSD1325Z2_drawPicture (SSD1325Z2_DeviceHandle dev,
                                  uint16_t xPos,
                                  uint16_t yPos,
                                  uint16_t width,
                                  uint16_t height,
                                  const uint8_t* picture,
                                  GDL_PictureType pixelType);

/**
 * This function clear the display setting off all pixel
 *
 * @param[in] dev The handle of the device
 */
void SSD1325Z2_clear (SSD1325Z2_DeviceHandle dev);

/**
 *
 *
 * @param[in] dev The handle of the device
 */
void SSD1325Z2_flush (SSD1325Z2_DeviceHandle dev);

/**
 *
 *
 * @param[in] dev The handle of the device
 * @param[in] xStart The x start position into the buffer
 * @param[in] xStop The x stop position into the buffer
 * @param[in] yStart The y start position into the buffer
 * @param[in] yStop The y stop position into the buffer
 */
void SSD1325Z2_flushPart (SSD1325Z2_DeviceHandle dev,
                          uint8_t xStart,
                          uint8_t xStop,
                          uint8_t yStart,
                          uint8_t yStop);

/**
 * The function switch on the display.
 *
 * @param[in] dev The handle of the device
 */
void SSD1325Z2_displayOn (SSD1325Z2_DeviceHandle dev);

/**
 * The function switch off the display.
 *
 * @param[in] dev The handle of the device
 */
void SSD1325Z2_displayOff (SSD1325Z2_DeviceHandle dev);

/**
 * The function set the current contrast of the display. The chip has
 * 128 contrast steps from 00H to 7FH.
 *
 * @param[in] dev The handle of the device
 * @param[in] value The level of the contrast
 * @return An error if the value is greater than the maximum allowed,
 *         GDL_ERRORS_OK otherwise.
 */
GDL_Errors SSD1325Z2_setContrast (SSD1325Z2_DeviceHandle dev, uint8_t value);

#endif /* __WARCOMEB_SSD1325Z2_H */

