/* 
 * File:   bdes.h
 * Author: minor
 *
 * Created on 15 de abril de 2014, 10:31 AM
 */

#ifndef BDES_H
#define	BDES_H
#include "bloqueDato.h"
#include "SerializadorBinario.h"


class bdes : public SerializadorBinario {
    
public:
    bdes();
    ~bdes();
    int lector(string, int, bloqueDato&);
    int escritor(string,bloqueDato&, int&, int&, int&, int&);
    int grabador(string, bloqueDato, int);
    int validador(string, int);
    int borrador(string, int);
    int compresor(string);
    int modificarNext(string, int&, int);
    
private:
    int serializarBloque(ofstream&, bloqueDato&, int&);
    int serializarDato(ofstream&, dato);
    bloqueDato* deserializarBloque(ifstream&);
    dato deserializarDato(ifstream&);
    int getPosEstado(string, int);
    SerializadorBinario sb;
    
};


#endif	/* BDES_H */

