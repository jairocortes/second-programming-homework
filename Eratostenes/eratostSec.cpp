/*
 * este programa encuentra los primeros 5000 n�meros primos utilizando el 
 * algoritmo de Erat�stenes de manera secuencial
 *
*/
#include<iostream>
#include<sys/timeb.h>
using namespace std;

//cabecera de funci�n
int criba(int tam);

int main(){

    // variables utilizadas para capturar el tiempo 
	struct timeb start, finish;

	int cantPrimos=48615, primos=0;

	ftime(&start);// se captura el tiempo de inicio

	primos = criba (cantPrimos);
	cout<<endl<<"hay "<<primos<<" numeros primos"<<endl<<endl;

	ftime(&finish);// se captura el tiempo de fin

    cout << "tard�: "<<finish.millitm - start.millitm<<" milisegundos"<<endl;

return 0;
}
//funci�n que desarrolla el algoritmo de Erat�stenes
int criba(int tam){
	int cuenta=0;
	bool m[tam];//se declara el arreglo que ser� usado como la criba
	m[0] = false;// las primeras dos posiciones se ignoran
	m[1] = false;

    // al inicio se considera que todos los n�meros son primos
	for(int i = 2; i <= tam; ++i)  
		m[i] = true;

    // se comprueba que el cuadrado del i-�simo n�mero
    // no sea mayor que el l�mite de la criba
	for(int i = 2; i*i <= tam; ++i) {
		if(m[i]) {
            // seguidamente se tachan los m�ltimos del i-�simo n�mero
			for(int h = 2; i*h <= tam; ++h)
				m[i*h] = false;
		}
	}

    // se cuentan los n�meros primos
	for(int n = 2; n <= tam; ++n) {
		if(m[n]) {
			cuenta+=1;
		}
	}
	return cuenta;
}


