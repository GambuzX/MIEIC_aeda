#include "Parque.h"
#include <vector>

using namespace std;

ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli): lotacao(lot), numMaximoClientes(nMaxCli) {
	vagas = lot;
}

unsigned int ParqueEstacionamento::getNumLugares() const {
	return lotacao;
}

unsigned int ParqueEstacionamento::getNumMaximoClientes() const {
	return numMaximoClientes;
}

int ParqueEstacionamento::posicaoCliente(const string &nome) const {
	int index = -1;
	for (unsigned i = 0; i < clientes.size(); i++)
		if (clientes[i].nome == nome)
			index = i;
	return index;
}

bool ParqueEstacionamento::adicionaCliente(const string & nome) {
	bool success = false;
	if (posicaoCliente(nome) == -1 && clientes.size() < numMaximoClientes) {
		InfoCartao newCard;
		newCard.nome = nome;
		newCard.presente = false;
		clientes.push_back(newCard);
		success=true;
	}
	return success;
}

bool ParqueEstacionamento::entrar(const string & nome) {
	vector<InfoCartao>::iterator it;
	for (it = clientes.begin(); it != clientes.end(); it++) {
		if (it->nome == nome) {
			if (!it->presente && vagas > 0) {
				it->presente = true;
				vagas--;
				return true;
			}
			else return false;
		}
	}
	return false;
}

bool ParqueEstacionamento::retiraCliente(const string & nome) {
	vector<InfoCartao>::iterator it;
	for (it = clientes.begin(); it != clientes.end(); it++) {
		if (it->nome == nome) {
			if (!it->presente){
				clientes.erase(it);
				return true;
			}
			else {
				return false;
			}
		}
	}
	return false;
}

bool ParqueEstacionamento::sair(const string & nome) {
	vector<InfoCartao>::iterator it;
	for (it = clientes.begin(); it != clientes.end(); it++) {
		if (it->nome == nome) {
			if (it->presente) {
				it->presente = false;
				vagas++;
				return true;
			}
			else return false;
		}
	}
	return false;
}

unsigned int ParqueEstacionamento::getNumLugaresOcupados() const {
	return lotacao-vagas;
}

unsigned int ParqueEstacionamento::getNumClientesAtuais() const {
	return clientes.size();
}
