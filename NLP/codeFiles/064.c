#include &lt;string.h&gt;#include &lt;stdlib.h&gt;
#include &lt;time.h&gt;
#include &lt;math.h&gt;
#include &lt;FreeImage.h&gt;

#define NUM_PARTICLES  1000
#define SIZE           800

void draw_brownian_tree(int world[SIZE][SIZE]){
  int px, py; // particle values
  int dx, dy; // offsets
  int i;
 
  // set the seed
  world[rand() % SIZE][rand() % SIZE] = 1;

  for (i = 0; i &lt; NUM_PARTICLES; i++){
    // set particle's initial position
    px = rand() % SIZE;
    py = rand() % SIZE;

    while (1){
      // randomly choose a direction
      dx = rand() % 3 - 1;
      dy = rand() % 3 - 1;

      if (dx + px &lt; 0 || dx + px &gt;= SIZE || dy + py &lt; 0 || dy + py &gt;= SIZE){
        // plop the particle into some other random location
        px = rand() % SIZE;
        py = rand() % SIZE;
      }else if (world[py + dy][px + dx] != 0){
        // bumped into something
        world[py][px] = 1;
        break;
      }else{
        py += dy;
        px += dx;
      }
    }
  }
}

int main(){
  int world[SIZE][SIZE];
  FIBITMAP * img;
  RGBQUAD rgb;
  int x, y;
 
  memset(world, 0, sizeof world);
  srand((unsigned)time(NULL));

  draw_brownian_tree(world);

  img = FreeImage_Allocate(SIZE, SIZE, 32, 0, 0, 0);

  for (y = 0; y &lt; SIZE; y++){
    for (x = 0; x &lt; SIZE; x++){
      rgb.rgbRed = rgb.rgbGreen = rgb.rgbBlue = (world[y][x] ? 255 : 0);
      FreeImage_SetPixelColor(img, x, y, &amp;rgb);
    }
  }
  FreeImage_Save(FIF_BMP, img, &quot;brownian_tree.bmp&quot;, 0);
  FreeImage_Unload(img);
}
