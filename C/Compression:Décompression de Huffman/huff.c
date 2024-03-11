#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Nombre de symbole de la table ASCII
#define MAX_ASCII 256
// Maximum d'occurence d'un caractère dans le fichier
#define MAX_OCCURRENCE 255
// Maximum de caractère pour le nom du fichier
#define MAX_NOM 255
// Si le fichier source n'est pas trouvé
#define SOURCE_INTROUVABLE -1
#define FICHIER_NON_GENERE -2

#define COUNT 5

/* Structure */
typedef struct Dictionnaire
{
    unsigned int code_binaire; // code binaire
    unsigned int nombre_bits;  // nombre de bits
} Dico_t;

typedef struct arbre_comp
{
    unsigned char symbole;     // charactères unicode
    unsigned int occurrence;   // nombre d'occurences du symbole
    unsigned int code_binaire; // code binaire
    unsigned int nombre_bits;  // nombre de bits
    struct arbre_comp *g;      // sous-arbre gauche
    struct arbre_comp *d;      // sous-arbre droit
} Arbre_t;

/* Variables globales */
/* Tableau d'occurences de chaque symbole de 0 à 255  contenu dans le fichier*/
unsigned int _tab_occurrences[MAX_ASCII];
/* Tableau de struct dico de 0 à 255 contenant le code binaire et le nb bits de chaque symbole */
Dico_t _dictionnaire[MAX_ASCII];
unsigned int _nb_symboles = 0;
unsigned int _nb_bits_max = 0;
unsigned int _nb_oct_entete = 0;
unsigned int _nb_oct_donnees = 0;

/* maximum d'occurences d'un symbole */
unsigned int _max_occurrences = 0;
/* nb d'octet du fichier a compréssé */
unsigned int _nb_oct_fichier_a_compress = 0;
unsigned int _nb_oct_fichier_a_decomp = 0;

/* Tableau de pointeur d'arbres de 0 à 255
contenant un pointeur vers un noeud arbre
construit pour chaque symbole */
Arbre_t *_tab_arbre[MAX_ASCII];

Arbre_t *_racine = NULL;

/* Procédures et fonctions du projet */
int compression(char nom_fichier_source[]);
void init_tab_occurrences(void);
int calcul_occurrences(char nomfichier[]);
void initialise_Dictionnaire();
void init_tableau_arbre(Arbre_t *tableau_arbre[]);
void construire_abr(void);
void tri_tableau_arbre_occurrences(Arbre_t *tableau_arbre[]);
void creer_code(Arbre_t *arbre_t, unsigned int code, unsigned int niveau);
void ecrire_entete(FILE *f_cible);
void encodage(FILE *f_source, FILE *f_cible);

int decompression(char nom_fichier_source[]);
unsigned int calcule_taille_fichier(FILE *f_entree);
void lire_entete(FILE *f_entree);
void lire_encodage(FILE *f_source, FILE *f_cible);
void affiche_synthaxe(char commande[]);

/* Fonctions annexes de debugage */
void parcours_prefixe(Arbre_t *a);
int compter_noeud_arbre(Arbre_t *a);
void print2DUtil(Arbre_t *root, int space);
void print2D(Arbre_t *root);
void affichebin(unsigned n);
char *bin(unsigned long int i);

