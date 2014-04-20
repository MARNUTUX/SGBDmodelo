/* 
 * File:   bloqueDato.h
 * Author: minor
 *
 * Created on 15 de abril de 2014, 09:03 AM
 */

#ifndef BLOQUEDATO_H
#define	BLOQUEDATO_H
#include <cstring>
#include "estructurasDiccionario.h"
using namespace std;
struct dato {
    string nombreColumna;
    string tipoDato;
    string valor;
};

struct bloqueDato {
    string tabla; // se guarda solo el nombre
    list<dato> datos; 
    int estado; 
    int next; // -1 si esta pendiente
    // int pos inicial
    //int pos final no guardar solo para administrar.
};



#endif	/* BLOQUEDATO_H */

