/* 
 * File:   bloqueDato.h
 * Author: minor
 *
 * Created on 15 de abril de 2014, 09:03 AM
 */

#ifndef BLOQUEDATO_H
#define	BLOQUEDATO_H
#include <cstring>
using namespace std;
struct dato {
    string nombreColumna;
    string tipoDato;
    string valor;
};

struct bloqueDato {
    string nombreTabla;
    list<dato> datos;
    int estado;
    int next;
};



#endif	/* BLOQUEDATO_H */

