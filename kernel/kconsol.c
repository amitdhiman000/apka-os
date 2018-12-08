#include <kconsol.h>

upoint ConsolCursor = {0, 0};
upoint ConsolSize={ConsolWidth, ConsolHeight};
__uint8 ConsolColor=ConsolDefaultColor;
__uint8* VideoRam=(__uint8*)VIDEO_RAM;

void ConsolClear()
{
	/*
	__uint32 i,l;
	for(i=0;i<ConsolSize.X*ConsolSize.Y*2;i++)
	{
	VideoRam[2*i]=0x00;
	VideoRam[2*i+1]=0x1F;
	}
	*/
		memsetw(VideoRam,0x1F00,ConsolSize.X*ConsolSize.Y);
		ConsolCursor.X=0;
		ConsolCursor.Y=0;
		ConsolMoveCursor();
}
	
	

/* Sets the forecolor and backcolor that we will use */
void SetConsolColor(unsigned char forecolor, unsigned char backcolor)
{
    /* Top 4 bytes are the background, bottom 4 bytes
    *  are the foreground color */
    ConsolColor = (backcolor << 4) | (forecolor & 0x0F);
}
	
	
	
void ConsolWriteCharColored(char c,__uint8 color)
{
	if(ConsolCursor.Y >= ConsolSize.Y)
	ConsolScroll();
	
	
	if(c=='\n')
	{
		ConsolCursor.Y++;
		ConsolCursor.X=0;
	}
	else if(c=='\t')
	{
		if(ConsolSize.X-ConsolCursor.X<6)
		ConsolCursor.Y++,ConsolCursor.X=0;
		else
		ConsolCursor.X=ConsolCursor.X+TabWidth;
		
	}
	else if(c=='\b')
	{
		BackSpace();
	}
	else if(c=='\r')
	{
		ConsolCursor.X=0;
	}
	else if(c >=' ')
	{
		__uint32 location=(ConsolCursor.X + ConsolCursor.Y*ConsolSize.X)*2;
		VideoRam[location]=c;
		VideoRam[location +1]=color;
	
		// now Incrementing the cursor to next location
		ConsolCursor.X++;
	}
	else
	{
		// donothing...
	}
	
		// Checking for Boundary Condition
		if(ConsolCursor.X>=ConsolSize.X)
		{
			ConsolCursor.X=0;
			ConsolCursor.Y++;
		}
		ConsolMoveCursor();
		
}
	
	
void ConsolWriteChar(char c)
{
	ConsolWriteCharColored(c,ConsolColor);
	}
	
	
	
void ConsolWriteStringColored(string s,__uint8 color)
{
	while(*s != 0)
	{
		ConsolWriteCharColored(*s,color);
		s++;
		}
	
}



void ConsolWriteString(string s)
{
	ConsolWriteStringColored(s,ConsolColor);
	}




void ConsolScroll(void)
{
	__uint32 temp;
    __uint16 blank=0x1F00;
	
        /* Move the current text chunk that makes up the screen
        *  back in the buffer by a line */
        temp = ConsolCursor.Y - ConsolSize.Y + 1;
        memcpy (VideoRam, VideoRam + temp * ConsolSize.X*2, (ConsolSize.Y - temp) * ConsolSize.X * 2);
        /* Finally, we set the chunk of memory that occupies
          the last line of text to our 'blank' character */
       memsetw (VideoRam + (ConsolSize.Y - temp) * ConsolSize.X*2, blank, ConsolSize.X);
       ConsolCursor.Y = ConsolSize.Y - 1;
}




/* Updates the hardware cursor: the little blinking line
*  on the screen under the last character pressed! */
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


	
void NextLine()
{
		ConsolCursor.X=0;
		ConsolCursor.Y++;
}	

void Tab()
{
	if(ConsolSize.X-ConsolCursor.X<TabWidth+1)
		ConsolCursor.Y++,ConsolCursor.X=0;
		else
		ConsolCursor.X=ConsolCursor.X+TabWidth;
	
	}
	
void BackSpace()
{
	if(ConsolCursor.X==0)
	{
		if(ConsolCursor.Y!=0)
		{
			ConsolCursor.Y--;
			ConsolCursor.X=ConsolSize.X-1;
			ConsolWriteChar(' ');
			ConsolCursor.Y--;
			ConsolCursor.X=ConsolSize.X-1;
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

