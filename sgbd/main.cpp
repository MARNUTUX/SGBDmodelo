/* 
 * File:   main.cpp
 * Author: minor
 *
 * Created on 15 de abril de 2014, 05:58 AM
 */

#include <cstdlib>
#include <iostream>

#include "diccionarioDatos.h"
using namespace std;


int main(int argc, char** argv) {
    diccionarioDatos dd;
    
    cout<<"HolaMundo"<<endl;
    dd.guardar();
    cout<<dd.toString()<<endl;
    return 0;
}

