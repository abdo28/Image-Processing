# Questions

## What's `stdint.h`?

Is a library that contains ** integer variables types** used in *bmp.h*

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

To determine the type of **integer** variables (used in bmp.h) whether it is *signed* integer or *unsigned* integer
or  whether the length of this integer  variable is 8-bit , 16-bit or etc.


## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

* 1
* 4
* 4
* 2

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

0x4d42

## What's the difference between `bfSize` and `biSize`?

bfsize represent* number of bytes __of the bitmap__ file* , while bisize represent *number of bytes __in the BITMAPINFOHEADER__ structure*

## What does it mean if `biHeight` is negative?

This makes a difference in how the image is stored in memory
*details*
so, if biHeight is negative ,the bitmap is a *top-down DIB*and its origin is the **upper-left** corner,
which is mean that  The top row of the image is the first row in memory, followed by the next row down.
The bottom row of the image is the last row in the buffer.
With a top-down DIB, the first byte in memory is the top-left pixel of the image.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitCount

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

if there is**no file** at all,so the program will face a segmentation error.

## Why is the third argument to `fread` always `1` in our code?

because any file contain **just one** *BITMAPFILEHEADER*
and **just one** *BITMAPINFOHEADER* .( the third argument represent the __quantity__ of the element (the struct)that the function will read)

## What value does line 63 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

3

## What does `fseek` do?

is used to **move file pointer** associated with a given file to a specific position.
in copy.c  we copy file and it is  skip over padding, if any.because ,this program will copy file content  to the other file without  any extra padding  .


## What is `SEEK_CUR`?


position from where offset is added,**current position** from where offset is added.
