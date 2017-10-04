#ifndef DOLIST_H
	#include "dolist.h"
#endif

//PRIVATE:
template <class ItemType>
Pos DOList<ItemType>::_indexOf_( const ItemType value ) {
	Pos tr = -1 ;
	if( !isEmpty() ){
		Node *current = first ;
		Pos position = 0 ;
		for( ;
			current != nullptr && current->value != value ;
			current = current->next ) {
				position++ ;
		}
		if( current != nullptr && current->value == value ) tr = position ;
	}
	return  tr ;
}

//PUBLIC:
//constr&dest
template <class ItemType>
DOList<ItemType>::DOList( void ){
	first, last = nullptr ;
	itemCount = 0 ;
}
template <class ItemType>
DOList<ItemType>::~DOList( void ){
	emptyList() ;
	if ( first ) delete first ;
	if ( last ) delete last ;
}

// adding, deleting and replacing functions
template <class ItemType>
void DOList<ItemType>::insert( ItemType value ){
	if( !contained( value ) ) {
		Node *newNode = new Node ;
		newNode->value = value ;


		Node *nextNode = _sortItem_( value ) ;

		if( nextNode != nullptr ) {
			newNode->prev = nextNode->prev ;
			newNode->next = nextNode ;

			nextNode->prev = newNode ;
		} else {
			if( first == nullptr ) {
				first = newNode ;
				last = newNode ;
			} else if ( first == last && first != nullptr ) {
				newNode->prev = first ;
				newNode->next = nullptr ;
				first->next = newNode ;

				last = newNode ;
			} else if ( first != last ) {
				newNode->prev = last ;
				newNode->next = nullptr ;

				last = newNode ;
			}
		}
		itemCount++ ;
	}
}
template <class ItemType>
ItemType DOList<ItemType>::extractByValue( const ItemType value ) {
	ItemType tr = NULL ;
	if( !isEmpty() ){
		Node *toExtract = _findNode_( value ) ;
		if( toExtract != nullptr ) {
			tr = toExtract->value ;
			itemCount-- ;
		}

	}
	return tr ;
}
template <class ItemType>
ItemType DOList<ItemType>::extractByIndex( const Pos position ) {
	ItemType tr = NULL ;
	if( !isEmpty() ){
		Node *toExtract = _findNodeByIndex_( position ) ;
		tr = toExtract->value ;
	}
	return tr ;
}
template <class ItemType>
ItemType DOList<ItemType>::extractFirst( void ) {
	ItemType tr = NULL ;
	if( !isEmpty() ) {
		Node *temp = first ;

		if( temp != nullptr ) {
			first->prev = nullptr ;
			first = first->next ;
			tr = temp->value ;
		} else {
			;
		}

		delete temp ;
		itemCount-- ;
	}

	return tr ;
}
template <class ItemType>
ItemType DOList<ItemType>::extractLast( void ) {
	ItemType tr = NULL ;
	if (!isEmpty() ) {
		Node *temp = last ;
		last = last->prev ;
		last->next = nullptr ;

		tr = temp->value ;

		delete temp ;
		itemCount-- ;
	}
	return tr ;
}
template <class ItemType>
bool DOList<ItemType>::replace( const ItemType valueOut, ItemType valueIn ) {
	bool tr = false ;
	if( contained( valueOut ) ) {
		extractByValue( valueOut ) ;
		insert( valueIn ) ;
		tr = true ;
	}
	return tr ;
}

// capacity and info functions
template <class ItemType>
bool DOList<ItemType>::isEmpty( void ) {
	return itemCount == 0 ;
}
template <class ItemType>
size DOList<ItemType>::listSize( void ) {
	return itemCount ;
}
template <class ItemType>
Pos DOList<ItemType>::indexOf( const ItemType value ) {
	Pos tr = -1 ;
	if( !isEmpty() ) tr = _indexOf_( value ) ;
	return tr ;
}
template <class ItemType>
bool DOList<ItemType>::contained( const ItemType value ) {
	Node *current = first ;
	for( ;
		current != nullptr && current->value != value ;
		current = current->next ) ;
	ItemType toCompare ;
	if( current == nullptr ) toCompare = NULL ;
	if( current != nullptr ) toCompare = current->value ;
	return toCompare == value ;
}
// manage functions
template <class ItemType>
void DOList<ItemType>::emptyList( void ) {
	while( !isEmpty() ) {
		extractLast() ;
	}
}
template <class ItemType>
void DOList<ItemType>::cleanRepeated( void ) { }
template <class ItemType>
void DOList<ItemType>::allocPtr( void ) { }

//
// TEMPLATE SPECIALIZATIONS
//
template class DOList<char*>;
template<>
class DOList<char*>: public IList<char*> {
	private:
		struct Node{
			char *value ;

			Node *next ;
			Node *prev ;

