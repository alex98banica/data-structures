/* Banica Alexandru Ionut - 311CB */


#include <stdio.h>
#include "info.h"
#include <stdlib.h>
#include <string.h>

Jucator AlocJucator(FILE *conf)							// Alocare elemente de tip jucator
{
	Jucator aux=(Jucator)malloc(sizeof(struct jucator));
	char NUME[100];
	fscanf(conf,"%s",NUME);
	aux->nume=strdup(NUME);
	fscanf(conf,"%d",&aux->nrMaini);
	return aux;
}


int InsListaJucatori(FILE *conf,ALista juc)					// Inserare elemente de tip jucator in lista de jucatori
{
	TLista aux=malloc(sizeof(Celula));
	if(!aux)
		return 0;
	aux->info=malloc(sizeof(struct jucator));
	if(!aux->info)
	{
		free(aux);
		return 0;
	}
	Jucator inf;
	inf=AlocJucator(conf);
	memcpy(aux->info,(void*)inf,sizeof(struct jucator));
	if((*juc)==NULL)
	{
		TLista aux2=malloc(sizeof(Celula));
		aux2->info=NULL;
		aux2->urm=aux;
		aux->urm=aux2;
		(*juc)=aux2;
	}
	else
	{
		TLista aux3=malloc(sizeof(Celula));
		aux3=(*juc);
		while(aux3->urm->info!=NULL)
		{
			aux3=aux3->urm;
		}
	aux->urm=(*juc);
	aux3->urm=aux;
	}
	return 1;
}

Masa AlocMasa(FILE *conf)							// Alocare elemente de tip masa cu lista de jucatori aferenta
{
	Masa aux=(Masa)malloc(sizeof(struct masa));
	char NUME[100];
	fscanf(conf,"%s",NUME);
	aux->numeMasa=strdup(NUME);
	fscanf(conf,"%d",&aux->nrCrtJucatori);
	fscanf(conf,"%d",&aux->nrMaxJucatori);
	TLista h=NULL;
	int i;
	for(i=0;i<aux->nrCrtJucatori;i++)
		InsListaJucatori(conf,&h);
	aux->jucatori=h;
	return aux;
}

int InsListaMese(FILE *conf,ALista mas)						// Inserare elemente de tip masa in lista de mese
{
	TLista aux=malloc(sizeof(Celula));
	if(!aux)
		return 0;
	aux->info=malloc(sizeof(struct masa));
	if(!aux->info)
	{
		free(aux);
		return 0;
	}
	aux->urm=NULL;
	Masa inf=malloc(sizeof(struct masa));
	inf=AlocMasa(conf);
	memcpy(aux->info,(void*)inf,sizeof(struct masa));

	if((*mas)==NULL)
	{
		(*mas)=aux;
		(*mas)->urm=NULL;

	}
	else
	{
		TLista aux3,ultim;
		aux3=(*mas);
		while(aux3!=NULL)
		{
			ultim=aux3;
			aux3=aux3->urm;
		}
		ultim->urm=aux;
	}

	return 1;
}

Sala CreareSala(FILE *conf)							// Creare sala
{
	Sala camera=malloc(sizeof(struct sala));
	TLista h=NULL;
	int i=0;
	fscanf(conf,"%d",&camera->nrMese);
	while(i<camera->nrMese)
	{
		InsListaMese(conf,&h);
		i++;
	}
	camera->masa=h;
	return camera;


}

void Print(FILE *out,Sala h)							// Afiseaza sala
{
	int i=0,j=0;
	TLista p1,p2;
	p1=h->masa;
	while(p1!=NULL)
	{
		fprintf(out,"%s: ",((Masa)(p1->info))->numeMasa);
		i=0;
		j=0;
		p2=((Masa)(p1->info))->jucatori;
		while(i<((Masa)(p1->info))->nrCrtJucatori)
		{
			fprintf(out,"%s - ",((Jucator)p2->urm->info)->nume);
			fprintf(out,"%d",((Jucator)p2->urm->info)->nrMaini);
			if(j<((Masa)(p1->info))->nrCrtJucatori-1)
				fprintf(out,"; ");
			else
				fprintf(out,".");
			p2=p2->urm;
			i++;
			j++;	
		}
		fprintf(out,"\n");
		p1=p1->urm;
	}	


}


