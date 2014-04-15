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
#define DEFAULT "default"


class diccionarioDatos {
public:
    diccionarioDatos();
    int prueba();
    
    //metodos cargar diccionario de datos del archivo
    int abrir();
    tablespace abrirTablespace(ifstream&);
    tabla abrirTabla(ifstream&);
    columna abrirColumna(ifstream&);
    //metodos guardar diccionario de datos en archivo
    int guardar();
    int guardarTablespace(ofstream&, tablespace);
    int guardarTabla(ofstream&,  tabla);
    int guardarColumna(ofstream&, columna);
    //metodos diccionario de datos
    int agregarTabla(tabla, string);
    int createTablespace(tabla, string);
    int quitarTabla(tabla);
    
    
    
    
    string toString();
 
    
    
private:
    list<tablespace> tablespaces;
    SerializadorBinario sb;
    
};


#endif	/* DICCIONARIODATOS_H */

