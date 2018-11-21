/*
 * Purchase.cpp
 *
 *  Created on: Nov 16, 2016
 *      Author: hlc
 */

#include "Purchase.h"

using namespace std;

Purchase::Purchase(long cli) : client (cli) {
}

long Purchase::getClient() const {
	return client;
}

list< stack<Article*> > Purchase::getBags() const {
	return bags;
}

/**
 * Create an Article associated with the client of this purchase.
 */
Article* Purchase::createArticle(long barCode, bool present, bool deliverHome) {

	Article * art = new Article(client, barCode);
	art->setPresent(present);
	art->setDeliverHome(deliverHome);

	return art;

}

/**
 * Add an Article to the bags of this purchase. A new bag is added when the last bag is full.
 */
void Purchase::putInBag(Article* article) {

	bool inserted = false;
	for (auto & bag : bags) {
		if (bag.size() < Purchase::BAG_SIZE) {
			inserted = true;
			bag.push(article);
		}
	}
	if (!inserted) {
		stack<Article*> newBag;
		newBag.push(article);
		bags.push_back(newBag);
	}

}

/**
 * Pop from the bags all articles that are presents.
 * All other articles are pushed back into the bags where they were, maintaining order.
 */
vector<Article*> Purchase::popPresents() {
	vector<Article*> presents;

	for (auto & bag : bags) {
		list<Article*> temp;
		while(bag.size() > 0) {
			if(bag.top()->getPresent()) {
				presents.push_back(bag.top());
			}
			else {
				temp.push_back(bag.top());
			}
			bag.pop();
		}
		list<Article*>::reverse_iterator it;
		for (it = temp.rbegin(); it != temp.rend(); it++) bag.push(*it);
	}

	return presents;

}

