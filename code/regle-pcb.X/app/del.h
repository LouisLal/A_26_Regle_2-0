/*
 * del.h
 *
 * 5 DEL en charlieplexing sur 3 broches (indicateur de niveau).
 *
 *   Noeud N1 : RC0 (CP_2) via R4 270
 *   Noeud N2 : RC1 (CP_3) via R5 270
 *   Noeud N3 : RA6 (CP_1) via R3 270
 *
 * Ordre physique sur la règle (gauche -> droite) : D1 D2 D3 D4 D5.
 * Une seule DEL est allumée à la fois, donc aucun balayage n'est nécessaire.
 */
#ifndef DEL_H
#define DEL_H

#include <stdint.h>

/* Mettre à 0 si les DEL s'allument dans le mauvais ordre (ou pas du tout) :
 * cela veut dire que la pastille 1 de l'empreinte SM0805HCL est la cathode. */
#ifndef DEL_PASTILLE1_ANODE
#define DEL_PASTILLE1_ANODE 1
#endif

void DEL_Init(void);

/* Allume la DEL n (1..5), ou éteint tout si n == 0. */
void DEL_Allume(uint8_t n);

#endif /* DEL_H */
