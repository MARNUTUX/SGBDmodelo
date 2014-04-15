/* 
 * File:   diccionarioDatos.h
 * Author: minor
 *
 * Created on 15 de abril de 2014, 06:17 AM
 */


#ifndef DICCIONARIODATOS_H
#define	DICCIONARIODATOS_H
#include "estructurasDiccionario.h"
#include "SerializadorBinario.h"

class diccionarioDatos {
public:
    diccionarioDatos();
    
    int prueba();
    
    int abrir();
    tablespace abrirTablespace(ifstream&);
    tabla abrirTabla(ifstream&);
    columna abrirColumna(ifstream&);
    
    int guardar();
    int guardarTablespace(ofstream&, tablespace);
    int guardarTabla(ofstream&,  tabla);
    int guardarColumna(ofstream&, columna);
    
    string toString();
 
    
    
private:
    list<tablespace> tablespaces;
    SerializadorBinario sb;
    
};


#endif	/* DICCIONARIODATOS_H */