void noroc(Sala h,char numemasa[100],char numejucator[100],int mana,FILE *out)		
{
	int i=0;
	TLista p1,p2;
	p1=h->masa;
	int verifmasa=0,verifjucator=0;
	while(p1!=NULL)
	{
		i=0;
		p2=((Masa)(p1->info))->jucatori;
		if(strcmp(numemasa,((Masa)(p1->info))->numeMasa)==0)
		{
			verifmasa=1;
			while(i<((Masa)(p1->info))->nrCrtJucatori)
			{
				if(strcmp(numejucator,((Jucator)p2->urm->info)->nume)==0)
				{
					((Jucator)p2->urm->info)->nrMaini+=mana;
					verifjucator=1;
				}
				p2=p2->urm;
				i++;
			}		
		}	
	p1=p1->urm;
	}
	if(verifjucator==0)
	{
		if(verifmasa==0)
			fprintf(out,"Masa %s nu exista!\n",numemasa);
		else
			fprintf(out,"Jucatorul %s nu exista la masa %s!\n",numejucator,numemasa);
	}
}


void ghinion(Sala h,char numemasa[100],char numejucator[100],int mana,FILE *out)
{
	TLista p1,p2,ant,ant2;
	p1=h->masa;
	ant2=NULL;
	int i;
	int verifmasa=0,verifjucator=0;
	TLista p5;
	TLista ver=h->masa;
	while(ver!=NULL)
	{
		i=0;
		p5=((Masa)(ver->info))->jucatori;
		if(strcmp(numemasa,((Masa)(ver->info))->numeMasa)==0)
		{
			verifmasa=1;
			while(i<((Masa)(ver->info))->nrCrtJucatori)
			{
				if(strcmp(numejucator,((Jucator)p5->urm->info)->nume)==0)
				{
					verifjucator=1;
				}
				p5=p5->urm;
				i++;
			}		
		}	
		ver=ver->urm;
	}
	if(verifjucator==1)
	{
		while(p1!=NULL)
		{
			p2=((Masa)(p1->info))->jucatori->urm;
			if(strcmp(numemasa,((Masa)(p1->info))->numeMasa)==0)
			{
				for(ant=((Masa)(p1->info))->jucatori;p2->info!=NULL 
					&& strcmp(numejucator,((Jucator)p2->info)->nume)!=0;ant=p2,p2=p2->urm);

				if(strcmp(numejucator,((Jucator)p2->info)->nume)==0)
					((Jucator)p2->info)->nrMaini-=mana;
				if(((Jucator)p2->info)->nrMaini<=0)
				{
					ant->urm=ant->urm->urm;
					((Masa)(p1->info))->nrCrtJucatori--;
					if(((Masa)(p1->info))->nrCrtJucatori==0)
					{
						if(ant2!=NULL && p1->urm!=NULL)
						{
							ant2->urm=ant2->urm->urm;
							h->nrMese--;
						}
						else if(ant2==NULL && p1->urm==NULL)
						{
							h->masa=NULL;	
						}
						else if(ant2!=NULL && p1->urm==NULL)
							ant2->urm=NULL;
						else if(ant2==NULL && p1->urm!=NULL)
							h->masa=h->masa->urm;
					}
				}		
			}
			ant2=p1;	
			p1=p1->urm;
		}
	}
	if(verifjucator==0)
	{
		if(verifmasa==0)
			fprintf(out,"Masa %s nu exista!\n",numemasa);
		else
			fprintf(out,"Jucatorul %s nu exista la masa %s!\n",numejucator,numemasa);
	}
}

