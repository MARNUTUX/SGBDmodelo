/* 
 * File:   bdes.h
 * Author: minor
 *
 * Created on 15 de abril de 2014, 10:31 AM
 */

#ifndef BDES_H
#define	BDES_H

#include "SerializadorBinario.h"


class bdes {
public: 
    int lector(string);
    int escritor(string, int);
    int grabador(string, int);
    int validador(string, int);
    int borrador(string, int);
    int compresor();
    
private:
    SerializadorBinario sb;
};


#endif	/* BDES_H */

