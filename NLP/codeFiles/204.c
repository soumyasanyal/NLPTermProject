grayimage tograyscale(image img){
   unsigned int x, y;
   grayimage timg;
   double rc, gc, bc, l;
   unsigned int ofs;

   timg = alloc_grayimg(img-&gt;width, img-&gt;height);
   
   for(x=0; x &lt; img-&gt;width; x++)
   {
      for(y=0; y &lt; img-&gt;height; y++)
      {
        ofs = (y * img-&gt;width) + x;
        rc = (double) img-&gt;buf[ofs][0];
        gc = (double) img-&gt;buf[ofs][1];
        bc = (double) img-&gt;buf[ofs][2];
        l = 0.2126*rc + 0.7152*gc + 0.0722*bc;
        timg-&gt;buf[ofs][0] = (luminance) (l+0.5);
      }
   }
   return timg;
}
