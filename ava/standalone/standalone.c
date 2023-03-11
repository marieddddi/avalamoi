#include <stdio.h>
#include <stdlib.h>
#include <avalam.h>
#include <topologie.h>
#include <string.h>

//prototypes
void ecritureJS(T_Position pos, T_Score score, char chaine_JS[]);
void menu() ;
void separateur(const char *chaine, char *partie);
	
	
int main(int argc, char *argv[]) {
	//déclaration des variables
    int i;
    T_Position pos;
	T_ListeCoups l; 
	T_Coup deplacement;
	T_Score score;
	int chgt=0;
    char chaine_JS[100] ;
    char nom_JS[100];
    char chemin[100]="./web/exemples/";

	//choix du fichier js
	printf0("choix du fichier js\n");
    printf0("----------------------------------------------------------------------------------------\n");
    printf1("Le programme a été appelé avec %d arguments:\n", argc) ;
    if(argc==2) {
		separateur(argv[1], nom_JS);
		if(strcmp(nom_JS,argv[1])==0) strcpy(chaine_JS, strcat(chemin, argv[1]));
		else strcpy(chaine_JS, strcat(chemin, nom_JS));
    }

    if(argc==1)
    { 
		strcpy(chaine_JS, "./web/exemples/refresh-data.js"); 
		printf("---> utilisation par dafaut de avalam-refresh ! <--- \n");
	}
    if(argc!=2 && argc!=1) 
    {
		printf("---> Nom de fichier avec espace, veuillez relancer le jeu !!! <--- \n"); 
		return 0;
	}
	printf("\n\n");

	//affichage du menu
    printf0("affichage du menu: \n");
    printf0("----------------------------------------------------------------------------------------\n");
    menu() ;
    
    
	//init
	//Création de la position initiale 
	printf0("création de la position initiale\n");
    printf0("----------------------------------------------------------------------------------------\n");
	pos = getPositionInitiale();
	
	//Récupération des coups légaux de la position initiale 
	printf0("Récuperation des coups légaux: \n");
    printf0("----------------------------------------------------------------------------------------\n");
 	l=getCoupsLegaux(pos);
	printf("\t Depuis la position initiale du jeu, il y a %d coups possibles \n", l.nb);
	printf("\t Depuis la position initiale du jeu, le trait est aux %ss \n", COLNAME(pos.trait));
	
	//Ecriture initiale dans le fichier JS 
	printf0("Ecriture initiale dans le fichier JS\n");
    printf0("----------------------------------------------------------------------------------------\n");
	ecritureJS(pos,score,chaine_JS);
	printf("\n");
	printf("----------------------------------------------------------------------------------------------------");
	printf("\n\n");
   
   
	//placement des bonus et malus
    printf0("Placement des bonus et malus: \n");
    printf0("----------------------------------------------------------------------------------------\n");
	do{
		chgt=0;
		printf("\033[33;01m \t\t Veuillez choisir la position du **bonus** jaune \033[00m \n");
		scanf("%hhd", &pos.evolution.bonusJ);
		getchar();
		printf1("bonus jaune demandé: %hhd \n",pos.evolution.bonusJ);
		printf("\n\n");
		if(pos.cols[pos.evolution.bonusJ].couleur==JAU) chgt=1;
		if (pos.evolution.bonusJ<0 ||pos.evolution.bonusJ>47) chgt=0;
		if(chgt==0)printf("----Vous ne pouvez pas mettre ce bonus ici ----\n");
		printf("\n");
	}while((chgt==0));
	printf0("Valeur demandée du bonus jaune ok \n");
    printf0("----------------------------------------------------------------------------------------\n");
	//ajout du bonus jaune dans le JS
	ecritureJS(pos,score,chaine_JS);
	
	do{
		chgt=0;
		printf("\033[31;01m \t\t Veuillez choisir la position du **bonus** rouge\033[00m \n");
		scanf("%hhd", &pos.evolution.bonusR);
		getchar();
		printf1("bonus rouge demandé: %hhd \n",pos.evolution.bonusR);
		printf("\n\n");
		if(pos.cols[pos.evolution.bonusR].couleur==ROU) chgt=1;
		if (pos.evolution.bonusR<0 ||pos.evolution.bonusR>47) chgt=0;
		if(chgt==0)printf("----Vous ne pouvez pas mettre ce bonus ici ----\n");
		printf("\n");
	}while((chgt==0));
	printf0("Valeur demandée du bonus rouge ok \n");
    printf0("----------------------------------------------------------------------------------------\n");
	//ajout du bonus jaune dans le JS
	ecritureJS(pos,score,chaine_JS);
	
	do{
		chgt=0;
		printf("\033[33;01m \t\t Veuillez choisir la position du **malus** jaune \033[00m \n");
		scanf("%hhd", &pos.evolution.malusJ);
		getchar();
		printf1("malus jaune demandé: %hhd \n",pos.evolution.malusJ);
		printf("\n\n");
		if(pos.cols[pos.evolution.malusJ].couleur==JAU) chgt=1;
		if (pos.evolution.malusJ<0 ||pos.evolution.malusJ>47) chgt=0;
		if(pos.evolution.malusJ==pos.evolution.bonusJ) chgt=0;
		if(chgt==0)printf("----Vous ne pouvez pas mettre ce malus ici ----\n");
		printf("\n");
	}while((chgt==0));
	printf0("Valeur demandée du malus jaune ok \n");
    printf0("----------------------------------------------------------------------------------------\n");
	//ajout du bonus jaune dans le JS
	ecritureJS(pos,score,chaine_JS);
	
	do{ 
		chgt=0;
		printf("\033[31;01m \t\t Veuillez choisir la position du **malus** rouge\033[00m \n\n");
		scanf("%hhd", &pos.evolution.malusR);
		getchar();
		printf1("malus rouge demandé: %hhd \n",pos.evolution.malusR);
		printf("\n\n");
		if(pos.cols[pos.evolution.malusR].couleur==ROU) chgt=1;
		if (pos.evolution.malusR<0 ||pos.evolution.malusR>47) chgt=0;
		if(pos.evolution.malusR==pos.evolution.bonusR) chgt=0;
		if(chgt==0)printf("----Vous ne pouvez pas mettre ce malus ici ----\n");
		printf("\n");
	}while((chgt==0));
	printf0("Valeur demandée du malus rouge ok \n");
    printf0("----------------------------------------------------------------------------------------\n");
	//ajout du bonus jaune dans le JS
	ecritureJS(pos,score,chaine_JS);
	printf4("Voici la position du bonus rouge: %hhd, du bonus jaune: %hhd, du malus rouge: %hhd, et du malus jaune: %hhd \n",pos.evolution.bonusR,pos.evolution.bonusJ,pos.evolution.malusR,pos.evolution.malusJ);
	printf("----------------------------------------------------------------------------------------------------");
	printf("\n\n");
	
	printf0("Début du jeu \n");
    printf0("----------------------------------------------------------------------------------------\n");
	//jouer
	while(l.nb!=0)
	{
		printf("Il y a %d coups possibles \n", l.nb);
		printf("Le trait est aux %ss\n", COLNAME(pos.trait));
		printf("Veuillez indiquer la position d'origine: \n");
		scanf("%d",&deplacement.origine) ; 
		getchar();
		printf1("Position d'origine demandée: %d \n",deplacement.origine);
		printf("Veuillez indiquer la destination du coup: \n");
		scanf("%d", &deplacement.destination );
		getchar();
		printf1("Destination demandée: %d \n",deplacement.destination);
        printf0("jeu du coup, verification de la validité du coup et evaluation du score \n");
        printf0("----------------------------------------------------------------------------------------\n");
		pos=jouerCoup(pos, deplacement.origine, deplacement.destination) ;
		l=getCoupsLegaux(pos);
		score=evaluerScore(pos);
		printf("\n");
		printf("----------------------------------------------------------------------------------------------------");
		printf("\n\n");
		
		//partie écriture du js	
		printf0("Ecriture dans le fichier JS\n");
        printf0("----------------------------------------------------------------------------------------\n");											
		ecritureJS(pos,score,chaine_JS);
	}
	
	//affichage du score
	printf0("Affichage du score: \n");
    printf0("----------------------------------------------------------------------------------------\n");
    printf2("score du joueur rouge: %hhd, score du joueur jaune: %hhd \n",score.nbR,score.nbJ);
    printf2("nombre de tours du joueur rouge: %hhd, nombre de tours du joueur jaune: %hhd \n",score.nbR5,score.nbJ5);
    printf0("----------------------------------------------------------------------------------------\n");
	if(score.nbJ = score.nbR) 
	{
		if(score.nbJ5 > score.nbR5) printf("\033[33;01m \t\t C'est le joueur jaune qui a gagné \033[00m \n");
		if (score.nbJ5 < score.nbR5) printf("\033[31;01m \t\t C'est le joueur rouge qui a gagné \033[00m \n");
		else printf("vous etes à égalité");
	}
	else 
	{
		if(score.nbJ > score.nbR) printf("\033[33;01m \t\t C'est le joueur jaune qui a gagné \033[00m \n");
		else printf("\033[31;01m \t\t C'est le joueur rouge qui a gagné \033[00m \n");
	}
	printf(" ---> Voici le score <--- \n");
	afficherScore(score);
	return 0;
}



