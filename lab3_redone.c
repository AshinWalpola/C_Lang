//
//  lab3_redone.c
//  IE2_SOL1_Ashin
//
//  Created by Ashin Walpola on 30.11.23.
//

//library functions
#define EARTH_RADIUS_KM 6371.0
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> //to use abs(),labs() and fabs() function
#include <math.h> //to use cos(),sin() and acos(), and PI constant function

int isNorthernHemisphere(float latitude){
    if (latitude >=0) {
        return 1; //returns value if in the norhtern hemisphere.
    }
    else {
        return 0; //returns this if the latitude is not in the southern hemisphere.
    }
}

bool isNorthernHemisphere(double latitude) {
    // Check if the latitude is in the Northern Hemisphere (0 to 90 degrees)
    return (latitude >= 0.0 && latitude <= 90.0);
}

bool isSouthernHemisphere(double latitude) {
    // Check if the latitude is in the Southern Hemisphere (-90 to 0 degrees)
    return (latitude >= -90.0 && latitude < 0.0);
}

/*
 int main(int argc, const char * argv[]) {
     // insert code here...
     printf("Hello, World!\n");
     double LocationLatitude = 47.7128;
     
     if (isNorthernHemisphere(LocationLatitude)) {
         printf("Location in N Hemisphere or Equator\n");
     } else {
         printf("Location in S Hemisphere or Equator\n");
     }
     
     double LocationLongitude = -44.8848;
     if (isSouthernHemisphere(LocationLongitude)) {
         printf("Location in S Hemisphere or Equator\n");
     } else {
         printf("Koheda OII Yanne Southern Hemishphere newei bung.\n");
     }
     return 0;
 }
 */

double toRadians(double degree) {
    return degree * M_PI / 180.0;
}

double distanceKm(double lat1, double lon1, double lat2, double lon2) {
    double delta_y = 111.3 * fabs((lat1 - lat2)) ;
    double delta_x = 111.3 * cos(toRadians((lat1 + lat2) / 2)) * fabs((lon1 - lon2));
    double distance = sqrt((pow(delta_x, 2) + (pow(delta_y, 2)))) ;
    return distance;
}

double localDistanceKm(double lat1, double lon1, double lat2, double lon2){
    double distance = (6378.388) * acos(sin(toRadians(lat1)) * sin(toRadians(lat2)) + cos(toRadians(lat1)) * cos(toRadians(lat2)) * cos(toRadians((lon1 - lon2))) ) ;
    return distance;
}

int main(void){
    
    float latitude;
    float longitude;
    //assigning values to latitude & longitude variables
    printf("Enter a Latitude: ");
    scanf("%f", &latitude);
    printf("Enter a Longitude: ");
    scanf("%f", &longitude);
    
    if (isNorthernHemisphere(latitude)) {
        printf("Is in Northern Hemisphere\n\n");
    }
    else{
        printf("Is in the Southern Hemisphere\n\n");
    }
    double latitude1 = 53.557078;
    double longitude1 = 10.023109;
    //this is the location of HAW
    
    double latitude2 [6] = {48.858363, 39.562553, 36.156214, -22.971177, 21.281004, -28.002695};
    double longitude2 [6] = {2.294481, 2.661947, -115.148736, -43.182543, -157.837456, 153.431781};
    char locations [6][100] = {"Eiffel Tower", "Palma de Mallorca", "Las Vegas", "Copacabana", "Waikiki Beach", "Surfer’s Paradise" };

    printf("City---Local Distance---Global Distance\n");
    
    for (int i=0; i<6; i++) {
        double result = distanceKm(latitude1 , longitude1 , latitude2 [i], longitude2 [i]);
        double longresult = localDistanceKm(latitude1, longitude1, latitude2 [i], longitude2 [i]);
        
        
        printf("%s----------%.2f km ---%.2f km\n",locations[i], result, longresult);
        
    }
    
    
    return 0 ;
}
