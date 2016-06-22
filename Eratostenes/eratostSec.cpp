/*
 * este programa encuentra los primeros 5000 números primos utilizando el 
 * algoritmo de Eratóstenes de manera secuencial
 *
*/
#include<iostream>
#include<sys/timeb.h>
using namespace std;

//cabecera de función
int criba(int tam);

int main(){

    // variables utilizadas para capturar el tiempo 
	struct timeb start, finish;

	int cantPrimos=48615, primos=0;

	ftime(&start);// se captura el tiempo de inicio

	primos = criba (cantPrimos);
	cout<<endl<<"hay "<<primos<<" numeros primos"<<endl<<endl;

	ftime(&finish);// se captura el tiempo de fin

    cout << "tardó: "<<finish.millitm - start.millitm<<" milisegundos"<<endl;

return 0;
}
//función que desarrolla el algoritmo de Eratóstenes
int criba(int tam){
	int cuenta=0;
	bool m[tam];//se declara el arreglo que será usado como la criba
	m[0] = false;// las primeras dos posiciones se ignoran
	m[1] = false;

    // al inicio se considera que todos los números son primos
	for(int i = 2; i <= tam; ++i)  
		m[i] = true;

    // se comprueba que el cuadrado del i-ésimo número
    // no sea mayor que el límite de la criba
	for(int i = 2; i*i <= tam; ++i) {
		if(m[i]) {
            // seguidamente se tachan los múltimos del i-ésimo número
			for(int h = 2; i*h <= tam; ++h)
				m[i*h] = false;
		}
	}

    // se cuentan los números primos
	for(int n = 2; n <= tam; ++n) {
		if(m[n]) {
			cuenta+=1;
		}
	}
	return cuenta;
}


