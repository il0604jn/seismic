#include <stdio.h>
#include <math.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define USAGE "USAGE: %s [fixed fname] [moving fname]\n"

struct hdr{
	float delta,depmin,depmax,scale,odelta,b,e,o,a,t0,t1,t2,t3,t4,t5,t6,t7,t8,t9, f, resp0, resp1, resp2, resp3, resp4, resp5, resp6, resp7, resp8, resp9, stla, stlo, stel, stdp, evla, evlo, evel, evdp, mag, user0, user1, user2, user3, user4, user5, user6, user7, user8, user9, dist, az, baz, gcarc, depmen, cmpaz, cmpinc, xminimum, xmaximum, yminimum, ymaximum, adjtm;
	int nzyear, nzjday, nzhour, nzmin, nzsec, nzmsec, nvhdr, norid, nevid, npts, nspts, nwfid, nxsize, nysize, iftype, idep, iztype, iinst, istreg, ievreg, ievtyp, iqual, isynth, imagtyp, imagsrc, leven, lpspol, lovrok, lcalda;
	char kstnm[30], kevnm[30], khole[30], ko[30], ka[30], kt0[30], kt1[30], kt2[30], kt3[30], kt4[30], kt5[30], kt6[30], kt7[30], kt8[30], kt9[30], kf[30], kuser0[30], kuser1[30], kuser2[30], kcmpnm[30], knetwk[30], kdatrd[30], kinst[30];
};

void errmessage(int argc, char **argv);
struct hdr readheader(struct hdr h, FILE *f);
void skipheader(FILE *file);
float *readdata(float *array,int npts,FILE *f);
void compare_dt(float dt1, float dt2);
float *zeropad(float *array, float *arrayz,  int n1, int n2);
float timeshift(float o, float b);
void crosscor(float *d1z, float *d2, int n1, int n2, float dt, float tshift);

int main(int argc, char **argv){
	FILE *f1, *f2;
	struct hdr h1, h2;
	float *dat1,*dat2, *dat1z;
	float tshift;
	
	errmessage(argc, argv); // Error message
	
	//Read headers
	f1=fopen(argv[1],"rb"); //open file
	f2=fopen(argv[2],"rb"); //open file
	h1=readheader(h1,f1); // Read header
	h2=readheader(h2,f2); // Read header
	//--------------------------
	
	// Read data
	dat1=(float *)malloc(h1.npts* sizeof(float)); // mem alloc
	dat2=(float *)malloc(h2.npts* sizeof(float)); // mem alloc
	readdata(dat1,h1.npts,f1); // Read data
	readdata(dat2,h2.npts,f2); // Read data
	fclose(f1);
	fclose(f2);
	//-------------------------------
	
	compare_dt(h1.delta, h2.delta); // check whether dt1 = dt2 or not
	
	dat1z=(float *)malloc((h1.npts+h2.npts)*sizeof(float)); // mem alloc
	dat1z=zeropad(dat1,dat1z,h1.npts,h2.npts); // zeros padding
	tshift=timeshift(h1.o, h1.b); // time shift (when o is not an empty field)
	crosscor(dat1z, dat2, h1.npts, h2.npts, h1.delta,tshift); // do crosscorr
	return 0;
}
// --------------End Of Main------------------//

void errmessage(int argc, char **argv){
	if(argc < 3){
		fprintf(stderr,USAGE,argv[0]);
		exit(0);
	}
}
struct hdr readheader(struct hdr h, FILE *file){
	rewind(file);
	float buff;
	int bufi;
	char bufc[30];
	int word=0, count=1,size=0;
	
