/* 
 * File:   main.cpp
 * Author: minor
 *
 * Created on 15 de abril de 2014, 05:58 AM
 */

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include "bdes.h"
#include "diccionarioDatos.h"
#include "bloqueDato.h"
using namespace std;

int prueba0() {
    FILE *fichero;
    string nombre = "datos5.dat";
    string dinero = "minorsaddsadsadsdsadsdasdsadsadsadsadasdsa";
    string p = "pruebadasdasdasdsadssadsdasdasdsada";
    char leer[10] = "nada" ;
    
    
    fichero = fopen(nombre.c_str(), "w+r");
    printf("Fichero: %s -> ", nombre.c_str());
    if (fichero)
        printf("creado (ABIERTO)\n");
    else {
        printf("Error (NO ABIERTO)\n");
        return 1;
    }

    fwrite(dinero.c_str(), 1, 10, fichero);
    fwrite(p.c_str(), 1, 10, fichero);

    printf("\nLeyendo los datos del fichero \"%s\":\n", nombre.c_str());
   // rewind(fichero);
    fseek( fichero, 10, 0 );
    fread(leer, 1, 10, fichero);

    printf("%s\t", leer);

    if (!fclose(fichero)) {
        printf("\nFichero cerrado\n");
        return 1;
    } else {
        printf("\nError: fichero NO CERRADO\n");
        return -1;
    }
    
   
}

int lector(string nombreF, int pos) {
    FILE* mifichero;
    mifichero = fopen(nombreF.c_str(), "r");
    
    if(mifichero){
        fseek(mifichero, pos, SEEK_SET);
     
    } else {
        return -1;
    }
    return fclose(mifichero)? 1: -1;
    
}

int escritor() {
    
}

int prueba1() {
    bloqueDato bd;
    bd.tabla = "t0";
    bd.estado = 1;
    bd.next = -1;
    dato d0;
    d0.nombreColumna = "c0";
    d0.tipoDato = "varchar";
    d0.valor = "xxx";
    bd.datos.push_front(d0);
    FILE *fichero;
    
}

int main(int argc, char** argv) {
    //prueba0();
    string str = "1234";
    printf("size--> %d \n", sizeof(str));
    cout<<"HolaMundo"<<endl;
    return 1;
}

