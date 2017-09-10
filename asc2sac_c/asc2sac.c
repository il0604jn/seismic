//Code written by S. E. HOUNG //

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define CHAR_MAX 1000

typedef struct SACheader{
	float delta,depmin,depmax,scale,odelta,b,e,o,a, internal_f, t[10], f, resp[10], stla, stlo, stel, stdp, evla, evlo, evel, evdp, mag, user[10], dist, az, baz, gcarc, depmen, cmpaz, cmpinc, xminimum, xmaximum, yminimum, ymaximum, adjtm, unused_f;
	int nzyear, nzjday, nzhour, nzmin, nzsec, nzmsec, nvhdr, norid, nevid, npts, nspts, internal_i, nwfid, nxsize, nysize, iftype, idep, iztype, iinst, istreg, ievreg, ievtyp, iqual, isynth, imagtyp, imagsrc, leven, lpspol, lovrok, lcalda, unused_i;
	char kstnm[8], kevnm[16], khole[8], ko[8], ka[8], kt0[8], kt1[8], kt2[8], kt3[8], kt4[8], kt5[8], kt6[8], kt7[8], kt8[8], kt9[8], kf[8], kuser0[8], kuser1[8], kuser2[8], kcmpnm[8], knetwk[8], kdatrd[8], kinst[8];
}SACheader;
typedef struct SACdata{
	double t;
	float y;
} SACdata;

void Errormessage(int argc, char **argv[]);
int Getline(FILE *f);
void Readdata(FILE *f, SACdata *data, int N);
void Init_header(SACheader *h);
void Readoption(int argc, char **argv[], SACheader *h);
double Getmax(SACdata *data, int N);
double Getmin(SACdata *data, int N);
double Getmean(SACdata *data, int N);
void Writeheader(FILE *f, SACheader h);
void Writedata(FILE *f,SACdata *data, int N);

int main(int argc, char **argv[]){
	Errormessage(argc, argv);

	int Ndata;
	FILE *fin, *fout;
	SACheader h;
	SACdata *data;
	char inputascii[CHAR_MAX], outputsac[CHAR_MAX];
	
	// open files
	sprintf(inputascii, "%s",argv[1]);
	sprintf(outputsac, "%s",argv[2]);
	fin=fopen(inputascii,"r");
	fout=fopen(outputsac,"wb");
	//--------------------------//
	
	// read two-column ascii file //
	Ndata=Getline(fin);
	data=(SACdata *)malloc(Ndata*sizeof(SACdata));
	Readdata(fin,data,Ndata);
	//----------------------//

	// fill header field//
	Init_header(&h);
	h.npts=Ndata;
	h.delta=(float) (data[1].t-data[0].t);
	h.e=h.b+h.delta*(h.npts-1);
	h.depmax=(float)Getmax(data,Ndata);
	h.depmin=(float)Getmin(data,Ndata);
	h.depmen=(float)Getmean(data,Ndata);
	Readoption(argc,argv,&h);
	//------------------------//

	// Write header and data field to output sac file //
	Writeheader(fout,h);
	Writedata(fout,data, Ndata);
	//---------------------------//

	fclose(fin);
	fclose(fout);
	free(data);

	return 1;
}
void Errormessage(int argc, char **argv[]){
	char inputascii[CHAR_MAX];
	if(argc==1){
		fprintf(stderr,"sac2asc (written by houng, 20151202)\n");
		fprintf(stderr,"Convert evenly spaced time series ASCII file (two-column: time amplitude) to SAC format binary file\n");
		fprintf(stderr,"USAGE: %s [input ASCII filename] [output SAC filename] ([-kstnm INC / -kcmpnm HHZ / ... ])\n",argv[0]);
		exit(0);
	}
	else{
		sprintf(inputascii,"%s",argv[1]);
		if(argc<3){
			fprintf(stderr,"Error: Not enough input parameters.\n");
			exit(0);
		}
		else if(access(inputascii,F_OK) == -1){
			fprintf(stderr,"Error: No such file: \"%s\"\n",inputascii);
			exit(0);
		}
		else if(access(inputascii, R_OK) == -1){
			fprintf(stderr,"Error: The input file is not readable: \"%s\"\n",inputascii);
			exit(0);
		}
	}
}