	while(word<158)
	{
		if(word<70)
		{
			size=4;
			fread(&buff,size,count,file);
			if(word==0) h.delta=buff;
			else if(word==1) h.depmin=buff;
			else if(word==2) h.depmax=buff;
			else if(word==3) h.scale=buff;
			else if(word==4) h.odelta=buff;
			else if(word==5) h.b=buff;
			else if(word==6) h.e=buff;
			else if(word==7) h.o=buff;
			else if(word==8) h.a=buff;
//			else if(word==9) h.internal=buff;
			else if(word==10) h.t0=buff;
			else if(word==11) h.t1=buff;
			else if(word==12) h.t2=buff;
			else if(word==13) h.t3=buff;
			else if(word==14) h.t4=buff;
			else if(word==15) h.t5=buff;
			else if(word==16) h.t6=buff;
			else if(word==17) h.t7=buff;
			else if(word==18) h.t8=buff;
			else if(word==19) h.t9=buff;
			else if(word==20) h.f=buff;
			else if(word==21) h.resp0=buff;
			else if(word==22) h.resp1=buff;
			else if(word==23) h.resp2=buff;
			else if(word==24) h.resp3=buff;
			else if(word==25) h.resp4=buff;
			else if(word==26) h.resp5=buff;
			else if(word==27) h.resp6=buff;
			else if(word==28) h.resp7=buff;
			else if(word==29) h.resp8=buff;
			else if(word==30) h.resp9=buff;
			else if(word==31) h.stla=buff;
			else if(word==32) h.stlo=buff;
			else if(word==33) h.stel=buff;
			else if(word==34) h.stdp=buff;
			else if(word==35) h.evla=buff;
			else if(word==36) h.evlo=buff;
			else if(word==37) h.evel=buff;
			else if(word==38) h.evdp=buff;
			else if(word==39) h.mag=buff;
			else if(word==40) h.user0=buff;
			else if(word==41) h.user1=buff;
			else if(word==42) h.user2=buff;
			else if(word==43) h.user3=buff;
			else if(word==44) h.user4=buff;
			else if(word==45) h.user5=buff;
			else if(word==46) h.user6=buff;
			else if(word==47) h.user7=buff;
			else if(word==48) h.user8=buff;
			else if(word==49) h.user9=buff;
			else if(word==50) h.dist=buff;
			else if(word==51) h.az=buff;
			else if(word==52) h.baz=buff;
			else if(word==53) h.gcarc=buff;
//			else if(word==54) h.internal=buff;
//			else if(word==55) h.internal=buff;
			else if(word==56) h.depmen=buff;
			else if(word==57) h.cmpaz=buff;
			else if(word==58) h.cmpinc=buff;
			else if(word==59) h.xminimum=buff;
			else if(word==60) h.xmaximum=buff;
			else if(word==61) h.yminimum=buff;
			else if(word==62) h.ymaximum=buff;
			else if(word==63) h.adjtm=buff;
//			else if(word==64) h.unused=buff;
//			else if(word==65) h.unused=buff;
//			else if(word==66) h.unused=buff;
//			else if(word==67) h.unused=buff;
//			else if(word==68) h.unused=buff;
//			else if(word==69) h.unused=buff;
			word+=count*size/4;
		}
		else if(word<110)
		{
			size=4;
			fread(&bufi,size,count,file);
			if(word==70) h.nzyear=bufi;
			else if(word==71) h.nzjday=bufi;
			else if(word==72) h.nzhour=bufi;
			else if(word==73) h.nzmin=bufi;
			else if(word==74) h.nzsec=bufi;
			else if(word==75) h.nzmsec=bufi;
			else if(word==76) h.nvhdr=bufi;
			else if(word==77) h.norid=bufi;
			else if(word==78) h.nevid=bufi;
			else if(word==79) h.npts=bufi;
			else if(word==80) h.nspts=bufi;
			else if(word==81) h.nwfid=bufi;
			else if(word==82) h.nxsize=bufi;
			else if(word==83) h.nysize=bufi;
//			else if(word==84) h.unused=bufi;
			else if(word==85) h.iftype=bufi;
			else if(word==86) h.idep=bufi;
			else if(word==87) h.iztype=bufi;
//			else if(word==88) h.unused=bufi;
			else if(word==89) h.iinst=bufi;
			else if(word==90) h.istreg=bufi;
			else if(word==91) h.ievreg=bufi;
			else if(word==92) h.ievtyp=bufi;
			else if(word==93) h.iqual=bufi;
			else if(word==94) h.isynth=bufi;
			else if(word==95) h.imagtyp=bufi;
			else if(word==96) h.imagsrc=bufi;
//			else if(word==97) h.unused=bufi;
//			else if(word==98) h.unused=bufi;
//			else if(word==99) h.unused=bufi;
//			else if(word==100) h.unused=bufi;
//			else if(word==101) h.unused=bufi;
//			else if(word==102) h.unused=bufi;
//			else if(word==103) h.unused=bufi;
//			else if(word==104) h.unused=bufi;
			else if(word==105) h.leven=bufi;
			else if(word==106) h.lpspol=bufi;
			else if(word==107) h.lovrok=bufi;
			else if(word==108) h.lcalda=bufi;
//			else if(word==109) h.unused=bufi;
			word+=count*size/4;
		}
		else if(word<112)
		{
			size=8;
			fread(bufc,size,count,file);
			if(word==110) strcpy(h.kstnm,bufc);
			word+=count*size/4;
		}
		else if(word<116)
		{
			size=16;
			fread(bufc,size,count,file);
			if(word==112) strcpy(h.kevnm,bufc);
			word+=count*size/4;
		}
		else if(word<158)
		{
			size=8;
			fread(bufc,size,count,file);
			if(word==116) strcpy(h.khole,bufc);
			else if(word==118) strcpy(h.ko,bufc);
			else if(word==120) strcpy(h.ka,bufc);
			else if(word==122) strcpy(h.kt0,bufc);
			else if(word==124) strcpy(h.kt1,bufc);
			else if(word==126) strcpy(h.kt2,bufc);
			else if(word==128) strcpy(h.kt3,bufc);
			else if(word==130) strcpy(h.kt4,bufc);
			else if(word==132) strcpy(h.kt5,bufc);
			else if(word==134) strcpy(h.kt6,bufc);
			else if(word==136) strcpy(h.kt7,bufc);
			else if(word==138) strcpy(h.kt8,bufc);
			else if(word==140) strcpy(h.kt9,bufc);
			else if(word==142) strcpy(h.kf,bufc);
			else if(word==144) strcpy(h.kuser0,bufc);
			else if(word==146) strcpy(h.kuser1,bufc);
			else if(word==148) strcpy(h.kuser2,bufc);
			else if(word==150) strcpy(h.kcmpnm,bufc);
			else if(word==152) strcpy(h.knetwk,bufc);
			else if(word==154) strcpy(h.kdatrd,bufc);
			else if(word==156) strcpy(h.kinst,bufc);
			word+=count*size/4;
		}
	}
	return h;
}

