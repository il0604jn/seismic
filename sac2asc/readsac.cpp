#include <stdio.h>
#include <math.h>
#include <iostream>
#include <string.h>
#define ER 6400
#define max(a,b) ((a>b)?a:b)
int main(void)
{
	float amplf=1;
	int word=0, count=1, size;
	float buff,data;
	float delta, btime, otime,stla, stlo,mag, dist,az, depmin, depmax;
	float maxamp=0, maxstlo=-180, minstlo=180, maxstla=-90, minstla=90, maxdist;
	float lon1,lon2,lat1, lat2,xtic, ytic;
	char stnm[30], stnwk[30], stcomp[30];
	int bufi;
	int npts;
	char bufc[30];
	
	
	char sacname[200];
	char outputname[210];
	FILE *saclist=fopen("saclist","r");
	FILE *stpos=fopen("stpos.txt","w");
	FILE *stmap=fopen("stmap.gmt.sc","w");
	
	maxdist=0;
	while(1)
	{
		fscanf(saclist,"%s",sacname);
		if(feof(saclist)) break;
		sprintf(outputname,"%s.data",sacname);
		FILE *file=fopen(sacname,"rb");
	
		//Read header//
		word=0;
		while(word<158)
		{
			if(word<70)
			{
				size=4;
				fread(&buff,size,count,file);
				if(word==0) delta=buff;
				if(word==1) depmin=buff;
				if(word==2) depmax=buff;
				if(word==5) btime=buff;
				if(word==7) otime=buff;
				if(word==31) stla=buff;
				if(word==32) stlo=buff;
				if(word==50) dist=buff;
				if(word==51) az=buff;
				word+=count*size/4;
			}
			else if(word<110)
			{
				size=4;
				fread(&bufi,size,count,file);
				if(word==79) npts=bufi;
				word+=count*size/4;
			}
			else if(word<112)
			{
				size=8;
				fread(bufc,size,count,file);
				if(word==110) strcpy(stnm,bufc);
				word+=count*size/4;
			}
			else if(word<116)
			{
				size=16;
				fread(bufc,size,count,file);
				word+=count*size/4;
			}
			else if(word<158)
			{
				size=8;
				fread(bufc,size,count,file);
				if(word==150) strcpy(stcomp,bufc);
				if(word==152) strcpy(stnwk,bufc);
				word+=count*size/4;
			}
		}
		if(dist>=maxdist) maxdist=dist;
	}
	maxdist=maxdist*180/(ER*M_PI);
	amplf=maxdist/40;
	
	rewind(saclist);
	while(1)
	{
		fscanf(saclist,"%s",sacname);
		if(feof(saclist)) break;
		FILE *file=fopen(sacname,"rb");
	
		//Read header//
		word=0;
		while(word<158)
		{
			if(word<70)
			{
				size=4;
				fread(&buff,size,count,file);
				if(word==0) delta=buff;
				if(word==1) depmin=buff;
				if(word==2) depmax=buff;
				if(word==5) btime=buff;
				if(word==7) otime=buff;
				if(word==31) stla=buff;
				if(word==32) stlo=buff;
				if(word==50) dist=buff;
				if(word==51) az=buff;
				word+=count*size/4;
			}
			else if(word<110)
			{
				size=4;
				fread(&bufi,size,count,file);
				if(word==79) npts=bufi;
				word+=count*size/4;
			}
			else if(word<112)
			{
				size=8;
				fread(bufc,size,count,file);
				if(word==110) strcpy(stnm,bufc);
				word+=count*size/4;
			}
			else if(word<116)
			{
				size=16;
				fread(bufc,size,count,file);
				word+=count*size/4;
			}
			else if(word<158)
			{
				size=8;
				fread(bufc,size,count,file);
				if(word==150) strcpy(stcomp,bufc);
				if(word==152) strcpy(stnwk,bufc);
				word+=count*size/4;
			}
		}
	
		//Find Max amplitude//
		maxamp=max(fabs(depmax),fabs(depmin));
		std::cout <<stnwk<<stnm<<stcomp<<", ";
		fclose(file);
		fprintf(stpos,"%f %f 10 0 MC %s %s %s %lf\n",stlo, stla, stnm, stnwk, stcomp,maxamp);
		if (stla>=maxstla) maxstla=stla;
		if (stla<=minstla) minstla=stla;
		if (stlo>=maxstlo) maxstlo=stlo;
		if (stlo<=minstlo) minstlo=stlo;
		xtic=(maxstlo-minstlo)/4;
		ytic=(maxstla-minstla)/4;
	}
	lon1=(maxstlo+minstlo)/2 -1.4*(maxstlo-minstlo)/2;
	lon2=(maxstlo+minstlo)/2 +1.4*(maxstlo-minstlo)/2;
	lat1=(maxstla+minstla)/2 -1.4*(maxstla-minstla)/2;
	lat2=(maxstla+minstla)/2 +1.4*(maxstla-minstla)/2;
	if(lon1<-179.9) lon1=-179.9;
	if(lon2>179.9) lon2=179.9;
	if(lat1<-89.9) lat1=-87;
	if(lat2>89.9) lat2=87;
//	std::cout << maxstla <<"\t" << minstla <<"\t" << maxstlo <<"\t" << minstlo <<"\n";
	fprintf(stmap,"pscoast -R%.1f/%.1f/%.1f/%.1f -P -JM6i -B%.1f/%.1f -G255/255/255 -S -Dh -W -K >stmap.ps\n", lon1, lon2, lat1, lat2,xtic,ytic);
	fprintf(stmap,"psxy stpos.txt -R -JM -O -W1/0/0/0 -G255/0/0 -St0.25 >>stmap.ps\n");
//	fprintf(stmap,"pstext stpos.txt -R -JM -P -B -S1p -K -G0/0/0 >>stmap.ps\n");
	fclose(saclist);
	fclose(stpos);
}
