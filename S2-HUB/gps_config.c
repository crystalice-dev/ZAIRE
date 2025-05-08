#include <globalVar.h> 

char* gps_latitude = "4255.11094";
char* gps_latitude_P = "-";
char* gps_longitude = "07124.23864";
char* gps_longitude_P = "-";
char* gps_elevation = "0FT";



void gps_get_lat_lon_speed(const char* line){
    uint8_t index = 0;
    uint8_t sub_index = 0;

    for(int i = 0; i < 100; i++){
        if(line[i] == ','){
            printf("\n");
            index += 1;
            i++;
        }
        
        if(index == 3 && sub_index < 10){
            gps_latitude[sub_index] = line[i];
            sub_index += 1;
            
        }
        if(index == 4){
            sub_index = 0;
            gps_latitude_P[sub_index] = line[i];
            sub_index = 0;
            break;
        }

        if(line[i] == '\0' || line[i] == '\n'){
            printf("\n");
            break;
        }
    }
    printf("%s\n", line);
    printf("%s\n", gps_latitude);
    printf("%s\n", gps_latitude_P);
    printf("%s\n", gps_longitude);
    printf("%s\n", gps_longitude_P);
}

void gps_get_alt(const char* line){
    //printf("A: %s\n", line);
}