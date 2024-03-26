//
//  Arrays&Pointers.c
//  IE2_SOL1_Ashin
//  IE2_SOL1_Lab4
//  Created by Ashin Walpola on 26.11.23.
//

#define EARTH_RADIUS_KM 6371.0
#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
//defining the rows and columns
#define ROWS 7
#define COLUMNS 2

#include <stdio.h>
#include <stdlib.h> //to use abs(),labs() and fabs() function
#include <math.h> //to use cos(),sin() and acos(), and PI constant function
#include <string.h> //to use strcpy() func

double MaximumDistance(double coordinates[ROWS][COLUMNS], int* index1, int* index2);

//this function converts the degree radians to radians
double toRadians(double degree) {
    return degree * M_PI / 180.0;
}

//the function to calculate the local distance in km.
double localDistance(double lat1, double lon1, double lat2, double lon2) {
    double delta_y = 111.3 * fabs((lat1 - lat2)) ;
    double delta_x = 111.3 * cos(toRadians((lat1 + lat2) / 2)) * fabs((lon1 - lon2));
    double distance = sqrt((pow(delta_x, 2) + (pow(delta_y, 2)))) ;
    return distance;
}

//the function to calculate the global distance in km.
double distanceKm(double lat1, double lon1, double lat2, double lon2){
    double distance = (6378.388) * acos(sin(toRadians(lat1)) * sin(toRadians(lat2)) + cos(toRadians(lat1)) * cos(toRadians(lat2)) * cos(toRadians((lon1 - lon2))) ) ;
    return distance;
}

//MAIN FUNCTION
int main(void){
    //initializing the variables for
    double temp;
    char Location1[20] = { '\0' };
    char Location2[20] = { '\0' };
    //null terminators to decrease the errors.
    
    //initializing the arrays
    //for latitude
    
    //code for 16.1 (1-D Arrays)
    double latitude[9] = { 53.557029, 53.557166, 53.557274, 53.560288, 53.561306, 53.562015, 53.558241, 53.557900, 53.557203};
    double longitude[9] = { 10.022918, 10.021343, 10.020297, 10.014906, 10.015426, 10.016568, 10.023244 ,10.022142, 10.022632 };
    int locations [9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    
    for (int i = 0; i < 9; i ++) {
        printf("%d- %lf, %lf\n",locations[i], latitude[i], longitude[i]);
    }
    
    //int points = (sizeof(latitude) / sizeof(longitude));
    double distanceBetweenPoints; //holds values of the distances
    double RouteDistance = 0.0;
    for (int  i = 0; i < (8); i++)
    {
        /*
        double latitude_1 = latitude[i]; //holdes the latitude for the next calculation
        double latitude_2 = latitude[i + 1];
        double longitude_1 = longitude[i]; //holdes the longitude for the next calculation
        double longitude_2 = longitude[i + 1];
        */

        distanceBetweenPoints = distanceKm(latitude[i], longitude[i], latitude[i + 1], longitude[i + 1]);
        RouteDistance += distanceBetweenPoints;

    }
    printf("The Distance between Points: %lf\n", RouteDistance);


    //code for exercise 16.2 (2-D Arrays)
    char *Location[] = {"HAW Hamburg", "Eiffel Tower", "Palma de Mallorca", "Las Vegas", "Copacabana", "Waikiki Beach", "Surfer's Paradise" };
    
    double coordinates[ROWS][COLUMNS] = {
        {53.557029, 10.022918}, //HAW Hamburg
        {48.858363, 2.294481}, //Eiffel Tower
        {39.562553, 2.661947}, //Palma de Mallorca
        {36.156214, -115.148736}, //Las Vegas
        {-22.971177, -43.182543}, //Copacabana
        {21.281004, -157.837456}, //Waikiki Beach
        {-28.002695, 153.431781}, //Surfer's Paradise
    };
    //printing the GeoGraphic Coordinates
    printf("\n");
    
    printf("Geo Graphic Coordinates\n");
    
    printf("    Location           Latitude       Longitude\n");
    for (int i = 0; i<ROWS; i ++) {
        printf("%15s      %10lf     %10lf\n", Location[i],coordinates[i][0],coordinates[i][1]);
    }
    
    printf("\n");
    //printing the addresses of locations
    for (int i = 0; i<ROWS; i++) {
        printf("%s Address: %p\n",Location[i] ,&Location[i]);
    }
    
    printf("\n");
    
    //testing the function
    printf("Testing the initial Function\n");
    double result = distanceKm(coordinates[0][0], coordinates[0][1], coordinates[1][0], coordinates[1][1]);
    printf("%s - %s Distance: %lf\n", Location[0], Location[1], result);
    
    printf("\n");
    //double maxDistance = 0.0;
    
    //printing all the distances between the locations.
    
    for (int i = 0; i < 6; i++) {
        
        for (int j = 0; j < 6; j++){
          
            temp = distanceKm(coordinates[i][0], coordinates[j + 1][0], coordinates[i][1], coordinates[j + 1][1]);
            strcpy(Location1, Location[i]);
            strcpy(Location2, Location[j+1]);
            printf("%s -- %s =  %lf Km\n",Location1, Location2 ,temp);
        }
    }
    
    int idx1, idx2;
    double temp1 = MaximumDistance(coordinates, &idx1, &idx2);
    printf("%lf, %d,%d \n",temp1, idx1,idx2);
    //function that prints out the highest distance
    //printf("%s and %s has the highest distance %.3lf km! consider taking a flight:)\n", Location1, Location2, maxDistance);
    
    return 0;
}

double MaximumDistance(double coordinates[ROWS][COLUMNS], int* index1, int* index2) {
    
    double maxDistance = 0.0;
    for (int i = 0; i < 6; i++) {

        for (int j = 0; j < 6; j++) {

           double temp = distanceKm(coordinates[i][0], coordinates[i][1], coordinates[j + 1][0], coordinates[j + 1][1]);
            if (temp > maxDistance) {
                maxDistance = temp;
                *index1 = i;
                *index2 = j;
            }
            
        }

    }
   
    //final
    
    return maxDistance;
}

