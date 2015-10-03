image tocolor(grayimage img){
   unsigned int x, y;
   image timg;
   luminance l;
   unsigned int ofs;

   timg = alloc_img(img-&gt;width, img-&gt;height);
   
   for(x=0; x &lt; img-&gt;width; x++)
   {
      for(y=0; y &lt; img-&gt;height; y++)
      {
        ofs = (y * img-&gt;width) + x;
        l = img-&gt;buf[ofs][0];
        timg-&gt;buf[ofs][0] = l;
        timg-&gt;buf[ofs][1] = l;
        timg-&gt;buf[ofs][2] = l;
      }
   }
   return timg;
}
