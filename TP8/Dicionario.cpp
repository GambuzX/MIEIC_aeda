#include <iostream>
#include <string>
#include <fstream>
#include "Dicionario.h"
#include "BST.h"

using namespace std;


BST<PalavraSignificado> Dicionario::getPalavras() const
{ return palavras; }



bool PalavraSignificado::operator < (const PalavraSignificado &ps1) const
{
	return palavra < ps1.getPalavra();
}


void Dicionario::lerDicionario(ifstream &fich)
{
	string savingString;
	while (getline(fich, savingString)) {
		string nome = savingString;
		getline(fich, savingString);
		string definition = savingString;
		palavras.insert(PalavraSignificado(nome, definition));
	}
	return;
}


string Dicionario::consulta(string palavra) const
{
	BSTItrIn<PalavraSignificado> iter(palavras);
	while (!iter.isAtEnd()) {
		if (iter.retrieve().getPalavra() == palavra) {
			return iter.retrieve().getSignificado();
		}
		PalavraSignificado pantes = iter.retrieve();
		iter.advance();

		if (! iter.isAtEnd() && iter.retrieve().getPalavra() > palavra) {
			throw PalavraNaoExiste(pantes.getPalavra(), pantes.getSignificado(), iter.retrieve().getPalavra(), iter.retrieve().getSignificado());
		}
	}
	throw PalavraNaoExiste("", "", "", "");
	return "";
}


bool Dicionario::corrige(string palavra, string significado)
{
	try {
		consulta(palavra);

		BST<PalavraSignificado> newBST(PalavraSignificado("",""));
		BSTItrIn<PalavraSignificado> iter(palavras);
		while (!iter.isAtEnd()) {
			if (iter.retrieve().getPalavra() == palavra) {
				newBST.insert(PalavraSignificado(palavra, significado));
			}
			newBST.insert(iter.retrieve());
			iter.advance();
		}
		palavras = newBST;
	}
	catch (PalavraNaoExiste & exc) {
		palavras.insert(PalavraSignificado(palavra, significado));
		return false;
	}

	return true;
}


void Dicionario::imprime() const
{
	BSTItrIn<PalavraSignificado> iter(palavras);
	while (!iter.isAtEnd()) {
		cout << iter.retrieve().getPalavra() << endl << iter.retrieve().getSignificado() << endl;
		iter.advance();
	}

    return;
}
