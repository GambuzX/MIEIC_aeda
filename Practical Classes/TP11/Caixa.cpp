/*
 * Caixa.cpp
 */

#include "Caixa.h"
#include <sstream>


Objeto::Objeto(unsigned idObj, unsigned pesoObj): id(idObj), peso(pesoObj)
{}

unsigned Objeto::getID() const {
	return id;
}

unsigned Objeto::getPeso() const {
	return peso;
}

Caixa::Caixa(unsigned cap): id(ultimoId++), capacidade(cap), cargaLivre(cap)
{}

unsigned Caixa::getID() const {
	return id;
}

unsigned Caixa::getCargaLivre() const {
	return cargaLivre;
}

void Caixa::addObjeto(Objeto& obj) {
	cargaLivre -= obj.getPeso();
	objetos.push(obj);
}

void Caixa::resetID(){
	ultimoId = 1;
}

unsigned Caixa::getSize() const {
	return objetos.size();
}


ostream& operator<<(ostream& os, Objeto obj) {
	os << "O" << obj.id << ": " << obj.peso;
	return os;
}

unsigned Caixa::ultimoId = 1;


/* a implementar pelos estudantes */

bool Objeto::operator<(const Objeto& o1) const {
	return peso < o1.getPeso();
}

bool Caixa::operator<(const Caixa& c1) const {
	return cargaLivre > c1.getCargaLivre();
}


string Caixa::imprimeConteudo() const {
	ostringstream oss;
	oss << getID();
	if (objetos.size() == 0) return "Caixa " + oss.str() + " vazia!\n";

	string retString = "C";
	retString += oss.str() + "[ ";

	STACK_OBJS copy = objetos;
	unsigned n_objs = copy.size();
	for (unsigned i = 0; i < n_objs; i++) {
		Objeto obj = copy.top();
		copy.pop();

		ostringstream oss2;
		oss2 << obj;
		retString += oss2.str() + ' ';
	}
	retString += ']';
	return retString;
}


