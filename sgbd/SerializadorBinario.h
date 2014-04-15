/*
	Autor: Steven Brenes Chavarr�a
	Email: sbrenesms@gmail.com
	Universidad Nacional de Costa Rica
	Licencia: GNU
*///

#pragma once
#include <string>
#include <fstream>
using namespace std;

class SerializadorBinario {
public:
	//
	// bloque de lectura de datos primitivos
	static string deserializeString(ifstream&);
	static int deserializeInt(ifstream&);
	static long deserializeLong(ifstream&);
	static double deserializeDouble(ifstream&);
	static float deserializeFloat(ifstream&);
	static char deserializeChar(ifstream&);
	//
	// bloque de serializacion de datos primitivos
	static bool serialize(ofstream&, const string&);
	static bool serialize(ofstream&, const int&);
	static bool serialize(ofstream&, const long&);
	static bool serialize(ofstream&, const double&);
	static bool serialize(ofstream&, const float&);
	static bool serialize(ofstream&, const char&);
	SerializadorBinario();
};

