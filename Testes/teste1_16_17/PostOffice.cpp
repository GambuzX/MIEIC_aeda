/*
 * PostOffice.cpp
 */

#include "PostOffice.h"
#include <string>

PostOffice::PostOffice(string firstZCode, string lastZCode):
								firstZipCode(firstZCode), lastZipCode(lastZCode)
{}
PostOffice::PostOffice() {}

void PostOffice::addMailToSend(Mail *m) {
	mailToSend.push_back(m);
}

void PostOffice::addMailToDeliver(Mail *m) {
	mailToDeliver.push_back(m);
}

void PostOffice::addPostman(const Postman &p){
	postmen.push_back(p);
}

vector<Mail *> PostOffice::getMailToSend() const {
	return mailToSend;
}

vector<Mail *> PostOffice::getMailToDeliver() const {
	return mailToDeliver;
}

vector<Postman> PostOffice::getPostman() const {
	return postmen;
}

vector<Mail *> PostOffice::removePostman(string name) {
	vector<Mail *> mail;
	for (size_t i = 0; i < postmen.size(); i++)
		if (postmen.at(i).getName() == name) {
			mail = postmen.at(i).getMail();
			postmen.erase(postmen.begin()+i);
			break;
		}
	return mail;
}


vector<Mail *> PostOffice::endOfDay(unsigned int &balance) {
	balance = 0;
	vector<Mail *> retVec;
	for (const auto & mail : mailToSend) {
		balance += mail->getPrice();
		if (mail->getZipCode() >= firstZipCode && mail->getZipCode() <= lastZipCode)
			addMailToDeliver(mail);
		else
			retVec.push_back(mail);
	}
	mailToSend.clear();
	return retVec;
}


Postman PostOffice::addMailToPostman(Mail *m, string name) {
	int index = -1;
	for (size_t i = 0 ; i < postmen.size(); i++)
		if (postmen.at(i).getName() == name)
			index = i;

	if (index == -1) throw NoPostmanException(name);
	postmen.at(index).addMail(m);
	return postmen.at(index);
}
