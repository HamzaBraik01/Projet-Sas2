#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
int choix;
typedef struct {
    char nom[50];
    char prenom[50];
    char telephone[15];
    int age;
    char statut[20]; 
    char reference[10]; 
    char date_reservation[11]; 
} Reservation;

Reservation reservations[100];
int total_reservations = 0;
int valider_nom_prenom(char str[]) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isalpha(str[i])) { 
            return 0;
        }
    }
    return 1;
}
int valider_telephone(char tel[]) {
    int len = strlen(tel);
    if (len != 10) return 0; 
    if (tel[0] != '0' || (tel[1] != '6' && tel[1] != '7' && tel[1] != '5' && tel[1] != '8')) return 0; 
    for (int i = 0; i < len; i++) {
        if (!isdigit(tel[i])) { 
            return 0;
        }
    }
    return 1;
}
int valider_age(int age) {
    return (age >= 0 && age <= 130);
}
int valider_date(char date[]) {
    if (strlen(date) != 10) return 0;
    if (date[4] != '-' || date[7] != '-') return 0;
    char annee_str[5], mois_str[3], jour_str[3];
    strncpy(annee_str, date, 4);
    annee_str[4] = '\0'; 
    strncpy(mois_str, date + 5, 2);
    mois_str[2] = '\0'; 
    strncpy(jour_str, date + 8, 2);
    jour_str[2] = '\0';  
    int annee = atoi(annee_str);
    int mois = atoi(mois_str);
    int jour = atoi(jour_str);
    if (annee < 2024) return 0;
    if (mois < 1 || mois > 12) return 0;
    if (jour < 1 || jour > 31) return 0;
    return 1;  
}
void initialiser_reservations() {
    Reservation initiales[] = {
        {"El Bakkali", "Mohamed", "0612345678", 30, "valide", "REF001", "2024-10-05"},
        {"Alaoui", "Fatima", "0623456789", 28, "reporte", "REF002", "2024-10-06"},
        {"Benjelloun", "Youssef", "0634567890", 35, "annule", "REF003", "2024-10-07"},
        {"Amrani", "Khadija", "0645678901", 22, "traite", "REF004", "2024-10-08"},
        {"Bennani", "Hicham", "0656789012", 40, "valide", "REF005", "2024-10-09"},
        {"Chakir", "Salma", "0667890123", 29, "reporte", "REF006", "2024-10-10"},
        {"Lahlou", "Imane", "0678901234", 33, "annule", "REF007", "2024-10-11"},
        {"Mansouri", "Omar", "0689012345", 27, "traite", "REF008", "2024-10-12"},
        {"Fassi", "Nadia", "0690123456", 26, "valide", "REF009", "2024-10-13"},
        {"Haddad", "Ali", "0701234567", 31, "reporte", "REF010", "2024-10-14"},
    };

    for (int i = 0; i < 10; i++) {
        reservations[i] = initiales[i];
    }
    total_reservations = 10; 
}
void ajouter_reservation() {
    if (total_reservations >= 100) {
        printf("Impossible d'ajouter une nouvelle reservation, la liste est pleine.\n");
        return;
    }

    Reservation r;
    
    do {
        printf("Entrez le nom : ");
        scanf("%s", r.nom);
        if (!valider_nom_prenom(r.nom)) {
            printf("Erreur : Le nom ne doit contenir que des lettres.\n");
        }
    } while (!valider_nom_prenom(r.nom));
    
    do {
        printf("Entrez le prenom : ");
        scanf("%s", r.prenom);
        if (!valider_nom_prenom(r.prenom)) {
            printf("Erreur : Le prenom ne doit contenir que des lettres.\n");
        }
    } while (!valider_nom_prenom(r.prenom));
    do {
        printf("Entrez le numero de telephone : ");
        scanf("%s", r.telephone);
        if (!valider_telephone(r.telephone)) {
            printf("Erreur : Le numero de telephone doit etre compose de 10 chiffres et commencer par 06, 07, 05 ou 08.\n");
        }
    } while (!valider_telephone(r.telephone));
   do {
        printf("Entrez l'age : ");
        scanf("%d", &r.age);
        if (!valider_age(r.age)) {
            printf("Erreur : L'age doit etre un nombre entre 0 et 130 ans.\n");
        }
    } while (!valider_age(r.age));
    printf("Choisissez le statut de la reservation :\n");
    printf("1. valide\n");
    printf("2. reporte\n");
    printf("3. annule\n");
    printf("4. traite\n");
    printf("Entrez votre choix (1-4) : ");
    int choix1;
    scanf("%d", &choix1);
    switch (choix1) {
        case 1:
            strcpy(r.statut, "valide");
            break;
        case 2:
            strcpy(r.statut, "reporte");
            break;
        case 3:
            strcpy(r.statut, "annule");
            break;
        case 4:
            strcpy(r.statut, "traite");
            break;
        default:
            printf("Choix invalide. Statut par defaut 'non specifie' attribue.\n");
            strcpy(r.statut, "non specifie");
    }

    do {
        printf("Entrez la date de reservation (AAAA-MM-JJ) : ");
        scanf("%s", r.date_reservation);
        if (!valider_date(r.date_reservation)) {
            printf("Erreur : La date doit etre au format AAAA-MM-JJ, avec une année >= 2024, un mois entre 1 et 12, et un jour entre 1 et 31.\n");
        }
    } while (!valider_date(r.date_reservation));

    sprintf(r.reference, "REF%03d", total_reservations + 1);
    reservations[total_reservations] = r;
    total_reservations++;

    printf("Reservation ajoutee avec succes. Reference : %s\n", r.reference);
}
void afficher_toutes_reservations() {
    if (total_reservations == 0) {
        printf("Aucune reservation à afficher.\n");
        return;
    }

    printf("\n=========================\n");
    printf("| Reservations Actuelles |\n");
    printf("=========================\n");
    printf("| Ref   | Nom         | Prenom     | Telephone    | Age | Statut   | Date         |\n");
    printf("==========================================================================\n");
    
    for (int i = 0; i < total_reservations; i++) {
        printf("| %-5s | %-10s | %-10s | %-12s | %-3d | %-8s | %-12s |\n", 
            reservations[i].reference, 
            reservations[i].nom, 
            reservations[i].prenom, 
            reservations[i].telephone, 
            reservations[i].age, 
            reservations[i].statut, 
            reservations[i].date_reservation);
    }
    printf("==========================================================================\n");
}
void modifier_reservation() {
    char ref[10];
    int trouve = 0;
    afficher_toutes_reservations();
    printf("Entrez la reference de la reservation à modifier : ");
    scanf("%s", ref);

    for (int i = 0; i < total_reservations; i++) {
        if (strcmp(reservations[i].reference, ref) == 0) {
            trouve = 1;
            printf("Reservation trouvee. Modifiez les informations :\n");
            printf("Entrez le nouveau nom : ");
            scanf("%s", reservations[i].nom);
            printf("Entrez le nouveau prenom : ");
            scanf("%s", reservations[i].prenom);
            printf("Entrez le nouveau numero de telephone : ");
            scanf("%s", reservations[i].telephone);
            printf("Entrez le nouvel age : ");
            scanf("%d", &reservations[i].age);
            printf("Entrez le nouveau statut : \n");
            printf("1. valide\n");
            printf("2. reporte\n");
            printf("3. annule\n");
            printf("4. traite\n");
            printf("Entrez votre choix (1-4) : ");
            int choix2;
            scanf("%d", &choix2);
            switch (choix2) {
                case 1:
                    strcpy(reservations[i].statut, "valide");
                    break;
                case 2:
                    strcpy(reservations[i].statut, "reporte");
                    break;
                case 3:
                    strcpy(reservations[i].statut, "annule");
                    break;
                case 4:
                    strcpy(reservations[i].statut, "traite");
                    break;
                default:
                    printf("Choix invalide. Statut par defaut 'non specifie' attribue.\n");
                    strcpy(reservations[i].statut, "non specifie");
            }
            printf("Entrez la nouvelle date de reservation (AAAA-MM-JJ) : ");
            scanf("%s", reservations[i].date_reservation);
            printf("La reservation a ete modifiee avec succes.\n");
            break;
        }
    }

    if (!trouve) {
        printf("Aucune reservation trouvee avec cette reference.\n");
    }
}
void supprimer_reservation() {
    char ref[10];
    int trouve = 0;

    afficher_toutes_reservations(); 
    printf("Entrez la reference de la reservation à supprimer : ");
    scanf("%s", ref);

    for (int i = 0; i < total_reservations; i++) {
        if (strcmp(reservations[i].reference, ref) == 0) {
            trouve = 1;
            for (int j = i; j < total_reservations - 1; j++) {
                reservations[j] = reservations[j + 1];
            }
            total_reservations--; 
            printf("La reservation avec la reference %s a ete supprimee avec succes.\n", ref);
            break;
        }
    }

    if (!trouve) {
        printf("Aucune reservation trouvee avec cette reference.\n");
    }
}
void rechercher_par_reference() {
    char ref[10];
    int trouve = 0;

    printf("Entrez la reference de la reservation à rechercher : ");
    scanf("%s", ref);

    for (int i = 0; i < total_reservations; i++) {
        if (strcmp(reservations[i].reference, ref) == 0) {
            printf("\nReservation trouvee :\n");
            printf("| Ref   | Nom         | Prenom     | Telephone    | Age | Statut   | Date         |\n");
            printf("==========================================================================\n");
            printf("| %-5s | %-10s | %-10s | %-12s | %-3d | %-8s | %-12s |\n", 
                reservations[i].reference, 
                reservations[i].nom, 
                reservations[i].prenom, 
                reservations[i].telephone, 
                reservations[i].age, 
                reservations[i].statut, 
                reservations[i].date_reservation);
            trouve = 1;
            break;
        }
    }

    if (!trouve) {
        printf("Aucune reservation trouvee avec cette reference.\n");
    }
}
void rechercher_par_nom() {
    char nom[50];
    int trouve = 0;

    printf("Entrez le nom de la reservation a rechercher : ");
    scanf("%s", nom);

    printf("\nResultats de la recherche pour le nom '%s' :\n", nom);
    printf("| Ref   | Nom         | Prenom     | Telephone    | Age | Statut   | Date         |\n");
    printf("==========================================================================\n");

    for (int i = 0; i < total_reservations; i++) {
        if (strcmp(reservations[i].nom, nom) == 0) {
            printf("| %-5s | %-10s | %-10s | %-12s | %-3d | %-8s | %-12s |\n", 
                reservations[i].reference, 
                reservations[i].nom, 
                reservations[i].prenom, 
                reservations[i].telephone, 
                reservations[i].age, 
                reservations[i].statut, 
                reservations[i].date_reservation);
            trouve = 1;
        }
    }

    if (!trouve) {
        printf("Aucune reservation trouvee avec ce nom.\n");
    }
}
void Tri_des_reservations(){
    int choix2,choixStatut;
    char statut[12];
     do{
    printf("1:Tri des reservations par Nom. \n");
    printf("2:Tri des reservations par statut. \n");
    printf("3:return aux Menu \n");
    scanf("%d",&choix2);
    if(choix2==1){
        for(int i=0;i<total_reservations; i++){
            for(int j=i+1;j<total_reservations; j++){
                if (strcasecmp(reservations[i].nom,reservations[j].nom)>0){
                    Reservation tmp;
                    tmp = reservations[i];
                    reservations[i]=reservations[j];
                    reservations[j]=tmp;
                }
                
            }
        }
        afficher_toutes_reservations();
    }
    else if(choix2 == 2) {
            for (int i = 0; i < total_reservations - 1; i++) {
        for (int j = i + 1; j < total_reservations; j++) {


            if(strcasecmp(reservations[i].statut,reservations[j].statut)>0){
                 Reservation tmp;
                tmp = reservations[i];
                reservations[i] = reservations[j];
                reservations[j] = tmp;
            }
    }}
        afficher_toutes_reservations();
    }else if(choix2==3){
        break;
    }else{
        printf("Enter un nombre soit 1 ou 2 ou 3 \n");
    }
    
    
     }while(1); 

}
void StatistiqueReservation(){
    int AgeEntier,Age18=0,Age36=0,Age19=0;
    int statutV=0,statutA=0,statutR=0,statutT=0;
    double Moyenne=0;
    for(int i=0;i<total_reservations;i++){
    
        Moyenne+=reservations[i].age;
    }
    Moyenne = Moyenne/total_reservations;
    for(int i=0;i<total_reservations;i++){
        AgeEntier = reservations[i].age;
        if(AgeEntier<=18){
            Age18++;
        }else if(AgeEntier>18 && AgeEntier<=35){
            Age19++;
        }else{
            Age36++;
        }
            }
            for(int i=0;i<total_reservations;i++){
                if(strcmp(reservations[i].statut,"valide")==0){
                    statutV++;
                }else if(strcmp(reservations[i].statut,"reporte")==0){
                    statutR++;
                }else if(strcmp(reservations[i].statut,"annule")==0){
                    statutA++;
                }else {
                    statutT++;
                }
            }

    printf("la moyenne dage des patients ayant reserve est :%.2lf \n\n",Moyenne);
    printf("le nombre de patients par tranche dage : \n 0-->18ans : %d \n 19-->35ans : %d \n +36ans : %d \n\n",Age18,Age19,Age36);
    printf("\n Valide : %d \n reporte : %d \n annule : %d \n traite : %d\n \n\n",statutV,statutR,statutA,statutT);
}



