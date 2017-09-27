#include "sensor.h"
#include <stdio.h>
#include <stdlib.h>

FILE *file;

int getNextData() {
    int data;
    if (file){
        fscanf(file,"%d",&data);
    }else {
        printf("File not found, aborting with 0.");
        return 0;
    }
    return data; // return sensor value
}

FILE* openfile(const char* filename) {
    file = fopen(filename, "r"); // Replace NULL with the actual file object

    return file;
}
