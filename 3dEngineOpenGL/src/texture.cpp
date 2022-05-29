#include "texture.h"
#include <iostream>
using namespace std;


void CTexture::LoadTexture(char *filename)
{
	image = IMG_Load(filename);
	if (!image) {
		cerr << "Error al cargar la textura" << endl;
	}

	width  = image->w;
	height = image->h;
	bitDepth = image->format->BitsPerPixel;

	data = new GLubyte[width * height * (bitDepth/8)];

	int pos = 0;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			Uint8 r, g, b ,a;

			Uint32 color = getpixel(image, x, y);

			if (bitDepth == 24) {
				SDL_GetRGB(color, image->format, &r, &g, &b);
			}
			else {
				SDL_GetRGBA(color, image->format, &r, &g, &b, &a);
			}

			data[pos] = r; pos++;
			data[pos] = g; pos++;
			data[pos] = b; pos++;
			if (bitDepth == 32) {
				data[pos] = a;
				pos ++;
			}
		}
	}
}



Uint32 CTexture::getpixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;

    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        return *p;

    case 2:
        return *(Uint16 *)p;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;

    case 4:
        return *(Uint32 *)p;

    default:
        return 0;      
    }
}
