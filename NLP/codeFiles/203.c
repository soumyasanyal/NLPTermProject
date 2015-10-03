grayimage alloc_grayimg(unsigned int width, unsigned int height){
     grayimage img;
     img = malloc(sizeof(grayimage_t));
     img-&gt;buf = malloc(width*height*sizeof(pixel1));
     img-&gt;width = width;
     img-&gt;height = height;
     return img;
}
