//
//  sol1_lab5.c
//  SOL1_Lab5

//  Created by Ashin Walpola on 24.12.23.
//  Author: Ashin Walpola
#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

//  17.1 Travel Planning using Double Arrays

double toRadians(double degree);
double localDistance(double lat1, double lon1, double lat2, double lon2);
double distanceKm(double lat1, double lon1, double lat2, double lon2);
bool isNumeric(const char *string);

int main(int argc, const char * argv[]) {
    int numWaypoints;
    char input[50];
    double *latitudes, *longitudes;
    
    
    do {
        printf("Enter the number of Waypoints (up to 20): ");
        scanf("%s", input);
        
        if (!isNumeric(input)) {
            printf("Invalid input. Please enter a numeric value.\n");
            numWaypoints = -1; //setting an invalid number to repeat the loop
        }
        else {
            numWaypoints = atoi(input); //convert the string to integer
            if (numWaypoints <=1) {
                printf("Invalid input. Number of waypoints cannot be less than 2\n");
            }
        }
    } while(numWaypoints <= 1 || numWaypoints >20);
    
    latitudes = (double *)malloc(numWaypoints *sizeof(double));
    longitudes = (double *)malloc(numWaypoints *sizeof(double));
    
    if (latitudes == NULL || longitudes == NULL) {
        printf("Memory Allocation Failed. Terminating... \n");
        return 1; //--"Exit Code 1 means that a container terminated, typically due to an application error or an invalid reference. An application error is a programming error in any code running within the container." --Source Internet
    }
    
    //Input Coordinates
    for (int i=0; i < numWaypoints; i++) {
        printf("Enter Coordinates for WayPoint Number: %d (Format: Latitude Longitude): ", i+1);
        scanf("%lf %lf", &latitudes[i], &longitudes[i]);
        //this will point all the user inputed coordinates into the separate strings
    }
    //this is just to see the coordinates the user entered
    printf("You Entered the Coordinates\n");
    for (int i = 0; i < numWaypoints; i ++) {
        printf("%.2lf %.2lf\n", latitudes[i], longitudes[i]);
    }
    
    //Calculate the total distance
    double totalDistance = 0.0;
    for (int i = 0; i < numWaypoints - 1; i++) {
        totalDistance += distanceKm(latitudes[i], longitudes[i], latitudes [i+1], longitudes[i+1]);
    }
    
    printf("The Overall length of the route is: %lf kilometers\n", totalDistance );
    
    //free dynamically allocated memory
    free(latitudes);
    free(longitudes);
    
    return 0;
}

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

//fucntion to check if the input is an number
bool isNumeric(const char *string){
    while (*string) {
        if (*string < '0' || *string > '9') {
            return false;
        }
        string++;
    }
    return true;
}
