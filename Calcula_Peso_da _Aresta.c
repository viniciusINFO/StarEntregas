#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct planeta_x{

	int H_R_Planeta = 12;// hora que começa a restrição do planeta
	int H_Restricao = 4;// tempo de restrição do planeta
	
}Planeta_x;


int main(){

	int Hora_Total = 0;
	int Peso_Aresta = 0;

	if(Hora_Total + Peso_Aresta) > Planeta_x->H_R_Planeta && (Hora_Total + Peso_Aresta) < (Planeta_x->H_R_Planeta + Planeta_x->H_Restricao){ //sabera se o planeta esta em restrição ou não para poder almentar o peso da aresta

		Peso_Aresta += (planeta->H_R_Planeta + Planeta_x->H_Restricao) - (Hora_Total + Peso_Aresta);//soma o peso na aresta normalmente + as horas de restrição
		Hora_Total += Peso_Aresta;//somo o novo valor da aresta no tempo
	}

//ato
	//so pra printar bunitinho

	if(Dias = 0){

		if(Hora_Total = 1){
			printf("gastou %i hora", Hora_Total);
		}else{
			printf("gastou %i horas", Hora_Total);
		}
		
	}else{

		if(Hora_Total = 1){
			if(Dias = 1){
				printf("gastou %i dia e %i hora", Dias, Hora_Total);
			}else{
				printf("gastou %i dias e %i hora", Dias, Hora_Total);
			}
		}else{
			if(Dias = 1){
				printf("gastou %i dia e %i horas", Dias, Hora_Total);
			}else{
				printf("gastou %i dias e %i horas", Dias, Hora_Total);
			}

	}
}
return 0;
}