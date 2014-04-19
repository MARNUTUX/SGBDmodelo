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
    int lector();
    int escritor();
    int grabador();
    int validador();
    int borrador();
    int compresor();
    
private:
    int serializarBloque(ofstream&, bloqueDato*);
    int serializarDato(ofstream&, dato);
    bloqueDato* deserializarBloque(ifstream&);
    dato deserializarDato(ifstream&);
    SerializadorBinario sb;
    
};


#endif	/* BDES_H */

