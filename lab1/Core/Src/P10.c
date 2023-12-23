#include "../inc/P10.h"

P10ErrorCode drawPixel(Pixel pix, uint8_t *spiFrame16, P10ABMux AB) {

	P10ErrorCode check = checkPixelData(&pix);

	if (check != P10EC_OK) {

	}
	else {

		uint8_t jy = pix.y % 4;
		if (jy  == AB) {
			uint8_t iy = pix.y / 4;
			uint8_t jx = pix.x % 8;
			uint8_t ix = pix.x / 8;

			spiFrame16[ix * 4 + iy] &= ~(1 << (7 - jx));

		}

	}

	return check;
}

P10ErrorCode erasePixel(Pixel pix, uint8_t *spiFrame16, P10ABMux AB){
	
	P10ErrorCode check = checkPixelData(&pix);

	if (check != P10EC_OK) {
	}
	else {
		uint8_t jy = pix.y % 4;
		if (jy  == AB) {
			uint8_t iy = pix.y / 4;
			uint8_t jx = pix.x % 8;
			uint8_t ix = pix.x / 8;

			spiFrame16[ix * 4 + iy] |= (1 << (7 - jx));
		}
	}
	return check;
}
	
P10ErrorCode invertPixel(Pixel pix, uint8_t *spiFrame16, P10ABMux AB){
	P10ErrorCode check = checkPixelData(&pix);

	if (check != P10EC_OK) {
	}
	else {
		uint8_t jy = pix.y % 4;
		if (jy  == AB) {
			uint8_t iy = pix.y / 4;
			uint8_t jx = pix.x % 8;
			uint8_t ix = pix.x / 8;

			spiFrame16[ix * 4 + iy] ^= (1 << (7 - jx));
		}
	}
	return check;
}	

P10ErrorCode drawPixels(const Pixel *pixAr, uint16_t size, uint8_t *spiFrame16, P10ABMux AB){
	P10ErrorCode check = P10EC_OK;
	
	if(size != 0){
		for(uint16_t i = 0; i < size; i++){
			P10ErrorCode pixCheck = drawPixel(pixAr[i], spiFrame16, AB);
			if (pixCheck != P10EC_OK) {
				check = pixCheck;
			}
		}
	}
	else{
		check = P10EC_EMPTY_ARRAY;
	}
	
	return check;
}

P10ErrorCode erasePixels(const Pixel *pixAr, uint16_t size, uint8_t *spiFrame16, P10ABMux AB) {
	P10ErrorCode check = P10EC_OK;

	if (size != 0) {
		for (uint16_t i = 0; i < size; i++) {
			P10ErrorCode pixCheck = erasePixel(pixAr[i], spiFrame16, AB);
			if (pixCheck != P10EC_OK) {
				check = pixCheck;
			}
		}
	}
	else {
		check = P10EC_EMPTY_ARRAY;
	}

	return check;
}

P10ErrorCode invertPixels(const Pixel *pixAr, uint16_t size, uint8_t *spiFrame16, P10ABMux AB) {
	P10ErrorCode check = P10EC_OK;

	if (size != 0) {
		for (uint16_t i = 0; i < size; i++) {
			P10ErrorCode pixCheck = invertPixel(pixAr[i], spiFrame16, AB);
			if (pixCheck != P10EC_OK) {
				check = pixCheck;
			}
		}
	}
	else {
		check = P10EC_EMPTY_ARRAY;
	}

	return check;
}

P10ErrorCode drawRect(Pixel leftUp, Pixel rightBottom, uint8_t *spiFrame16, P10ABMux AB)
{
	P10ErrorCode checkLU = checkPixelData(&leftUp);
	P10ErrorCode checkRB = checkPixelData(&rightBottom);
	
	P10ErrorCode check = P10EC_OK;
	

	if (checkLU == P10EC_OK && checkRB == P10EC_OK) {
		if (rightBottom.x < leftUp.x || leftUp.y < rightBottom.y) {
			check = P10EC_RECT_POINTS_ERROR;
		}
		else {
			uint8_t width = rightBottom.x - leftUp.x;
			uint8_t height = leftUp.y - rightBottom.y;

			for (uint8_t i = 0; i <= width; i++) {
				uint8_t y[2] = { leftUp.y, rightBottom.y };

				for (uint8_t k = 0; k < 2; k++) {
					uint8_t jy = y[k] % 4;
					if (jy == AB) {
						uint8_t iy = y[k] / 4;
						uint8_t jx = (leftUp.x + i) % 8;
						uint8_t ix = (leftUp.x + i) / 8;

						spiFrame16[ix * 4 + iy] &= ~(1 << (7 - jx));
					}
				}
			}

			for (uint8_t i = 1; i < height; i++) {
				uint8_t x[2] = { leftUp.x, rightBottom.x };

				for (uint8_t k = 0; k < 2; k++) {
					uint8_t jy = (rightBottom.y + i) % 4;
					if (jy == AB) {
						uint8_t iy = (rightBottom.y + i) / 4;
						uint8_t jx = x[k] % 8;
						uint8_t ix = x[k] / 8;

						spiFrame16[ix * 4 + iy] &= ~(1 << (7 - jx));
					}
				}
			}
		}
	}
	else {
		if (checkLU != checkRB) {
			check = P10EC_DATA_RANGE_ERROR;
		}
		else {
			check = checkLU;
		}
	}

	return check;
}

