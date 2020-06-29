#include<iostream>//Libreria que maneja entrada y salida cout/cin
#include<exception> //Libreria que permite abortar el juego
using namespace std;
#define NO_JUGAR 0
#define ESPACIO_VACIO 1
#define FICHAS_BLANCAS 2
#define FICHAS_NEGRAS 3
#define FILAS 8
#define COLUMNAS 8
#define DAMAB 4
#define DAMAN 5

int intro(); //Funcion para la impresion del menu
void intercambio(int matrix[FILAS][COLUMNAS], int filaOrigen, int colOrigen, int filaDestino, int colDestino);//Funcion para el cambio de las fichas
int turno(int matrix[][COLUMNAS], int turnada,int filaOrigen,int colOrigen,int filaDestino,int colDestino);//Funcion que se ocupa de los turnos
char simbolos(int i);//Convierte los numeros en simbolos
void tablero(int matrix[FILAS][COLUMNAS]);//Impresion de tablero

int intro(){
    int op=0;
    do{
       do{
            system("cls");
            cout<<"\t\t_____________________________________________________________________"<<endl;
            cout<<"\t\t                                                                    "<<endl;
            cout<<"\t\t UNIVERSIDAD EUROPEA - ESCUELA DE ARQUITECTURA, INGENIERIA Y DISEÑO"<<endl;
            cout<<"\t\t_____________________________________________________________________"<<endl<<endl;
            cout<<"\t\tProf.:Christian Sucuzhanay.      Alumno : Arturo Alba Sanchez-Mayoral"<<endl<<endl<<endl;
            cout<<"\t\t              << JUEGO DE LAS DAMAS ESPANOLAS >>"<<endl<<endl;
            cout<<"\t\t\t    	Seleccionar una opcion del menu [0-2] **"<<endl<<endl;
            cout<<"\t\t\t\t  [ 1 ] Ver reglas del juego "<<endl;
            cout<<"\t\t\t\t  [ 2 ] Jugar"<<endl;
            cout<<"\t\t\t\t  [ 0 ] SALIR"<<endl<<endl;
            cout<<"\t\t\t              Ingrese su opcion ? : ";
            cin>>op;
        } while (op<0||op>2);
            switch (op){
                case 1:
                    system("cls");
                    cout<<"\t\t_____________________________________________________________________"<<endl;
                    cout<<"\t\t                                                                    "<<endl;
                    cout<<"\t\t UNIVERSIDAD EUROPEA - ESCUELA DE ARQUITECTURA, INGENIERIA Y DISEÑO"<<endl;
                    cout<<"\t\t_____________________________________________________________________"<<endl<<endl;
                    cout<<"\t\tProf.:Christian Sucuzhanay.      Alumno : Arturo Alba Sanchez-Mayoral"<<endl<<endl<<endl;
                    cout<<"\t\t                                                                    "<<endl;
                    cout<<"\t\t            << REGLAS DEL JUEGO DE LAS DAMAS ESPANOLAS >>\n";
                    cout<<"\t\t           ----------------------------------------------\n\n";
                    cout<<"\t\t1.- Inician el juego las fichas blancas por defecto"<<endl<<endl;
                    cout<<"\t\t2.- Las fichas SOLO se mueven 1 casilla hacia ADELANTE y en DIAGONAL\n ";
                    cout<<"\t\t    excepto al comer FICHA que pueden saltar\n\n";
                    cout<<"\t\t3.- Las fichas SALTAN mas de una casilla  SOLO cuando haya una ficha\n ";
                    cout<<"\t\t    contaria y la siguiente este vacia\n\n "; 
                    cout<<"\t\t4.- Gana quien coma mas fichas \n\n";
                    cout<<"\t\t5.- Si pasan mas de 2 horas sin que nadie gane se declara EMPATE\n\n\n\n ";
                    cout<<"\t\t\t\t PULSE [ 0 ] para SALIR: ";
                    cin>>op;
                    intro();
                case 2:
                    break;
                case 0:
                    system("cls");
                    abort();               
            }
        return 0;
    }while(op!=0);
    abort();
    
}


