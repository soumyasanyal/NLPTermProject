#ifndef _IMGLIB_0#define _IMGLIB_0

#include &lt;stdio.h&gt;
#include &lt;stdlib.h&gt;
#include &lt;sys/types.h&gt;
#include &lt;string.h&gt;
#include &lt;math.h&gt;
#include &lt;sys/queue.h&gt;

typedef unsigned char color_component;
typedef color_component pixel[3];
typedef struct {
    unsigned int width;
    unsigned int height;
    pixel * buf;
} image_t;
typedef image_t * image;

image alloc_img(unsigned int width, unsigned int height);
void free_img(image);
void fill_img(image img,
        color_component r,
        color_component g,
        color_component b );
void put_pixel_unsafe(
       	image img,
        unsigned int x,
        unsigned int y,
        color_component r,
        color_component g,
        color_component b );
void put_pixel_clip(
       	image img,
        unsigned int x,
        unsigned int y,
        color_component r,
        color_component g,
        color_component b );
#define GET_PIXEL(IMG, X, Y) (IMG-&gt;buf[ ((Y) * IMG-&gt;width + (X)) ])
#endif