int Getline(FILE *f){
	int N=0;
	char buf[1000];
	rewind(f);
	
	while(1){
		fgets(buf,sizeof(buf),f);
		if(feof(f)) break;
		N++;
	}
	rewind(f);
	return N;
}
void Readdata(FILE *f, SACdata *data, int N){
	float x,y;
	int i;
	for(i=0;i<N;i++) fscanf(f,"%lf %f",&data[i].t, &data[i].y);
}
void Init_header(SACheader *h){
	int i;
	// float field //
	h->delta=-12345.0,h->depmin=-12345.0,h->depmax=-12345.0,h->scale=-12345.0,h->odelta=-12345.0,
	h->b=0.0,h->e=-12345.0,h->o=-12345.0,h->a=-12345.0, h->internal_f=-12345.0,
	h->f=-12345.0, h->stla=-12345.0, h->stlo=-12345.0, h->stel=-12345.0, h->stdp=-12345.0,
	h->evla=-12345.0, h->evlo=-12345.0, h->evel=-12345.0, h->evdp=-12345.0, h->mag=-12345.0,
	h->dist=-12345.0, h->az=-12345.0, h->baz=-12345.0, h->gcarc=-12345.0,
	h->depmen=-12345.0,h->cmpaz=-12345.0, h->cmpinc=-12345.0, h->xminimum=-12345.0,
	h->xmaximum=-12345.0, h->yminimum=-12345.0,h->ymaximum=-12345.0, h->adjtm=-12345.0, h->unused_f=-12345.0;
	for(i=0;i<10;i++) h->t[i]=-12345.0;
	for(i=0;i<10;i++) h->resp[i]=-12345.0;
	for(i=0;i<10;i++) h->user[i]=-12345.0;
	//-----------------//
	
	// int field //
	h->nzyear=1986, h->nzjday=155, h->nzhour=12, h->nzmin=30, h->nzsec=00,
	h->nzmsec=000, h->nvhdr=6, h->norid=-12345, h->nevid=-12345, h->npts=-12345,
	h->internal_i=-12345, h->nwfid=-12345, h->nxsize=-12345, h->nysize=-12345, h->iftype=1,
	h->idep=-12345, h->iztype=-12345, h->iinst=-12345, h->istreg=-12345, h->ievreg=-12345,
	h->ievtyp=-12345, h->iqual=-12345, h->isynth=-12345, h->imagtyp=-12345, h->imagsrc=-12345,
	h->leven=1, h->lpspol=-12345, h->lovrok=-12345, h->lcalda=-12345, h->unused_i=-12345;
	//-------------------//
	
	// char field //
	strcpy(h->kstnm, "NIMS"), strcpy(h->kevnm, "-12345"),
	strcpy(h->khole, "-12345"), strcpy(h->ko, "-12345"), strcpy(h->ka, "-12345"),
	strcpy(h->kt0, "-12345"), strcpy(h->kt1, "-12345"), strcpy(h->kt2, "-12345"),
	strcpy(h->kt3, "-12345"), strcpy(h->kt4, "-12345"), strcpy(h->kt5, "-12345"),
	strcpy(h->kt6, "-12345"), strcpy(h->kt7, "-12345"), strcpy(h->kt8, "-12345"),
	strcpy(h->kt9, "-12345"), strcpy(h->kf, "-12345"), strcpy(h->kuser0, "-12345"),
	strcpy(h->kuser1, "-12345"), strcpy(h->kuser2, "-12345"), strcpy(h->kcmpnm, "SEH"),
	strcpy(h->knetwk, "-12345"), strcpy(h->kdatrd, "-12345"), strcpy(h->kinst, "-12345");
}
void Readoption(int argc, char **argv[], SACheader *h){
	int i;
	char field1[CHAR_MAX], field2[CHAR_MAX];
	for(i=1;i<argc-1;i++){
		sprintf(field1, "%s", argv[i]);
		sprintf(field2, "%s",argv[i+1]);
		if(strcmp(field1,"-delta")==0) h->delta=(float)atof(field2);
		else if(strcmp(field1,"-depmin")==0) h->depmin=(float)atof(field2);
		else if(strcmp(field1,"-depmax")==0) h->depmax=(float)atof(field2);
		else if(strcmp(field1,"-scale")==0) h->scale=(float)atof(field2);
		else if(strcmp(field1,"-odelta")==0) h->odelta=(float)atof(field2);

		else if(strcmp(field1,"-b")==0) h->b=(float)atof(field2);
		else if(strcmp(field1,"-e")==0) h->e=(float)atof(field2);
		else if(strcmp(field1,"-o")==0) h->o=(float)atof(field2);
		else if(strcmp(field1,"-a")==0) h->a=(float)atof(field2);

		else if(strcmp(field1,"-t0")==0) h->t[0]=(float)atof(field2);
		else if(strcmp(field1,"-t1")==0) h->t[1]=(float)atof(field2);
		else if(strcmp(field1,"-t2")==0) h->t[2]=(float)atof(field2);
		else if(strcmp(field1,"-t3")==0) h->t[3]=(float)atof(field2);
		else if(strcmp(field1,"-t4")==0) h->t[4]=(float)atof(field2);

		else if(strcmp(field1,"-t5")==0) h->t[5]=(float)atof(field2);
		else if(strcmp(field1,"-t6")==0) h->t[6]=(float)atof(field2);
		else if(strcmp(field1,"-t7")==0) h->t[7]=(float)atof(field2);
		else if(strcmp(field1,"-t8")==0) h->t[8]=(float)atof(field2);
		else if(strcmp(field1,"-t9")==0) h->t[9]=(float)atof(field2);
		
		else if(strcmp(field1,"-f")==0) h->f=(float)atof(field2);
		else if(strcmp(field1,"-resp0")==0) h->resp[0]=(float)atof(field2);
		else if(strcmp(field1,"-resp1")==0) h->resp[1]=(float)atof(field2);
		else if(strcmp(field1,"-resp2")==0) h->resp[2]=(float)atof(field2);
		else if(strcmp(field1,"-resp3")==0) h->resp[3]=(float)atof(field2);
		
		else if(strcmp(field1,"-resp4")==0) h->resp[4]=(float)atof(field2);
		else if(strcmp(field1,"-resp5")==0) h->resp[5]=(float)atof(field2);
		else if(strcmp(field1,"-resp6")==0) h->resp[6]=(float)atof(field2);
		else if(strcmp(field1,"-resp7")==0) h->resp[7]=(float)atof(field2);
		else if(strcmp(field1,"-resp8")==0) h->resp[8]=(float)atof(field2);

		else if(strcmp(field1,"-resp9")==0) h->resp[9]=(float)atof(field2);
		else if(strcmp(field1,"-stla")==0) h->stla=(float)atof(field2);
		else if(strcmp(field1,"-stlo")==0) h->stlo=(float)atof(field2);
		else if(strcmp(field1,"-stel")==0) h->stel=(float)atof(field2);
		else if(strcmp(field1,"-stdp")==0) h->stdp=(float)atof(field2);
		
		else if(strcmp(field1,"-evla")==0) h->evla=(float)atof(field2);
		else if(strcmp(field1,"-evlo")==0) h->evlo=(float)atof(field2);
		else if(strcmp(field1,"-evel")==0) h->evel=(float)atof(field2);
		else if(strcmp(field1,"-evdp")==0) h->evdp=(float)atof(field2);
		else if(strcmp(field1,"-mag")==0) h->mag=(float)atof(field2);
		
		else if(strcmp(field1,"-user0")==0) h->user[0]=(float)atof(field2);
		else if(strcmp(field1,"-user1")==0) h->user[1]=(float)atof(field2);
		else if(strcmp(field1,"-user2")==0) h->user[2]=(float)atof(field2);
		else if(strcmp(field1,"-user3")==0) h->user[3]=(float)atof(field2);
		else if(strcmp(field1,"-user4")==0) h->user[4]=(float)atof(field2);
		
		else if(strcmp(field1,"-user5")==0) h->user[5]=(float)atof(field2);
		else if(strcmp(field1,"-user6")==0) h->user[6]=(float)atof(field2);
		else if(strcmp(field1,"-user7")==0) h->user[7]=(float)atof(field2);
		else if(strcmp(field1,"-user8")==0) h->user[8]=(float)atof(field2);
		else if(strcmp(field1,"-user9")==0) h->user[9]=(float)atof(field2);
		
		else if(strcmp(field1,"-dist")==0) h->dist=(float)atof(field2);
		else if(strcmp(field1,"-az")==0) h->az=(float)atof(field2);
		else if(strcmp(field1,"-baz")==0) h->baz=(float)atof(field2);
		else if(strcmp(field1,"-gcarc")==0) h->gcarc=(float)atof(field2);
		
		else if(strcmp(field1,"-depmen")==0) h->depmen=(float)atof(field2);
		else if(strcmp(field1,"-cmpaz")==0) h->cmpaz=(float)atof(field2);
		else if(strcmp(field1,"-cmpinc")==0) h->cmpinc=(float)atof(field2);
		else if(strcmp(field1,"-xminimum")==0) h->xminimum=(float)atof(field2);
		
		else if(strcmp(field1,"-xmaximum")==0) h->xmaximum=(float)atof(field2);
		else if(strcmp(field1,"-yminimum")==0) h->yminimum=(float)atof(field2);
		else if(strcmp(field1,"-ymaximum")==0) h->ymaximum=(float)atof(field2);
		
		else if(strcmp(field1,"-nzyear")==0) h->nzyear=(int)atoi(field2);
		else if(strcmp(field1,"-nzjday")==0) h->nzjday=(int)atoi(field2);
		else if(strcmp(field1,"-nzhour")==0) h->nzhour=(int)atoi(field2);
		else if(strcmp(field1,"-nzmin")==0) h->nzmin=(int)atoi(field2);
		else if(strcmp(field1,"-nzsec")==0) h->nzsec=(int)atoi(field2);
		
		else if(strcmp(field1,"-nzmsec")==0) h->nzmsec=(int)atoi(field2);
		else if(strcmp(field1,"-nvhdr")==0) h->nvhdr=(int)atoi(field2);
		else if(strcmp(field1,"-norid")==0) h->norid=(int)atoi(field2);
		else if(strcmp(field1,"-nevid")==0) h->nevid=(int)atoi(field2);
		else if(strcmp(field1,"-npts")==0) h->npts=(int)atoi(field2);

		else if(strcmp(field1,"-nwfid")==0) h->nwfid=(int)atoi(field2);
		else if(strcmp(field1,"-nxsize")==0) h->nxsize=(int)atoi(field2);
		else if(strcmp(field1,"-nysize")==0) h->nysize=(int)atoi(field2);

		else if(strcmp(field1,"-iftype")==0) h->iftype=(int)atoi(field2);
		else if(strcmp(field1,"-idep")==0) h->idep=(int)atoi(field2);
		else if(strcmp(field1,"-iztype")==0) h->iztype=(int)atoi(field2);
		else if(strcmp(field1,"-iinst")==0) h->iinst=(int)atoi(field2);
		
		else if(strcmp(field1,"-istreg")==0) h->istreg=(int)atoi(field2);
		else if(strcmp(field1,"-ievreg")==0) h->ievreg=(int)atoi(field2);
		else if(strcmp(field1,"-ievtyp")==0) h->ievtyp=(int)atoi(field2);
		else if(strcmp(field1,"-iqual")==0) h->iqual=(int)atoi(field2);
		else if(strcmp(field1,"-isynth")==0) h->isynth=(int)atoi(field2);
		
		else if(strcmp(field1,"-imagtyp")==0) h->imagtyp=(int)atoi(field2);
		else if(strcmp(field1,"-imagsrc")==0) h->imagsrc=(int)atoi(field2);
		
		else if(strcmp(field1,"-leven")==0) h->leven=(int)atoi(field2);
		else if(strcmp(field1,"-lpspol")==0) h->lpspol=(int)atoi(field2);
		else if(strcmp(field1,"-lovrok")==0) h->lovrok=(int)atoi(field2);
		else if(strcmp(field1,"-lcalda")==0) h->lcalda=(int)atoi(field2);
		
		else if(strcmp(field1,"-kstnm")==0) strcpy(h->kstnm, field2);
		else if(strcmp(field1,"-kevnm")==0) strcpy(h->kevnm, field2);		
		
		else if(strcmp(field1,"-khole")==0) strcpy(h->khole, field2);
		else if(strcmp(field1,"-ko")==0) strcpy(h->ko, field2);
		else if(strcmp(field1,"-ka")==0) strcpy(h->ka, field2);
		
		else if(strcmp(field1,"-kt0")==0) strcpy(h->kt0, field2);
		else if(strcmp(field1,"-kt1")==0) strcpy(h->kt1, field2);
		else if(strcmp(field1,"-kt2")==0) strcpy(h->kt2, field2);
		
		else if(strcmp(field1,"-kt3")==0) strcpy(h->kt3, field2);
		else if(strcmp(field1,"-kt4")==0) strcpy(h->kt4, field2);
		else if(strcmp(field1,"-kt5")==0) strcpy(h->kt5, field2);
		
		else if(strcmp(field1,"-kt6")==0) strcpy(h->kt6, field2);
		else if(strcmp(field1,"-kt7")==0) strcpy(h->kt7, field2);
		else if(strcmp(field1,"-kt8")==0) strcpy(h->kt8, field2);
		
		else if(strcmp(field1,"-kt9")==0) strcpy(h->kt9, field2);
		else if(strcmp(field1,"-kf")==0) strcpy(h->kf, field2);
		else if(strcmp(field1,"-kuser0")==0) strcpy(h->kuser0, field2);
		
		else if(strcmp(field1,"-kuser1")==0) strcpy(h->kuser1, field2);
		else if(strcmp(field1,"-kuser2")==0) strcpy(h->kuser2, field2);
		else if(strcmp(field1,"-kcmpnm")==0) strcpy(h->kcmpnm, field2);
		
		else if(strcmp(field1,"-knetwk")==0) strcpy(h->knetwk, field2);
		else if(strcmp(field1,"-kdatrd")==0) strcpy(h->kdatrd, field2);
		else if(strcmp(field1,"-kinst")==0) strcpy(h->kinst, field2);
	}
}
double Getmax(SACdata *data, int N){
	int i;
	double maxval=0.0;
	for(i=0;i<N;i++){
		if(i==0){
			maxval=data[i].y;
		}
		else{
			if(data[i].y>=maxval) maxval=data[i].y;
		}
	}
	
	return maxval;
}
double Getmin(SACdata *data, int N){
	int i;
	double minval=0.0;
	for(i=0;i<N;i++){
		if(i==0){
			minval=data[i].y;
		}
		else{
			if(data[i].y<=minval) minval=data[i].y;
		}
	}
	
	return minval;
}
double Getmean(SACdata *data, int N){
	int i;
	double meanval=0;
	for(i=0;i<N;i++){
		meanval+=data[i].y;
	}
	meanval/=N;
	return meanval;
}