P10ErrorCode eraseRect(Pixel leftUp, Pixel rightBottom, uint8_t *spiFrame16, P10ABMux AB)
{
	P10ErrorCode checkLU = checkPixelData(&leftUp);
	P10ErrorCode checkRB = checkPixelData(&rightBottom);

	P10ErrorCode check = P10EC_OK;


	if (checkLU == P10EC_OK && checkRB == P10EC_OK) {
		if (rightBottom.x < leftUp.x || leftUp.y < rightBottom.y) {
			check = P10EC_RECT_POINTS_ERROR;
		}
		else {
			uint8_t width = rightBottom.x - leftUp.x;
			uint8_t height = leftUp.y - rightBottom.y;

			for (uint8_t i = 0; i <= width; i++) {
				uint8_t y[2] = { leftUp.y, rightBottom.y };

				for (uint8_t k = 0; k < 2; k++) {
					uint8_t jy = y[k] % 4;
					if (jy == AB) {
						uint8_t iy = y[k] / 4;
						uint8_t jx = (leftUp.x + i) % 8;
						uint8_t ix = (leftUp.x + i) / 8;

						spiFrame16[ix * 4 + iy] |= (1 << (7 - jx));
					}
				}
			}

			for (uint8_t i = 1; i < height; i++) {
				uint8_t x[2] = { leftUp.x, rightBottom.x };

				for (uint8_t k = 0; k < 2; k++) {
					uint8_t jy = (rightBottom.y + i) % 4;
					if (jy == AB) {
						uint8_t iy = (rightBottom.y + i) / 4;
						uint8_t jx = x[k] % 8;
						uint8_t ix = x[k] / 8;

						spiFrame16[ix * 4 + iy] |= (1 << (7 - jx));
					}
				}
			}
		}
	}
	else {
		if (checkLU != checkRB) {
			check = P10EC_DATA_RANGE_ERROR;
		}
		else {
			check = checkLU;
		}
	}

	return check;
}

P10ErrorCode invertRect(Pixel leftUp, Pixel rightBottom, uint8_t *spiFrame16, P10ABMux AB)
{
	P10ErrorCode checkLU = checkPixelData(&leftUp);
	P10ErrorCode checkRB = checkPixelData(&rightBottom);

	P10ErrorCode check = P10EC_OK;


	if (checkLU == P10EC_OK && checkRB == P10EC_OK) {
		if (rightBottom.x < leftUp.x || leftUp.y < rightBottom.y) {
			check = P10EC_RECT_POINTS_ERROR;
		}
		else {
			uint8_t width = rightBottom.x - leftUp.x;
			uint8_t height = leftUp.y - rightBottom.y;

			for (uint8_t i = 0; i <= width; i++) {
				uint8_t y[2] = { leftUp.y, rightBottom.y };

				for (uint8_t k = 0; k < 2; k++) {
					uint8_t jy = y[k] % 4;
					if (jy == AB) {
						uint8_t iy = y[k] / 4;
						uint8_t jx = (leftUp.x + i) % 8;
						uint8_t ix = (leftUp.x + i) / 8;

						spiFrame16[ix * 4 + iy] ^= (1 << (7 - jx));
					}
				}
			}

			for (uint8_t i = 1; i < height; i++) {
				uint8_t x[2] = { leftUp.x, rightBottom.x };

				for (uint8_t k = 0; k < 2; k++) {
					uint8_t jy = (rightBottom.y + i) % 4;
					if (jy == AB) {
						uint8_t iy = (rightBottom.y + i) / 4;
						uint8_t jx = x[k] % 8;
						uint8_t ix = x[k] / 8;

						spiFrame16[ix * 4 + iy] ^= (1 << (7 - jx));
					}
				}
			}
		}
	}
	else {
		if (checkLU != checkRB) {
			check = P10EC_DATA_RANGE_ERROR;
		}
		else {
			check = checkLU;
		}
	}

	return check;
}

