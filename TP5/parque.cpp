#include "parque.h"
#include "insertionSort.h"
#include "sequentialSearch.h"
#include <vector>

using namespace std;


ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli):
	lotacao(lot), numMaximoClientes(nMaxCli) {
    numClientes = 0;
    vagas=lot; 
}

ParqueEstacionamento::~ParqueEstacionamento() {}

vector<InfoCartao> ParqueEstacionamento::getClientes() const { return clientes; }


bool ParqueEstacionamento::adicionaCliente(const string & nome)
{
 	if ( numClientes == numMaximoClientes ) return false;
	if ( posicaoCliente(nome) != -1 ) return false;
	InfoCartao info;
	info.nome = nome;
    info.presente = false;
    info.frequencia = 0;  // a fazer
	clientes.push_back(info);
	numClientes++;
	return true;
}
 
bool ParqueEstacionamento::retiraCliente(const string & nome)
{
	for (vector<InfoCartao>::iterator it = clientes.begin(); it != clientes.end(); it++)
		if ( it->nome == nome ) {
			if ( it->presente == false ) {
				clientes.erase(it);
				numClientes--;
				return true;
			}
			else return false;
		}
	return false;
}
  
unsigned int ParqueEstacionamento::getNumLugares() const
{
	return lotacao;
}
                   
unsigned int ParqueEstacionamento::getNumLugaresOcupados() const
{
	return lotacao-vagas;
}

int ParqueEstacionamento::getFrequencia(const string &nome) const {
	int index = posicaoCliente(nome);
	if (index == -1) throw ClienteNaoExistente(nome);
	return clientes[index].frequencia;
}

bool ParqueEstacionamento::entrar(const string & nome)
{
	if ( vagas == 0 ) return false;
	int pos = posicaoCliente(nome);
	if ( pos == -1 ) return false;
	if ( clientes[pos].presente == true ) return false;
	clientes[pos].frequencia++;
	clientes[pos].presente = true;
	vagas--;
	return true;
}

bool ParqueEstacionamento::sair(const string & nome)
{
	int pos = posicaoCliente(nome);
	if ( pos == -1 ) return false;
	if ( clientes[pos].presente == false ) return false;
	clientes[pos].presente = false;
	vagas++;
	return true;
}

int ParqueEstacionamento::posicaoCliente(const string & nome) const {
	InfoCartao ic;
	ic.nome = nome;
	return sequentialSearch(clientes, ic);
}

void ParqueEstacionamento::ordenaClientesPorFrequencia() {
	insertionSort(clientes);
}

void ParqueEstacionamento::ordenaClientesPorNome() {
	for(unsigned int j=clientes.size()-1; j>0; j--){
		bool troca=false;
		for(unsigned int i = 0; i<j; i++)
			if(clientes[i+1].nome < clientes[i].nome) {
				swap(clientes[i],clientes[i+1]);
				troca = true;
			}
		if (!troca) return;
	}
}

vector<string> ParqueEstacionamento::clientesGamaUso(int n1, int n2) {
	vector<InfoCartao> v = clientes;
	vector<string> nomes;
	insertionSort(v);

	for (size_t i = 0; i < v.size(); i++)
		if (v.at(i).frequencia >= n1 && v.at(i).frequencia <= n2)
			nomes.push_back(v.at(i).nome);
	return nomes;
}

InfoCartao ParqueEstacionamento::getClienteAtPos(vector<InfoCartao>::size_type p) const {
	if (p > clientes.size()-1) throw PosicaoNaoExistente(p);
	return clientes.at(p);
}

bool InfoCartao::operator==(const InfoCartao &ic1) const { return ic1.nome == nome; }
bool InfoCartao::operator<(const InfoCartao &ic1) const {
	if (ic1.frequencia == frequencia) {
		return  nome < ic1.nome;
	}
	return ic1.frequencia < frequencia;
}

ostream & operator<<(ostream & os, const ParqueEstacionamento & pe) {
	for (const auto &cl : pe.clientes) {
		os << cl.nome << " " << cl.frequencia;
		if (cl.presente) os << " - Present" << endl;
		else os << " - Not Present" << endl;
	}
	return os;
}