/* === PROGRAMME PRINCIPAL === */
int main(int argc, char *argv[])
{
    /* ===== D E B U G  calcul occurrences ====== */
    /* int calcul = -1;
    if (argc == 3)
    {
        calcul = calcul_occurrences(argv[2]);
    }
    printf("calcul return : %d \n", calcul); */

    /* Affichage du _tab_ocurrences */
    /* for (int i = 0; i < MAX_ASCII; i++)
    {
        printf("L'Element %d du Tableau est : %d \n", i, _tab_occurrences[i]);
    } */
    /* ======================= */

    int retour;
    /* Buffer nom de fichier */
    char _nom_fichier_a_comp[MAX_NOM], _nom_fichier_a_decomp[MAX_NOM];

    if (argc != 3)
    {
        affiche_synthaxe(argv[0]);
    }
    else
    {
        /* ===================== C O M P R E S S I O N ===================== */
        /* comparaison str du 2eme argument de compilation */
        if (!strcmp(argv[1], "-c"))
        {
            /* copie du nom de fichier dans var globales */
            strcpy(_nom_fichier_a_comp, argv[2]);
            retour = compression(_nom_fichier_a_comp);

            /* GESTION code retour de Compression */
            if (retour == SOURCE_INTROUVABLE)
                printf("Fichier %s non trouvé \n", _nom_fichier_a_comp);
            else if (retour == FICHIER_NON_GENERE)
                printf("Impossible de générer le Fichier %s.huff \n", _nom_fichier_a_comp);
            else
                printf(" • Compression du fichier %s bien effectué !\n", _nom_fichier_a_comp);
        }
        /* ================== D E C O M P R E S S I O N =================== */
        /* comparaison str du 2eme argument de compilation */
        else if (!strcmp(argv[1], "-d"))
        {
            /* copie du nom de fichier dans var globales */
            strcpy(_nom_fichier_a_decomp, argv[2]);
            retour = decompression(_nom_fichier_a_decomp);

            /* Gestion code retour de Décompression */
            if (retour == SOURCE_INTROUVABLE)
                printf("Fichier %s non trouvé \n", _nom_fichier_a_decomp);
            else if (retour == FICHIER_NON_GENERE)
                printf("Impossible de générer le fichier %s.comp \n", _nom_fichier_a_decomp);
            else
                printf(" • Décompression du fichier %s bien effectué !\n", _nom_fichier_a_decomp);
        }
        else
            affiche_synthaxe(argv[0]);
    }
    // parcours_prefixe(_racine);
    return 0;
}

void parcours_prefixe(Arbre_t *a)
{
    if (!a)
        printf("<>\n");
    else
    {
        printf(" [%c/%d][code: %d / nb_bits: %d] \n", a->symbole, a->occurrence, a->code_binaire, a->nombre_bits);
        // printf(" [%c/%d] \n", a->symbole, a->occurrence);
        parcours_prefixe(a->g);
        parcours_prefixe(a->d);
    }
}

/*compter noeud*/
int compter_noeud_arbre(Arbre_t *a)
{
    if (a == NULL)
        return 0;
    else
        return (1 + compter_noeud_arbre(a->g) + compter_noeud_arbre(a->d));
}

/* Magnifique fonction permmettant l'affichage de base 10 en binaire */
char *bin(unsigned long int i)
{
    static char buffer[1 + sizeof(unsigned long int) * 8] = {0};
    char *p = buffer - 1 + sizeof(unsigned long int) * 8;
    do
    {
        *--p = '0' + (i & 1);
        i >>= 1;
    } while (i);
    return p;
}

