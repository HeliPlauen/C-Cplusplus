// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: scale (a positive integer) infile outfile\n");
        return 1;
    }

    // remember filenames
    char *scale = argv[1];
    char *infile = argv[2];
    char *outfile = argv[3];

    // argv[1] - control
    float scale3 = atof(scale);

    if (scale3 >= 100)
    {
        printf("Input the positive intrger (less, than 100) for scale!!!!\n");
        return 1;
    }

    // open input file
    FILE *inptr = fopen(infile, "r");
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
    int aaa = bf.bfSize;

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    int xx = bi.biHeight;
    int yy = bi.biWidth;

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 1;
    }

    // determine padding for old scanlines
    int padding1 = (4 - (yy * sizeof(RGBTRIPLE)) % 4) % 4;

    // determine padding for new scanlines   ./ResizeM 2 small.bmp large.bmp    ./ResizeM 0.5 large.bmp small2.bmp
    int padding;
    int scale4;
    if (scale3 > 1)
    {
        int scale5 = scale3;
        padding = (4 - (yy * scale5 * sizeof(RGBTRIPLE)) % 4) % 4;
    }
    else
    {
        scale4 = 1 / scale3;
        padding = (4 - ((yy / scale4) * sizeof(RGBTRIPLE)) % 4) % 4;
    }

    //changing bf.bfSize
    if (scale3 != 1)
    {
        bf.bfSize = (aaa - abs(xx) * padding1 - 54) * scale3 * scale3 + padding * abs(xx) * scale3 + 54;
    }

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // Scalling global width and height
    if (scale3 != 1)
    {
        bi.biWidth *= scale3;
        bi.biHeight *= scale3;
    }

    if (scale3 != 1)
    {
        bi.biSizeImage = (bi.biWidth * sizeof(RGBTRIPLE) + padding) * abs(bi.biHeight);
    }

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    if (scale3 > 1)
    {
        for (int i = 0, mod = abs(xx); i < mod; i++)
        {
            // set the score
            int score = 0;

            while(1 == 1)
            {
                for (int j = 0; j < yy; j++)
                {
                    // temporary storage
                    RGBTRIPLE triple;

                    // read RGB triple from infile
                    fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                    // write RGB triple to sluce
                    for (int k = 0; k < scale3; k ++)
                    {
                        fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                    }
                }

                // then add it back (to demonstrate how)
                for (int k = 0; k < padding; k++)
                {
                    fputc(0x00, outptr);
                }
                score ++ ;

                // skip over intpr for creating a ney copy of
                if (score < scale3)
                {
                    fseek(inptr, - sizeof(RGBTRIPLE) * yy, SEEK_CUR);
                }
                else
                {
                    break;
                }
            }

            // skip over padding, if any
            fseek(inptr, padding1, SEEK_CUR);
        }
    }
    else
    {
        for (int i = 0, mod = abs(xx); i < mod; i++)
        {
            if (i % scale4 == 0)
            {
                for (int j = 0; j < yy; j++)
                {
                    // temporary storage
                    RGBTRIPLE triple;

                    // defying the counting to avoid the pixels
                    int padding2 = scale4 - 1;

                    // read and write RGB triple from infile
                    if (j % scale4 == 0)
                    {
                        fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                        fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                    }
                    else
                    {
                        fseek(inptr, sizeof(RGBTRIPLE) * padding2, SEEK_CUR);
                    }
                }

                // then add it back (to demonstrate how)
                for (int k = 0; k < padding; k++)
                {
                    fputc(0x00, outptr);
                }

                // skip over padding, if any
                fseek(inptr, padding1, SEEK_CUR);
            }
            else
            {
                // skip over padding, if any
                fseek(inptr, sizeof(RGBTRIPLE) * yy + padding1, SEEK_CUR);
            }
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}



