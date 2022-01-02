#include "personaggi.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

//Inserimento in lista ordinata
link SortListIns(link h, pg_t val, link *tail){
    link x,p;
    char *k = val.codice;

    //Si gestisce il caso in cui la lista sia nulla o l'elemento che si sta inserendo è maggiore stretto del primo elemento della lista
    if (h==NULL || strcmp(k, h->pg.codice)<0)
        return newNode(val, h);
    //Il ciclo itera su tutta la lista o si ferma anticipatamente se il nuovo elemento è minore stretto di quello che si sta considerando in lista
    for(x=h->next, p=h; x!=NULL && strcmp(k, x->pg.codice)>0; p=x, x=x->next);
    //Alla fine del ciclo viene creato un nuovo nodo dopo l'ultimo considerato in lista
    p->next = newNode(val,x);
    for(x=h; x->next!=NULL; x=x->next);
    *tail = x;
    return h;
}

link newNode(pg_t val, link next){
    link x = malloc(sizeof *x);
    if (x==NULL)
        return NULL;
    x->pg = val;
    x->next = next;
    //Viene allocato il vettore equipaggiamento del personaggio
    x->pg.equip=malloc(sizeof(*x->pg.equip));
    x->pg.equip->inUso=0;
    x->pg.equip->vettEq[x->pg.equip->inUso]=NULL;
    return x;
}

void leggiFilePg(tabPg_t *tabPg){
    FILE *fp;
    pg_t pg;

    if((fp=fopen("pg.txt", "r"))==NULL){
        fprintf(stderr, "Errore nell'apertura del file pg.txt\n");
        exit(1);
    }

    while(fscanf(fp, "%s %s %s %d %d %d %d %d %d", pg.codice, pg.nome, pg.classe, &pg.stat.hp, &pg.stat.mp, &pg.stat.atk, &pg.stat.def, &pg.stat.mag, &pg.stat.spr)!=EOF) {
        pg.stat_base=pg.stat;
        tabPg->headPg=SortListIns(tabPg->headPg, pg, &tabPg->tailPg);
        tabPg->nPg++;
    }
    fclose(fp);
}

void rimuoviPg(tabPg_t *tabPg){
    link *xp, t;
    char code[CODE_LEN];
    printf("Inserire il codice del personaggio da eliminare (<PGXXXX>):\n");
    scanf("%s", code);
    for(xp=&(tabPg->headPg); (*xp)!=NULL; xp=&((*xp)->next)){
        if(strcmp((*xp)->pg.codice, code)==0) {
            t=*xp;
            *xp = (*xp)->next;
            free(t->pg.equip);
            free(t);
            break;
        }
    }
    printf("Personaggio eliminato!\n");
    stampaTabPg(tabPg);
}

//Si cerca all'interno della lista il personaggio inserito da tastiera e si controlla che abbia almeno un oggetto equipaggiato
//In caso positivo tutti gli eventuali oggetti nel vettore equipaggiamento dopo quello che dev'essere rimosso vengono
//scalati di una posizione indietro e nell'indice "inUso" viene assegnato il puntatore a NULL per indicare
//la fine del vettore equipaggiamento.
void rimuoviOgg(tabPg_t *tabPg){
    link x;
    int j,i;
    char code[CODE_LEN], ogg[MAXC];

    printf("Inserire codice personaggio <PGXXXX> e nome dell'oggetto da rimuovere:\n");
    scanf("%s %s", code, ogg);

    for(x=tabPg->headPg; x!=tabPg->tailPg->next; x=x->next){
        if(strcmp(x->pg.codice, code)==0){
            for(j=0; j<x->pg.equip->inUso; j++) {
                if(strcmp(x->pg.equip->vettEq[j]->nome, ogg)==0) {
                    for(i=j; i<x->pg.equip->inUso; i++) {
                        x->pg.equip->vettEq[i]=x->pg.equip->vettEq[i+1];
                    }
                    x->pg.equip->vettEq[i]=NULL;
                    x->pg.equip->inUso--;
                    printf("Oggetto (%s) rimosso con successo.\n", ogg);
                    calcoloStat(tabPg, code);
                    return;
                }
            }
            printf("Oggetto inserito (%s) non presente nell'equipaggiamento del personaggio (%s)!\n", ogg, code);
            return;
        }
    }
    printf("Codice inserito (%s) non presente nella tabella!\n", code);
}

