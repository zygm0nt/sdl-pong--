/*
 *                          The Art Of
 *                      D E M O M A K I N G
 *
 *
 *                     by Alex J. Champandard
 *                          Base Sixteen
 *
 *
 *                http://www.flipcode.com/demomaking
 *
 *                This file is in the public domain.
 *                      Use at your own risk.
 */


#include <dpmi.h>
#include <dos.h>
#include <malloc.h>
#include <string.h>
#include <sys/nearptr.h>
#include "vga.h"


/*
 * initialize mode 320x200x8 and prepare the double buffering
 */
VGA::VGA()
{
// set mode 0x13
   union REGS regs;
   regs.x.ax = 0x13;
   int86( 0x10, &regs, &regs );
// setup double buffering
   page_draw = new (unsigned char)[64000];
// clear our temporary page
   memset( page_draw, 0, 64000 );
// enable access to the memory we use
   __djgpp_nearptr_enable();
// get pointer to video memory
   video_buffer = (unsigned char *)( 0xa0000 + __djgpp_conventional_base );
// clear video memory
   memset( video_buffer, 0, 64000 );
};

/*
 * set a colour in the palette
 */
void VGA::SetColour( unsigned char i, unsigned char r, unsigned char g, unsigned char b )
{
// output the index of the colour
     outp( 0x3c8, i );
// and it's RGB components
     outp( 0x3c9, r );
     outp( 0x3c9, g );
     outp( 0x3c9, b );
};

/*
 * return to text mode, and clean up
 */
VGA::~VGA()
{
// set mode 0x03
   union REGS regs;
   regs.x.ax = 0x03;
   int86( 0x10, &regs, &regs );
// re-enable memory checking
   __djgpp_nearptr_disable();
// free memory
   delete [] (page_draw);
};

/*
 * flip the double buffer to the screen
 */
void VGA::Update()
{
// wait for retrace, disable for performance testing
   while (inportb(0x3da) & 0x08);
   while (!(inportb(0x3da) & 0x08));
// dump temporary buffer to the video memory
   memcpy( video_buffer, page_draw, 64000 );
};

/*
 * draw a pixel in the temporary buffer
 */
void VGA::PutPixel( int x, int y, unsigned c )
{
// clipping: check if pixel is out of the screen
// remove this for extra speed, and if you are sure x and y are always valid
   if ((x<0) || (x>319) || (y<0) || (y>199)) return;
// set the memory
   page_draw[(y<<8)+(y<<6)+x] = c;  // same as y*320+x, but slightly quicker
}

/*
 * clear the double buffer
 */
void VGA::Clear()
{
   memset( page_draw, 0, 64000 );
}
