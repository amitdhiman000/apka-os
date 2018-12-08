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
	BlueWhite   = 0x1F,
};

typedef struct {
	int32_t X;
	int32_t Y;
} point_t;

typedef struct {
	uint32_t X;
	uint32_t Y;
} upoint_t;

extern void ConsolClear(void);

extern void SetConsolColor(const byte_t fg, const byte_t bg);

extern void ConsolWriteChar(const char ch);

extern void ConsolWriteCharColored(const char ch, uint8_t color);

extern void ConsolWriteStringColored(const char *str, uint8_t color);

extern void ConsolWriteString(const char *str);

extern void putch(const byte_t c); // for keyboard input .

extern void NextLine();

extern void Tab();

extern void BackSpace();

#endif /* __KCONSOL_H__ */
