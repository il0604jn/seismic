//inputs: 3 files (input1, input2, result)
//output: 3-column data: time, cross correlation value, cross correlation coefficient
//input file format: 2-coloumn: time & amplitude
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
	if( argv != 4)
	{
		fprintf(stderr, "crosscor (SEH)\n\n");
		fprintf(stderr, "Usage: %s [fixed fname] [moving fname] [output fname]\n",argc[0]);
		fprintf(stderr, "Every input file should consist of 2 columns: time and amplitude\n");
		return 0;
	}
	char fname1[2000], fname2[2000], fname3[2000];
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
	
	//cross correlation 하기, cross crrelation coefficient 구하기
	int k1, k2;
	double sum, sum1, sqsum1, mean1, sqmean1, stdv1, sum2, sqsum2, mean2, sqmean2, stdv2;
	double ccc;
	for(k1=0;k1<n1;k1++)
	{
		sum=0;
		sum1=0, sqsum1=0, mean1=0, sqmean1=0, stdv1=0, sum2=0, sqsum2=0, mean2=0, sqmean2=0, stdv2=0;
		for(k2=0;k2<n2;k2++)
		{
			sum+=wave1[k1+k2].amp*wave2[k2].amp;
			
			sum1+=wave1[k1+k2].amp;
			sqsum1+=wave1[k1+k2].amp*wave1[k1+k2].amp;
			sum2+=wave2[k2].amp;
			sqsum2+=wave2[k2].amp*wave2[k2].amp;
		}
		cc[k1].time=wave1[k1].time;
		cc[k1].amp=sum;
		
		mean1=sum1/n2;
		sqmean1=sqsum1/n2;
		stdv1=sqrt(sqmean1-mean1*mean1);
		mean2=sum2/n2;
		sqmean2=sqsum2/n2;
		stdv2=sqrt(sqmean2-mean2*mean2);
		
		ccc=0;
		for(k2=0;k2<n2;k2++) ccc+=(wave1[k1+k2].amp-mean1)*(wave2[k2].amp-mean2);
		cc[k1].a1=ccc/((n2)*stdv1*stdv2);
	}
	
	//cc 결과 output 파일에 넣기
	for (i=0;i<n1;i++) fprintf(file3,"%lf %lf %lf\n", cc[i].time, cc[i].amp,cc[i].a1);
	
	return 0;
}
