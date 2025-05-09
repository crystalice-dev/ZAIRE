#include <globalVar.h> 

char gps_latitude[1024];
char gps_longitude[1024];
float gps_elevation = 0;
uint8_t gps_speed = 0;

void gps_get_lat_lon_speed(const char* line) {
    char gps[13][20]; // 13 fields, each max 20 characters
    int index = 0;
    int subIndex = 0;

    for (int i = 0; line[i] != '\0' && index < 13; i++) {
        if (line[i] == ',') {
            gps[index][subIndex] = '\0';  // Null-terminate current token
            index++;
            subIndex = 0;
        } else {
            gps[index][subIndex++] = line[i];
        }
    }
    gps[index][subIndex] = '\0'; // Null-terminate last token if needed

    snprintf(gps_latitude, sizeof(gps_latitude),"%s° %s", gps[3], gps[4]);
    snprintf(gps_longitude, sizeof(gps_longitude),"%s° %s", gps[5], gps[6]);
    // Example use
    printf("Location: %s ",gps_latitude);
    printf("%s\n",gps_longitude);
    // printf("Speed (knots): %s\n", gps[7]);
}

void gps_get_alt(const char* line){
    char *fields[15] = {0};
    char buffer[128];
    strncpy(buffer, line, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';

    // Tokenize
    int i = 0;
    char *token = strtok(buffer, ",");
    while (token && i < 15) {
        fields[i++] = token;
        token = strtok(NULL, ",");
    }

    if (i < 10) {
        printf("Invalid GPGGA sentence\n");
        return;
    }


    printf("Altitude: %s %s\n", fields[9], fields[10]);
    float data = atof(fields[9]);
    printf("data: %.2f\n", data);
}