//fonctions

/*******************************************************************/
/* Nom: ecritureJS                                                 */
/* Description: permet d'écrire le trait, les scores, la position  */
/* des malus et bonus, et la position de chaque pion à chaque tour.*/
/* Cela permet à avalm-refresh d'etre actualisé à chaque partie    */
/* afin de pouvoir jouer.                                          */
/*******************************************************************/
void ecritureJS(T_Position pos, T_Score score, char chaine_JS[])
{
	FILE *fichier ; 
    fichier = fopen(chaine_JS, "w");
	fprintf(fichier,"traiterJson({\n");
	fprintf(fichier,"%s:%d,\n",STR_TURN,pos.trait);
	fprintf(fichier,"%s:%d,\n",STR_SCORE_J, score.nbJ);
	fprintf(fichier,"%s:%d,\n",STR_SCORE_J5, score.nbJ5);
	fprintf(fichier,"%s:%d,\n",STR_SCORE_R, score.nbR);
	fprintf(fichier,"%s:%d,\n",STR_SCORE_R5, score.nbR5);
	fprintf(fichier,"%s:%hhd,\n",STR_BONUS_J, pos.evolution.bonusJ);
	fprintf(fichier,"%s:%hhd,\n",STR_MALUS_J, pos.evolution.malusJ);
	fprintf(fichier,"%s:%hhd,\n",STR_BONUS_R, pos.evolution.bonusR);
	fprintf(fichier,"%s:%hhd,\n",STR_MALUS_R, pos.evolution.malusR);
	fprintf(fichier,"\"cols\": [\n");
	for (int i=0 ; i<NBCASES ; i++)fprintf(fichier, "\t {%s:%hhd, %s:%hhd},\n",STR_NB,pos.cols[i].nb, STR_COULEUR,pos.cols[i].couleur) ;
	fprintf(fichier,"]\n");
	fprintf(fichier,"});");
	fclose(fichier) ; 
}

 

