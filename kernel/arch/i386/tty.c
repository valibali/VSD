#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <kernel/vga.h>
#include <kernel/tty.h>

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

void terminal_initialize(void)
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = make_color(COLOR_LIGHT_GREY, COLOR_BLACK);
	terminal_buffer = VGA_MEMORY;
	for ( size_t y = 0; y < VGA_HEIGHT; y++ )
	{
		for ( size_t x = 0; x < VGA_WIDTH; x++ )
		{
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = make_vgaentry(' ', terminal_color);
		}
	}
}

void terminal_setcolor(uint8_t color)
{
	terminal_color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = make_vgaentry(c, color);
}

void terminal_putchar(char c)
{
    switch (c)
    {
        case ((char)'\n'):
            terminal_column = 0;
            terminal_row++;
            break;
        default:
            terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
            if ( ++terminal_column == VGA_WIDTH )
                {
                    terminal_column = 0;
                    if ( ++terminal_row == VGA_HEIGHT )
                    {
                            terminal_row = 0;
                    }
                }
            break;
    }
}

void terminal_write(const char* data, size_t size)
{
	for ( size_t i = 0; i < size; i++ )
		terminal_putchar(data[i]);
}

void terminal_writestring(const char* data)
{
	terminal_write(data, strlen(data));
}

void terminal_write_hex(uint32_t n)
{
    int32_t tmp;

    terminal_writestring("0x");

    char noZeroes = 1;

    int i;
    for (i = 28; i > 0; i -= 4)
    {
        tmp = (n >> i) & 0xF;
        if (tmp == 0 && noZeroes != 0)
        {
            continue;
        }
    
        if (tmp >= 0xA)
        {
            noZeroes = 0;
            terminal_putchar (tmp-0xA+'a' );
        }
        else
        {
            noZeroes = 0;
            terminal_putchar( tmp+'0' );
        }
    }
  
    tmp = n & 0xF;
    if (tmp >= 0xA)
    {
        terminal_putchar (tmp-0xA+'a');
    }
    else
    {
        terminal_putchar (tmp+'0');
    }

}

void terminal_write_dec(uint32_t n)
{

    if (n == 0)
    {
        terminal_putchar('0');
        return;
    }

    int32_t acc = n;
    char c[32];
    int i = 0;
    while (acc > 0)
    {
        c[i] = '0' + acc%10;
        acc /= 10;
        i++;
    }
    c[i] = 0;

    char c2[32];
    c2[i--] = 0;
    int j = 0;
    while(i >= 0)
    {
        c2[i--] = c[j++];
    }
    terminal_writestring(c2);

}