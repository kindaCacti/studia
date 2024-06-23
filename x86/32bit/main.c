#include <stdio.h>
#include <stdlib.h>

extern int check_marker(int* x, int* y, unsigned char* data);

int main(int argc, char* argv[]){

    if(argc != 2){
        printf("%s", "\n\ninvalid number of arguments (1 expected)\n\n");
        return 0;
    }

    int header_size = 54*sizeof(unsigned char);
    unsigned char* header;
    FILE* fptr;
    fptr = fopen(argv[1], "r");

    if(fptr == NULL){
        printf("%s", "\ninvalid file name\n\n");
        return 0;
    }

    header = (unsigned char*) malloc(header_size);
    fgets(header, header_size, fptr);
    fclose(fptr);

    if(header[0] != 'B' || header[1] != 'M'){
        printf("%s","wrong file format (24bit bitmap expected)");
        return 0;
    }

    unsigned int width = 0, height = 0, file_size = 0;
    width += (unsigned int)header[18];
    width += (unsigned int)header[19] * (1<<8);

    height += (unsigned int)header[22];
    height += (unsigned int)header[23] * (1<<8);

    file_size += header[2];
    file_size += header[3] * (1<<8);
    file_size += header[4] * (1<<16);
    file_size += header[5] * (1<<24);

    printf("%s", "size of the bitmap: ");

    printf("%i", width);
    printf("%s", " x ");

    printf("%i", height);

    printf("%s", "\nfile size (in bytes) is: ");
    printf("%i", file_size);

    unsigned char* data = malloc(file_size * sizeof(unsigned char));
    fptr = fopen(argv[1], "r");
    fgets(data, file_size, fptr);
    fclose(fptr);

    for(int i = 0; i<width; i++){
        for(int j = 0; j<height; j++){
            int tmp = check_marker(&i, &j, data);
            if(tmp){
                printf("%s", "\nmarker: ");
                printf("%i", i);
                printf("%s", "x");
                printf("%i", j);
            }
        }
    }

    free(data);
    printf("%s", "\n\n\nend of running\n\n\n");
    return 0;
}