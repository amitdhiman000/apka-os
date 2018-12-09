#include <kmouse.h>
#include <ktypes.h>
#include <kio.h>
#include <kirq.h>

#include <stdio.h>


#define MOUSE_READ_PORT 0x60
#define MOUSE_WRITE_PORT 0x64


byte_t mouse_cycle = 0;
int8_t mouse_byte[3];
int32_t mouse_x = 0;
int32_t mouse_y = 0;

//Mouse functions
void mouse_handler(regs_t *regs) //struct regs *a_r (not used but just there)
{
    switch(mouse_cycle)
    {
        case 0:
        {
            mouse_byte[0] = inportb(MOUSE_READ_PORT);
            mouse_cycle++;
            break;
        }
        case 1:
        {
            mouse_byte[1] = inportb(MOUSE_READ_PORT);
            mouse_cycle++;
            break;
        }
        case 2:
        {
            mouse_byte[2] = inportb(MOUSE_READ_PORT);
            mouse_x = mouse_byte[1];
            mouse_y = mouse_byte[2];
            mouse_cycle = 0;
            printf("Mouse Move\n");
            printf("mouse pos : x: %d, y: %d\n", mouse_x, mouse_y);
            break;
        }
    }
}

void mouse_wait(byte_t a_type)
{
    uint32_t time_out = 100000;
    if (a_type == 0)
    {
        while( time_out--) //Data
        {
            if((inportb(MOUSE_WRITE_PORT) & 1) == 1)
            {
                return;
            }
        }
        return;
    }
    else
    {
        while( time_out--) //Signal
        {
            if((inportb(MOUSE_WRITE_PORT) & 2) == 0)
            {
                return;
            }
        }
        return;
    }
}

void mouse_write(byte_t a_write) //unsigned char
{
    //Wait to be able to send a command
    mouse_wait(1);
    //Tell the mouse we are sending a command
    outportb(MOUSE_WRITE_PORT, 0xD4);
    //Wait for the final part
    mouse_wait(1);
    //Finally write
    outportb(MOUSE_READ_PORT, a_write);
}

byte_t mouse_read(void)
{
  //Get's response from mouse
  mouse_wait(0); 
  return inportb(MOUSE_READ_PORT);
}

void mouse_install(void)
{
    byte_t _status;  //unsigned char

    //Enable the auxiliary mouse device
    mouse_wait(1);
    outportb(MOUSE_WRITE_PORT, 0xA8);

    //Enable the interrupts
    mouse_wait(1);
    outportb(MOUSE_WRITE_PORT, 0x20);
    mouse_wait(0);
    _status = (inportb(0x60) | 2);
    mouse_wait(1);
    outportb(MOUSE_WRITE_PORT, 0x60);
    mouse_wait(1);
    outportb(MOUSE_READ_PORT, _status);

    //Tell the mouse to use default settings
    mouse_write(0xF6);
    mouse_read();  //Acknowledge

    //Enable the mouse
    mouse_write(0xF4);
    mouse_read();  //Acknowledge

    //Setup the mouse handler
    irq_install_handler(12, mouse_handler);
}