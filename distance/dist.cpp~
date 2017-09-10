#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <iostream>

#define ER 6371
#define PI 3.14159265
double dist_rad(double la1, double lo1, double la2, double lo2);
double az_rad(double la1, double lo1, double la2, double lo2, double rada);
double Deg2rad(double deg);
int main(int argc, char *argv[]){
	if(argc<5){
		fprintf(stderr,"USAGE: %s [evla] [evlo] [stla] [stlo]\n",argv[0]);
		fprintf(stderr,"USAGE: %s [la1] [lo1] [la2] [lo2]\n",argv[0]);
		return 0;
	}
	double la1,lo1,la2,lo2;
	la1=atof(argv[3]);
	lo1=atof(argv[4]);
	la2=atof(argv[1]);
	lo2=atof(argv[2]);

	printf("%.12lf\n",ER*dist_rad(la1,lo1,la2,lo2));
	return 0;
}



double dist_rad(double la1, double lo1, double la2, double lo2){
	double radlo1 = Deg2rad(lo1);
	double radlo2 = Deg2rad(lo2);
	double radla1 = Deg2rad(la1);
	double radla2 = Deg2rad(la2);
	double dist_rad = acos( cos(radlo1-radlo2)*cos(radla1)*cos(radla2) + sin(radla1)*sin(radla2) );	
	return dist_rad;
}
double az_rad(double la1, double lo1, double la2, double lo2, double rada){
	double radlo1 = Deg2rad(lo1);
	double radlo2 = Deg2rad(lo2);
	double radla1 = Deg2rad(la1);
	double radla2 = Deg2rad(la2);
	double az_rad=asin(sin(radlo1-radlo2)*cos(radla1)/sin(rada));
	return az_rad;
	
}
double Deg2rad(double deg){
	return deg*PI*0.005555555556;
}

