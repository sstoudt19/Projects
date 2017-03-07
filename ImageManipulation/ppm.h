/****************************************************************
 *
 * ppm.h
 *
 * Read and write PPM files.  Only works for "raw" format.
 *
 *
 ****************************************************************/

typedef struct Image
{
  int width;
  int height;
  unsigned char *data;   /* array of triples of (r,g,b) values for width*height pixels */
} Image;

Image *imageCreate(int width, int height);
Image *imageRead(char *filename);
void   imageWrite(Image *image, char *filename);

int    imageWidth(Image *image);
int    imageHeight(Image *image);

void   imageClear(Image *image, unsigned char red, unsigned char green, unsigned char blue);

void   imageSetPixel(Image *image, int x, int y, int chan, unsigned char val);
unsigned char   imageGetPixel(Image *image, int x, int y, int chan);

Image* imageCopy(Image *original);
