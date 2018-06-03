/*
	Alunos:
	Frederico Pinheiro Dib - 15/0125925
	Amanda Oliveira Alves - 15/0116276

	Para compilar e executar o codigo:
	gcc -ansi -Wall -o main main.c
	./main
*/
#include <stdio.h>
#include <stdlib.h>

/*Parser que le o arquivo dado e constro a matriz de professores e a matriz das escolas*/
void parser(int prof[100][7], int esc[50][3]) {
	FILE * fp;
	int number;
    int i;
    char c;
    fp = fopen("entradaProj3TAG.txt", "r");

  	   
  	for(i=0;i<100;i++) {

  		fscanf (fp, "%c", &c);
  		fscanf (fp, "%c", &c);
  		fscanf (fp, "%d", &number); 

    	fscanf (fp, "%c", &c);
  		fscanf (fp, "%c", &c);
  		fscanf (fp, "%d", &number); 
    	prof[i][0] = number;

    	fscanf (fp, "%c", &c);
    	fscanf (fp, "%c", &c);
    	fscanf (fp, "%c", &c);
    	fscanf (fp, "%c", &c);
  		fscanf (fp, "%c", &c);
  		fscanf (fp, "%d", &number); 
  		prof[i][1] = number;

    	fscanf (fp, "%c", &c);
    	fscanf (fp, "%c", &c);
  		fscanf (fp, "%c", &c);
  		fscanf (fp, "%d", &number); 
    	prof[i][2] = number;

    	fscanf (fp, "%c", &c);
    	fscanf (fp, "%c", &c);
  		fscanf (fp, "%c", &c);
  		fscanf (fp, "%d", &number); 
    	prof[i][3] = number;

    	fscanf (fp, "%c", &c);
    	fscanf (fp, "%c", &c);
  		fscanf (fp, "%c", &c);
  		fscanf (fp, "%d", &number); 
    	prof[i][4] = number;

    	fscanf (fp, "%c", &c);
    	fscanf (fp, "%c", &c);
  		fscanf (fp, "%c", &c);
  		fscanf (fp, "%d", &number); 
    	prof[i][5] = number; 
    	prof[i][6] = 0;

    	fscanf (fp, "%c", &c);
    	fscanf (fp, "%c", &c);     
    }

	fscanf (fp, "%c", &c);

    for(i=0;i<50;i++) {

  		fscanf (fp, "%c", &c);
  		fscanf (fp, "%c", &c);
  		fscanf (fp, "%d", &number); 

    	fscanf (fp, "%c", &c);
    	fscanf (fp, "%c", &c);
  		fscanf (fp, "%c", &c);
  		fscanf (fp, "%d", &number); 
    	esc[i][0] = number;

    	fscanf (fp, "%c", &c);
    	fscanf (fp, "%c", &c);
  		fscanf (fp, "%c", &c);
  		fscanf (fp, "%d", &number); 
    	esc[i][1] = number;
    	esc[i][2] = 0;

    	fscanf (fp, "%c", &c);
    	fscanf (fp, "%c", &c);     
    }

    fclose(fp);
}

/*Função que adiciona 0 em toda matriz*/
void clean_matrix(int emp[50][2]) {
	int i;
	for(i=0;i<50;i++) {
		emp[i][0] = 0;
		emp[i][1] = 0;
	}
}


int main() {
	int prof[100][7];
	int esc[50][3];
	int emp[50][2];
	int i, j, school_id, prof_id, change=0;

	parser(prof, esc);
	clean_matrix(emp);

	while(change == 0) {/*Ele fará o loop até n houver mais mudanças(emparelhamento estável)*/
		change = 1;
		for(i=0;i<100;i++) {
			if(prof[i][6] == 0) { /*Para cada professor desempregado*/
				for (j=1;j<6;j++) {/*For que pecorrerá suas preferencias*/
					school_id = prof[i][j] - 1;
					if(esc[school_id][2] == 0) {/*Se a escola ainda tiver espaço o professor sera adicionado instantaneamente*/
						if(emp[school_id][0] == 0) {
							emp[school_id][0] = i;
							if (esc[school_id][1] == 1) {
								esc[school_id][2] = 1;
							}
						}
						else {
							emp[school_id][1] = i;
							esc[school_id][2] = 1;
						}
						prof[i][6] = 1;/*Professor agora não é mais desempregado*/
						change = 0;
						break;
					}
					else {/*Se a escola não tem mais espaço*/
						if (esc[school_id][0] == prof[i][0]) {/*Primeiramente é checado se o professor tem a habilidade que a escola quer*/
							prof_id = emp[school_id][0];
							if (esc[school_id][0] != prof[prof_id][0]) {/*Caso o professor tenha a habilidade, mas o professor antigo n tiver, o novo entra e o antigo sai*/
								emp[school_id][0] = i;
								prof[i][6] = 1;/*Professor agora não é mais desempregado*/
								prof[prof_id][6] = 0;/*Professor antigo agora é mais desempregado*/
								change = 0;
								break;
							}
							if (esc[school_id][1] == 2) {
								prof_id = emp[school_id][1];
								if(prof[i][6] == 0) {
									if (esc[school_id][0] != prof[prof_id][0]) {/*Caso o professor tenha a habilidade, mas o professor antigo n tiver, o novo entra e o antigo sai*/
										emp[school_id][0] = i;
										prof[i][6] = 1;/*Professor agora não é mais desempregado*/
										prof[prof_id][6] = 0;/*Professor antigo agora é mais desempregado*/
										change = 0;
										break;
									}
								}
							}
						}
					}
				}
			}
		}
	}

	printf("Emparelhamento encontrado\n");
	for(i=0;i<50;i++) {
		if(esc[i][1] == 1) {
			printf("E%d - P%d\n", i+1, emp[i][0]+1);
		}
		else {
			printf("E%d - P%d, P%d\n", i+1, emp[i][0]+1, emp[i][1]+1 );
		}
	}
	

	return 0;
}