void inchide(Sala h,char numemasa[100],FILE *out)
{
	TLista p1,p2,p3,p4,ant2,ant3,p5;
	p1=h->masa;
	p5=h->masa;
	p3=h->masa;
	ant2=NULL;
	int verifmasa=0;
	int nrjuc=0,nr,nr2;
	while(p5!=NULL)						// calculeaza suma locurilor libere si retine locurile libere si numarul curent de la sala cautata
	{
		if(strcmp(numemasa,((Masa)(p5->info))->numeMasa)==0)
		{
			verifmasa=1;
			nr=((Masa)(p5->info))->nrCrtJucatori;
			nr2=((Masa)(p5->info))->nrMaxJucatori-((Masa)(p5->info))->nrCrtJucatori;
		}
		nrjuc+=((Masa)(p5->info))->nrMaxJucatori-((Masa)(p5->info))->nrCrtJucatori;
	 	p5=p5->urm;
	}
	if(verifmasa==1)
	{
		if(nrjuc-nr-nr2>=0){			//verifica daca exista destule locuri in sala 
			while(p1!=NULL)
			{
				p2=((Masa)(p1->info))->jucatori->urm;
				if(strcmp(numemasa,((Masa)(p1->info))->numeMasa)==0)
				{
					verifmasa=1;
					while(p3!=NULL)
					{
						if(strcmp(numemasa,((Masa)(p3->info))->numeMasa)!=0){
							p4=((Masa)(p3->info))->jucatori->urm;
							ant3=((Masa)(p3->info))->jucatori;
							nrjuc -= ((Masa)(p3->info))->nrMaxJucatori - ((Masa)(p3->info))->nrCrtJucatori;
									//Scade din numarul de locuri libere,numarul locurilor de la masa respectiva 
							while( ((Masa)(p3->info))->nrCrtJucatori < ((Masa)(p3->info))->nrMaxJucatori	
														 && p2->info!=NULL) 	//parcurege mesele libere si pune jucatorii de la masa eliberata
							{
								((Masa)(p3->info))->nrCrtJucatori++;
								p5=p2;
								p2=p2->urm;
								while(p4->urm->info!=NULL)
									p4=p4->urm;
								p4->urm=p5;
								p5->urm=ant3;
							}
						}
						p3=p3->urm;
					}

					if(ant2!=NULL && p1->urm!=NULL)				//sterge masa ceruta
					{
						ant2->urm=ant2->urm->urm;
						h->nrMese--;
					}
					else if(ant2==NULL && p1->urm==NULL)
					{
						h->masa=NULL;	
					}
					else if(ant2!=NULL && p1->urm==NULL)
						ant2->urm=NULL;
					else if(ant2==NULL && p1->urm!=NULL)
						h->masa=h->masa->urm;
				

					verifmasa=1;		
				}
				ant2=p1;	
				p1=p1->urm;
			}	
		}
		else
			fprintf(out,"Nu exista suficiente locuri in sala!\n");
	}
	if(verifmasa==0)
		fprintf(out,"Masa %s nu exista!\n",numemasa);
}


void tura(Sala h,char numemasa[100],FILE *out)
{
	TLista p1,p2,ant2,santinela,p3,p4;
	p1=h->masa;
	ant2=NULL;;
	int verifmasa=0;
	while(p1!=NULL)
	{
		santinela=((Masa)(p1->info))->jucatori;
		p2=((Masa)(p1->info))->jucatori->urm;
		p3=p2;
		if(strcmp(numemasa,((Masa)(p1->info))->numeMasa)==0)
		{
			verifmasa=1;
			while(p3->urm->info!=NULL)	//permuta jucatorii de la masa 
				p3=p3->urm;
			p3->urm=p2;
			santinela->urm=p2->urm;
			p2->urm=santinela;
			while(santinela->urm->info!=NULL)	// scade numarul de maini
			{
				p3=santinela->urm;
				((Jucator)santinela->urm->info)->nrMaini--;
				santinela=santinela->urm;
			}
			p2=santinela->urm;			
			p4=santinela->urm->urm;
			while(p4->info!=NULL)			//parcurge lista de jucatori la inceput 
			{
					if(((Jucator)p4->info)->nrMaini<=0)		//elimina jucatorul
					{
						((Masa)(p1->info))->nrCrtJucatori--;	
						p2->urm=p4->urm;
						p4=p4->urm;
					}
					else
					{
					p2=p4;
					p4=p4->urm;
					}	
			}		
		}
		ant2=p1;	
		p1=p1->urm;
	}
	if(verifmasa==0)
		fprintf(out,"Masa %s nu exista!\n",numemasa);
	p1=h->masa;
	ant2=NULL;
	while(p1!=NULL)
	{
		if(((Masa)(p1->info))->nrCrtJucatori<=0) //verifica daca trebuie stearsa masa respectiva
		{
			if(ant2!=NULL && p1->urm!=NULL)			//sterge masa
			{
				ant2->urm=ant2->urm->urm;
				h->nrMese--;
			}
			else if(ant2==NULL && p1->urm==NULL)
			{
				h->masa=NULL;	
			}
			else if(ant2!=NULL && p1->urm==NULL)
				ant2->urm=NULL;
			else if(ant2==NULL && p1->urm!=NULL)
				h->masa=h->masa->urm;			
		}		
		ant2=p1;
		p1=p1->urm;
	}	

}

