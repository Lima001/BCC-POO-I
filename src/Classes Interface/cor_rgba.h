#ifndef COR_RGBA_H
#define COR_RGBA_H

#include <iostream>
#include <SDL.h>

class CorRGBA {
    protected:

        int r;
        int g;
        int b;
        int a;

    public:

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
            a(a){
        }

        int get_r(){
            return r;
        };

        int get_g(){
            return g;
        };

        int get_b(){
            return b;
        };

        int get_a(){
            return a;
        }

        void set_a(int a){
            CorRGBA::a = a;
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