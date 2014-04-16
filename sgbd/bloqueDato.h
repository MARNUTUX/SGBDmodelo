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
    int next;
};

struct bloqueDato {
    string tabla; // se guarda solo el nombre
    int estado; 
    int next; // -1 si esta pendiente
};



#endif	/* BLOQUEDATO_H */

