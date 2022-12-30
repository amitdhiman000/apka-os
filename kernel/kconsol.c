#include <kconsol.h>
#include <kio.h>


upoint_t ConsolCursor = {0, 0};
upoint_t ConsolSize = {ConsolWidth, ConsolHeight};
uint8_t ConsolColor = ConsolDefaultColor;
uint8_t* VideoRam = (uint8_t*)VIDEO_RAM;


void ConsolScroll(void)
{
	uint32_t temp;
    uint16_t blank = 0x1F00;
	
	/* Move the current text chunk that makes up the screen
	*  back in the buffer by a line */
	temp = ConsolCursor.Y - ConsolSize.Y + 1;
	memcpy(VideoRam, VideoRam + temp * ConsolSize.X*2, (ConsolSize.Y - temp) * ConsolSize.X * 2);
	/* Finally, we set the chunk of memory that occupies
		the last line of text to our 'blank' character */
	memsetw(VideoRam + (ConsolSize.Y - temp) * ConsolSize.X * 2, blank, ConsolSize.X);
	ConsolCursor.Y = ConsolSize.Y - 1;
}


/* Updates the hardware cursor: the little blinking line
*  on the screen under the last character pressed!
*/
void ConsolMoveCursor(void)
{
    unsigned temp;

    /* The equation for finding the index in a linear
    *  chunk of memory can be represented by:
    *  Index = [(y * width) + x] */
    temp = ConsolCursor.Y * ConsolSize.X + ConsolCursor.X;

    /* This sends a command to indicies 14 and 15 in the
    *  CRT Control Register of the VGA controller. These
    *  are the high and low bytes of the index that show
    *  where the hardware cursor is to be 'blinking'. To
    *  learn more, you should look up some VGA specific
    *  programming documents. A great start to graphics:
    *  http://www.brackeen.com/home/vga */
    outportb(0x3D4, 14);
    outportb(0x3D5, temp >> 8);
    outportb(0x3D4, 15);
    outportb(0x3D5, temp);
}


void ConsolClear(void)
{
	/*
	uint32_t i;
	for(i = 0; i < ConsolSize.X * ConsolSize.Y * 2; ++i)
	{
		VideoRam[2 * i] = 0x00;
		VideoRam[(2 * i) + 1] = 0x1F;
	}
	*/
	memsetw(VideoRam, 0x1F00, ConsolSize.X * ConsolSize.Y);
	ConsolCursor.X = 0;
	ConsolCursor.Y = 0;
	ConsolMoveCursor();
}
	
	

/* Sets the forecolor and backcolor that we will use */
void SetConsolColor(const byte_t forecolor, const byte_t backcolor)
{
    /* Top 4 bytes are the background, bottom 4 bytes
    *  are the foreground color */
    ConsolColor = (backcolor << 4) | (forecolor & 0x0F);
}
	
	
	
void ConsolWriteCharColored(const char ch, const uint8_t color)
{
	if (ConsolCursor.Y >= ConsolSize.Y) {
		ConsolScroll();
	}
	
	if ('\n' == ch)
	{
		ConsolCursor.Y++;
		ConsolCursor.X = 0;
	}
	else if ('\t' == ch)
	{
		if (ConsolSize.X - ConsolCursor.X < 6) {
			ConsolCursor.Y++;
			ConsolCursor.X = 0;
		} else {
			ConsolCursor.X = ConsolCursor.X + TabWidth;
		}
	}
	else if ('\b' == ch)
	{
		BackSpace();
	}
	else if('\r' == ch)
	{
		ConsolCursor.X = 0;
	}
	else if(ch >= ' ')
	{
		uint32_t location = (ConsolCursor.X + ConsolCursor.Y * ConsolSize.X) * 2;
		VideoRam[location] = ch;
		VideoRam[location +1] = color;
		// now Incrementing the cursor to next location
		ConsolCursor.X++;
	}
	else
	{
		// donothing...
	}
	
	// Checking for Boundary Condition
	if (ConsolCursor.X >= ConsolSize.X)
	{
		ConsolCursor.X = 0;
		ConsolCursor.Y++;
	}
	ConsolMoveCursor();	
}


void ConsolWriteChar(const char ch)
{
	ConsolWriteCharColored(ch, ConsolColor);
}
	
	
void ConsolWriteStringColored(const char *str, const uint8_t color)
{
	while (*str != 0)
	{
		ConsolWriteCharColored(*str, color);
		++str;
	}
}


void ConsolWriteString(const char *str)
{
	ConsolWriteStringColored(str, ConsolColor);
}
	
void NextLine(void)
{
	ConsolCursor.X = 0;
	ConsolCursor.Y++;
}	

void Tab(void)
{
	if (ConsolSize.X - ConsolCursor.X < TabWidth + 1)
	{
		ConsolCursor.Y++;
		ConsolCursor.X = 0;
	} else
	{
		ConsolCursor.X = ConsolCursor.X + TabWidth;
	}
}

void Space(void)
{
	ConsolWriteChar(' ');
}

void BackSpace(void)
{
	if (ConsolCursor.X == 0)
	{
		if (ConsolCursor.Y != 0)
		{
			ConsolCursor.Y--;
			ConsolCursor.X = ConsolSize.X - 1;
			ConsolWriteChar(' ');
			ConsolCursor.Y--;
			ConsolCursor.X = ConsolSize.X - 1;
		}
	}
	else
	{
		ConsolCursor.X--;
		ConsolWriteChar(' ');
		ConsolCursor.X--;
	}

	ConsolMoveCursor();
}

