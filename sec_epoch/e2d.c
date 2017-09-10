#include <stdio.h>

int Yoon(int y);

// 2001  9  9  1 46 40.00

int main(){
	double sec=384823.0;
	double sec_1d=86400.0;
	double rem;
	int cumd;

	cum=0;
	rem=sec;
	while(rem>sec_1d){
		rem-=sec_1d;
		cumd+=1;
	}

	printf("%d %f, %f\n", cumd, rem, cumd*60.0*60.0*24.0+rem);
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