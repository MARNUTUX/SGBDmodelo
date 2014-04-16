/*
	Autor: Steven Brenes Chavarr�a
	Email: sbrenesms@gmail.com
	Universidad Nacional de Costa Rica
	Licencia: GNU
*///

#include "SerializadorBinario.h"
#include <fstream>
#include <sstream>

SerializadorBinario::SerializadorBinario() {
}

string SerializadorBinario::deserializeString(ifstream &in) {
	string r;

	size_t n = 0;
	in.read((char*)&n, sizeof(size_t));
	
	char* c = new char[n];
	in.read(c, (std::streamsize)n);
	r = string(c);
	delete c;
	if(!in.good())
		throw -1;

	return r;
}

int SerializadorBinario::deserializeInt(ifstream &in) {
	string r = deserializeString(in);
	stringstream s;
	s << r;
	int destino;
	s >> destino;
	return destino;
}

long SerializadorBinario::deserializeLong(ifstream &in) {
	string r = deserializeString(in);
	stringstream s;
	s << r;
	long destino;
	s >> destino;
	return destino;
}

double SerializadorBinario::deserializeDouble(ifstream &in) {
	string r = deserializeString(in);
	stringstream s;
	s << r;
	double destino;
	s >> destino;
	return destino;
}

float SerializadorBinario::deserializeFloat(ifstream &in) {
	string r = deserializeString(in);
	stringstream s;
	s << r;
	float destino;
	s >> destino;
	return destino;
}

char SerializadorBinario::deserializeChar(ifstream &in) {
	string r = deserializeString(in);
	stringstream s;
	s << r;
	char destino;
	s >> destino;
	return destino;
}

bool SerializadorBinario::serialize(ofstream &out, const string &s) {
	bool r = true;

	// Primero, guarda la longitud de la hilera,
	// tomando en cuenta el caracter nulo de terminaci�n.

	size_t n = s.length() + 1;
	out.write((char*)&n, sizeof(size_t));
        

	// Luego graba los caracteres componentes de la
	// hilera.

	out.write(s.c_str(), (std::streamsize)n);
	return out.good();
}

bool SerializadorBinario::serialize(ofstream &out, const int &s) {
	stringstream r;
	r << s;
	return serialize(out, r.str());
}

bool SerializadorBinario::serialize(ofstream &out, const long &s) {
	stringstream r;
	r << s;
	return serialize(out, r.str());
}

bool SerializadorBinario::serialize(ofstream &out, const double &s) {
	stringstream r;
	r << s;
	return serialize(out, r.str());
}

bool SerializadorBinario::serialize(ofstream &out, const float &s) {
	stringstream r;
	r << s;
	return serialize(out, r.str());
}

bool SerializadorBinario::serialize(ofstream &out, const char &s) {
	stringstream r;
	r << s;
	return serialize(out, r.str());
}