			Node( void ){
				value, next, prev = nullptr ;

			}
			~Node( void ) { } ;

			private:
				Node( const Node &otherNode ) ;
				Node& operator= ( const Node &otherNode ) ;
		} ;

		Node *first , *last ;

		size itemCount ;

		// helpers
		Pos _indexOf_( const char *value ) {
			Pos tr = -1 ;
			if( !isEmpty() ){
				Node *current = first ;
				Pos position = 0 ;
				for( ;
					current != nullptr && *current->value != *value ;
					current = current->next ) {
						position++ ;
				}
			if( current != nullptr && *current->value == *value ) tr = position ;
			}
			return  tr ;
		}
		Node* _findNode_( const char* value ) {
			Node *found = nullptr ;
			if( !isEmpty() ){
				Node *current = first ;
				for( ;
					 current != nullptr && *current->value != *value ;
					 current = current->next ) ;
						found = current ;
			}
			return found ;
		}
		Node* _findNodeByIndex_ ( const Pos position ){
			Pos count = 0 ;
			Node *current = first ;
			Node *found = nullptr ;
			for (;
				current != nullptr ;
				current = current->next ){
				if( position == count ) found = current ;
				count++ ;
			}
			return found ;
		}

		Node* _sortItem_( char *value ) {
			Node *current = nullptr ;
			if( !isEmpty()){
				current = first ;
				for( ;
					 current != nullptr && *current->value < *value ;
					 current = current->next ) ;
			}
			return current ;
		}
		// copy constructor ;
		DOList(const DOList &otherList ) ;
		// operator=
		DOList& operator=( const DOList& otherList ) ;


 public:
	//constr&dest
	DOList( void ){
		first, last = nullptr ;
		itemCount = 0 ;
	}
	~DOList( void ){
		emptyList() ;
		if ( first ) delete first ;
		if ( last ) delete last ;
	}

	// adding, deleting and replacing functions
	void insert( char *value ){
		if( !contained( value ) ) {
			Node *newNode = new Node ;
			newNode->value = value ;

			Node *nextNode = _sortItem_( value ) ;

			if( nextNode != nullptr ) {
				newNode->prev = nextNode->prev ;
				newNode->next = nextNode ;

				nextNode->prev = newNode ;
			} else {
				if( first == nullptr ) {
					first = newNode ;
					last = newNode ;
				} else if ( first == last && first != nullptr ) {
					newNode->prev = first ;
					newNode->next = nullptr ;
					first->next = newNode ;

					last = newNode ;
				} else if ( first != last ) {
					newNode->prev = last ;
					newNode->next = nullptr ;

					last = newNode ;
				}
			}
			itemCount++ ;
		}
	}
	char* extractByValue( const char *value ) {
		char *tr = NULL ;
		if( !isEmpty() ){
			Node *toExtract = _findNode_( value ) ;
			if( toExtract != nullptr ) {
				tr = toExtract->value ;
				itemCount-- ;
			}

		}
		return tr ;
	}
	char* extractByIndex( const Pos position ) {
		char *tr = NULL ;
		if( !isEmpty() ){
			Node *toExtract = _findNodeByIndex_( position ) ;
			tr = toExtract->value ;
		}
		return tr ;
	}
	char* extractFirst( void ) {
		char *tr = NULL ;
		if( !isEmpty() ) {
			Node *temp = first ;

			if( temp != nullptr ) {
				first->prev = nullptr ;
				first = first->next ;
				tr = temp->value ;
			} else {
				;
			}

			delete temp ;
			itemCount-- ;
		}

		return tr ;
	}
	char* extractLast( void ) {
		char *tr = NULL ;
		if (!isEmpty() ) {
			Node *temp = last ;
			last = last->prev ;
			last->next = nullptr ;

			tr = temp->value ;

			delete temp ;
			itemCount-- ;
		}
		return tr ;
	}
	bool replace( const char *valueOut, char *valueIn ) {
		bool tr = false ;
		if( contained( valueOut ) ) {
			extractByValue( valueOut ) ;
			insert( valueIn ) ;
			tr = true ;
		}
		return tr ;
	}

	// capacity and info functions
	bool isEmpty( void ) {
		return itemCount == 0 ;
	}
	size listSize( void ) {
		return itemCount ;
	}
	Pos indexOf( const char *value ) {
		return _indexOf_( value ) ;
	}
	bool contained( const char *value ) {
		Node *current = first ;
		for( ;
			current != nullptr && *current->value != *value ;
			current = current->next ) ;
		char *toCompare ;
		if( current == nullptr ) toCompare = NULL ;
		if ( current != nullptr ) toCompare = current->value ;
		return *toCompare == *value ;
	}
	// manage functions
	void emptyList( void ) {
		while( !isEmpty() ) {
			extractLast() ;
		}
	}
	void cleanRepeated( void ) { }
	void allocPtr( void ) { }
} ;
