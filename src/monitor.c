#include "monitor.h"

u16int cursor_x = 0;
u16int cursor_y = 0;

u16int * const video_memory = (u16int * const)0xB8000;

const int SCREEN_WIDTH = 80;
const int SCREEN_HEIGTH = 25;

const int VGA_CONTROL_PORT = 0x3d4;
const int VGA_DATA_PORT = 0x3d5;
// Updates the hardware cursor.
static void move_cursor()
{
	// The screen is 80 characters wide...
	u16int cursorLocation = cursor_y * SCREEN_WIDTH + cursor_x;
	outb(VGA_CONTROL_PORT, 14);                  // Tell the VGA board we are setting the high cursor byte.
	outb(VGA_DATA_PORT, cursorLocation >> 8); // Send the high cursor byte.
	outb(VGA_CONTROL_PORT, 15);                  // Tell the VGA board we are setting the low cursor byte.
	outb(VGA_DATA_PORT, cursorLocation);      // Send the low cursor byte.
}

// Scrolls the text on the screen up by one line.
static void scroll()
{

	// Get a space character with the default colour attributes.
	u8int attributeByte = (0 /*black*/ << 4) | (15 /*white*/ & 0x0F);
	u16int blank = 0x20 /* space */ | (attributeByte << 8);

	// Row 25 is the end, this means we need to scroll up
	if(cursor_y >= SCREEN_HEIGTH)
	{
		// Move the current text chunk that makes up the screen
		// back in the buffer by a line
		int i;
		for (i = 0; i < (SCREEN_HEIGTH-1)*SCREEN_WIDTH; i++)
		{
			video_memory[i] = video_memory[i+SCREEN_WIDTH];
		}

		// The last line should now be blank. Do this by writing
		// 80 spaces to it.
		for (i = (SCREEN_HEIGTH-1)*SCREEN_WIDTH; i < SCREEN_HEIGTH*SCREEN_WIDTH; i++)
		{
			video_memory[i] = blank;
		}
		// The cursor should now be on the last line.
		cursor_y = SCREEN_HEIGTH-1;
	}
}


// Writes a single character out to the screen.
void monitor_put(char c)
{
	// The background colour is black (0), the foreground is white (15).
	u8int backColour = 0;
	u8int foreColour = 15;

	// The attribute byte is made up of two nibbles - the lower being the
	// foreground colour, and the upper the background colour.
	u8int  attributeByte = (backColour << 4) | (foreColour & 0x0F);
	// The attribute byte is the top 8 bits of the word we have to send to the
	// VGA board.
	u16int attribute = attributeByte << 8;
	u16int *location;

	// Handle a backspace, by moving the cursor back one space
	if (c == 0x08 && cursor_x)
	{
		cursor_x--;
	}

	// Handle a tab by increasing the cursor's X, but only to a point
	// where it is divisible by 8.
	else if (c == 0x09)
	{
		cursor_x = (cursor_x+8) & ~(8-1);
	}

	// Handle carriage return
	else if (c == '\r')
	{
		cursor_x = 0;
	}

	// Handle newline by moving cursor back to left and increasing the row
	else if (c == '\n')
	{
		cursor_x = 0;
		cursor_y++;
	}
	// Handle any other printable character.
	else if(c >= ' ')
	{
		location = video_memory + (cursor_y*SCREEN_WIDTH + cursor_x);
		*location = c | attribute;
		cursor_x++;
	}

	// Check if we need to insert a new line because we have reached the end
	// of the screen.
	if (cursor_x >= SCREEN_WIDTH)
	{
		cursor_x = 0;
		cursor_y ++;
	}

	// Scroll the screen if needed.
	scroll();
	// Move the hardware cursor.
	move_cursor();
}

// Clears the screen, by copying lots of spaces to the framebuffer.
void monitor_clear()
{
	// Make an attribute byte for the default colours
	u8int attributeByte = (0 /*black*/ << 4) | (15 /*white*/ & 0x0F);
	u16int blank = 0x20 /* space */ | (attributeByte << 8);

	int i;
	for (i = 0; i < SCREEN_WIDTH*SCREEN_HEIGTH; i++)
	{
		video_memory[i] = blank;
	}

	// Move the hardware cursor back to the start.
	cursor_x = 0;
	cursor_y = 0;
	move_cursor();
}

// Outputs a null-terminated ASCII string to the monitor.
void monitor_write(char *c)
{
	int i = 0;
	while (c[i])
	{
		monitor_put(c[i++]);
	}
}


void monitor_write_hex(u32int n)
{
	int i = 8;
	char hx[16]={'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};
	monitor_put('0');
	monitor_put('x');

	while(i--)
	{
		monitor_put(hx[(n&(0xf<<28))>>28]);
		n<<=4;
	}
}

void monitor_write_dec(s32int n)
{
	u32int body = n<0?-n:n;
	int i = 0;
	char str[10]={0};

	if(!body)
	{
		monitor_put('0');
		return;
	}

	while(body)
	{
		str[i]=body%10;
		body /= 10;
		i++;
	}

	if(n<0)
		monitor_put('-');

	for(i--;i>=0;i--)
		monitor_put('0'+str[i]);

	return;
}