void skipheader(FILE *file){
	int word=0, count=1, size;
	float buff;
	int bufi;
	char bufc[30];
	rewind(file);

	while(word<158)
	{
		if(word<70)
		{
			size=4;
			fread(&buff,size,count,file);
			word+=count*size/4;
		}
		else if(word<110)
		{
			size=4;
			fread(&bufi,size,count,file);
			word+=count*size/4;
		}
		else if(word<112)
		{
			size=8;
			fread(bufc,size,count,file);
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
			word+=count*size/4;
		}
	}
}

float *readdata(float *array,int npts,FILE *f){
	int k=0;
	int size=4, count=1, word=0;
	rewind(f);
	skipheader(f);
	while(word<npts){
		fread(&array[k],size,count,f);
		word+=count*size/4;
		k++;
	}
	return array;
}

void compare_dt(float dt1, float dt2){
		if(fabs(dt1-dt2)>0.00001){
			fprintf(stderr,"ERROR: dt1 and dt2 must be identical.");
			exit(0);
		}
}

float *zeropad(float *array, float *arrayz,  int n1, int n2){
	int i;
	for (i=0;i<n1+n2;i++){
		if(i<n1) arrayz[i]=array[i];
		else arrayz[i]=0;
	}
	return arrayz;
}

float timeshift(float o, float b){
	if (o>-12350.01 && o<-12344.99) return 0.0;
	else return b-o;
}

void crosscor(float *d1z, float *d2, int n1, int n2, float dt, float tshift){
	int k1, k2;
	double sum, sum1, sqsum1, mean1, sqmean1, stdv1, sum2, sqsum2, mean2, sqmean2, stdv2;
	double ccc;
	float *cc, *CC;
	cc=(float *)malloc(n1* sizeof(float)); // mem alloc
	CC=(float *)malloc(n1* sizeof(float)); // mem alloc
	for(k1=0;k1<n1;k1++){
		sum=0;
		sum1=0, sqsum1=0, mean1=0, sqmean1=0, stdv1=0, sum2=0, sqsum2=0, mean2=0, sqmean2=0, stdv2=0;
		for(k2=0;k2<n2;k2++){
			sum+=d1z[k1+k2]*d2[k2];
			sum1+=d1z[k1+k2];
			sqsum1+=d1z[k1+k2]*d1z[k1+k2];
			sum2+=d2[k2];
			sqsum2+=d2[k2]*d2[k2];
		}
		cc[k1]=sum;
		mean1=sum1/n2;
		sqmean1=sqsum1/n2;
		stdv1=sqrt(sqmean1-mean1*mean1);
		mean2=sum2/n2;
		sqmean2=sqsum2/n2;
		stdv2=sqrt(sqmean2-mean2*mean2);
		
		ccc=0;
		for(k2=0;k2<n2;k2++) ccc+=(d1z[k1+k2]-mean1)*(d2[k2]-mean2);
		CC[k1]=ccc/((n2)*stdv1*stdv2);
	}
	
	for(k1=0;k1<n1;k1++) printf("%f %.12e %f\n",dt*k1+tshift, cc[k1], CC[k1]);
}