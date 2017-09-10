//파일명 3개를 인풋으로 받아서 (input1, input2, result) 결과로 time, cross correlation 결과, cross correlation coefficient 결과 의 세 칼럼으로 뽑아내기
//인풋파일 은 time, amp의 두 칼럼으로 이루어져야함
#include <stdio.h>
#include <math.h>
#include <string.h>

struct wave {
	double time;
	double amp;
	double a1;
};

int main(int argv,char *argc[])
{
	if( argv != 4) break;
	char fname1[500], fname2[500], fname3[500];
	strcpy(fname1,argc[1]);
	strcpy(fname2,argc[2]);
	strcpy(fname3,argc[3]);
//	scanf("%s %s %s",fname1, fname2,fname3);
	FILE* file1=fopen(fname1,"r");
	FILE* file2=fopen(fname2,"r");
	FILE* file3=fopen(fname3,"w");
	
	// data 갯수, time 인터벌 읽기
	double t,a,dt, t1,t2;
	int n1=0,n2=0;
	while(1)
	{
		fscanf(file1,"%lf %lf",&t,&a);
		if(feof(file1)) break;
		n1++;
		if(n1==1) t1=t;
		if(n1==2) t2=t;
	}
	dt=t2-t1;
	rewind(file1);
	while(1)
	{
		fscanf(file2,"%lf %lf",&t,&a);
		if(feof(file2)) break;
		n2++;
	}
	rewind(file2);

	
	// 데이터 저장할 구조체 만들기
	struct wave *wave1 = new struct wave [n1+n2];
	struct wave *wave2 = new struct wave [n2];
	struct wave *wave2m = new struct wave [n1+n2];
	struct wave *cc= new struct wave [n1];
	
	//구조체에 데이터 저장하기
	int i;
	for (i=0;i<n1+n2;i++)
	{
		if(i<n1)
		{
			fscanf(file1,"%lf %lf",&t,&a);
			wave1[i].time=t;
			wave1[i].amp=a;
		}
		else
		{
			wave1[i].time=dt*i;
			wave1[i].amp=0;
		}
	}
	for (i=0;i<n2;i++)
	{
		fscanf(file2,"%lf %lf",&t,&a);
		wave2[i].time=t;
		wave2[i].amp=a;
	}
	fclose(file1);
	fclose(file2);

	for (i=0;i<n1;i++)
	{
		memset(wave2m, 0, n1+n2);
		
		fprintf(file3,"%d\n",i);
	}
	fclose(file3);
	
	//cc 결과 output 파일에 넣기
//	for (i=0;i<n1;i++) fprintf(file3,"%lf %lf %lf\n", cc[i].time, cc[i].amp,cc[i].a1);
	
	return 0;
}

