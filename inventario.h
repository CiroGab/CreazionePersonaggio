#ifndef APA_INVENTARIO_H
#define APA_INVENTARIO_H
#define MAXC 50+1

typedef struct{
    int hp, mp, atk, def, mag, spr;
}stat_t;

typedef struct{
    char nome[MAXC], tipo[MAXC];
    stat_t stat;
}inv_t;

typedef struct{
    inv_t* vettInv;
    int nInv;
    int maxInv;
}tabInv_t;

void ricercaOgg(tabInv_t *tabInv);
void leggiFileInv(tabInv_t *tabInv);
void stampaTabInv(tabInv_t *tabInv);
void liberaTabInv(tabInv_t *tabInv);
tabInv_t *allocaTabInv();



#endif //APA_INVENTARIO_H
