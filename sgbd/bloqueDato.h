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


struct bloqueDato {
    string tabla; // se guarda solo el nombre
    list<string> datos; 
    int estado; 
    int next; // -1 si esta pendiente
    int posInicial;
    int posFinal;
    //int tamano;
};



#endif	/* BLOQUEDATO_H */

