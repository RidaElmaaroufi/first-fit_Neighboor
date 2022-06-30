#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define taille 8

typedef char sol[taille+1];
int decod(sol s){
	int value = 0;
	int i;
	for(i=0;i<taille;i++){
		value = value*2 + (s[i]-'0');
	}
	return value;
}

int f(int x){
	return x*x*x-60*x*x+900*x+100;
}
sol so="";
void getRandomSolution(){
	int i;
	int b;
	for(i=0;i<taille;i++){
		srand ( time(NULL) );
		b = rand()%RAND_MAX;
		if((b%10)>5){
			so[i] = '1';	
		}
		else{
			so[i] = '0';
		}
	}
}

void local_Search(int MAX_ITR){
	sol s_best="",s_cur="",s_temp="";
	//sol V[8];
	int f_best,f_cur;
	int num_itr = 1;
	strcpy(s_best,so);
	while(num_itr<MAX_ITR){
		strcpy(s_cur,s_best);
		f_best = f(decod(s_cur));
		int i;
		for(i=0;i<taille-1;i++){
			strcpy(s_temp,s_cur);//on va utiliser une solution temporaire(s_temp)
			// pour garder les s_cur le meme pour bien recuperer ses 8 voisins
			char temp = s_temp[i];
			s_temp[i] = s_temp[i+1];
			s_temp[i+1] = temp; 	
			if(f(decod(s_temp))<f_best){
				strcpy(s_best,s_temp);
				f_best = f(decod(s_best));
			}	
		}
		num_itr++;
	}
	//affichage de chaque iteration dans un fichier
	FILE* fichier = NULL;
	fichier = fopen("fichier.txt","a+");
	if(fichier!=NULL){
        fprintf(fichier,"Pour %d iterations on a :\n",MAX_ITR);
		fprintf(fichier,"la meilleur solution local est : %d\n",decod(s_best));
		fprintf(fichier,"qui correspond a f(%d) = %d\n\n",decod(s_best),f_best);
	fclose(fichier);
	}
	else{
		printf("impossible d\'ouvrir le fichier");
	}

}
int main(int argc, char *argv[]) {
	int i ;
	
	getRandomSolution();
	for(i=0;i<taille;i++){
		printf("%c",so[i]);
	}
	
	int j=10;
	
	while(j<1001){
		local_Search(j);
		j+=10;
	}
	printf("\n\nOk");
	
	return 0;
}

