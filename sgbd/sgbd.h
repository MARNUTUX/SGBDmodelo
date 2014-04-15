/* 
 * File:   sgbd.h
 * Author: minor
 *
 * Created on 15 de abril de 2014, 10:19 AM
 */

#ifndef SGBD_H
#define	SGBD_H

#include "diccionarioDatos.h"


class sgbd {
public:
    int creador(tabla, string);
    int insertor();
    int actualizador();
    int borrador();
    int seleccionador();
    
private:
    diccionarioDatos dd;
};


#endif	/* SGBD_H */

