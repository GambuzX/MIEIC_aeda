/*
 * Postman.h
 */

#ifndef SRC_POSTMAN_H_
#define SRC_POSTMAN_H_

#include "Mail.h"
#include <string>
#include <vector>

class Postman {
	static int currID;
	unsigned int id;
	string name;
	vector<Mail *> myMail;
public:
	Postman();
	Postman(string name);
	void setName(string nm);
	void addMail(Mail *m);
	void addMail(vector<Mail *> mails);
	string getName() const;
	vector<Mail *> getMail() const;
	unsigned int getID() const;
	bool operator<(const Postman &) const;
};

class NoPostmanException {
	string name;
public:
	NoPostmanException(string n) { name = n; }
	string getName() const { return name; }
};


#endif /* SRC_POSTMAN_H_ */
