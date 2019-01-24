#include <queue>
#include <cstdlib>
#include "Balcao.h"
#include <random>

using namespace std;


Cliente::Cliente() {
	numPresentes = rand() % 5 + 1;
}


int Cliente::getNumPresentes() const {
	return numPresentes;
}


Balcao::Balcao(int te): tempo_embrulho(te) {
	tempo_atual = 0;
	prox_chegada = rand() % 20 + 1;
	prox_saida = 0;
	clientes_atendidos = 0;
}      


void Balcao:: proximoEvento()
{
	if (clientes.empty() || prox_chegada < prox_saida) {
		tempo_atual = prox_chegada;
		chegada();
	}
	else {
		tempo_atual = prox_saida;
		saida();
	}
}


void Balcao::chegada()
{
	Cliente cl = Cliente();
	clientes.push(cl);
	prox_chegada = rand() % 20 + 1;

	if (clientes.size() == 1)
		prox_saida = tempo_atual + cl.getNumPresentes() * tempo_embrulho;

	cout << "tempo= " << tempo_atual << "'\nchegou novo cliente com " << cl.getNumPresentes() << " presentes" << endl;
}   


void Balcao::saida()
{
	Cliente cl = getProxCliente();
	clientes.pop();
	clientes_atendidos++;

	if (clientes.size() == 0) prox_saida = tempo_atual;
	else prox_saida = tempo_atual + clientes.front().getNumPresentes() * tempo_embrulho;

	cout << "tempo= " << tempo_atual << "'\nsaiu cliente com " << cl.getNumPresentes() << " presentes" << endl;
}


int Balcao::getTempoAtual() const { return tempo_atual; }


int Balcao::getProxChegada() const { return prox_chegada; }


ostream & operator << (ostream & out, const Balcao & b1)
{
	cout << "Numero de clientes atendidos: " << b1.clientes_atendidos << ", Numero de clientes em espera: " << b1.clientes.size() << endl;

    return out;
}


int Balcao::getTempoEmbrulho() const {
	return tempo_embrulho;
}


int Balcao::getProxSaida() const {
	return prox_saida;
}


int Balcao::getClientesAtendidos() const {
	return clientes_atendidos;
}


Cliente & Balcao::getProxCliente() {
	if (clientes.empty()) throw FilaVazia();
	return clientes.front();
}

