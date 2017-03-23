#include <vesa.h>
#include <stdint.h>
#include <common.h>

/* Variables. */
static int video_video_ypos;	/* Save the X position. */
static int ypos;	/* Save the Y position. */
static volatile uint8_t *video_memory = (uint8_t *) VESA_VIDEO_MEMORY; /* Point to the video memory. */

/* Clear the screen and initialize VIDEO, XPOS and YPOS. */
void vesa_init(void)
{
	int i;

	for (i = 0; i < COLUMNS * LINES * 2; i++)
		*(video_memory + i) = 0;

	video_video_ypos = 0;
	ypos = 0;
}

/* Scrolls the text on the screen up by one line. */
static void vesa_scroll()
{
	/* move the lines in the video buffer up by one */
	memcpy((void *)video_memory, (void *)video_memory+COLUMNS*2, LINES*COLUMNS*2);

	/* blank out the last line */
	memset((void *)video_memory+LINES*COLUMNS*2, 0, COLUMNS*2);
}

/* Put the character C on the screen. */
void putchar (int c)
{
	if (c == '\n' || c == '\r') {
newline:
		video_video_ypos = 0;
		ypos++;
		if (ypos > LINES) {
			vesa_scroll();
			ypos = LINES;
		}
		return;
	}

	*(video_memory + (video_video_ypos + ypos * COLUMNS) * 2) = c & 0xFF;
	*(video_memory + (video_video_ypos + ypos * COLUMNS) * 2 + 1) = ATTRIBUTE;

	video_video_ypos++;
	if (video_video_ypos >= COLUMNS)
		goto newline;
}

/*
void outb(unsigned int port, short value)
{
	asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}


void move_cursor(int x, int y)
{
	unsigned int location = y * COLUMNS + x;

	outb(0x3D4, 14);		// Tell the VGA board we are setting the high cursor byte.
	outb(0x3D5, location >> 8);	// Send the high cursor byte.
	outb(0x3D4, 15);		// Tell the VGA board we are setting the lower cursor byte.
	outb(0x3D5, location);		// Send the low cursor byte.
}
*/