void calcoloStat(tabPg_t *tabPg, char *code){
    link x;
    int i;
    for(x=tabPg->headPg; x!=tabPg->tailPg->next; x=x->next){
        if(strcmp(code, x->pg.codice)==0){
            x->pg.stat=x->pg.stat_base;
            for(i=0; i<x->pg.equip->inUso; i++){
                x->pg.stat.hp+=x->pg.equip->vettEq[i]->stat.hp;
                x->pg.stat.mp+=x->pg.equip->vettEq[i]->stat.mp;
                x->pg.stat.atk+=x->pg.equip->vettEq[i]->stat.atk;
                x->pg.stat.def+=x->pg.equip->vettEq[i]->stat.def;
                x->pg.stat.mag+=x->pg.equip->vettEq[i]->stat.mag;
                x->pg.stat.spr+=x->pg.equip->vettEq[i]->stat.spr;
            }
            if(x->pg.stat.hp<1)
                x->pg.stat.hp=1;
            if(x->pg.stat.mp<1)
                x->pg.stat.mp=1;
            if(x->pg.stat.atk<1)
                x->pg.stat.atk=1;
            if(x->pg.stat.def<1)
                x->pg.stat.def=1;
            if(x->pg.stat.mag<1)
                x->pg.stat.mag=1;
            if(x->pg.stat.spr<1)
                x->pg.stat.spr=1;
            stampaPg(x->pg);
        }
    }
}

void stampaPg(pg_t pg){
    int i;
    printf("%s %s %s %d %d %d %d %d %d\n", pg.codice, pg.nome, pg.classe, pg.stat.hp, pg.stat.mp, pg.stat.atk, pg.stat.def, pg.stat.mag, pg.stat.spr);
    if(pg.equip->vettEq[0]!=NULL){
        printf("Oggetti Equip: ");
        for(i=0; i<MAXOGG && pg.equip->vettEq[i]!=NULL; i++){
            printf("%s ", pg.equip->vettEq[i]->nome);
        }
        printf("\n");
    } else
        printf("Nessun oggetto equipaggiato.\n");

}

void equipOgg(tabPg_t *tabPg, tabInv_t *tabInv){
    link x;
    int j;
    char code[CODE_LEN], ogg[MAXC];

    printf("Tabella degli oggetti:\n");
    stampaTabInv(tabInv);
    printf("Inserire codice personaggio <PGXXXX> e nome dell'oggetto:\n");
    scanf("%s %s", code, ogg);

    for(x=tabPg->headPg; x!=tabPg->tailPg->next; x=x->next){
        if(strcmp(x->pg.codice, code)==0){
            if(x->pg.equip->inUso<MAXOGG){
                for(j=0; j<tabInv->nInv; j++){
                    if(strcmp(tabInv->vettInv[j].nome, ogg)==0){
                        x->pg.equip->vettEq[x->pg.equip->inUso]=&tabInv->vettInv[j];
                        x->pg.equip->inUso++;
                        x->pg.equip->vettEq[x->pg.equip->inUso]=NULL;
                        printf("Oggetto equipaggiato con successo!\n");
                        calcoloStat(tabPg, code);
                        return;
                    }
                }
                printf("Nome dell'oggetto inserito (%s) non presente nella tabella!\n", ogg);
                return;
            }
            printf("Numero massimo di oggetti per %s raggiunto!\n", code);
            return;
        }
    }
    printf("Codice inserito (%s) non presente nella tabella!\n", code);
}

void inserisciPg(tabPg_t* tabPg){
    pg_t pg;
    printf("Inserire nuovo personaggio: <PGXXXX> dove X = (0-9) <Nome> <Classe> <HP> <MP> <ATK> <DEF> <MAG> <SPR>:\n");
    scanf("%s %s %s %d %d %d %d %d %d", pg.codice, pg.nome, pg.classe, &pg.stat.hp, &pg.stat.mp, &pg.stat.atk, &pg.stat.def, &pg.stat.mag, &pg.stat.spr);
    pg.stat_base=pg.stat;
    tabPg->headPg=SortListIns(tabPg->headPg, pg, &tabPg->tailPg);
    tabPg->nPg++;
    stampaTabPg(tabPg);
}

void stampaTabPg(tabPg_t *tabPg){
    link x;
    printf("\n");
    for(x=tabPg->headPg; x!=tabPg->tailPg->next; x=x->next){
        printf("%s %s %s %d %d %d %d %d %d\n", x->pg.codice, x->pg.nome, x->pg.classe, x->pg.stat.hp, x->pg.stat.mp, x->pg.stat.atk, x->pg.stat.def, x->pg.stat.mag, x->pg.stat.spr);
    }
    printf("\n");
}

//Deallocazione della tabella dei personaggi (Vengono prima deallocati gli eventuali equipaggiamenti, poi i personaggi e infine il puntatore alla tabella)
void liberaTabPg(tabPg_t *tabPg){
    link x, t;
    if(tabPg->headPg!=NULL)
        for(x=tabPg->headPg, t=x->next; t!=NULL; x=t, t=x->next) {
            if(x->pg.equip!=NULL)
                free(x->pg.equip);
            free(x);
        }
    free(tabPg);
}

//Allocazione e inizializzazione della tabella dei personaggi
tabPg_t *allocaTabPg(){
    tabPg_t *tabPg;
    tabPg=malloc(sizeof(*tabPg));
    tabPg->headPg=NULL; tabPg->nPg=0;
    return tabPg;
}
