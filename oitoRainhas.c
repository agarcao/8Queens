#include <stdio.h>      
#include <stdlib.h> 

/* CONSTANTES */
#define MAX_ITER 10000
#define N_RAINHAS 8

/* VAR GLOBAIS */
int rainhas[N_RAINHAS] = {-1};   


/* FUNÇOES */
int veConflCol(int col) {	// calcula número de conflitos da rainha na coluna i
	int conflitos = 0;
	int x=0; // coluna teste
	int linhaTst=0, linha=0;
	int conflitosTst=0;
	
	for(linhaTst=0; linhaTst < N_RAINHAS; linhaTst++){
		for (x=0; x < N_RAINHAS; x++){	// coluna
			if (x != col){		// não compara coluna com ela própria
				if (linhaTst == rainhas[x] || abs(x-col) == abs(linhaTst-rainhas[x])) {
					conflitosTst++;
				}
			}
		}
		if(!linhaTst){
			linha = linhaTst;
			conflitos = conflitosTst;
		}
		else{
			if(conflitosTst < conflitos){
				linha = linhaTst;
				conflitos = conflitosTst;
			}
		}
		conflitosTst=0;	// reset do contador de conflitos
	}	
	return linha;
}

int haConflitos(){
	int i, j, conflitos=0;
	
	for (i=0; i < N_RAINHAS; i++){	// ve os conflitos entre as rainhas no tabuleiro
			for (j=i+1; j < N_RAINHAS; j++){
				if (rainhas[i] == rainhas[j] || abs(j-i) == abs(rainhas[i]-rainhas[j])){
					conflitos++;
				}				
			}
	}
	return conflitos;
}

int main(){
	int i, j, var, value, count=0;
	
	for(i=0; i<N_RAINHAS; i++){			/* põe uma rainha em cada coluna */
		rainhas[i]=(int)(lrand48()) % N_RAINHAS;
	} 
	
	for(i=0; i<MAX_ITER; i++){
		if(haConflitos()){
			var = (int)(lrand48()) % N_RAINHAS;	// escolhemos uma variavel aleatoriamente
			value = veConflCol(var); // retorna o valor que minimaliza os conflitos (var=coluna)
			rainhas[var]=value;		
		}
		else{
			/* Apresenta tabuleiro */
			printf("TABULEIRO FINAL\n");
			for(i=0; i<N_RAINHAS; i++){	// linha
				for(j=0; j<N_RAINHAS; j++){
					if(rainhas[j]==i)
						printf("|Q|");
					else
						printf("| |");
				}
				printf("\n");
			}
			return 0; 
		}
		if(count > 100){	// por vezes pode-se chegar a uma situação de maximo local
			for(i=0; i<N_RAINHAS; i++){			/* põe uma rainha em cada coluna */
				rainhas[i]=(int)(lrand48()) % N_RAINHAS;
			} 
			count=0;
		}
		count++;			
	}	
	return 0;
}