/* ===================== C O M P R E S S I O N ===================== */
/* compression du fichier source passé en parametre */
int compression(char nom_fichier_source[])
{
    /* code retour si la fonction à bien fonctionné */
    int code_retour = 0;
    /* Chaine de caractères du nom de fichier */
    char nom_fichier_cible[MAX_NOM];
    /* Fichier sourcer et fichier cible */
    FILE *f_source, *f_cible;

    /* Vérification du calcul d'occurences bien éffectué */
    code_retour = calcul_occurrences(nom_fichier_source);

    /* si calcul éffectué */
    if (code_retour != SOURCE_INTROUVABLE)
    {
        /* initialisation du tableau dictionnaire à 0 code binaire et nb bits */
        initialise_Dictionnaire();
        /* initialisation du tableau arbres avec construction
            du noeud arbre pour chaque symbole présent dans le tab
            d'occurrences + affectation des propriétés symbole et occurences  */
        init_tableau_arbre(_tab_arbre);

        /* tri dans l'ordre décroissant du tableau arbres en fonction des occur */
        tri_tableau_arbre_occurrences(_tab_arbre);

        /* Display array for debug */
        /* for (int i = 0; i < MAX_ASCII; i++)
        {
            printf("tab_arbre[%d / %c] = %d \n", i, _tab_arbre[i]->symbole,  _tab_arbre[i]->occurrence);
        } */

        /* Construction de l'arbre binaire */
        construire_abr();

        /*compter noeud*/
        int nb_noeud = compter_noeud_arbre(_racine);
        printf(" • L'arbre _racine contient  %d noeuds\n", nb_noeud);
        printf(" • nb_occurences de la racine = %d \n", _racine->occurrence);

        /* creation des codes binaires */
        creer_code(_racine, 0, 0);

        /* Pour affichage dictionnaire */
        /* for (int i = 0; i < 256; i++)
        {
            printf("%c", i);
            printf(" [dec: %d][code: %s][nb_bits: %d] \n", _dictionnaire[i].code_binaire, bin(_dictionnaire[i].code_binaire), _dictionnaire[i].nombre_bits);
            // affichebin(_dictionnaire[i].code_binaire);
            printf("\n");
        } */

        /* affichage arbre  */
        // parcours_prefixe(_racine);

        /* génération du nom de fichier cible */
        strcpy(nom_fichier_cible, nom_fichier_source);
        /* concatenation du nom de fichier */
        strcat(nom_fichier_cible, ".huff");

        /* Ouverture des fichiers en mode lecture et écriture */
        f_source = fopen(nom_fichier_source, "r");
        f_cible = fopen(nom_fichier_cible, "w");

        if (f_cible == NULL)
        {
            code_retour = FICHIER_NON_GENERE;
        }
        else
        {

            ecrire_entete(f_cible);
            encodage(f_source, f_cible);

            /* Informations de compressions  */
            printf(" • Taille du fichier à compresser : %9d octets \n", _nb_oct_fichier_a_compress);
            printf(" • Taille du fichier compressé : %9d octets \n", _nb_oct_fichier_a_decomp);
            printf(" • Taille de l'en-tete du fichier compressé : %9d octets \n", _nb_oct_entete);
            printf(" • Taille des données à décompressé: %9d octets \n", _nb_oct_donnees);
            printf(" • Taux de compression : %4.1f %% \n", 100 * (1 - ((float)_nb_oct_fichier_a_decomp / (float)_nb_oct_fichier_a_compress)));
            fclose(f_cible);
        }
        fclose(f_source);
    }
    return code_retour;
}

/* Initialisation du tableau d'occurences */
void init_tab_occurrences()
{
    int i;
    for (i = 0; i < MAX_ASCII; i++)
    {
        _tab_occurrences[i] = 0;
    }
}

/* Calcul des occurences des symboles dans le fichier */
int calcul_occurrences(char nomfichier[])
{
    /* code retour pour vérifier que la fonction s'est bien déroulé */
    int i, res_lecture, code_retour = 0;
    /* octet a valeur d'indice représentant la valeur Ascii du char */
    unsigned char octet;
    FILE *f_source;
    /* initialisation du tableau d'occ à 0 */
    init_tab_occurrences();
    /* ouverture du fichier en lecture */
    f_source = fopen(nomfichier, "r");
    /* si erreur ouverture retourne erreur -1 */
    if (f_source == NULL)
    {
        code_retour = SOURCE_INTROUVABLE;
    }
    else
    {
        printf("fsource : %s \n", nomfichier);

        /* tant que la fin du fichier n'est pas atteinte */
        while (!feof(f_source))
        {
            /*lecture caractere ou symbole avec fscanf */
            res_lecture = fscanf(f_source, "%c", &octet);
            /* si la fin du fichier n'est pas atteinte */
            if (res_lecture != EOF)
            {
                // incrémente tableau d'occurences
                _tab_occurrences[octet]++;
                // incrémente nb octet
                _nb_oct_fichier_a_compress++;
            }
        }
        /* fermeture du fichier */
        fclose(f_source);
        /* memorise le nombre maximal d'occurences */
        for (i = 0; i < MAX_ASCII; i++)
        {
            if (_tab_occurrences[i] > _max_occurrences)
                _max_occurrences = _tab_occurrences[i];
        }
    }
    // si tout s'est bien passé
    return code_retour;
}

void initialise_Dictionnaire()
{
    int i;

    for (i = 0; i < MAX_ASCII; i++)
    {
        /* Initialisation des elements du dictionnaire à 0 */
        _dictionnaire[i].code_binaire = 0;
        _dictionnaire[i].nombre_bits = 0;
    }
}