/******************************************************************/
/* Nom: menu                                                      */
/* Description: menu permettant au joueur d'afficher les règles,  */
/* des astuces et de jouer au jeu.                                */
/******************************************************************/
void menu(){
    int choice;
	do 
	{   
        printf("\033[1;36m");  // mettre couleur
        printf("=== MENU ===\n");
        printf("\033[0m");   
        printf("1. Description\n");
        printf("2. Afficher les règles\n");
        printf("3. Afficher les astuces\n");
        printf("4. Jouer au jeu\n");
        printf("Entrez votre choix : ");
        scanf("%d", &choice);
        getchar();

        switch (choice) 
        {
            case 1:
                printf("\033[1;34m"); 
                printf("Description : \n\n");
                printf("Jeu abstrait pour deux, Avalam a remporté de nombreuses récompenses.\nA la fois rapide et stratégique, Avalam est un jeu de réflexion qui séduit autant par sa mécanique et ses règles simples que par son matériel original et de qualité.\n\n");
                printf("\033[0m");   
                break;
                
            case 2:
                printf("\033[1;32m"); 
                printf("Voici les règles du jeu : \n\n");
                printf("Le principe du jeu est simple : au début de la partie, les joueurs choisissent une couleur de pions. Cependant, chaque joueur à le droit de jouer avec les pions de son adversaire !\n");
                printf("À leur tour, ils déplacent tous les pions placés sur une case vers une case voisine occupée. Les pions s'empilent, formant des tours de 1 à 5 pions.\n");
                printf("Le joueur qui parvient à placer le plus de pions de sa couleur au sommet des piles de pions constituées au cours de la partie l emporte.\n");
                printf("A savoir qu'une pile ne peut dépasser cinq pions, et qu'un pion ne se déplace jamais sur un emplacement vide... Les tours ont donc des hauteurs variables, au gré de la stratégie.\n");
                printf("Dans cette septième édition « Evolution », une variante a été ajoutée : chaque joueur dispose de 2 pions bonus et malus qui augmentent ou diminuent la valeur de la tour.");
                printf(" Ces 2 x 2 pions sont placés sur le plateau en début de partie.\n\n");
                printf("\033[0m");
                break ; 
                  
            case 3:
                printf("\033[1;33m");
                printf("Voici quelques astuces pour le jeu :\n\n");
                printf("-Essayez d'isoler les tours des que possible sans chercher les piles de 5 forcements, ainsi commencer par isoler les pions au bord qui sont plus simple.\n");
                printf("-Mettre les bonus dans le coin pour pouvoir a son tour l'isoler et marquer plus de point.s\n");
                printf("-Pensez que les tours de 3 qui vous appartiennent sont très utiles car soit elle reste a vous tout le long ou alors si l'adversaire décide de mettre un pion dessu, vous pouvez en rajouter un de votre couleurs juste après pour former une tour de 5 .\n");
                printf("-malus au milieu si l'adversaire joue les jaunes.\n");
                printf("-mettre les pions adverse sur les malus.\n");
                printf("\033[0m");   
                break;
                
            case 4:
                printf("\033[1;34m"); 
                printf("Lancement du jeu...\n\n");
                printf("\033[0m");   
                break;
                
            default:
                printf("\033[1;31m"); 
                printf("Choix invalide. Veuillez réessayer.\n\n");
                printf("\033[0m");   
                break;
        }
    } 
    while (choice != 4);
}


/****************************************************************/
/* Nom: separateur 	                         				    */
/* Description: sert à separer la chaine de caractère "chaine"  */
/* au dernier / . Ainsi le dernier mot qui est le nom du fichier*/
/* js est récupéré dans "partie".								*/
/****************************************************************/
void separateur(const char *chaine, char *partie) 
{
    const char *dernier_slash = strrchr(chaine, '/');
    if (dernier_slash == NULL) {
        // Aucun slash trouvé, renvoie la chaine de base qui est donc un nom de js
        strcpy(partie,chaine);
    } 
    else {
        // Copie la partie de la chaîne après le dernier slash
        strcpy(partie, dernier_slash + 1);
    }
}
