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
	int index = nP % criancas.size();
	list<Crianca>::iterator it = criancas.begin();
	for (int i = 0; i < index; i++) it++;
	return *it;
}


list<Crianca>& Jogo::inverte()
{
	// a alterar
	return criancas;
}


list<Crianca> Jogo::divide(unsigned id)
{
	// a alterar
		list<Crianca> res;
		return res;
}


void Jogo::setCriancasJogo(const list<Crianca>& l1)
{
	for (const auto & c : l1) criancas.push_back(c);
}


bool Jogo::operator==(Jogo& j2)
{
	// a alterar
	return true;
}


list<Crianca> Jogo::baralha() const
{
	// a alterar
	list<Crianca> res;
	return res;
}
