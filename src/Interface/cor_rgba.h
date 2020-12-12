#ifndef COR_RGBA_H
#define COR_RGBA_H

#include <iostream>
#include <SDL.h>

class CorRGBA {
    public:
        int r;
        int g;
        int b;
        int a;

        CorRGBA():
            r(255),
            g(255),
            b(255),
            a(255){
        }

        CorRGBA(int r, int g, int b, int a=255):
            r(r),
            g(g),
            b(b),
            a(a)
        {
        }

        Uint32 getCor(SDL_Surface* surface){
            return SDL_MapRGB(surface->format,r,g,b);
        }

        friend std::ostream& operator<< (std::ostream &out, const CorRGBA &cor){
            out << "(" << cor.r << ", " << cor.g << ", " << cor.b << ", " << cor.a <<  ")";
            return out;
        }
};

#endif