/* Initialisation du tableau d'arbre */
void init_tableau_arbre(Arbre_t *tableau_arbre[])
{
    int i, j = 0;
    Arbre_t *arbre;
    /* Initialisation de chaque cellule du tableau arbre à NULL */
    for (i = 0; i < MAX_ASCII; i++)
    {
        tableau_arbre[i] = NULL;
    }
    /* Si le tableau d'occurrence est different de 0, donc je créais un noeud (le caractère est dans le fichier) */
    for (i = 0; i < MAX_ASCII; i++)
    {
        if (_tab_occurrences[i] != 0)
        {
            arbre = (Arbre_t *)malloc(sizeof(Arbre_t));
            arbre->g = NULL;
            arbre->d = NULL;
            arbre->symbole = i;
            arbre->code_binaire = 0;
            arbre->nombre_bits = 0;
            arbre->occurrence = _tab_occurrences[i];
            tableau_arbre[j++] = arbre;
        }
    }
}

/* construction arbre binaire de compression */
void construire_abr(void)
{
    int i;
    Arbre_t *gauche, *droite, *new_arbre;
    Arbre_t *tableau_arbre[MAX_ASCII];

    /* Copie du _tab_arbre dans tableau_arbre[] */
    for (i = 0; i < MAX_ASCII; i++)
    {
        tableau_arbre[i] = _tab_arbre[i];
    }
    /* for (int i = 0; i < MAX_ASCII; i++)
    {
        printf("| tab_arbre[%d] char = %c , occur = %d  |\n", i, tableau_arbre[i]->symbole, tableau_arbre[i]->occurrence);
    } */

    /* Tant que tous les noeuds n'ont pas été fusionés dans 0  */
    while (tableau_arbre[1] != NULL)
    {
        /* on fusionne les arbres 0 & 1 */
        /* Le résultat est rangé en 0 */

        /* arbre gauche = le noeud a l'index 0 */
        gauche = tableau_arbre[0];
        /* arbre droit = le noeud a l'index 1 */
        droite = tableau_arbre[1];

        /* Création d'un nouvel Arbre */
        new_arbre = (Arbre_t *)malloc(sizeof(Arbre_t));
        /* fusion des occurences gauche et droite */
        new_arbre->occurrence = gauche->occurrence + droite->occurrence;
        /* affectation des arbres gauche et droite en enfant du nouvel arbre */
        new_arbre->g = gauche;
        new_arbre->d = droite;
        /* symbole a 0 */
        new_arbre->symbole = 0;
        /* rangement de l'arbre dans 0 */
        tableau_arbre[0] = new_arbre;
        /* fin création + fusion */

        /* on decale la case 1 à la fin et on l'affecte à NULL */
        i = 1;

        while ((i < MAX_ASCII - 1) && (tableau_arbre[i] != NULL))
        {
            tableau_arbre[i] = tableau_arbre[i + 1];
            i++;
        }

        tableau_arbre[i] = NULL;
        /* on trie le tableau  */
        tri_tableau_arbre_occurrences(tableau_arbre);
    }
    _racine = tableau_arbre[0];
    // parcours_prefixe(_racine);
}

/* Tri par occurrences */
void tri_tableau_arbre_occurrences(Arbre_t *tableau_arbre[])
{
    /* Déclaration i a l'index 1 et j à l'index suivant*/
    int i = 1;
    int j = 2;

    /* Declaration Arbre temporaire */
    Arbre_t *arbre;

    /* Tant que i < 256  et  que le noeud est présent dans le tableau */
    while ((i < MAX_ASCII) && (tableau_arbre[i] != NULL))
    {
        /* si l'occurrence de la cellule précédente est plus grande que l'occurrence actuelle */
        if (tableau_arbre[i - 1]->occurrence < tableau_arbre[i]->occurrence)
        {
            /* on avance nos 2 index et on continue */
            i = j;
            j++;
        }
        /* sinon (i-1) est plus petit que (i) */
        else
        {
            /* on permute (i-1) avec (i) */
            arbre = tableau_arbre[i - 1];
            tableau_arbre[i - 1] = tableau_arbre[i];
            tableau_arbre[i] = arbre;

            i--;
            i = (i == 0) ? j++ : i;
        }
    }
}

