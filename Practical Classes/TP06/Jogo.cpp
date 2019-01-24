/*
 * Jogo.cpp
 *
 */

#include "Jogo.h"
using namespace std;


unsigned Jogo::numPalavras(string frase)
{
  if ( frase.length() == 0 ) return 0;
  int n=1;
  unsigned pos = frase.find(' ');
  while ( pos != string::npos ) {
    frase = frase.substr(pos+1);
    pos = frase.find(' ');
    n++;
  }
  return n;
}


Jogo::Jogo()
{
	criancas.clear();
}

Jogo::Jogo(list<Crianca>& lc2)
{
	for (const auto & c : lc2) criancas.push_back(c);
}

void Jogo::insereCrianca(const Crianca &c1)
{
	criancas.push_back(c1);
}

list<Crianca> Jogo::getCriancasJogo() const
{
	return criancas;
}


string Jogo::escreve() const
{
	string res = "";
	for (const auto & c : criancas) res += c.escreve() + '\n';
	return res;
}


Crianca& Jogo::perdeJogo(string frase)
{
	int nP = numPalavras(frase);
	while(criancas.size() > 1) {
		int index = (nP-1) % criancas.size();
		list<Crianca>::iterator it = criancas.begin();
		for (int i = 0; i < index; i++) it++;
		criancas.erase(it);
	}
	return *(criancas.begin());
}


list<Crianca>& Jogo::inverte()
{
	list<Crianca> lista;
	int n = criancas.size();
	for (int i = 0; i < n; i++) {
		lista.push_back(criancas.back());
		criancas.pop_back();
	}
	criancas.clear();
	for (const auto & c: lista) criancas.push_back(c);
	// a alterar
	return criancas;
}


list<Crianca> Jogo::divide(unsigned id)
{
	list<Crianca> lista;
	list<Crianca>::iterator it;
	for (it = criancas.begin(); it != criancas.end(); it++) {
		if (it->getIdade() > id) {
			lista.push_back(*it);
			it = criancas.erase(it);
			it--;
		}
	}

	return lista;
}


void Jogo::setCriancasJogo(const list<Crianca>& l1)
{
	for (const auto & c : l1) criancas.push_back(c);
}


bool Jogo::operator==(Jogo& j2)
{
	return criancas == j2.getCriancasJogo();
}


list<Crianca> Jogo::baralha() const
{
	list<Crianca> copy = criancas;
	list<Crianca> randomL;
	for (unsigned i = 0; i < criancas.size(); i++){
		int index = rand() % copy.size();
		list<Crianca>::iterator it = copy.begin();
		for (int j = 0; j < index; j++) it++;
		randomL.push_back(*it);
		copy.erase(it);
	}
	return randomL;
}
