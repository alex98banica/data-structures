#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct celula
{
	void *info;
	struct celula *urm;

}Celula,*TCelula;

typedef struct stiva
{
	size_t dim;
	TCelula vf;

}Turn,*TTurn;

typedef struct
{ 
	char *culoare;
	TTurn A;
	TTurn B;
	TTurn C;

}Sistem,*TSistem;


typedef struct lista
{
	TSistem sis;
	struct lista *urm;
	
}Lista,*TLista,**ALista;


TTurn Init()
{
	TTurn h=malloc(sizeof(Turn));	
	return h;	
}


void Ins(TTurn *h,int d)
{
	TCelula aux=malloc(sizeof(Celula));
	aux->info=malloc(sizeof(int));
	(aux->info)=(void*)d;
	aux->urm=NULL;
	TCelula aux3=malloc(sizeof(Celula));
	if((*h)==NULL)
		(*h)->vf=aux;
	else
	{
		TTurn k=malloc(sizeof(Turn));
		k->vf=NULL;
		while((*h)->vf!=NULL &&(int)((*h)->vf->info)>(int)(aux->info))
		{
				
			aux3=(*h)->vf;
			(*h)->vf=(*h)->vf->urm;
			aux3->urm=k->vf;
			k->vf=aux3;
			
		}
		aux->urm=(*h)->vf;
		(*h)->vf=aux;
		while( k->vf!=NULL)
		{
			aux3=k->vf;
			k->vf=k->vf->urm;
			aux3->urm=(*h)->vf;
			(*h)->vf=aux3;			
	
		
		}
	}	

}


void AlocLista(ALista h,char tip[100],int disc)
{
	TLista aux=malloc(sizeof(Lista));
	TSistem r=malloc(sizeof(Sistem));
	r->culoare=strdup(tip);
	r->A=malloc(sizeof(Turn));
	r->B=malloc(sizeof(Turn));
	r->C=malloc(sizeof(Turn));
	TTurn z;
	z=Init();
	Ins(&z,disc);
	r->A=z;
	aux->sis=r;
	aux->urm=NULL;
	if( (*h)==NULL)
		(*h)=aux;
	else
	{
		aux->urm=(*h);
		(*h)=aux;
	}

}

int main(int argc, char *argv[])
{

	TLista k=malloc(sizeof(Lista));
	k=NULL;
	FILE *in = fopen(argv[1], "rt");
	FILE *out = fopen(argv[2], "wt");
	int n,i;
	char comanda[100];
	char tip[100];
	int disc;
	fscanf(in,"%d",&n);
	for(i=0;i<n;i++)
	{
		fscanf(in,"%s",comanda);
		if(strcmp(comanda,"add")==0)
		{
				fscanf(in,"%s",tip);
				fscanf(in,"%d",&disc);
				TLista y=malloc(sizeof(Lista));
				y=k;
				int t=0;
				if(k==NULL)
					AlocLista(&k,tip,disc);
				else
				{
					while(y!=NULL)
					{
						if(strcmp(y->sis->culoare,tip)==0)
							t=1;
						y=y->urm;
						
					}
					if(t==1)
					{
						y=k;
						while(strcmp(y->sis->culoare,tip)!=0)
							y=y->urm;
						Ins(&(y->sis->A),disc);	
		
					}
					else
						
						AlocLista(&k,tip,disc);			

				}
		}
		if( strcmp(comanda,"show")==0 )
		{
			fscanf(in,"%s",tip);
				TLista y=malloc(sizeof(Lista));
				y=k;
			if(y!=NULL)
			{
				while(y!=NULL && strcmp(y->sis->culoare,tip)!=0 )
					y=y->urm;
				fprintf(out,"A_%s: ",y->sis->culoare);
				TCelula d=malloc(sizeof(Celula));
				d=y->sis->A->vf;

				for(;y->sis->A->vf!=NULL;y->sis->A->vf=y->sis->A->vf->urm)
				{
					fprintf(out,"%d",(int)y->sis->A->vf->info);
					if(y->sis->A->vf->urm!=NULL)
					 fprintf(out," ");
				}

				fprintf(out,"\n");
				y->sis->A->vf=d;
				fprintf(out,"B_%s:",y->sis->culoare);
				for(;y->sis->B->vf!=NULL;y->sis->B->vf=y->sis->B->vf->urm)
					fprintf(out,"%d ",(int)y->sis->B->vf->info);
				fprintf(out,"\n");

				fprintf(out,"C_%s:",y->sis->culoare);
				for(;y->sis->C->vf!=NULL;y->sis->C->vf=y->sis->C->vf->urm)
					fprintf(out,"%d ",(int)y->sis->C->vf->info);
				fprintf(out,"\n");

			}
			if(y==NULL)
			{
					fprintf(out,"A_%s:\n",tip);
					fprintf(out,"B_%s:\n",tip);
					fprintf(out,"C_%s:\n",tip);
					
			}
		}
		
	}


	fclose(in);
	fclose(out);
	

}