P10ErrorCode drawLine(Pixel p1, Pixel p2, uint8_t * spiFrame16, P10ABMux AB)
{
	P10ErrorCode check1 = checkPixelData(&p1);
	P10ErrorCode check2 = checkPixelData(&p2);

	P10ErrorCode check = P10EC_OK;

	if (check1 == P10EC_OK && check2 == P10EC_OK) {
		
		int8_t width = p2.x - p1.x, height = p2.y - p1.y, absWidth, absHeight;
		if (width > 0) {
			absWidth = width;
		}
		else {
			absWidth = -width;
		}
		if (height > 0) {
			absHeight = height;
		}
		else {
			absHeight = -height;
		}

		if (absWidth >= absHeight){ //left to right
			Pixel pl, pr;
			if (p1.x <= p2.x) {
				pl = p1;
				pr = p2;
			}
			else{
				pl = p2;
				pr = p1;
			}
			for (int8_t xi = (int8_t)pl.x; xi <= (int8_t)pr.x; xi++) {
				uint8_t x = (uint8_t)xi;
				int8_t dy = (int8_t)(pr.y - pl.y);
				int8_t dx = (int8_t)(pr.x - pl.x);
				int8_t dxi = (xi - (int8_t)pl.x);
				
				//rounding staff
				int8_t add = dx / 2;
				if (dy < 0) {
					add = -add;
				}

				uint8_t y = (uint8_t)((int16_t)pl.y + ((int16_t)(dy*dxi) + add)/dx) ;
				
				uint8_t jy = y % 4;
				if (jy == AB) {
					uint8_t iy = y / 4;
					uint8_t jx = x % 8;
					uint8_t ix = x / 8;

					spiFrame16[ix * 4 + iy] &= ~(1 << (7 - jx));
				}
			}
		}
		else { //bottom to up
			Pixel pb, pu;
			if (p1.y <= p2.y) {
				pb = p1;
				pu = p2;
			}
			else {
				pb = p2;
				pu = p1;
			}
			for (int8_t yi = (int8_t)pb.y; yi <= (int8_t)pu.y; yi++) {
				uint8_t y = (uint8_t)yi;
				int8_t dy = (int8_t)(pb.y - pu.y);
				int8_t dx = (int8_t)(pb.x - pu.x);
				int8_t dyi = yi - (int8_t)pb.y;

				//rounding staff
				int8_t add = dy / 2;
				if (dx > 0) {
					add = -add;
				}

				uint8_t x = (uint8_t)((int16_t)pb.x + ((int16_t)(dx*dyi) + add) / dy);

				uint8_t jy = y % 4;
				if (jy == AB) {
					uint8_t iy = y / 4;
					uint8_t jx = x % 8;
					uint8_t ix = x / 8;

					spiFrame16[ix * 4 + iy] &= ~(1 << (7 - jx));
				}
			}
		}
	}
	else {
		if (check1 != check2) {
			check = P10EC_DATA_RANGE_ERROR;
		}
		else {
			check = check1;
		}
	}
	return check;
}

P10ErrorCode eraseLine(Pixel p1, Pixel p2, uint8_t * spiFrame16, P10ABMux AB)
{
	P10ErrorCode check1 = checkPixelData(&p1);
	P10ErrorCode check2 = checkPixelData(&p2);

	P10ErrorCode check = P10EC_OK;

	if (check1 == P10EC_OK && check2 == P10EC_OK) {

		int8_t width = p2.x - p1.x, height = p2.y - p1.y, absWidth, absHeight;
		if (width > 0) {
			absWidth = width;
		}
		else {
			absWidth = -width;
		}
		if (height > 0) {
			absHeight = height;
		}
		else {
			absHeight = -height;
		}

		if (absWidth >= absHeight) { //left to right
			Pixel pl, pr;
			if (p1.x <= p2.x) {
				pl = p1;
				pr = p2;
			}
			else {
				pl = p2;
				pr = p1;
			}
			for (int8_t xi = (int8_t)pl.x; xi <= (int8_t)pr.x; xi++) {
				uint8_t x = (uint8_t)xi;
				int8_t dy = (int8_t)(pr.y - pl.y);
				int8_t dx = (int8_t)(pr.x - pl.x);
				int8_t dxi = (xi - (int8_t)pl.x);

				//rounding staff
				int8_t add = dx / 2;
				if (dy < 0) {
					add = -add;
				}

				uint8_t y = (uint8_t)((int16_t)pl.y + ((int16_t)(dy*dxi) + add) / dx);

				uint8_t jy = y % 4;
				if (jy == AB) {
					uint8_t iy = y / 4;
					uint8_t jx = x % 8;
					uint8_t ix = x / 8;

					spiFrame16[ix * 4 + iy] |= (1 << (7 - jx));
				}
			}
		}
		else { //bottom to up
			Pixel pb, pu;
			if (p1.y <= p2.y) {
				pb = p1;
				pu = p2;
			}
			else {
				pb = p2;
				pu = p1;
			}
			for (int8_t yi = (int8_t)pb.y; yi <= (int8_t)pu.y; yi++) {
				uint8_t y = (uint8_t)yi;
				int8_t dy = (int8_t)(pb.y - pu.y);
				int8_t dx = (int8_t)(pb.x - pu.x);
				int8_t dyi = yi - (int8_t)pb.y;

				//rounding staff
				int8_t add = dy / 2;
				if (dx > 0) {
					add = -add;
				}

				uint8_t x = (uint8_t)((int16_t)pb.x + ((int16_t)(dx*dyi) + add) / dy);

				uint8_t jy = y % 4;
				if (jy == AB) {
					uint8_t iy = y / 4;
					uint8_t jx = x % 8;
					uint8_t ix = x / 8;

					spiFrame16[ix * 4 + iy] |= (1 << (7 - jx));
				}
			}
		}
	}
	else {
		if (check1 != check2) {
			check = P10EC_DATA_RANGE_ERROR;
		}
		else {
			check = check1;
		}
	}
	return check;
}