void verifstergemasa(Sala h)				//verifica daca trebuie stearsa masa
{	
	TLista p1,ant2;
	p1=h->masa;
	ant2=NULL;
	while(p1!=NULL)
	{
			if(((Masa)(p1->info))->nrCrtJucatori<=0)
				{
					if(ant2!=NULL && p1->urm!=NULL)
					{
						ant2->urm=ant2->urm->urm;
						h->nrMese--;
					}
					else if(ant2==NULL && p1->urm==NULL)
					{
						h->masa=NULL;	
					}
					else if(ant2!=NULL && p1->urm==NULL)
						ant2->urm=NULL;
					else if(ant2==NULL && p1->urm!=NULL)
						h->masa=h->masa->urm;
					

				}		
		ant2=p1;
		p1=p1->urm;
	}

}

void turacompleta(Sala h,FILE *out)
{
	TLista p1,p2,santinela,p3,p4;
	p1=h->masa;
	while(p1!=NULL)
	{
		santinela=((Masa)(p1->info))->jucatori;
		p2=((Masa)(p1->info))->jucatori->urm;
		p3=p2;
		while(p3->urm->info!=NULL)		//permuta jucatorii de la o masa
			p3=p3->urm;
		p3->urm=p2;
		santinela->urm=p2->urm;
		p2->urm=santinela;
		while(santinela->urm->info!=NULL)	//scade numarul de maini de la fiecare jucator
		{
			p3=santinela->urm;
			((Jucator)santinela->urm->info)->nrMaini--;
			santinela=santinela->urm;
			p2=santinela->urm;
			p4=santinela->urm->urm;
			while(p4->info!=NULL)		//parcurge lista de jucatori	
			{
				if(((Jucator)p4->info)->nrMaini<=0)
				{
					((Masa)(p1->info))->nrCrtJucatori--;		//scade numarul de jucatori de la masa
					p2->urm=p4->urm;
					p4=p4->urm;
					verifstergemasa(h);		//verifica  daca trebuie stearsa masa si o sterge
				}
				else
				{
					p2=p4;
					p4=p4->urm;
				}
			}		
		}	
		p1=p1->urm;
	}
}


int InsListaClasament(ALista juc,Jucator x)		//insereaza intr-o lista noua jucatorii ordonati dupa numarul de maini
{
	TLista aux=malloc(sizeof(Celula));
	TLista *aux3;
	if(!aux)
		return 0;
	aux->info=malloc(sizeof(struct jucator));
	if(!aux->info)
	{
		free(aux);
		return 0;
	}
	Jucator inf;
	inf=x;
	memcpy(aux->info,(void*)inf,sizeof(struct jucator));
	aux->urm=NULL;
	if((*juc)==NULL)					//creaza lista ordonata
	{

		(*juc)=aux;
	}
	else
	{
		int t=0;
		for(aux3=&(*juc);(*aux3)!=NULL;aux3=(&(*aux3)->urm))
		{
			if(((Jucator)(*aux3)->info)->nrMaini<((Jucator)aux->info)->nrMaini)
			{ 
				break;
			}
			if(((Jucator)(*aux3)->info)->nrMaini==((Jucator)aux->info)->nrMaini)
				if( strcmp( ((Jucator)(*aux3)->info)->nume, ((Jucator)aux->info)->nume ) <0)
					t=1;
		if(t==1)
			break;
		}
		aux->urm=(*aux3);
		(*aux3)=aux;
	}
	return 1;
}


