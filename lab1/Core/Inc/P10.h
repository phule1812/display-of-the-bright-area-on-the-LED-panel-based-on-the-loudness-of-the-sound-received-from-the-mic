#ifndef __P10_H__
#define __P10_H__

#include <stdint.h>
#include <math.h>

#if defined(__cplusplus)
extern "C"
{
#endif

	typedef struct
	{
		uint8_t x;
		uint8_t y;
	} Pixel;


	typedef enum
	{
		P10EC_OK,
		P10EC_X_RANGE_ERROR,
		P10EC_Y_RANGE_ERROR,
		P10EC_DATA_RANGE_ERROR,
		P10EC_EMPTY_ARRAY,
		P10EC_RECT_POINTS_ERROR
	} P10ErrorCode;

	typedef enum {
		P10AB_11,
		P10AB_10,
		P10AB_01,
		P10AB_00,
	} P10ABMux;

	//pixel
	P10ErrorCode drawPixel(Pixel pix, uint8_t *spiFrame16, P10ABMux AB);
	P10ErrorCode erasePixel(Pixel pix, uint8_t *spiFrame16, P10ABMux AB);
	P10ErrorCode invertPixel(Pixel pix, uint8_t *spiFrame16, P10ABMux AB);

	//Pixels
	P10ErrorCode drawPixels(const Pixel *pixAr, uint16_t size, uint8_t *spiFrame16, P10ABMux AB);
	P10ErrorCode erasePixels(const Pixel *pixAr, uint16_t size, uint8_t *spiFrame16, P10ABMux AB);
	P10ErrorCode invertPixels(const Pixel *pixAr, uint16_t size, uint8_t *spiFrame16, P10ABMux AB);

	//Rect 
	P10ErrorCode drawRect(Pixel leftUp, Pixel rightBottom, uint8_t *spiFrame16, P10ABMux AB);
	P10ErrorCode eraseRect(Pixel leftUp, Pixel rightBottom, uint8_t *spiFrame16, P10ABMux AB);
	P10ErrorCode invertRect(Pixel leftUp, Pixel rightBottom, uint8_t *spiFrame16, P10ABMux AB);

	//Line
	P10ErrorCode drawLine(Pixel p1, Pixel p2, uint8_t *spiFrame16, P10ABMux AB);
	P10ErrorCode eraseLine(Pixel p1, Pixel p2, uint8_t *spiFrame16, P10ABMux AB);
	P10ErrorCode invertLine(Pixel p1, Pixel p2, uint8_t *spiFrame16, P10ABMux AB);

	//check data
	P10ErrorCode checkPixelData(const Pixel *pix);
	void clearScreen(uint8_t *spiFrame16);
	void fillScreen(uint8_t *spiFrame16);

#if defined(__cplusplus)
}
#endif

#endif // !__P10_H__