int turno(int matrix[FILAS][COLUMNAS], int turnada,int filaOrigen,int colOrigen,int filaDestino,int colDestino){
    int comerFichaBlancas;
    int comerFichaNegras;
    
    if((filaOrigen < 0 && FILAS <= filaOrigen)&&(colOrigen < 0 && COLUMNAS <= colOrigen)){ 
        cout<<"\n El tablero no tiene la posicion indicada\n";
        return -1;
    }
    if((filaDestino < 0 && FILAS <= filaDestino)&&(colDestino < 0 && COLUMNAS<= colDestino)){
        cout<<"\n El tablero no tiene la posicion indicada\n";
        return -1;
    }
        
    if(turnada == FICHAS_BLANCAS || turnada == DAMAB){
        if((matrix[filaOrigen][colOrigen] != FICHAS_BLANCAS) && (matrix[filaOrigen][colOrigen] != DAMAB)){
            cout<<"\n <<< No tienes fichas BLANCAS en esa posicion >>>\n";
            return -1;
        }
    } else if (turnada == FICHAS_NEGRAS || turnada == DAMAN){ 
        if((matrix[filaOrigen][colOrigen] != FICHAS_NEGRAS) && (matrix[filaOrigen][colOrigen] != DAMAN)){
            cout<<"\n <<< No tienes fichas NEGRAS en esa posicion >>>\n";
            return -1;
        }
    }
    
    if(matrix[filaDestino][colDestino] != ESPACIO_VACIO){
        cout<<"\nSolo puedes mover a un espacios VACIOS";
        return -1;
    }
    
    if(turnada == FICHAS_BLANCAS){
        if(filaOrigen >= filaDestino){
            cout<<"\nNo puedes mover hacia atras o quedarte en el mismo lugar\n";
            return -1;
        }
    } else if(turnada == FICHAS_NEGRAS){
        if(filaOrigen <= filaDestino){
            cout<<"\nNo puedes mover hacia atras o quedarte en el mismo lugar\n";
            return -1;
        }
    }
      
    //Comprueba si es un desplazamiento normal, una sola posicion
    if(turnada == FICHAS_BLANCAS || turnada == FICHAS_NEGRAS){
        if(filaOrigen - filaDestino == -1 || filaOrigen - filaDestino == 1){
            if(colOrigen - colDestino == 1 || colOrigen - colDestino == -1){
                intercambio(matrix,filaOrigen,colOrigen,filaDestino,colDestino);
                return 0;
            }
        }
    }

    
    //Comprueba si es un desplazamiento de dama diagonal
    if(turnada == DAMAB || turnada == DAMAN){
        if((abs(filaOrigen - filaDestino)) == (abs(colOrigen - colDestino))){
            int diago;//Cremaos variable para ver a la diagonal donde se moverá la dama
            if((filaOrigen > filaDestino) && (colOrigen > colDestino)){//desplazamiento diagonal arriba-izquierda
                diago = 1;
            }else if((filaOrigen < filaDestino) && (colOrigen < colDestino)){//Desplazamiento diagonal abajo-derecha
                diago = 2;
            }else if((filaOrigen < filaDestino) && (colOrigen > colDestino)){//Desplazamiento diagonal abajo-izquierda
                diago = 3;
            }else if((filaOrigen > filaDestino) && (colOrigen < colDestino)){//Desplazamiento diagonal arriba-derecha
                diago = 4;
            }
            if(diago == 1){ //desplazamiento diagonal arriba-izquierda
                for(int i = filaOrigen, j= colOrigen; (filaOrigen != filaDestino) && (colOrigen != colDestino);i--,j--){//Recorremos filas y columnas
                    if (((matrix[i][j] == FICHAS_NEGRAS)||(matrix[i][j] == DAMAN))&&(matrix[i - 1][j - 1] == 1)){//Verificamos si la siguiente posicion es vacia (negras)
                        intercambio(matrix, filaOrigen, colOrigen, i - 1, j - 1);//Realizamos el intercambio
                        return 0;
                    }else if (((matrix[i][j] == FICHAS_BLANCAS)||(matrix[i][j] == DAMAB))&&(matrix[i - 1][j - 1] == 1)){//Verificamos si la siguiente posicion es vacia (blancas)
                        matrix[i][j] = 1;//Se come a la ficha y deja una posicion vacia
                        intercambio(matrix, filaOrigen, colOrigen, i - 1, j - 1);//Realizamos el intercambio
                        return 0;
                    }
                }
            }else if(diago == 2){ //desplazamiento diagonal abajo-derecha
                for(int i = filaOrigen, j= colOrigen; (filaOrigen != filaDestino) && (colOrigen != colDestino);i++,j++){//Recorremos filas y columnas
                    if (((matrix[i][j] == FICHAS_NEGRAS)||(matrix[i][j] == DAMAN))&&(matrix[i + 1][j + 1] == 1)){//Verificamos si la siguiente posicion es vacia (negras)
                        matrix[i][j] = 1;//Se come a la ficha y deja una posicion vacia
                        intercambio(matrix, filaOrigen, colOrigen, i + 1, j + 1);//Realizamos el intercambio
                        return 0;
                    }else if (((matrix[i][j] == FICHAS_BLANCAS)||(matrix[i][j] == DAMAB))&&(matrix[i + 1][j + 1] == 1)){//Verificamos si la siguiente posicion es vacia (blancas)
                        matrix[i][j] = 1;//Se come a la ficha y deja una posicion vacia
                        intercambio(matrix, filaOrigen, colOrigen, i + 1, j + 1);//Realizamos el intercambio
                        return 0;
                    }
                }
            }else if(diago == 3){ //desplazamiento diagonal abajo-izquierda
                for(int i = filaOrigen, j= colOrigen; (filaOrigen != filaDestino) && (colOrigen != colDestino);i++,j--){//Recorremos filas y columnas
                    if (((matrix[i][j] == FICHAS_NEGRAS)||(matrix[i][j] == DAMAN))&&(matrix[i + 1][j - 1] == 1)){//Verificamos si la siguiente posicion es vacia (negras)
                        matrix[i][j] = 1;//Se come a la ficha y deja una posicion vacia
                        intercambio(matrix, filaOrigen, colOrigen, i + 1, j - 1);//Realizamos el intercambio
                        return 0;
                    }else if (((matrix[i][j] == FICHAS_BLANCAS)||(matrix[i][j] == DAMAB))&&(matrix[i + 1][j - 1] == 1)){//Verificamos si la siguiente posicion es vacia (blancas)
                        matrix[i][j] = 1;//Se come a la ficha y deja una posicion vacia
                        intercambio(matrix, filaOrigen, colOrigen, i + 1, j - 1);//Realizamos el intercambio
                        return 0;
                    }
                }
            }else if(diago == 4){ //desplazamiento diagonal arriba-derecha
                for(int i = filaOrigen, j= colOrigen; (filaOrigen != filaDestino) && (colOrigen != colDestino);i--,j++){//Recorremos filas y columnas
                    if (((matrix[i][j] == FICHAS_NEGRAS)||(matrix[i][j] == DAMAN))&&(matrix[i - 1][j + 1] == 1)){//Verificamos si la siguiente posicion es vacia (negras)
                        matrix[i][j] = 1;//Se come a la ficha y deja una posicion vacia
                        intercambio(matrix, filaOrigen, colOrigen, i - 1, j + 1);//Realizamos el intercambio
                        return 0;
                    }else if (((matrix[i][j] == FICHAS_BLANCAS)||(matrix[i][j] == DAMAB))&&(matrix[i - 1][j + 1] == 1)){//Verificamos si la siguiente posicion es vacia (blancas)
                        matrix[i][j] = 1;//Se come a la ficha y deja una posicion vacia
                        intercambio(matrix, filaOrigen, colOrigen, i - 1, j + 1);//Realizamos el intercambio
                        return 0;
                    }
                }
            }
        }
    }

    //Comprueba si ha comido ficha de adversario
    if(filaOrigen - filaDestino == -2 || filaOrigen - filaDestino == 2){
        if(colOrigen - colDestino == -2 || colOrigen - colDestino == 2){
            // Comprueba si en la posicion del salto hay ficha contraria
            if(filaOrigen < filaDestino){ // desplazamiento hacia abajo
                comerFichaBlancas = filaOrigen + 1;
            } else { // desplazamiento hacia arriba
                comerFichaBlancas = filaOrigen - 1;
            }
            if(colOrigen < colDestino){ // desplazamiento hacia abajo
                comerFichaNegras = colOrigen + 1;
            } else { // desplazamiento hacia arriba
                comerFichaNegras = colOrigen - 1;
            }       
            if(turnada==FICHAS_BLANCAS && matrix[comerFichaBlancas][comerFichaNegras]!=FICHAS_NEGRAS)
            {
                cout<<"\nSolo puedes saltar si COMES FICHA"<<comerFichaBlancas<<comerFichaNegras;
                return -1;
            }
            if(turnada==FICHAS_NEGRAS && matrix[comerFichaBlancas][comerFichaNegras] != FICHAS_BLANCAS){
                cout<<"\nSolo puedes saltar si COMES FICHA \n";
                return -1;
            }
            matrix[comerFichaBlancas][comerFichaNegras] = 1;
            intercambio(matrix,filaOrigen,colOrigen,filaDestino,colDestino);
            return 0;
        }
    }
    cout<<"Las fichas solo se pueden mover DIAGONALMENTE\n";
    return -1;
    
}


