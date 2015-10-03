image alloc_img(unsigned int width, unsigned int height){
    image img;
    img = malloc(sizeof(image_t));
    img-&gt;buf = malloc(width * height * sizeof(pixel));
    img-&gt;width = width;
    img-&gt;height = height;
    return img;
}

void free_img(image img)
{
    free(img-&gt;buf);
    free(img);
}

void fill_img(
        image img,
        color_component r,
        color_component g,
        color_component b )
{
    unsigned int i, n;
    n = img-&gt;width * img-&gt;height;
    for (i=0; i &lt; n; ++i)
    {
        img-&gt;buf[i][0] = r;
        img-&gt;buf[i][1] = g;
        img-&gt;buf[i][2] = b;
    }
}

void put_pixel_unsafe(
       	image img,
        unsigned int x,
        unsigned int y,
        color_component r,
        color_component g,
        color_component b )
{
    unsigned int ofs;
    ofs = (y * img-&gt;width) + x;
    img-&gt;buf[ofs][0] = r;
    img-&gt;buf[ofs][1] = g;
    img-&gt;buf[ofs][2] = b;
}

void put_pixel_clip(
       	image img,
        unsigned int x,
        unsigned int y,
        color_component r,
        color_component g,
        color_component b )
{
    if (x &lt; img-&gt;width &amp;&amp; y &lt; img-&gt;height)
      put_pixel_unsafe(img, x, y, r, g, b);
}
