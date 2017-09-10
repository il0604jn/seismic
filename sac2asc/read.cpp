#include <stdio.h>
#include <math.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define USAGE "USAGE: %s [-f fname]\n"
void skipheader(FILE *file);

int main(int argc, char **argv)
{
	int c;
	extern char *optarg;
	while((c = getopt(argc, argv, "f"))!=(-1))
	{
		switch(c)
		{
			case 'f':
				break;
			default:
				fprintf(stderr,USAGE,argv[0]);
				exit(1);
		}
	}
	if(argc < 2 )
	{
		fprintf(stderr,USAGE,argv[0]);
		exit(1);
	}

	int word=0, count=1, size;
	float buff;
	int bufi;
	char bufc[30];

	float delta,depmin,depmax,scale,odelta,b,e,o,a, t[10], f, resp[10], stla, stlo, stel, stdp, evla, evlo, evel, evdp, mag, user[10], dist, az, baz, gcarc, depmen, cmpaz, cmpinc, xminimum, xmaximum, yminimum, ymaximum, adjtm;
	int nzyear, nzjday, nzhour, nzmin, nzsec, nzmsec, nvhdr, norid, nevid, npts, nspts, nwfid, nxsize, nysize, iftype, idep, iztype, iinst, istreg, ievreg, ievtyp, iqual, isynth, imagtyp, imagsrc, leven, lpspol, lovrok, lcalda;
	char kstnm[30], kevnm[30], khole[30], ko[30], ka[30], kt0[30], kt1[30], kt2[30], kt3[30], kt4[30], kt5[30], kt6[30], kt7[30], kt8[30], kt9[30], kf[30], kuser0[30], kuser1[30], kuser2[30], kcmpnm[30], knetwk[30], kdatrd[30], kinst[30];

	char sacname[200]="test.sac";
	FILE *file=fopen(sacname,"rb");
	
	//////////////////////Read header///////////////////////
	word=0;
	while(word<158)
	{
		if(word<70)
		{
			size=4;
			fread(&buff,size,count,file);
			if(word==0) delta=buff;
			else if(word==1) depmin=buff;
			else if(word==2) depmax=buff;
			else if(word==3) scale=buff;
			else if(word==4) odelta=buff;
			else if(word==5) b=buff;
			else if(word==6) e=buff;
			else if(word==7) o=buff;
			else if(word==8) a=buff;
//			else if(word==9) internal=buff;
			else if(word==10) t[0]=buff;
			else if(word==11) t[1]=buff;
			else if(word==12) t[2]=buff;
			else if(word==13) t[3]=buff;
			else if(word==14) t[4]=buff;
			else if(word==15) t[5]=buff;
			else if(word==16) t[6]=buff;
			else if(word==17) t[7]=buff;
			else if(word==18) t[8]=buff;
			else if(word==19) t[9]=buff;
			else if(word==20) f=buff;
			else if(word==21) resp[0]=buff;
			else if(word==22) resp[1]=buff;
			else if(word==23) resp[2]=buff;
			else if(word==24) resp[3]=buff;
			else if(word==25) resp[4]=buff;
			else if(word==26) resp[5]=buff;
			else if(word==27) resp[6]=buff;
			else if(word==28) resp[7]=buff;
			else if(word==29) resp[8]=buff;
			else if(word==30) resp[9]=buff;
			else if(word==31) stla=buff;
			else if(word==32) stlo=buff;
			else if(word==33) stel=buff;
			else if(word==34) stdp=buff;
			else if(word==35) evla=buff;
			else if(word==36) evlo=buff;
			else if(word==37) evel=buff;
			else if(word==38) evdp=buff;
			else if(word==39) mag=buff;
			else if(word==40) user[0]=buff;
			else if(word==41) user[1]=buff;
			else if(word==42) user[2]=buff;
			else if(word==43) user[3]=buff;
			else if(word==44) user[4]=buff;
			else if(word==45) user[5]=buff;
			else if(word==46) user[6]=buff;
			else if(word==47) user[7]=buff;
			else if(word==48) user[8]=buff;
			else if(word==49) user[9]=buff;
			else if(word==50) dist=buff;
			else if(word==51) az=buff;
			else if(word==52) baz=buff;
			else if(word==53) gcarc=buff;
//			else if(word==54) internal=buff;
//			else if(word==55) internal=buff;
			else if(word==56) depmen=buff;
			else if(word==57) cmpaz=buff;
			else if(word==58) cmpinc=buff;
			else if(word==59) xminimum=buff;
			else if(word==60) xmaximum=buff;
			else if(word==61) yminimum=buff;
			else if(word==62) ymaximum=buff;
			else if(word==63) adjtm=buff;
//			else if(word==64) unused=buff;
//			else if(word==65) unused=buff;
//			else if(word==66) unused=buff;
//			else if(word==67) unused=buff;
//			else if(word==68) unused=buff;
//			else if(word==69) unused=buff;
			word+=count*size/4;
		}
		else if(word<110)
		{
			size=4;
			fread(&bufi,size,count,file);
			if(word==70) nzyear=bufi;
			else if(word==71) nzjday=bufi;
			else if(word==72) nzhour=bufi;
			else if(word==73) nzmin=bufi;
			else if(word==74) nzsec=bufi;
			else if(word==75) nzmsec=bufi;
			else if(word==76) nvhdr=bufi;
			else if(word==77) norid=bufi;
			else if(word==78) nevid=bufi;
			else if(word==79) npts=bufi;
			else if(word==80) nspts=bufi;
			else if(word==81) nwfid=bufi;
			else if(word==82) nxsize=bufi;
			else if(word==83) nysize=bufi;
//			else if(word==84) unused=bufi;
			else if(word==85) iftype=bufi;
			else if(word==86) idep=bufi;
			else if(word==87) iztype=bufi;
//			else if(word==88) unused=bufi;
			else if(word==89) iinst=bufi;
			else if(word==90) istreg=bufi;
			else if(word==91) ievreg=bufi;
			else if(word==92) ievtyp=bufi;
			else if(word==93) iqual=bufi;
			else if(word==94) isynth=bufi;
			else if(word==95) imagtyp=bufi;
			else if(word==96) imagsrc=bufi;
//			else if(word==97) unused=bufi;
//			else if(word==98) unused=bufi;
//			else if(word==99) unused=bufi;
//			else if(word==100) unused=bufi;
//			else if(word==101) unused=bufi;
//			else if(word==102) unused=bufi;
//			else if(word==103) unused=bufi;
//			else if(word==104) unused=bufi;
			else if(word==105) leven=bufi;
			else if(word==106) lpspol=bufi;
			else if(word==107) lovrok=bufi;
			else if(word==108) lcalda=bufi;
//			else if(word==109) unused=bufi;
			word+=count*size/4;
		}
		else if(word<112)
		{
			size=8;
			fread(bufc,size,count,file);
			if(word==110) strcpy(kstnm,bufc);
			word+=count*size/4;
		}
		else if(word<116)
		{
			size=16;
			fread(bufc,size,count,file);
			if(word==112) strcpy(kevnm,bufc);
			word+=count*size/4;
		}
		else if(word<158)
		{
			size=8;
			fread(bufc,size,count,file);
			if(word==116) strcpy(khole,bufc);
			else if(word==118) strcpy(ko,bufc);
			else if(word==120) strcpy(ka,bufc);
			else if(word==122) strcpy(kt0,bufc);
			else if(word==124) strcpy(kt1,bufc);
			else if(word==126) strcpy(kt2,bufc);
			else if(word==128) strcpy(kt3,bufc);
			else if(word==130) strcpy(kt4,bufc);
			else if(word==132) strcpy(kt5,bufc);
			else if(word==134) strcpy(kt6,bufc);
			else if(word==136) strcpy(kt7,bufc);
			else if(word==138) strcpy(kt8,bufc);
			else if(word==140) strcpy(kt9,bufc);
			else if(word==142) strcpy(kf,bufc);
			else if(word==144) strcpy(kuser0,bufc);
			else if(word==146) strcpy(kuser1,bufc);
			else if(word==148) strcpy(kuser2,bufc);
			else if(word==150) strcpy(kcmpnm,bufc);
			else if(word==152) strcpy(knetwk,bufc);
			else if(word==154) strcpy(kdatrd,bufc);
			else if(word==156) strcpy(kinst,bufc);
			word+=count*size/4;
		}
	}
	

	///////////////////////// Read data ///////////////////////////
	size=4;
	while(word<158+npts)
	{
		fread(&buff,size,count,file);
		word+=count*size/4;
	}
	fclose(file);
}

void skipheader(FILE *file)
{
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


