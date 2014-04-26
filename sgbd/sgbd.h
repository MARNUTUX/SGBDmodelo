/* 
 * File:   sgbd.h
 * Author: minor
 *
 * Created on 15 de abril de 2014, 10:19 AM
 */

#ifndef SGBD_H
#define	SGBD_H

#include "diccionarioDatos.h"
#include "Parser.h"
#include "splitstring.h"
#include "bdes.h" 
#include <vector> 
#include <iostream> 
#include <stdlib.h> 

class sgbd {
public:
    sgbd();
    bool reconocedor(string);


private:
    diccionarioDatos dd;
    Parser parser;
    bdes bdess;
    int creador(tabla, string);
    int creador(string);
    int actualizador(string);
    int borrador(string);
    int seleccionador(string);
    //utiles
    vector<string> separador(string, char);
    int creaTabla(string, list<columna>);
    columna creaCol(string, string);
    int creaEscritor();
    bloqueDato creaBloque(string, list<string>);

    //validadores
    int validaInsertor(string);
    bool validaNumeros(string);

    //operaciones basicas
    int insertor(vector<string>);

};


#endif	/* SGBD_H */

