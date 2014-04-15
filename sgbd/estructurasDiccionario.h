/* 
 * File:   estructurasDiccionario.h
 * Author: minor
 *
 * Created on 15 de abril de 2014, 05:44 AM
 */

#ifndef ESTRUCTURASDICCIONARIO_H
#define	ESTRUCTURASDICCIONARIO_H
#include <cstring>
#include <list>
using namespace std;

struct tablespace {
    string nombre;
    string ruta;
    list<tabla> tablas;
    tablespace();
    int guardar();
};

struct tabla {
    string nombre;
    list<columna> columnas;
    tabla();
    int guardar();
};

struct columna {
    string nombre;
    string tipo;     
    columna();
    int guardar();
};

#endif	/* ESTRUCTURASDICCIONARIO_H */

