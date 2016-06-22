/*
 * este programa encuentra los primeros 5000 números primos utilizando el 
 * algoritmo de Eratóstenes de manera paralelizada utilizando la librería
 * OpenMPI y el lenguage de programación C
 *
*/
#include<stdio.h>
#include<string.h>
#include<stdbool.h> // header para utilizar booleanos
#include<mpi.h>// header de las llamadas a MPI
#include<sys/timeb.h>// header para utilizar funciones de medir el tiempo

void main(int argc, char* argv[]) {

	// variables utilizadas para medir el tiempo en cada proceso
	struct timeb start1, finish1,start2, finish2,start3, finish3; 

	int tamCriba=48615, cantPrimos=0;
	bool m[tamCriba];//se declara el arreglo que será usado como la criba
	m[0] = false;// las primeras dos posiciones se ignoran
	m[1] = false;

	int         mi_rango;      // rango del proceso
    int         cantProc;      // numero de procesos
    int         fuente;        // rango del que envia
    int         dest;          // rango del que recibe
    int         tag;           // etiqueta del mensaje
    char        mensaje[100];  // mensaje
    char        mensaje2[100]; // mensaje
    MPI_Status  estado;        // devuelve estado al recibir

	
	
    // se llama al constructor de MPI
    MPI_Init(&argc, &argv);

    // Averiguamos el rango de nuestro proceso
    MPI_Comm_rank(MPI_COMM_WORLD, &mi_rango);

    // Averiguamos el número de procesos que estan 
    // ejecutando nuestro porgrama 
    MPI_Comm_size(MPI_COMM_WORLD, &cantProc);

    //empezamos a otorgar código a cada proceso
	if(mi_rango == 1){
		ftime(&start1);
		// el proceso 1 llena toda la criba de "true"
		for(int i = 2; i <= tamCriba; ++i) 
			m[i] = true;
		ftime(&finish1);
		printf("proceso 1 tardÃ³ %d milisegundos\n", finish1.millitm - start1.millitm);
	}
	else if(mi_rango == 2){
		ftime(&start2);
		// el proceso 2 está sobrecargado ya que este va tachando 
		// todos los multiplos de los números cuyo cuadrado es menor
		// que el número mayor de la criba
		for(int i = 2; i*i <= tamCriba; ++i) {
			if(m[i]) {
				for(int h = 2; i*h <= tamCriba; ++h){
					m[i*h] = false;
				}
			}
		}
		ftime(&finish2);
		printf("proceso 2 tarda %d milisegundos\n", finish2.millitm - start2.millitm);
	}
	else if(mi_rango == 3){
		ftime(&start3);
		// este proceso Ãºnicamente va a ir contando los true, ya que 
		// esos serÃ¡n los nÃºmeros primos, y se lo informarÃ¡ al proceso 0
		for(int n = 2; n <= tamCriba; ++n) {
			if(m[n]) {
				cantPrimos = cantPrimos + 1;
			}
		}
		// Crea mensaje despues de contar los numeros primos
        sprintf(mensaje, "hay %d numeros primos!",cantPrimos);
        dest = 0;tag=0;
		// se usa strlen+1 para que la marca "/0" se transmita
        MPI_Send(mensaje, strlen(mensaje)+1, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
		ftime(&finish3);
		printf("proceso 3 tarda %d milisegundos\n", finish3.millitm - start3.millitm);
	}
	else if (mi_rango == 0){
		fuente = 3;tag=0;
		MPI_Recv(mensaje, 100, MPI_CHAR, fuente, tag, MPI_COMM_WORLD, &estado);
        printf("%s\n", mensaje);
	}
    // Termina con MPI 
     MPI_Finalize();
}