void Writeheader(FILE *f, SACheader h){
	int size=4;
	int count=1;
	fwrite(&h.delta,size,count,f),   fwrite(&h.depmin,size,count,f),   fwrite(&h.depmax,size,count,f),   fwrite(&h.scale,size,count,f),   fwrite(&h.odelta,size,count,f);
	fwrite(&h.b,size,count,f),   fwrite(&h.e,size,count,f),   fwrite(&h.o,size,count,f),   fwrite(&h.a,size,count,f),   fwrite(&h.internal_f,size,count,f);
	fwrite(&h.t[0],size,count,f),   fwrite(&h.t[1],size,count,f),   fwrite(&h.t[2],size,count,f),   fwrite(&h.t[3],size,count,f),   fwrite(&h.t[4],size,count,f);
	fwrite(&h.t[5],size,count,f),   fwrite(&h.t[6],size,count,f),   fwrite(&h.t[7],size,count,f),   fwrite(&h.t[8],size,count,f),   fwrite(&h.t[9],size,count,f);
	fwrite(&h.f,size,count,f),   fwrite(&h.resp[0],size,count,f),   fwrite(&h.resp[1],size,count,f),   fwrite(&h.resp[2],size,count,f),   fwrite(&h.resp[3],size,count,f);
	fwrite(&h.resp[4],size,count,f),   fwrite(&h.resp[5],size,count,f),   fwrite(&h.resp[6],size,count,f),   fwrite(&h.resp[7],size,count,f),   fwrite(&h.resp[8],size,count,f);
	fwrite(&h.resp[9],size,count,f),   fwrite(&h.stla,size,count,f),   fwrite(&h.stlo,size,count,f),   fwrite(&h.stel,size,count,f),   fwrite(&h.stdp,size,count,f);
	fwrite(&h.evla,size,count,f),   fwrite(&h.evlo,size,count,f),   fwrite(&h.evel,size,count,f),   fwrite(&h.evdp,size,count,f),   fwrite(&h.mag,size,count,f);
	fwrite(&h.user[0],size,count,f),   fwrite(&h.user[1],size,count,f),   fwrite(&h.user[2],size,count,f),   fwrite(&h.user[3],size,count,f),   fwrite(&h.user[4],size,count,f);
	fwrite(&h.user[5],size,count,f),   fwrite(&h.user[6],size,count,f),   fwrite(&h.user[7],size,count,f),   fwrite(&h.user[8],size,count,f),   fwrite(&h.user[9],size,count,f);
	fwrite(&h.dist,size,count,f),   fwrite(&h.az,size,count,f),   fwrite(&h.baz,size,count,f),   fwrite(&h.gcarc,size,count,f),   fwrite(&h.internal_f,size,count,f);
	fwrite(&h.internal_f,size,count,f),   fwrite(&h.depmen,size,count,f),   fwrite(&h.cmpaz,size,count,f),   fwrite(&h.cmpinc,size,count,f),   fwrite(&h.xminimum,size,count,f);
	fwrite(&h.xmaximum,size,count,f),   fwrite(&h.yminimum,size,count,f),   fwrite(&h.ymaximum,size,count,f),   fwrite(&h.unused_f,size,count,f),   fwrite(&h.unused_f,size,count,f);
	fwrite(&h.unused_f,size,count,f),   fwrite(&h.unused_f,size,count,f),   fwrite(&h.unused_f,size,count,f),   fwrite(&h.unused_f,size,count,f),   fwrite(&h.unused_f,size,count,f);
	
	fwrite(&h.nzyear,size,count,f),   fwrite(&h.nzjday,size,count,f),   fwrite(&h.nzhour,size,count,f),   fwrite(&h.nzmin,size,count,f),   fwrite(&h.nzsec,size,count,f);
	fwrite(&h.nzmsec,size,count,f),   fwrite(&h.nvhdr,size,count,f),   fwrite(&h.norid,size,count,f),   fwrite(&h.nevid,size,count,f),   fwrite(&h.npts,size,count,f);
	fwrite(&h.internal_i,size,count,f),   fwrite(&h.nwfid,size,count,f),   fwrite(&h.nxsize,size,count,f),   fwrite(&h.nysize,size,count,f),   fwrite(&h.unused_i,size,count,f);
	fwrite(&h.iftype,size,count,f),   fwrite(&h.idep,size,count,f),   fwrite(&h.iztype,size,count,f),   fwrite(&h.unused_i,size,count,f),   fwrite(&h.iinst,size,count,f);
	fwrite(&h.istreg,size,count,f),   fwrite(&h.ievreg,size,count,f),   fwrite(&h.ievtyp,size,count,f),   fwrite(&h.iqual,size,count,f),   fwrite(&h.isynth,size,count,f);
	fwrite(&h.imagtyp,size,count,f),   fwrite(&h.imagsrc,size,count,f),   fwrite(&h.unused_i,size,count,f),   fwrite(&h.unused_i,size,count,f),   fwrite(&h.unused_i,size,count,f);
	fwrite(&h.unused_i,size,count,f),   fwrite(&h.unused_i,size,count,f),   fwrite(&h.unused_i,size,count,f),   fwrite(&h.unused_i,size,count,f),   fwrite(&h.unused_i,size,count,f);
	fwrite(&h.leven,size,count,f),   fwrite(&h.lpspol,size,count,f),   fwrite(&h.lovrok,size,count,f),   fwrite(&h.lcalda,size,count,f),   fwrite(&h.unused_i,size,count,f);
	
	fwrite(h.kstnm,size*2,count,f),   fwrite(h.kevnm,size*4,count,f);
	fwrite(h.khole,size*2,count,f),   fwrite(h.ko,size*2,count,f),   fwrite(h.ka,size*2,count,f);
	fwrite(h.kt0,size*2,count,f),   fwrite(h.kt1,size*2,count,f),   fwrite(h.kt2,size*2,count,f);
	fwrite(h.kt3,size*2,count,f),   fwrite(h.kt4,size*2,count,f),   fwrite(h.kt5,size*2,count,f);
	fwrite(h.kt6,size*2,count,f),   fwrite(h.kt7,size*2,count,f),   fwrite(h.kt8,size*2,count,f);
	fwrite(h.kt9,size*2,count,f),   fwrite(h.kf,size*2,count,f),   fwrite(h.kuser0,size*2,count,f);
	fwrite(h.kuser1,size*2,count,f),   fwrite(h.kuser2,size*2,count,f),   fwrite(h.kcmpnm,size*2,count,f);
	fwrite(h.knetwk,size*2,count,f),   fwrite(h.kdatrd,size*2,count,f),   fwrite(h.kinst,size*2,count,f);
}
void Writedata(FILE *f,SACdata *data, int N){
	int i;
	int size=4;
	int count=1;
	for(i=0;i<N;i++){
		fwrite(&data[i].y,size,count,f);
	}
}