void clasament(Sala h,char numemasa[100],FILE *out)
{
	TLista p1,p2;
	TLista p3=NULL;
	p1=h->masa;
	int verifmasa=0;
	while(p1!=NULL)
	{
		p2=((Masa)(p1->info))->jucatori->urm;
		if(strcmp(numemasa,((Masa)(p1->info))->numeMasa)==0)
		{
			verifmasa=1;
			while(p2->info!=NULL)
			{
				InsListaClasament(&p3,((Jucator)p2->info));		//creaza lista pentru clasament
				p2=p2->urm;
			}	
		}	
		p1=p1->urm;
	}
	if(verifmasa==0)
		fprintf(out,"Masa %s nu exista!\n",numemasa);
	else
	{
		fprintf(out,"Clasament %s:\n",numemasa);
		while(p3!=NULL)
		{
			fprintf(out,"%s %d\n",((Jucator)(p3->info))->nume,((Jucator)(p3->info))->nrMaini);
			p3=p3->urm;	
		}
	}	

}

void Elibereaza(Sala h)
{
	int i=0;
	TLista p1,p2,aux;
	p1=h->masa;
	while(p1!=NULL)
	{
		p2=((Masa)(p1->info))->jucatori;
		while(i<((Masa)(p1->info))->nrCrtJucatori)
		{
			aux=p2;
			p2=p2->urm;
			free(aux);
			i++;	
		}
		aux=p1;
		p1=p1->urm;
		free(aux);
	}	

	

}

int main(int argc, char *argv[])
{	
	FILE *conf = fopen(argv[1], "rt");
	FILE *eveniment = fopen(argv[2], "rt");
	FILE *out = fopen (argv[3], "wt");
	Sala camera=malloc(sizeof(struct sala));
	camera=CreareSala(conf);
	char comanda[100],masa[100]="masa2",jucator[100]="Hunter";
	int mana=10;
	while(fscanf(eveniment,"%s",comanda)!=EOF)		//cauta comanda si citeste elementele pentru comanda respectiva
	{	
		if(strcmp(comanda,"print")==0)
		{
			Print(out,camera);
			if(camera->masa==NULL)
				fprintf(out,"Sala este inchisa!\n");	
		}
		if(strcmp(comanda,"noroc")==0)
		{
			fscanf(eveniment,"%s",masa);
			fscanf(eveniment,"%s",jucator);
			fscanf(eveniment,"%d",&mana);
			noroc(camera,masa,jucator,mana,out);
		}
		if(strcmp(comanda,"ghinion")==0)
		{
			fscanf(eveniment,"%s",masa);
			fscanf(eveniment,"%s",jucator);
			fscanf(eveniment,"%d",&mana);
			ghinion(camera,masa,jucator,mana,out);
		}
		if(strcmp(comanda,"tura")==0)
		{
			fscanf(eveniment,"%s",masa);
			tura(camera,masa,out);
		}
		if(strcmp(comanda,"inchide")==0)
		{
			fscanf(eveniment,"%s",masa);
			inchide(camera,masa,out);
		}
		if(strcmp(comanda,"tura_completa")==0)
		{
			turacompleta(camera,out);
		}
		if(strcmp(comanda,"clasament")==0)
		{
			fscanf(eveniment,"%s",masa);
			clasament(camera,masa,out);
		}
	}
	
	Elibereaza(camera);					// elibereaza memoria folosita pentru sala
	
	fclose(conf);
	fclose(out);
	fclose(eveniment);
}
