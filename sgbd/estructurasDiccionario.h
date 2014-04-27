/* 
 * File:   estructurasDiccionario.h
 * Author: minor
 *
 * Created on 15 de abril de 2014, 05:44 AM
 */

#ifndef ESTRUCTURASDICCIONARIO_H
#define	ESTRUCTURASDICCIONARIO_H
#include <cstring>
#include <sstream>
#include <list>
using namespace std;

struct columna {
    string nombre;
    string tipo;    
};

struct tabla {
    string nombre;
    int bloqueInicial;
    int bloqueFinal;
    list<columna> columnas;
};

struct tablespace {
    string nombre;
    string ruta;
    list<tabla> tablas;
}; 

struct pivote {
    string tabla;
    int pivote;
};



#endif	/* ESTRUCTURASDICCIONARIO_H */

