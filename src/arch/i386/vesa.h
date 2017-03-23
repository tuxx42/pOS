#ifndef VESA_H
#define VESA_H

/* Some screen stuff. */
#define VESA_VIDEO_MEMORY       0xB8000	/* The video memory address. */
#define COLUMNS                 80	/* The number of columns. */
#define LINES                   24	/* The number of lines. */
#define ATTRIBUTE               7	/* The attribute of an character. */

void putchar (int c);
void vesa_init(void);
#endif