int main() {
    initialiser_reservations();
    do {
        printf("\nMenu principal :\n");
        printf("1. Ajouter une reservation\n");
        printf("2. Modifier une reservation\n");
        printf("3. Supprimer une reservation\n");
        printf("4. Afficher une reservation\n");
        printf("5. Tri des reservations\n");
        printf("6. Rechercher une reservation\n");
        printf("7. Statistiques\n");
        printf("8. Quitter\n");
        printf("Choisissez une option : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                ajouter_reservation();
                break;
            case 2:
                modifier_reservation();
                break;
            case 3:
                supprimer_reservation();
                break;
            case 4:
                afficher_toutes_reservations();
                break;
            case 5:
                Tri_des_reservations();
                break;
            case 6:{
               printf("\nRechercher une reservation :\n");
               printf("1. Par reference\n");
               printf("2. Par nom\n");
               printf("Choisissez une option : ");
               int choix_recherche;
               scanf("%d", &choix_recherche);
               switch (choix_recherche) {
                    case 1:
                        rechercher_par_reference();
                        break;
                    case 2:
                        rechercher_par_nom();
                        break;
                    default:
                        printf("Choix invalide.\n");
                }
                break;
            }
            case 7:
               StatistiqueReservation();
                break;
            case 8:
                printf("Au revoir !\n");
                break;
            default:
                printf("Choix invalide, veuillez reessayer.\n");
        }
    } while (choix != 8);

    return 0;
}