/* Création du code avec un parcours préfixe */
void creer_code(Arbre_t *arbre, unsigned int code, unsigned int niveau)
{
    /* Savoir si on est sur une feuille */
    if (arbre->g == NULL && arbre->d == NULL)
    {
        /* Remplissage des informations des symboles dans les noeuds correspondant */
        arbre->nombre_bits = niveau;
        arbre->code_binaire = code;
        /* Remplissage du dictionnaire */
        // printf("niveau++ = %d\n", niveau);
        _dictionnaire[arbre->symbole].code_binaire = code;
        _dictionnaire[arbre->symbole].nombre_bits = niveau;
        /* incrémente le nb de symboles contenu dans l'arbre */
        _nb_symboles++;

        /* nb bits max equivaut au nb de niveau de l'arbre */
        if (niveau > _nb_bits_max)
        {
            _nb_bits_max = niveau;
        }
    }
    else
    {
        /* décalage de bit a gauche (0) lors d'un parcours fils gauche */
        creer_code(arbre->g, code << 1, niveau + 1);
        /* décalage de bit a gauche +1 (1) lors d'un parcours fils droit */
        creer_code(arbre->d, (code << 1) + 1, niveau + 1);
    }
}

/* écriture de l'en-tete  */
void ecrire_entete(FILE *f_cible)
{
    /* static car variables utilisés dans d'autres fonctions */
    static unsigned int nb_octets_occ = 1, nb_octets_code_binaire = 1, res = 0;

    unsigned i, j, k, occurence_a_ecrire, code_binaire_a_ecrire;

    unsigned int taille_fichier_source, taille_unsigned_int;
    unsigned char tab_octets[8];

    /* 3 octets = écriture des infos nécéssaires à la lecture de l'en-tête  */

    /* premier octet = le nombre de symboles sauvegardés : 256 Symboles  */
    /* 0 à 255 pour indiquer 1 à 256 Symboles  */
    /* (on retire -1 pour éviter le passage à 8 pour la valeur 256) */
    fprintf(f_cible, "%c", _nb_symboles - 1);
    _nb_oct_entete++;
    // printf("nb octet entete(1) : %d \n", _nb_oct_entete);

    /* Deuxième octet = nombre d'octets utilisés (nb_octets_occ) */
    /*                  pour écrire la valeur occurence d'un symbole */
    res = _max_occurrences;
    /* si jamais un meme symbole est présent plus de 256 fois */
    while ((res = res / 256) != 0)
        nb_octets_occ++;
    fprintf(f_cible, "%c", nb_octets_occ);
    _nb_oct_entete++;

    /* Troisième octet = nombre d'octets utilisés pour écrire */
    /*                   le code binaire d'un symbole */
    res = _nb_bits_max;
    /* code binaire 8bits par octet */
    nb_octets_code_binaire = (res / 8) + 1;
    fprintf(f_cible, "%c", nb_octets_code_binaire);
    _nb_oct_entete++;

    /*  4 octets = écriture de la taille du fichier  */
    /*             source en nombre d'octets  */

    /* nb total de char contenu dans le fichier */
    taille_fichier_source = _nb_oct_fichier_a_compress;

    /* taille d'un entier non signé 4 bytes */
    taille_unsigned_int = sizeof(unsigned int);

    for (i = 0; i < taille_unsigned_int; i++)
    {
        j = taille_unsigned_int - i - 1;
        /* tab octet de 8 char */
        tab_octets[j] = taille_fichier_source;
        /* décalage d'un octet à droite */
        taille_fichier_source = taille_fichier_source >> 8;
    }
    /* ajout des 4 octets  */
    for (i = 0; i < taille_unsigned_int; i++)
    {
        fprintf(f_cible, "%c", tab_octets[i]);
        _nb_oct_entete++;
    }
    printf(" • _nb_symboles : %d \n", _nb_symboles);
    for (k = 0; k < _nb_symboles; k++)
    {
        /* Pour chaque symbole de _tab_arbre on écrit : */
        /* - un octet pour le symbole */
        /* - nb_octet_occ octets pour la valeur de l'occurrence */
        /* - nb_octets_code_binaire octets pour le code binaire du symbole */

        /* écriture du symbole sur un octet */
        fprintf(f_cible, "%c", _tab_arbre[k]->symbole);
        _nb_oct_entete++;

        /* écriture du nombre d'occurrences sur nb_octets_occ octets */
        occurence_a_ecrire = _tab_arbre[k]->occurrence;

        // printf("var : %d \n", nb_octets_occ);
        for (i = 0; i < nb_octets_occ; i++)
        {
            j = nb_octets_occ - i - 1;
            tab_octets[j] = occurence_a_ecrire;
            /* décalage d'un octet à droite  */
            occurence_a_ecrire = occurence_a_ecrire >> 8;
        }
        //printf("nb octets occ : %d \n", nb_octets_occ);
        for (i = 0; i < nb_octets_occ; i++)
        {
            fprintf(f_cible, "%c", tab_octets[i]);
            _nb_oct_entete++;
        }

        /* Ecriture du code binaire sur nb_octets_code_binaire octets  */
        code_binaire_a_ecrire = _tab_arbre[k]->code_binaire;

        for (i = 0; i < nb_octets_code_binaire; i++)
        {
            j = nb_octets_code_binaire - i - 1;
            tab_octets[j] = code_binaire_a_ecrire;
            /* décalage d'un octet à droite  */
            code_binaire_a_ecrire = code_binaire_a_ecrire >> 8;
        }

        for (i = 0; i < nb_octets_code_binaire; i++)
        {
            fprintf(f_cible, "%c", tab_octets[i]);
            _nb_oct_entete++;
        }

        /* Ecrire du nombre de bits sur un octet  */
        fprintf(f_cible, "%c", _tab_arbre[k]->nombre_bits);
        _nb_oct_entete++;
    
    }
}

