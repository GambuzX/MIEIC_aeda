#ifndef _DIC
#define _DIC
#include <string>
#include <fstream>
#include "BST.h"


class PalavraSignificado {
      string palavra;
      string significado;
public:
       PalavraSignificado(string p, string s): palavra(p), significado(s) {}
       string getPalavra() const { return palavra; }
       string getSignificado() const { return significado; }
       void setSignificado(string sig) { significado = sig; }
       bool operator < (const PalavraSignificado &ps1) const;
};

class Dicionario
{
      BST<PalavraSignificado> palavras;
public:
      Dicionario(): palavras(PalavraSignificado("","")){};
      BST<PalavraSignificado> getPalavras() const;
      void lerDicionario(ifstream &fich);
      string consulta(string palavra) const;
      bool corrige(string palavra, string significado);
      void imprime() const;
};


// a alterar
class PalavraNaoExiste
{
	string pantes, santes, pdepois, sdepois;
public:
	PalavraNaoExiste(string a, string b, string c,string d): pantes(a), santes(b), pdepois(c), sdepois(d) {}
	string getPalavraAntes() const { return pantes; }
	string getSignificadoAntes() const { return santes; }
	string getPalavraApos() const { return pdepois; }
	string getSignificadoApos() const { return sdepois; }
};



#endif
