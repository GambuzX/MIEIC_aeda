/*
 * Postman.cpp
 */
#include "Postman.h"

template <class N>
extern unsigned int numberDifferent(const vector<N> &);

Postman::Postman(): id(0) {}

Postman::Postman(string n) {
	name = n;
	id = currID;
	currID++;
}

int Postman::currID = 1;

void Postman::setName(string nm){
	name = nm;
}

string Postman::getName() const{
	return name;
}

vector<Mail *> Postman::getMail() const {
	return myMail;
}

void Postman::addMail(Mail *m) {
	myMail.push_back(m);
}

void Postman::addMail(vector<Mail *> mails) {
	myMail.insert(myMail.end(),mails.begin(),mails.end());
}

unsigned int Postman::getID() const{
	return id;
}

bool Postman::operator<(const Postman &postman) const {
	int n1, n2;
	vector<string> zipCodes;
	for (const auto & mail : myMail)
		zipCodes.push_back(mail->getZipCode());
	n1 = numberDifferent(zipCodes);

	zipCodes.clear();

	for (const auto & mail : postman.getMail())
		zipCodes.push_back(mail->getZipCode());
	n2 = numberDifferent(zipCodes);

	return n1 < n2;
}