/* Encodage*/
void encodage(FILE *f_source, FILE *f_cible)
{
    unsigned int code_binaire_symbole, nombre_bits_symbole, nombre_bits_unsigned_int;
    unsigned char octet, octet_a_ecrire;
    int resultat_lecture;
    int nombre_bits_tampon = 0;
    unsigned int tampon = 0;

    nombre_bits_unsigned_int = sizeof(unsigned int) * 8;

    while ((resultat_lecture = fscanf(f_source, "%c", &octet)) != EOF)
    {
        /* récupération des codes et nb_bits du dictionnaire */
        code_binaire_symbole = _dictionnaire[octet].code_binaire;
        nombre_bits_symbole = _dictionnaire[octet].nombre_bits;

        /* on cherche a positionner le code binaire en fin de tampon */
        /* pour cela on commence par deplacer les valeurs binaires a gauche */
        code_binaire_symbole = (code_binaire_symbole << (nombre_bits_unsigned_int - nombre_bits_symbole));

        /* puis on deplace les valeurs binaires a droite de nombre_bits_tampon */
        code_binaire_symbole = (code_binaire_symbole >> nombre_bits_tampon);

        /* OR inclusif */
        tampon = tampon | code_binaire_symbole;
        nombre_bits_tampon = nombre_bits_tampon + nombre_bits_symbole;

        while ((nombre_bits_tampon / 8) > 0)
        {
            /* si le tampon contient plusieurs octets, on ecrit un octet dans le fichier */
            octet_a_ecrire = (tampon >> (nombre_bits_unsigned_int - 8));
            fprintf(f_cible, "%c", octet_a_ecrire);
            _nb_oct_donnees++;

            /* puis on retire l'octet du tampon et on met a jour nombre_bits_tampon */
            tampon = tampon << 8;
            nombre_bits_tampon = nombre_bits_tampon - 8;
        }
    }

    /* si le tampon contient encore des bits significatif, il faut les ecrire */
    if (nombre_bits_tampon != 0)
    {
        octet_a_ecrire = (tampon >> (nombre_bits_unsigned_int - 8));
        fprintf(f_cible, "%c", octet_a_ecrire);
        _nb_oct_donnees++;
        tampon = tampon << nombre_bits_tampon;
        nombre_bits_tampon = 0;
        _nb_oct_fichier_a_decomp++;
    }
    _nb_oct_fichier_a_decomp = _nb_oct_entete + _nb_oct_donnees;
}

/* === DECOMPRESSION === */

