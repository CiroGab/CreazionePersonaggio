#ifndef APA_PERSONAGGI_H
#define APA_PERSONAGGI_H
#define MAXOGG 8
#define CODE_LEN 6+1
#include "inventario.h" //Il modulo personaggi deve utilizzare alcune funzioni del modulo inventario per poter definire l'equipaggiamento

typedef struct{
    int inUso;
    inv_t *vettEq[MAXOGG];
}equip_t;

typedef struct{
    char codice[CODE_LEN];
    char nome[MAXC], classe[MAXC];
    equip_t *equip;
    stat_t stat_base;
    stat_t stat;
}pg_t;

typedef struct Nodopg_t *link;
struct Nodopg_t{
    pg_t pg;
    link next;
};

typedef struct{
    link headPg;
    link tailPg;
    int nPg;
}tabPg_t;

link newNode(pg_t val, link next);
link SortListIns(link h, pg_t val, link *tail);
void rimuoviPg(tabPg_t *tabPg);
void stampaPg(pg_t pg);
void equipOgg(tabPg_t *tabPg, tabInv_t *tabInv);
void calcoloStat(tabPg_t *tabPg, char *code);
void inserisciPg(tabPg_t *tabPg);
void leggiFilePg(tabPg_t *tabPg);
void stampaTabPg(tabPg_t *tabPg);
void rimuoviOgg(tabPg_t *tabPg);
void liberaTabPg(tabPg_t *tabPg);
tabPg_t *allocaTabPg();
#endif //APA_PERSONAGGI_H
