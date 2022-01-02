#include "inventario.h"
#include "personaggi.h"
#include <stdio.h>

int main(){
    int comando;
    int continua=1;
    tabPg_t *tabPg=allocaTabPg();
    tabInv_t *tabInv=allocaTabInv();

    leggiFilePg(tabPg);
    leggiFileInv(tabInv);

    while(continua) {

        printf("Inserire comando (qualsiasi altro numero per uscire):\n");
        printf("0) Inserisci personaggio:\n");
        printf("1) Elimina personaggio:\n");
        printf("2) Equipaggia oggetto:\n");
        printf("3) Rimuovi oggetto:\n");
        printf("4) Stampa personaggi:\n");
        printf("5) Ricerca oggetto:\n");

        if(scanf("%d", &comando)!=1){
            printf("Errore nell'immissione del comando!\n");
            comando=-1;
        }

        switch (comando) {
            case 0:
                inserisciPg(tabPg);

                break;
            case 1:
                rimuoviPg(tabPg);

                break;
            case 2:
                equipOgg(tabPg, tabInv);

                break;
            case 3:
                rimuoviOgg(tabPg);

                break;
            case 4:
                stampaTabPg(tabPg);

                break;
            case 5:
                ricercaOgg(tabInv);

                break;
            default:
                continua=0;
                break;
        }
    }
    liberaTabPg(tabPg);
    liberaTabInv(tabInv);
    return 0;
}