/* Décompression du fichier source */
int decompression(char nom_fichier_source[])
{
    /* code_retour permet de s'assurer que la fonction a bien fonctionné */
    int code_retour = 0;
    /* Chaine de caractères du nom de fichier */
    char nom_fichier_cible[MAX_NOM];
    /* Fichier sourcer et fichier cible */
    FILE *f_source, *f_cible;

    /* on va generer le nom du fichier cible */
    strcpy(nom_fichier_cible, nom_fichier_source);
    strcat(nom_fichier_cible, ".decomp");

    /* si probleme lie a l'ouverture du fichier source, on associe a code_retour la valeur -1, signifiant qu'il y a eu un probleme (avec le fichier source). */
    f_source = fopen(nom_fichier_source, "r");
    if (f_source == NULL)
    {
        code_retour = SOURCE_INTROUVABLE;
    }
    /* si probleme lie a l'ouverture du fichier cible, on associe a code_retour la valeur -2, signifiant qu'il y a eu un probleme (avec le fichier cible). */
    f_cible = fopen(nom_fichier_cible, "w");
    if (f_cible == NULL)
    {
        code_retour = FICHIER_NON_GENERE;
    }

    /* s'il n'y a pas de problemes et que nos fichiers ne sont pas vide alors on peut lancer la procedure de decompression. */
    if (f_cible != NULL && f_source != NULL)
    {
        init_tab_occurrences();
        init_tableau_arbre(_tab_arbre);

        /* on calcule la taille du fichier à décompresser */
        _nb_oct_fichier_a_decomp = calcule_taille_fichier(f_source);

        /* lecture de l'en-tête du fichier et mise à jour de _tab_arbre */
        lire_entete(f_source);
        _nb_oct_donnees = _nb_oct_fichier_a_decomp - _nb_oct_entete;

        /* reconstruction de l'arbre binaire */
        construire_abr();

        /* décodage des données compressées */
        lire_encodage(f_source, f_cible);
    }
    fclose(f_source);
    fclose(f_cible);
    return code_retour;
}

/* calcul de la taille du fichier */
unsigned int calcule_taille_fichier(FILE *f_entree)
{
    unsigned int taille = 0;
    int retour;
    unsigned char octet;
    while (!feof(f_entree))
    {
        retour = fscanf(f_entree, "%c", &octet);
        if (retour != EOF)
        {
            taille++;
        }
    }
    rewind(f_entree);
    return taille;
}