void tablero(int matrix[FILAS][COLUMNAS]){
    int pintarFilas, pintarCol;
    system("cls");
    cout<<"\t\t_____________________________________________________________________"<<endl;
    cout<<"\t\t                                                                    "<<endl;
    cout<<"\t\t UNIVERSIDAD EUROPEA - ESCUELA DE ARQUITECTURA, INGENIERIA Y DISEÑO"<<endl;
    cout<<"\t\t_____________________________________________________________________"<<endl<<endl;
    cout<<"\t\tProf.:Christian Sucuzhanay.      Alumno : Arturo Alba Sanchez-Mayoral"<<endl<<endl<<endl;
    cout<<"\t\t                << TABLERO DE LAS DAMAS ESPANOLAS >>"<<endl<<endl;
    cout<<"\n\t\t\t\t     B = fichas BLANCAS";
    cout<<"\n\t\t\t\t     N = fichas NEGRAS";
    cout<<"\n\t\t\t\t     v = espacios VACIOS jugables";
    cout<<"\n\n\t\t\t\t   +---+---+---+---+---+---+---+---+\n"; 
    
    for (pintarFilas=0; pintarFilas<FILAS; ++pintarFilas)
    {
        cout<<"\t\t\t\t"<<  pintarFilas+1  <<"  | "; 
        for (pintarCol=0; pintarCol<COLUMNAS; ++pintarCol)
        {
            cout<<simbolos(matrix[pintarFilas][pintarCol])<< " | " ;
        }
        cout<<"\n";
        cout<<"\t\t\t\t   +---+---+---+---+---+---+---+---+\n";
    }
    cout<<"\n\t\t\t\t     a   b   c   d   e   f   g   h\n\n\n";
}


