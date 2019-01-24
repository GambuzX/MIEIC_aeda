#include "Jogo.h"
#include <sstream>

BinaryTree<Circulo> & Jogo::getJogo() {
	return jogo;
}


ostream &operator << (ostream &os, Circulo &c1)
{
	// a alterar
	return os;
}



Jogo::Jogo(int niv, vector<int> &pontos, vector<bool> &estados)
{

	jogo = criaJogo(0, niv, pontos, estados);
}

BinaryTree<Circulo> Jogo::criaJogo(int pos, int niv, vector<int> &pontos, vector<bool> &estados) {

	if (niv == 0) return Circulo(pontos[pos], estados[pos]);
	return BinaryTree<Circulo>(Circulo(pontos[pos], estados[pos]), criaJogo(2*pos+1, niv-1, pontos, estados), criaJogo(2*pos+2, niv-1, pontos, estados));
}


string Jogo::escreveJogo()
{
	BTItrLevel<Circulo> iter(jogo);
	string returnS = "";
	while (!iter.isAtEnd()) {
		ostringstream oss("");
		oss << iter.retrieve().getPontuacao() << '-';

		if (iter.retrieve().getEstado()) oss << "true-";
		else oss << "false-";

		oss << iter.retrieve().getNVisitas() << '\n';
		returnS += oss.str();
		iter.advance();
	}
	return returnS;
}


int Jogo::jogada()
{
	int pos=1, score;
	BTItrLevel<Circulo> iter(jogo);
	if(iter.isAtEnd()) return -1;
	while(true) {
		Circulo &c1 = iter.retrieve();
		bool state = c1.getEstado(); int n;
		if (!state) n = pos;
		else n = pos+1;
		c1.mudaEstado();
		c1.incrementVisits();
		score = c1.getPontuacao();
		int i = 0;
		while (i<n && !iter.isAtEnd()) {
			iter.advance();
			i++;
		}
		if (!iter.isAtEnd()) pos += n;
		else break;
	}
	return score;
}



int Jogo::maisVisitado()
{
	int max = 0;

	BTItrLevel<Circulo> iter(jogo);
	iter.advance();
	while(!iter.isAtEnd()) {
		if (iter.retrieve().getNVisitas() > max)
			max = iter.retrieve().getNVisitas();
		iter.advance();
	}

	return max;;
}




