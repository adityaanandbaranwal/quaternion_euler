#define _USE_MATH_DEFINES
#include <stdio.h>
#include <math.h>

double deg_rad(double ang) {
    double rad = (ang/360) * M_PI;
    return rad;
}

int main() {
    printf("\nThis is a program to interconvert between unit quaternion and"
    " Euler angles.\n\n");
    printf("Press 1 to convert from quaternion to corresponding "
    "Euler angles and\nPress 2 to convert from Euler angles to "
    "corresponding quaternion: ");    
    int choice;
    int f = 0;
    while (f == 0) {
        scanf("%d", &choice);
        if (choice == 1) {
            f = 1;
        }
        else if (choice == 2) {
            f = 2;
        }
        else {
            printf("Invalid choice. Please enter either 1 or 2: ");
            continue;
        }
    }
    if (f == 1) {
        char quat[9][10] = {"1st", "2nd", "3rd", "4th"};
        float qcs[5];
        while (f == 1) {
            for (int i=0;i<4;i++) {
                printf("Enter %s component of the unit quaternion: ", quat[i]);
                scanf("%f", &qcs[i]);
            }
            if (sqrt(pow(qcs[0], 2)+pow(qcs[1], 2)+pow(qcs[2], 2)+pow(qcs[3], 2)) == 1) {
                f = 0;
                printf("The quaternion is: %f + %fi + %fj + %fk\n", qcs[0], qcs[1], qcs[2], qcs[3]);
            }
            else {
                printf("Please enter values for a unit quaternion\n");
                continue;
            }
        }
        printf("The corresponding euler angles are:\n");
        float phi, theta, psi;
        phi = (atan2(2 * (qcs[0] * qcs[1]+qcs[2] * qcs[3]), 1-2 * (pow(qcs[1], 2)+pow(qcs[2], 2))))/M_PI*180;
        theta = -90 + (2 * atan2(sqrt(1+2 * (qcs[0] * qcs[2]-qcs[1] * qcs[3])), sqrt(sqrt(1-2 * (qcs[0] * qcs[2]-qcs[1] * qcs[3])))))/M_PI*180;
        psi = (atan2(2 * (qcs[0] * qcs[3]+qcs[1] * qcs[2]), 1-2 * (pow(qcs[2], 2)+pow(qcs[3], 2))))/M_PI*180;
        printf("%f, %f, %f", psi, theta, phi);
    }
    if (f == 2) {
        char eu_comp[4][4] = {"1st", "2nd", "3rd"};
        float eu_ang[3];
        for (int i=0;i<3;i++) {
            printf("Enter %s rotation angle (in degrees): ", eu_comp[i]);
            scanf("%f", &eu_ang[i]);
        }
        printf("The Euler angles (in degrees) are: %f, %f, %f\n", eu_ang[0], eu_ang[1], eu_ang[2]);
        double cr = cos(deg_rad(eu_ang[2]));
        double sr = sin(deg_rad(eu_ang[2]));
        double cp = cos(deg_rad(eu_ang[1]));
        double sp = sin(deg_rad(eu_ang[1]));
        double cy = cos(deg_rad(eu_ang[0]));
        double sy = sin(deg_rad(eu_ang[0]));
        double q[4];
        q[0] = cr * cp * cy + sr * sp * sy;
        q[1] = sr * cp * cy - cr * sp * sy;
        q[2] = cr * sp * cy + sr * cp * sy;
        q[3] = cr * cp * sy - sr * sp * cy;
        printf("the corresponding unit quaternion is q = %lf + %lfi + %lfj + %lfk", q[0], q[1], q[2], q[3]);
    }
    return 0;
}