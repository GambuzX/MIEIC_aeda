#include "Aposta.h"
#include <iostream>
#include <sstream>

using namespace std;

bool Aposta::contem(unsigned num) const
{
	tabHInt::const_iterator it = numeros.find(num);
	if (it != numeros.end()) return true;
	return false;
}


void Aposta::geraAposta(const vector<unsigned> & valores, unsigned n)
{
	unsigned inserted = 0;
	for (unsigned i = 0; i < valores.size(); i++) {
		if (inserted >= n) break;
		pair<tabHInt::iterator, bool> ret = numeros.insert(valores[i]);
		if (ret.second) inserted ++;
	}
}


unsigned Aposta::calculaCertos(const tabHInt & sorteio) const
{
	unsigned certos = 0;
	tabHInt::const_iterator it;
	for (it = sorteio.begin(); it != sorteio.end(); it++) {
		if (contem(*it)) certos++;
	}
	return certos;
}