void intercambio(int matrix[FILAS][COLUMNAS], int filaOrigen, int colOrigen, int filaDestino, int colDestino){
  int temp;

  if ((matrix[filaOrigen][colOrigen]==FICHAS_BLANCAS) && (filaDestino==7)){
 	temp = matrix[filaOrigen][colOrigen];
	matrix[filaOrigen][colOrigen] = matrix[filaDestino][colDestino];
  	matrix[filaDestino][colDestino] = DAMAB;
  }else if((matrix[filaOrigen][colOrigen]==FICHAS_NEGRAS) && (filaDestino==0)){
 	temp = matrix[filaOrigen][colOrigen];
	matrix[filaOrigen][colOrigen] = matrix[filaDestino][colDestino];
  	matrix[filaDestino][colDestino] = DAMAN;
  }else{
 	temp = matrix[filaOrigen][colOrigen];
	matrix[filaOrigen][colOrigen] = matrix[filaDestino][colDestino];
  	matrix[filaDestino][colDestino] = temp;
  }
}


char simbolos(int i){
    switch(i)
    {
  		case 0:
            return ' ';
        case 1:
            return 'v'; 
        case 2:
            return 'B';
        case 3:
            return 'N';
		case 4:
			return 'X';
		case 5:
			return 'O';
    }
    return ('?');
}


