#include "sensor.h"
#include <stdio.h>
#include <stdlib.h>

FILE *file;

int getNextData() {
    int data;
    fscanf(file,"%d",&data);

    return data; // return sensor value
}

FILE* openfile(const char* filename) {
    file = fopen(filename, "r"); // Replace NULL with the actual file object

    return file;
}
