#include "inventario.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void leggiFileInv(tabInv_t *tabInv){
    FILE *fp;
    inv_t inv;

    if((fp=fopen("inventario.txt", "r"))==NULL){
        fprintf(stderr, "Errore nell'apertura del file inventario.txt\n");
        exit(1);
    }

    fscanf(fp,"%d", &tabInv->maxInv);
    tabInv->vettInv=malloc(tabInv->maxInv* sizeof(inv_t));
    tabInv->nInv=0;
    while(fscanf(fp, "%s %s %d %d %d %d %d %d", inv.nome, inv.tipo, &inv.stat.hp, &inv.stat.mp, &inv.stat.atk, &inv.stat.def, &inv.stat.mag, &inv.stat.spr)!=EOF){
        tabInv->vettInv[tabInv->nInv]=inv;
        tabInv->nInv++;
    }
}

//Ricerca un oggetto per nome all'interno della tabella dell'inventario e lo stampa a video
void ricercaOgg(tabInv_t *tabInv){
    int i;
    char nome[MAXC];
    printf("Inserire nome oggetto:\n");
    scanf("%s", nome);
    for(i=0; i<tabInv->maxInv; i++){
        if(strcmp(tabInv->vettInv[i].nome, nome)==0) {
            printf("Oggetto trovato: %s %s %d %d %d %d %d %d\n", tabInv->vettInv[i].nome, tabInv->vettInv[i].tipo,
                   tabInv->vettInv[i].stat.hp, tabInv->vettInv[i].stat.mp, tabInv->vettInv[i].stat.atk,
                   tabInv->vettInv[i].stat.def, tabInv->vettInv[i].stat.mag, tabInv->vettInv[i].stat.spr);
            return;
        }    
    }
    printf("Oggetto (%s) non trovato.\n", nome);
}

//Stampa della tabella inventario
void stampaTabInv(tabInv_t *tabInv){
    int i;
    for(i=0; i<tabInv->maxInv; i++){
        printf("%s %s %d %d %d %d %d %d\n", tabInv->vettInv[i].nome, tabInv->vettInv[i].tipo, tabInv->vettInv[i].stat.hp, tabInv->vettInv[i].stat.mp, tabInv->vettInv[i].stat.atk, tabInv->vettInv[i].stat.def, tabInv->vettInv[i].stat.mag, tabInv->vettInv[i].stat.spr);
    }
    printf("\n");
}

//Deallocazione della tabella inventario (vengono prima deallocati tutti i vettori(puntatori) interni)
void liberaTabInv(tabInv_t *tabInv){
    int i;
    for(i=0; i<tabInv->maxInv; i++){
        free(tabInv[i].vettInv);
    }
    free(tabInv);
}

//Allocazione del puntatore alla tabella
tabInv_t *allocaTabInv(){
    tabInv_t *tabInv;
    tabInv=malloc(sizeof(*tabInv));
    return tabInv;
}
