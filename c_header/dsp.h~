#include <stdio.h>
#include <math.h>
#include <string.h>

struct wave {
	double time;
	double amp;
	double a1;
};

void xcorr(struct wave *wave1, int n1, struct wave *wave2, int n2, struct wave *cc) //cc, ncc 구하기
{
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
}
