// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: copy infile outfile\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];
    int n=atoi(argv[1]);


    // open input file
    FILE *inptr = fopen( infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 1;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 1;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 1;
    }

       bi.biWidth*=n;
       bi.biHeight*=n;
       int padding= (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
       bi.biSizeImage=((sizeof(RGBTRIPLE)*bi.biWidth)+padding)*abs(bi.biHeight);
       bf.bfSize= bi.biSizeImage+sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);
    BYTE arr[1000000];
    int x=0;

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight/n); i < biHeight; i++)
    {
        x=0;
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth/n; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            int k;
            for( k=0;k<n;k++){
               arr[x]=triple.rgbtBlue;
                  x++;
               arr[x]=triple.rgbtGreen;
                  x++;
               arr[x]=triple.rgbtRed;
                   x++;
            }





            // write RGB triple to outfile
           // fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
        }
        padding= (4 - ((bi.biWidth) * sizeof(RGBTRIPLE)) % 4) % 4;

        for(int o=0 ; o<n ; o++){
            for(int h=0 ; h<x ;h++){
               fputc(arr[h],outptr);}
             // then add it back (to demonstrate how)
            for (int m = 0; m < padding ; m++){
               fputc(0x00, outptr);}
        }

         // skip over padding, if any
        padding= (4 - ((bi.biWidth/n) * sizeof(RGBTRIPLE)) % 4) % 4;
        fseek(inptr, padding, SEEK_CUR);

    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