/* Lecture entete  */
void lire_entete(FILE *f_entree)
{
    /* Variables char pour lecture avec fscanf pour les 3 premiers octets*/
    unsigned char nb_symboles, nb_oct_occur, nb_oct_code_binaire;
    /* Variables char pour la lecture avec fscanf de chaque symbole et ses informations */
    unsigned char symbole, nbbits, un_octet;

    unsigned int nb_octets_occ, nb_octets_code_binaire;
    unsigned int i, j, occurrence, code_binaire, nb_octets_entete = 0;
    unsigned int nb_bits, taille_fichier_source, taille_unsigned_int;
    Arbre_t *arbre;

    /* Lecture des 3 premiers octets  */
    /* Premier octet = nb de symboles à lire, valeurs possibl : 0 à 255 */
    /*                  (on ajoute 1 pour retrouver la valeur entre 1 et 256) */
    fscanf(f_entree, "%c", &nb_symboles);
    nb_octets_entete++;

    /* si sa valeur est 255 */
    /* nb_symboles passe a 0 et non a 256 */
    /* (nb_symboles => unsigned char) */
    _nb_symboles = nb_symboles + 1;

    /* Deuxième octet = nombre d'octets utilisés (nb_octets_occ) */
    /*                  pour lire la valeur occurence s'un symbole */
    fscanf(f_entree, "%c", &nb_oct_occur);
    nb_octets_entete++;
    nb_octets_occ = nb_oct_occur;

    /* Troisième octet = nombre d'octets utilisé pour lire le */
    /*                   le code binaire d'un symbole */
    fscanf(f_entree, "%c", &nb_oct_code_binaire);
    nb_octets_entete++;
    nb_octets_code_binaire = nb_oct_code_binaire;

    /* lecture des 4 octets suivants */
    taille_fichier_source = 0;
    taille_unsigned_int = sizeof(unsigned int);
    for (i = 0; i < taille_unsigned_int; i++)
    {
        fscanf(f_entree, "%c", &un_octet);
        nb_octets_entete++;
        taille_fichier_source = (taille_fichier_source << 8) + un_octet;
    }
    _nb_oct_fichier_a_compress = taille_fichier_source;

    /* Lecture des symboles et de leur information */
    /* commentaires */
    for (j = 0; j < _nb_symboles; j++)
    {
        /* lecture du symbole sur un octet */
        fscanf(f_entree, "%c", &symbole);
        nb_octets_entete++;
        /* lecture du nombre d'occurences sur nb_octets_occ octets */
        occurrence = 0;
        for (i = 0; i < nb_octets_occ; i++)
        {
            fscanf(f_entree, "%c", &un_octet);
            nb_octets_entete++;
            occurrence = (occurrence << 8) + un_octet;
        }
        /* lecture du code binaire sur nb_octets_code_binaire octets */
        code_binaire = 0;
        for (i = 0; i < nb_octets_code_binaire; i++)
        {
            fscanf(f_entree, "%c", &un_octet);
            nb_octets_entete++;
            code_binaire = (code_binaire << 8) + un_octet;
        }

        /* -- lecture du nombre de bits sur un octet -- */
        fscanf(f_entree, "%c", &nbbits);
        nb_octets_entete++;
        nb_bits = nbbits;
        /* on met à jour le tableau des occurrences */
        _tab_occurrences[symbole] = occurrence;
        /* on range les informations des _tab_arbres */
        arbre = (Arbre_t *)malloc(sizeof(Arbre_t));
        arbre->g = NULL;
        arbre->d = NULL;
        arbre->symbole = symbole;
        arbre->code_binaire = code_binaire;
        arbre->nombre_bits = nb_bits;
        arbre->occurrence = occurrence;
        _tab_arbre[j] = arbre;
    }
    _nb_oct_entete = nb_octets_entete;
}

void lire_encodage(FILE *f_source, FILE *f_cible)
{
    unsigned char octet;
    int retour_lecture = 0;
    unsigned int tampon = 0, temp = 0, nb_bits_unsigned_int;
    unsigned int nb_bits_tampon = 0, val_bit, masque = 1;
    unsigned int nb_octet_a_lire, nb_octet_a_ecrire;
    Arbre_t *noeud_courant;

    nb_bits_unsigned_int = sizeof(unsigned int) * 8;
    masque = masque << (nb_bits_unsigned_int - 1);
    nb_octet_a_lire = _nb_oct_donnees;
    nb_octet_a_ecrire = _nb_oct_fichier_a_compress;

    while (nb_octet_a_ecrire > 0)
    {
        /* on remplit le tampon, si on peut lui ajouter un octet */
        while ((nb_bits_tampon < (nb_bits_unsigned_int - 16)) && (nb_octet_a_lire > 0))
        {
            octet = 0;
            retour_lecture = fscanf(f_source, "%c", &octet);

            if (retour_lecture != EOF)
            {
                nb_octet_a_lire--;
                temp = octet;
                temp = (temp << (nb_bits_unsigned_int - (nb_bits_tampon + 8)));
                tampon = tampon | temp;
                nb_bits_tampon += 8;
            }
        }
        noeud_courant = _racine;
        while ((nb_octet_a_ecrire > 0) && (!((noeud_courant->g == NULL) && (noeud_courant->d == NULL))))
        {
            val_bit = tampon & masque;
            val_bit = val_bit >> (nb_bits_unsigned_int - 1);
            tampon = tampon << 1;
            nb_bits_tampon--;

            if (val_bit == 0)
            {
                noeud_courant = noeud_courant->g;
            }

            else
            {
                noeud_courant = noeud_courant->d;
            }
        }
        fprintf(f_cible, "%c", noeud_courant->symbole);
        nb_octet_a_ecrire--;
    }
}

/* Afficher les paramètres de compilation */
void affiche_synthaxe(char commande[])
{
    printf("Compression : %s -c fichier \n", commande);
    printf("Decompression : %s -d fichier \n", commande);
}