P10ErrorCode invertLine(Pixel p1, Pixel p2, uint8_t * spiFrame16, P10ABMux AB)
{
	P10ErrorCode check1 = checkPixelData(&p1);
	P10ErrorCode check2 = checkPixelData(&p2);

	P10ErrorCode check = P10EC_OK;

	if (check1 == P10EC_OK && check2 == P10EC_OK) {

		int8_t width = p2.x - p1.x, height = p2.y - p1.y, absWidth, absHeight;
		if (width > 0) {
			absWidth = width;
		}
		else {
			absWidth = -width;
		}
		if (height > 0) {
			absHeight = height;
		}
		else {
			absHeight = -height;
		}

		if (absWidth >= absHeight) { //left to right
			Pixel pl, pr;
			if (p1.x <= p2.x) {
				pl = p1;
				pr = p2;
			}
			else {
				pl = p2;
				pr = p1;
			}
			for (int8_t xi = (int8_t)pl.x; xi <= (int8_t)pr.x; xi++) {
				uint8_t x = (uint8_t)xi;
				int8_t dy = (int8_t)(pr.y - pl.y);
				int8_t dx = (int8_t)(pr.x - pl.x);
				int8_t dxi = (xi - (int8_t)pl.x);

				//rounding staff
				int8_t add = dx / 2;
				if (dy < 0) {
					add = -add;
				}

				uint8_t y = (uint8_t)((int16_t)pl.y + ((int16_t)(dy*dxi) + add) / dx);

				uint8_t jy = y % 4;
				if (jy == AB) {
					uint8_t iy = y / 4;
					uint8_t jx = x % 8;
					uint8_t ix = x / 8;

					spiFrame16[ix * 4 + iy] ^= (1 << (7 - jx));
				}
			}
		}
		else { //bottom to up
			Pixel pb, pu;
			if (p1.y <= p2.y) {
				pb = p1;
				pu = p2;
			}
			else {
				pb = p2;
				pu = p1;
			}
			for (int8_t yi = (int8_t)pb.y; yi <= (int8_t)pu.y; yi++) {
				uint8_t y = (uint8_t)yi;
				int8_t dy = (int8_t)(pb.y - pu.y);
				int8_t dx = (int8_t)(pb.x - pu.x);
				int8_t dyi = yi - (int8_t)pb.y;

				//rounding staff
				int8_t add = dy / 2;
				if (dx > 0) {
					add = -add;
				}

				uint8_t x = (uint8_t)((int16_t)pb.x + ((int16_t)(dx*dyi) + add) / dy);

				uint8_t jy = y % 4;
				if (jy == AB) {
					uint8_t iy = y / 4;
					uint8_t jx = x % 8;
					uint8_t ix = x / 8;

					spiFrame16[ix * 4 + iy] ^= (1 << (7 - jx));
				}
			}
		}
	}
	else {
		if (check1 != check2) {
			check = P10EC_DATA_RANGE_ERROR;
		}
		else {
			check = check1;
		}
	}
	return check;
}

P10ErrorCode checkPixelData(const Pixel *pix) {

	P10ErrorCode returnValue = P10EC_OK;

	if (pix->x < 32 && pix->y < 16) {



	}
	else {
		if (pix->x >= 32 && pix->y >= 16) {
			returnValue = P10EC_DATA_RANGE_ERROR;
		}
		else
		{
			if (pix->x >= 32) {
				returnValue = P10EC_X_RANGE_ERROR;
			}
			else {
				returnValue = P10EC_Y_RANGE_ERROR;
			}
		}
	}

	return returnValue;
}

void clearScreen(uint8_t *spiFrame16)
{
	for (uint8_t i = 0; i < 16; i++) {
		spiFrame16[i] = 0xff;
	}
}

void fillScreen(uint8_t * spiFrame16)
{
	for (uint8_t i = 0; i < 16; i++) {
		spiFrame16[i] = 0;
	}
}
