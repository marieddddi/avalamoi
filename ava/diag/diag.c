#include <ctype.h>
#include <stdio.h>
#include "../include/avalam.h"
#include <stdlib.h>
#include <string.h>


int main(int argc,char **argv)
{
	//Verification du nmobre d'arguments
	if(argc!=3)
	{
		fprintf(stderr,"Pas le bon nombre d'arguments");
		return 0;
	}
	//Initialisation de la varriable fenlen contenant la longueur du fen
	int fenlen=strlen(argv[2])-1;
	//Verification de la longueur du fen : 4 bonus, 48 cases, un espace et le trait
	if (fenlen>54 || fenlen<0) 
	{
		fprintf(stderr,"Fen trop long (ou a longueur negative même si ça parrait complexe...)");
		return 0;
	}

	int trait;
	// Attribution du trait. Si il n'est pas correct, alors arret du programme.
	if (argv[2][fenlen]=='j' || argv[2][fenlen]=='J') trait=1;
	else
	{
		if(argv[2][fenlen]=='r' || argv[2][fenlen]=='R') trait =2;
		else 
		{
			fprintf(stderr,"Erreur de fen : trait incorect");
			return 0;
		}
	}
	
char nomFichier[80],chemin[92]="../web/data/";
	//Saisie du nom du fichier, il ne peut dépasser les 80 caracteres.
	printf("Entrez le nom du fichier :");
	fgets(nomFichier, 80, stdin);
	
	int i;
	//Nettoyage du nom du fichier : on enlève le \n et le $ qui se glissait parfois
	for(i=0;nomFichier[i]!='$' && nomFichier[i]!='\n' ;i++);
	nomFichier[i]='\0';
	
	//Nom par defaut
	if ((strlen(nomFichier) == 0)) strcpy(nomFichier, "diag.js");
	//Ajout de l'extension .js au nom choisi
	else strcat(nomFichier,".js");
	strcat(chemin,nomFichier);
	
	//Ouverture du fichier
	FILE *fichier = NULL;
	//Si l'ouverture est impossible, arret du programme
	if ((fichier = fopen(chemin, "w+")) == NULL)
    {
        fprintf(stderr,"\n\nImpossible d'ouvrir le fichier\n\n");
        return(0);
    }
	fichier = fopen(chemin, "w+");
	//Ajout des caracteristiques connues au fichier
	fprintf(fichier,"traiterJson({\n");
	fprintf(fichier,"\"trait\":%d,\n",trait);
	fprintf(fichier,"\"numDiag\":%s,\n",argv[1]);
	fprintf(fichier,"\"notes\":[\n"); //Les differentes lignes sont stockées dans un tableau

	//Ajout de la note, nombre de lignes infini, mais 1000 caracteres par ligne car c'est suffisant
	char ligne[1000];
	printf("Entrez votre note.\nPour arreter d'écrire, entrez une ligne vide.\n");
	do
	{
		strcpy(ligne,"");			//Utile pour l'entrée par redirection de fichier, evite un 'echo' pour la deniere ligne
		fgets(ligne, 1000, stdin);  
		if (strcmp(ligne,"\n")!=0)	//On ajoute la ligne uniquement si elle est interessante, donc non vide.
		{
			ligne[strlen(ligne)-1]='\0';
			fprintf(fichier,"	\"%s\",\n",ligne);
			
		}
	}while (strcmp(ligne,"\n")!=0 && strlen(ligne)>=1); // On arrete lorsque la ligne est "vide" ou vide.
	fprintf(fichier,"	\"\"\n],\n");//Fin du tableau, ajout d'une derniere ligne vide pour finir sans virgule (Eviter "texte",])
	fprintf(fichier,"\"fen\":\"%s\",\n",argv[2]);//Ajout du FEN
	
	//Ajout des quatres bonus
	for(i=0;i<=fenlen;i=i+1)
	{
		switch(argv[2][i])
		{
			case 'b': fprintf(fichier,"%s:\"%d\",\n",STR_BONUS_J,i-1);
					  break;
		
			case 'm': fprintf(fichier,"%s:\"%d\",\n",STR_MALUS_J,i-1);
					  break;
		
			case 'B': fprintf(fichier,"%s:\"%d\",\n",STR_BONUS_R,i-1);
					  break;

			case 'M': fprintf(fichier,"%s:\"%d\",\n",STR_MALUS_R,i-1);
					  break;
		}
	}

	//Ajout des pions
	fprintf(fichier,"\"cols\":[\n");
	int espace,k,compteur=0,ajout; 
	//espace represente le nombre de cases vides a ajouter au cas ou le programme rencontre un nombre.
	//compteur represente le nombre de cases ajoutées. Il ne doit pas depasser 48, sinon on arrete l'ajout de pions.
	for(i=0;i<=fenlen;i=i+1)
	{
		ajout=1;
		switch(argv[2][i])
		{
			//Pour chaque lettre ayant un sens, on ajoute son equivalent. Les caracteres n'ayant rien a faire ici seront passés.
			case 'u': fprintf(fichier,"	{\"nb\":1, \"couleur\":1}");
					  compteur++;
					  break;
					  
			case 'd': fprintf(fichier,"	{\"nb\":2, \"couleur\":1}");
					  compteur++;
					  break;
					  
			case 't': fprintf(fichier,"	{\"nb\":3, \"couleur\":1}");
					  compteur++;
					  break;
					  
			case 'q': fprintf(fichier,"	{\"nb\":4, \"couleur\":1}");
					  compteur++;
					  break;
					  
			case 'c': fprintf(fichier,"	{\"nb\":5, \"couleur\":1}");
					  compteur++;
					  break;
					  
			case 'U': fprintf(fichier,"	{\"nb\":1, \"couleur\":1}");
					  compteur++;
					  break;
					  
			case 'D': fprintf(fichier,"	{\"nb\":2, \"couleur\":1}");
					  compteur++;
					  break;
					  
			case 'T': fprintf(fichier,"	{\"nb\":3, \"couleur\":1}");
					  compteur++;
					  break;
					  
			case 'Q': fprintf(fichier,"	{\"nb\":4, \"couleur\":1}");
					  compteur++;
					  break;
					  
			case 'C': fprintf(fichier,"	{\"nb\":5, \"couleur\":1}");
					  compteur++;
					  break;

			//Si le programme ne rencontre aucun des cas precedent, on verrifie si c'est un chiffre ou un nombre.
			default: if(isdigit(argv[2][i]) && isdigit(argv[2][i+1]))//Si c'est un nombre (Deux chiffres cote a cote)
					 { //On ajoute autant de cases vides qu'il le faut, en s'arretant si l'on atteint la limite.
						 espace=10*(argv[2][i]-'0')+(argv[2][i+1]-'0');
						 for(i=0;k<espace;k=k+1)
						 {
							 fprintf(fichier,"	{\"nb\":0, \"couleur\":0}");
							 compteur++;
							 if(compteur==NBCASES)
							 {
								fprintf(fichier,"\n]\n});\n");
								return 1;
							 }
							 fprintf(fichier,",\n");
						 }
						 i=i+1;
					 }
					 else
					 {
						 if(isdigit(argv[2][i]))
						 { //Pareil que pour les nombres
							 espace=argv[2][i]-'0';
							 for(k=0;k<espace;k=k+1)
							 {
								 fprintf(fichier,"	{\"nb\":0, \"couleur\":0}");
								 compteur++;
								 if(compteur==NBCASES){
									fprintf(fichier,"\n]\n});\n");
									return 1;
									}
							 }
						 }
						 else ajout=0;
					 }
		}

		// Si on a ajouté quelquechose
		if(ajout){
			//Si on vient d'ajouter le dernier pion, alors on ne met pas de virgule et on finit le programme
			if (i!=fenlen)
			{
				fprintf(fichier,",\n");
			}
			else
			{
				fprintf(fichier,"]\n});\n");
				return 1;
			}

			//Si on a atteint la quantité maximale de pions, on finit le programme.
			if(compteur==NBCASES){
				fprintf(fichier,"\n]\n});\n");
				return 1;
			}
		}
	}
	fprintf(fichier,"]\n});\n");
	return 1;
}
