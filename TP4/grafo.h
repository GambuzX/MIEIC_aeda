#include <iostream>
#include <vector>

using namespace std;

/**
 * Versao da classe generica Grafo usando a classe vector
 */

template <class N, class A> class Aresta;

template <class N, class A>
class No {
public:
	N info;
	vector< Aresta<N,A> > arestas;
	No(N inf) {
		info = inf;
	}
};

template <class N, class A>
class Aresta {
public:
	A valor;
	No<N,A> *destino;
	Aresta(No<N,A> *dest, A val) {
		valor = val;
		destino = dest;
	}
};

template <class N, class A> 
class Grafo { 
	vector< No<N,A> *> nos;
  public: 
    Grafo();
    ~Grafo(); 
    Grafo & inserirNo(const N &dados);
    Grafo & inserirAresta(const N &inicio, const N &fim, const A &val);
    Grafo & eliminarAresta(const N &inicio, const N &fim);
    A & valorAresta(const N &inicio, const N &fim);
    int numArestas(void) const;
    int numNos(void) const;
    void imprimir(std::ostream &os) const; 
};

template <class N, class A>
std::ostream & operator<<(std::ostream &out, const Grafo<N,A> &g);


// excecao  NoRepetido
template <class N>
class NoRepetido
{
public:
   N info;
   NoRepetido(N inf) { info=inf; }
};
template <class N>
std::ostream & operator<<(std::ostream &out, const NoRepetido<N> &no)
{ out << "No repetido: " << no.info; return out; }



// excecao NoInexistente
template <class N>
class NoInexistente {
public:
	N info;
	NoInexistente(N inf) {
		info = inf;
	}
};
template <class N>
std::ostream & operator<<(std::ostream &out, const NoInexistente<N> &ni)
{ out << "No inexistente: " << ni.info; return out; }



// excecao ArestaRepetida
template <class N>
class ArestaRepetida {
public:
	N start, end;
	ArestaRepetida(N s, N e) {
		start = s;
		end = e;
	}
};
template <class N>
std::ostream & operator<<(std::ostream &out, const ArestaRepetida<N> &ni)
{ out << "Aresta repetida: " << ni.start << " , " << ni.end;; return out; }

// excecao ArestaInexistente
template <class N>
class ArestaInexistente {
public:
	N start, end;
	ArestaInexistente(N s, N e) {
		start = s;
		end = e;
	}
};
template <class N>
std::ostream & operator<<(std::ostream &out, const ArestaInexistente<N> &ni)
{ out << "Aresta inexistente: " << ni.start << " , " << ni.end;; return out; }


template <class N, class A>
Grafo<N,A>::Grafo() {}

template <class N, class A>
Grafo<N,A>::~Grafo() {
	typename vector <No<N,A> *>::const_iterator it;
	for (it = nos.begin(); it!=nos.end(); it++)
		delete *it;
}

template <class N, class A>
int Grafo<N,A>::numNos() const {
	return nos.size();
}

template <class N, class A>
int Grafo<N,A>::numArestas() const {
	int total = 0;
	for (size_t i = 0; i < nos.size(); i++)
		total += (*nos[i]).arestas.size();
	return total;
}

template <class N, class A>
Grafo<N, A> & Grafo<N,A>::inserirNo(const N &dados) {
	for (size_t i = 0; i < nos.size(); i++) {
		if ((*nos[i]).info == dados)
			throw NoRepetido<N>(dados);
	}
	No<N,A> * newNode = new No<N,A>(dados);
	nos.push_back(newNode);
	return *this;
}


template <class N, class A>
Grafo<N, A> & Grafo<N, A>::inserirAresta(const N &inicio, const N &fim, const A &val) {
	No<N,A> * start = NULL;
	No<N,A> * end = NULL;

	for (size_t i = 0; i < nos.size(); i++)
		if ((*nos[i]).info == inicio) start = nos[i];
		else if ((*nos[i]).info == fim) end = nos[i];

	if (start == NULL) throw NoInexistente<N>(inicio);
	if (end == NULL) throw NoInexistente<N>(fim);

	for (auto it = start->arestas.begin(); it != start->arestas.end(); it++) {
		if (it->destino == end) throw ArestaRepetida<N>(inicio, fim);
	}

	Aresta<N, A> ar (end, val);
	start->arestas.push_back(ar);
	return *this;
}

template <class N, class A>
A & Grafo<N, A>::valorAresta(const N &inicio, const N &fim) {
	No<N,A> * start = NULL;
	No<N,A> * end = NULL;
	Aresta<N,A> * edge = NULL;

	for (size_t i = 0; i < nos.size(); i++) {
		if ((*nos[i]).info == inicio) start = nos[i];
		if ((*nos[i]).info == fim) end = nos[i];
	}

	if (start == NULL) throw NoInexistente<N>(inicio);
	if (end == NULL) throw NoInexistente<N>(fim);

	for (auto it = start->arestas.begin(); it != start->arestas.end(); it++)
		if (it->destino == end) edge = &(*it);

	if (edge == NULL) throw ArestaInexistente<N>(inicio, fim);

	return edge->valor;
}

template <class N, class A>
Grafo<N,A> & Grafo<N,A>::eliminarAresta(const N &inicio, const N &fim) {
	No<N,A> * start = NULL;
	No<N,A> * end = NULL;
	int index = -1;

	for (size_t i = 0; i < nos.size(); i++) {
		if ((*nos[i]).info == inicio) start = nos[i];
		if ((*nos[i]).info == fim) end = nos[i];
	}

	if (start == NULL) throw NoInexistente<N>(inicio);
	if (end == NULL) throw NoInexistente<N>(fim);


	for (size_t i = 0; i < start->arestas.size(); i++) {
		if (start->arestas[i].destino == end)
			index = i;
	}

	if (index == -1) throw ArestaInexistente<N>(inicio, fim);

	start->arestas.erase(start->arestas.begin()+index);
	return *this;
}

template <class N, class A>
void Grafo<N,A>::imprimir(std::ostream &os) const {
	for (const auto & node: nos) {
		os << "( " << node->info;
		for (const auto & edge: node->arestas) {
			os << "[ " << edge.destino->info << " " << edge.valor << "] ";
		}
		os << ") ";
	}
}


template <class N, class A>
std::ostream & operator<<(std::ostream &out, const Grafo<N,A> &g) {
	g.imprimir(out);
	return out;
}

