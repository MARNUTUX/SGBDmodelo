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
    ~diccionarioDatos();
    int prueba();

    //metodos cargar diccionario de datos del archivo
    int abrir();

    //metodos guardar diccionario de datos en archivo
    int guardar();

    //metodos diccionario de datos
    int agregarTabla(tabla, string);
    int quitarTabla(tabla);
    bool existeColumna(string);
    int existeTabla(string, tabla&);//agreog de lo de minor
    list<pivote> pivotes;
    string toString();

    int miPivote; // falta serializarlo
private:
    list<tablespace> tablespaces;

    SerializadorBinario sb;
    
    //persistencia
    tablespace abrirTablespace(ifstream&);
    tabla abrirTabla(ifstream&);
    columna abrirColumna(ifstream&);
    list<pivote> abrirPrivotes(ifstream&);
    pivote abrirPivote(ifstream&);
    int guardarTablespace(ofstream&, tablespace);
    int guardarTabla(ofstream&, tabla);
    int guardarColumna(ofstream&, columna);
    int guardarPivotes(ofstream&);
    int guardarPivote(ofstream&, pivote);
    
    //utiles
    tablespace* existeTablespace(string);
    int crearTabla(tabla, string);
    tablespace createTablespace(string);

    
};


#endif	/* DICCIONARIODATOS_H */