int main(){
    int turnada;
    int filaOrigen, filaDestino;
    char colOrigen, colDestino;
    int matrix[FILAS][COLUMNAS]={
                {0,2,0,2,0,2,0,2},
                {2,0,2,0,2,0,2,0}, 
                {0,2,0,2,0,2,0,2}, 
                {2,0,1,0,1,0,1,0}, 
                {0,3,0,1,0,1,0,1}, 
                {3,0,1,0,3,0,3,0},
                {0,3,0,3,0,3,0,3},
                {3,0,3,0,3,0,3,0}};
    intro();
    system("cls");
    for(;;){
        tablero(matrix);
        while(1){
            cout<<"\nTURNO de las  * BLANCAS *  Ingrese FILA 1-8 y COLUMNA a-h de la ficha que desea mover, por ejemplo 3b\n";
            cin>>filaOrigen>>colOrigen;
            colOrigen = tolower(colOrigen);
    	    cout<<"Introduzca FILA 1-8 y COLUMNA a-h del destino de la ficha a mover,  por ejemplo 4a \n";
            cin>>filaDestino>>colDestino;
            colDestino = tolower(colDestino);

            if(matrix[filaOrigen - 1][colOrigen - 'a'] == FICHAS_BLANCAS){//Detecto si es un peon blanco
                turnada = FICHAS_BLANCAS;
            }else if(matrix[filaOrigen - 1][colOrigen - 'a'] == DAMAB){//Detecto si es una dama blanca
                turnada = DAMAB;
            }else{
                turnada = -1; //Produce un turnada erroneo en caso de fallo
            }
        	if(turno(matrix, FICHAS_BLANCAS, filaOrigen - 1,colOrigen - 'a',filaDestino - 1,colDestino - 'a') == 0)
        	    break;
            cout<<"\nINTENTA de nuevo :\n";
        }
        system("cls");
        tablero(matrix);
        while(1){
            cout<<"\nTURNO de las  * NEGRAS *  Ingrese FILA 1-8 y COLUMNA a-h de la ficha que desea mover, por ejemplo 6g\n";
            cin>>filaOrigen>>colOrigen;
            colOrigen = tolower(colOrigen);
    	    cout<<"Introduzca FILA 1-8 y COLUMNA a-h del destino de la ficha a mover,  por ejemplo 5h \n";
            cin>>filaDestino>>colDestino;
            colDestino = tolower(colDestino);

            if(matrix[filaOrigen - 1][colOrigen - 'a'] == FICHAS_NEGRAS){
                turnada = FICHAS_NEGRAS;
            }else if(matrix[filaOrigen - 1][colOrigen - 'a'] == DAMAN){
                turnada = DAMAN;
            }else{
                turnada = -1;//Produce un turnada erroneo en caso de fallo
            }
        	if(turno(matrix, FICHAS_NEGRAS, filaOrigen-1,colOrigen - 'a',filaDestino-1,colDestino - 'a') == 0)
        	    break;
            cout<<"\nINTENTA de nuevo :\n)";
        }
    }
    return 0;
}
