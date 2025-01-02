#include <stdio.h>
#include <math.h>

// Constants
#define SPEED_OF_SOUND 343.0   // Speed of sound in air (m/s)
#define EARTH_RADIUS 6371000.0 // Earth radius in meters

// Function to calculate Doppler shift
double calculateDopplerShift(double originalFreq, double receivedFreq) {
    return (receivedFreq - originalFreq) / originalFreq * SPEED_OF_SOUND;
}

// Function to calculate new latitude in radians
double calculateLatitudeChange(double distance, double heading) {
    return (distance / EARTH_RADIUS) * cos(heading * M_PI / 180.0);
}

// Function to calculate new longitude in radians
double calculateLongitudeChange(double distance, double heading, double latitude) {
    return (distance / (EARTH_RADIUS * cos(latitude))) * sin(heading * M_PI / 180.0);
}

int main() {
    double originalFreq, receivedFreqA, receivedFreqB, initialLat, initialLon, heading, time;

    // Get user inputs
    printf("Enter the initial latitude (degrees): ");
    scanf("%lf", &initialLat);
    initialLat = initialLat * M_PI / 180.0; // Convert to radians

    printf("Enter the initial longitude (degrees): ");
    scanf("%lf", &initialLon);
    initialLon = initialLon * M_PI / 180.0; // Convert to radians

    printf("Enter the original frequency (Hz): ");
    scanf("%lf", &originalFreq);

    printf("Enter the received frequency from transmitter A (Hz): ");
    scanf("%lf", &receivedFreqA);

    printf("Enter the received frequency from transmitter B (Hz): ");
    scanf("%lf", &receivedFreqB);

    printf("Enter the heading (degrees): ");
    scanf("%lf", &heading);

    printf("Enter the time (seconds): ");
    scanf("%lf", &time);

    // Calculate Doppler shifts
    double velocityA = calculateDopplerShift(originalFreq, receivedFreqA);
    double velocityB = calculateDopplerShift(originalFreq, receivedFreqB);
    printf("Speed from transmitter A: %.2f km/h\n", (velocityA * 3.6));
    printf("Speed from transmitter B: %.2f km/h\n", (velocityB * 3.6));

    // Calculate average speed
    double averageSpeed = (fabs(velocityA) + fabs(velocityB)) / 2.0;

    // Calculate distance traveled
    double distance = averageSpeed * time;

    // Calculate latitude and longitude changes
    double latChange = calculateLatitudeChange(distance, heading);
    double lonChange = calculateLongitudeChange(distance, heading, initialLat);

    // Calculate new coordinates in radians
    double newLat = initialLat + latChange;
    double newLon = initialLon + lonChange;

    // Convert new coordinates to degrees
    newLat = newLat * 180.0 / M_PI;
    newLon = newLon * 180.0 / M_PI;

    // Print the new coordinates in decimal degrees
    printf("New Latitude: %.6f\n", newLat);
    printf("New Longitude: %.6f\n", newLon);
    printf("New Position: %.6f, %.6f\n", newLat, newLon);

    return 0;
}

