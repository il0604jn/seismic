#include <stdio.h>
#include <stdlib.h>
typedef struct date{
	int y;
	int m;
	int d;
	int H;
	int M;
	double S;
} date;

int Yoon(int y);

int main(int argc, char* argv[]){
	int y,m;
	double cumd, cumS;
	
	if(argc!=7){
		fprintf(stderr,"USAGE: %s [y] [m] [d] [H] [M] [S.S]\n",argv[0]);
		return 0;
	}

	date T;
	T.y=atoi(argv[1]);
	T.m=atoi(argv[2]);
	T.d=atoi(argv[3]);
	T.H=atoi(argv[4]);
	T.M=atoi(argv[5]);
	T.S=atof(argv[6]);

	
	cumd=0.0, cumS=0.0;
	for (y=1970;y<T.y;y++){
		if(Yoon(y)==0) cumd+=365;
		else cumd+=366;
	}
	for(m=1;m<T.m;m++){
		if(m==1 || m==3 || m==5 || m==7 || m==8 || m==10 || m==12) cumd+=31;
		else if(m==4 || m==6 || m==9 || m==11) cumd+= 30;
		else if(m==2){
			if(Yoon(T.y)==0) cumd+=28;
			else cumd+=29;
		}
	}
	cumd+=T.d-1;
	cumS+=cumd*24.0*60.0*60.0;
	cumS+=T.H*60.0*60.0+T.M*60.0+T.S*1.0;
	printf("%lf",cumS);
	return 0;
}

// 윤년이면 1, 평년이면 0
int Yoon(int y){
	if(y%400==0) return 1;
	else{
		if(y%100==0) return 0;
		else{
			if(y%4==0) return 1;
			else return 0;
		}
	}
}
