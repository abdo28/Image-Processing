#include <stdio.h>
#include<cs50.h>
#include <stdint.h>
typedef uint8_t  BYTE;


int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: copy infile outfile\n");
        return 1;
    }

    // open file file
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        fprintf(stderr, "Could not open %s.\n",argv[1]);
        return 2;
    }

    BYTE arr[512];
    int numberoffile=0;
    bool findj=false;
    FILE *img;
   int  size=fread(arr,1,512,file);
   char filename[8];


    while(size==512){
        if(arr[0]==0xff&&arr[1]==0xd8&&arr[2]==0xff&&(arr[3] &0xf0)==0xe0){
            if (findj==false){
               findj=true;
               sprintf(filename,"%03i.jpg",numberoffile);
               img=fopen(filename,"w");
               fwrite(arr,1,512,img);
               numberoffile++;
            }
            else  if(findj==true){
                fclose(img);
                sprintf(filename,"%03i.jpg",numberoffile);
                img=fopen(filename,"w");
                fwrite(arr,1,512,img);
                numberoffile++;
            }
    }
        else if(findj==true){
            //fread(arr,1,512,file);
            fwrite(arr,1,512,img);
        }
        size=fread(arr,1,512,file);

    }
    fclose(img);
    fclose(file);
    return 0;
}