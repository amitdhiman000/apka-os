#ifndef __KCONSOL_H__
#define __KCONSOL_H__

#include <kernel.h>
#include <ktypes.h>
#include <kmem.h>
#include <kio.h>

#define ConsolWidth 80
#define ConsolHeight 25
#define ConsolDefaultColor 0x07
#define TabWidth 5


enum colors
{
		Black 		= 0x0,
		Blue 		= 0x1,
		Green 		= 0x2,
		Cyan 		= 0x3,
		Red 		= 0x4,
		Megenta 	= 0x5,
		Brown 		= 0x6,
		LightGray 	= 0x7,
		DarkGray 	= 0x8,
		LightBlue 	= 0x9,
		LightGreen 	= 0xA,
		LightCyan 	= 0xB,
		LightRed    = 0xC,
		LightMagenta= 0xD,
		Yellow 		= 0xE,
		White 		= 0xF,
		BlueWhite   = 0x1F
		
};



extern void ConsolClear();
extern void SetConsolColor(unsigned char, unsigned char);
extern void ConsolWriteCharColored(char c,__uint8 color);
extern void ConsolWriteChar(char c);
extern void ConsolWriteStringSolored(string s,__uint8 color);
extern void ConsolWriteString(string s);
extern void putch(unsigned char c); // for keyboard input .
void NextLine();
void Tab();
void BackSpace();



#endif
