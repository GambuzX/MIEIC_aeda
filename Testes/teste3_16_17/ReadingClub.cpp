/*
 * ReadingClub.cpp
 *
 *  Created on: 11/12/2016
 *      Author: RRossetti
 */

#include "ReadingClub.h"

ReadingClub::ReadingClub(): catalogItems(BookCatalogItem("", "", 0)) {
	//do nothing!
}

ReadingClub::ReadingClub(vector<Book*> books): catalogItems(BookCatalogItem("", "", 0)) {
	this->books = books;
}

void ReadingClub::addBook(Book* book) {
	this->books.push_back(book);
}

void ReadingClub::addBooks(vector<Book*> books) {
	this->books = books;
}

vector<Book*> ReadingClub::getBooks() const{
	return this->books;
}

BookCatalogItem ReadingClub::getCatalogItem(string title, string author) {
	BookCatalogItem itemNotFound("", "", 0);
	BSTItrIn<BookCatalogItem> it(catalogItems);
	while (!it.isAtEnd())
	{
		if( it.retrieve().getTitle() == title && it.retrieve().getAuthor() == author) {
			BookCatalogItem bci(it.retrieve().getTitle(), it.retrieve().getAuthor(), 0);
			bci.setItems(it.retrieve().getItems());
			return bci;
		}
		it.advance();
	}
	return itemNotFound;
}

void ReadingClub::addCatalogItem(Book* book) {
	BookCatalogItem itemNotFound("", "", 0);
	BookCatalogItem bci(book->getTitle(), book->getAuthor(), book->getYear());
	BookCatalogItem bciX = catalogItems.find(bci);
	if(bciX == itemNotFound) {
		bci.addItems(book);
		this->catalogItems.insert(bci);
	}
	else {
		this->catalogItems.remove(bciX);
		bciX.addItems(book);
		this->catalogItems.insert(bciX);
	}
	books.push_back(book);
}

BST<BookCatalogItem> ReadingClub::getCatalogItems() const {
	return this->catalogItems;
}

vector<UserRecord> ReadingClub::getUserRecords() const {
	vector<UserRecord> records;
	HashTabUserRecord::const_iterator it1 = this->userRecords.begin();
	HashTabUserRecord::const_iterator it2 = this->userRecords.end();
	for(; it1 != it2; it1++) {
			records.push_back(*it1);
	}
	return records;
}

void ReadingClub::setUserRecords(vector<UserRecord>& urs) {
	for(unsigned i = 0; i < urs.size(); i++) userRecords.insert(urs[i]);
}

priority_queue<User> ReadingClub::getBestReaderCandidates() const {
	return readerCandidates;
}
void ReadingClub::setBestReaderCandidates(priority_queue<User>& candidates) {
	readerCandidates = candidates;
}



//
// TODO: Part I   - BST
//

void ReadingClub::generateCatalog() {

	vector<BookCatalogItem> items;

	for (unsigned i = 0 ; i < books.size(); i++) {
		Book currBook = *books.at(i);

		bool newItem = true;
		for (unsigned j = 0; j < items.size(); j++) {
			for (unsigned k = 0; k < items.at(j).getItems().size(); k++) {
				Book cmp = *(items.at(j).getItems().at(k));
				if (cmp.getTitle() == currBook.getTitle() && cmp.getAuthor() == currBook.getAuthor()){
					items.at(j).addItems(books.at(i));
					newItem = false;
					break;
				}
			}
		}

		if (!newItem) continue;
		items.push_back(BookCatalogItem(currBook.getTitle(), currBook.getAuthor(), 1));
		items[items.size()-1].addItems(books.at(i));
	}

	for (unsigned i = 0 ; i < items.size(); i++) {
		catalogItems.insert(items.at(i));
	}

}

vector<Book*> ReadingClub::getAvailableItems(Book* book) const {
	vector<Book*> temp;

	BSTItrIn<BookCatalogItem> it(catalogItems);
	while (!it.isAtEnd()) {
		BookCatalogItem & curr = it.retrieve();

		if (curr.getTitle() == book->getTitle() && curr.getAuthor() == book->getAuthor()) {
			for (unsigned i = 0; i < curr.getItems().size(); i++)
				if (curr.getItems().at(i)->getReader() == 0)
					temp.push_back(curr.getItems().at(i));
		}

		it.advance();
	}

	return temp;
}

bool ReadingClub::borrowBookFromCatalog(Book* book, User* reader) {
	//TODO:
	//...

	return false;
}


//
// TODO: Part II  - Hash Table
//

void ReadingClub::addUserRecord(User* user) {
	//TODO:
	//...

}

void ReadingClub::changeUserEMail(User* user, string newEMail) {
	//TODO:
	//...

}


//
// TODO: Part III - Priority Queue
//

void ReadingClub::addBestReaderCandidates(const vector<User>& candidates, int min) {
	//TODO:
	//...

}

int ReadingClub::awardReaderChampion(User& champion) {
	//TODO:
	//...

	return 0;
}
























