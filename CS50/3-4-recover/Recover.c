#include <stdio.h>
#include <stdlib.h>

const int b_len = 512;
int block_control(unsigned char *tempb_lock);
int end_control(unsigned char *temp_block, int real_len);
int main(int argc, char *argv[])
{
    // checking the number of arguments
    if (argc != 2)
    {
        fprintf(stderr, "Usage: recoverfile\n" );
        return 1;
    }

    // remember infile's filename
    char *infile = argv[1];

    // creating the infile flow
    FILE *card_flow = fopen(infile, "r");

    // checking the existance of the infile
    if (card_flow == NULL)
    {
        fprintf(stderr, "The file to be recovered has to exist!!\n" );
        return 2;
    }

    // creating the real length of 512B block variable
    int real_len;

    // creating the temporary char
    unsigned char *temp_block;
    temp_block = malloc(sizeof(char) * b_len);

    // creating the 1 main bool variable
    int bool_value_1;

    // creating the temporary filename
    char *filename;
    filename = malloc(sizeof(char) * 3);

    // the looking for the start of the start of the JPEG
    do
    {
        // reading the data from infile
        fread(temp_block, 1, b_len, card_flow);

        // getting the meaning of the control of the 512 MB block by bool_value_1
        bool_value_1 = block_control(temp_block);
    }
    while (bool_value_1 == 1);

    // setting the counter No2
    int count_2 = 0;

    // creating the stop-point
    stop: ;

    // rename the new image file (before creating it!!!!)
    sprintf(filename, "%03i.jpg", count_2);

    // creating and openning the new image file
    FILE *pic_1 = fopen(filename, "w");

    // checking the existance of the outfile
    if (pic_1 == NULL)
    {
        fprintf(stderr, "The outfile does not exist!!\n" );
        return 3;
    }

    // creating the 2 main bool variable
    int bool_value_2;

    // creating the 3 main bool variable
    int bool_value_3;

    do
    {
        // writing the new image file
        fwrite(temp_block, 1, b_len, pic_1);

        // defining the real length of 512B block
        real_len = fread(temp_block, 1, b_len, card_flow);

        // getting the meaning of the control of the 512 MB block by bool_value_2
        bool_value_2 = block_control(temp_block);

        // getting the meaning of the control of the 512 MB block by bool_value_3
        bool_value_3 = end_control(temp_block, real_len);
    }
    while (bool_value_2 == 1 && bool_value_3 == 1);

    // writing the end of the last image
    if (bool_value_3 == 0)
    {
        fwrite(temp_block, 1, real_len, pic_1);
    }

    // increasing the counter N02 by 1
    count_2 ++ ;

    // closing the new image file
    fclose(pic_1);

    if (bool_value_2 == 0 && bool_value_3 == 1)
    {
        goto stop;
    }

    // making free temp_block memory
    free(temp_block);

    // making free the temporary file name memory
    free(filename);

    // closing th infile flow
    fclose(card_flow);

    // success
    return 0;
}

// control of the 512B block
int block_control(unsigned char *temp_block)
{
    // we have reached the beginning of a new image
    if (temp_block[0] == 0xff &&
        temp_block[1] == 0xd8 &&
        temp_block[2] == 0xff &&
        (temp_block[3] >= 0xe0 && temp_block[3] <= 0xef))
    {
        return 0;
    }

    // we have NOT reached the beginning of a new image
    else
    {
        return 1;
    }
}

// control of the end
int end_control(unsigned char *temp_block, int real_len)
{
    // we have reached the end of the last image
    if (real_len < b_len)
     {
         return 0;
     }

    // we have NOT reached the end of the last image
    else
    {
        return 1;
    }
}
