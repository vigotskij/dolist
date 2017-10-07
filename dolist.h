#ifndef DOLIST_H

#define DOLIST_H

#ifndef ILIST_H
	#include "ilist.h"
#endif

#define nullptr 0
#define NULL 0

template <class ItemType>
class DOList: public IList<ItemType>{
	private:
		struct Node{
			ItemType value ;

			Node *next ;
			Node *prev ;

			Node( void ){
				value = nullptr ;
				next, prev = nullptr ;

			}
			~Node( void ) { } ;

			private:
				Node( const Node &otherNode ) ;
				Node& operator= ( const Node &otherNode ) ;

		};

		Node *first ;
		Node *last ;

		size itemCount ;

		// helpers
		Pos _indexOf_( const ItemType value ) ;

		Node* _findNode_( const ItemType value ) {
			Node *found = nullptr ;
			if( !isEmpty() ){
				Node *current = first ;
				for( ;
					 current != nullptr && current->value != value ;
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

		Node* _sortItem_( const ItemType value ) {
			Node *current = nullptr ;
			if( !isEmpty()){
				current = first ;
				for( ;
					 current != nullptr && current->value < value ;
					 current = current->next ) ;
			}

			return current;
		}
		// copy constructor ;
		DOList(const DOList &otherList ) ;
		// operator=
		DOList& operator=( const DOList& otherList ) ;

		void sortItem( ItemType value ) ;
	public:
		//const&dest
		DOList( void ) ;
		~DOList( void ) ;
		// adding, deleting and replacing functions
		virtual void insert( ItemType value ) ;
		virtual ItemType extractByValue( ItemType value ) ;
		virtual ItemType extractByIndex( Pos position ) ;
		virtual ItemType extractFirst( void ) ;
		virtual ItemType extractLast( void ) ;
		virtual bool replace( ItemType valueOut, ItemType valueIn ) ;
		// capacity and info functions
		virtual bool isEmpty( void ) ;
		virtual size listSize( void ) ;
		virtual Pos indexOf( ItemType value ) ;
		virtual bool contained( ItemType value ) ;
		// manage functions
		virtual void emptyList( void ) ;
		virtual void cleanRepeated( void ) ;
		virtual void allocPtr( void ) ;
};

//PRIVATE:
template <class ItemType>
Pos DOList<ItemType>::_indexOf_( ItemType value ) {
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
ItemType DOList<ItemType>::extractByValue( ItemType value ) {
	ItemType tr = NULL ;
	if( !isEmpty() ){
		Node *toExtract = _findNode_( value ) ;
		if( toExtract != nullptr ){
			tr = toExtract->value ;
			if( toExtract != first && toExtract != last ){
				Node *prev = toExtract->prev ;
				Node *next = toExtract->next ;

				prev->next = next ;
				next->prev = prev ;
			} else if( toExtract == first ){
				first = toExtract->next ;
				Node *next = toExtract->next ;
				if( next != nullptr ) next->prev = nullptr ;
			} else if( toExtract == last ) {
				last = toExtract->prev ;
				Node *prev = toExtract->prev ;
				if( prev != nullptr ) prev->next = nullptr ;
			}
			delete toExtract ;
			itemCount-- ;
		}
	}
	return tr ;
}
template <class ItemType>
ItemType DOList<ItemType>::extractByIndex( Pos position ) {
	ItemType tr = NULL ;
	if( !isEmpty() ){
		Node *toExtract = _findNodeByIndex_( position ) ;
		if( toExtract != nullptr ){
			tr = toExtract->value ;
			if( toExtract != first && toExtract != last ){
				Node *prev = toExtract->prev ;
				Node *next = toExtract->next ;

				prev->next = next ;
				next->prev = prev ;
			} else if( toExtract == first ){
				first = toExtract->next ;
				Node *next = toExtract->next ;
				if( next != nullptr ) next->prev = nullptr ;
			} else if( toExtract == last ) {
				last = toExtract->prev ;
				Node *prev = toExtract->prev ;
				if( prev != nullptr ) prev->next = nullptr ;
			}
			delete toExtract ;
			itemCount-- ;
		}
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
bool DOList<ItemType>::replace( ItemType valueOut, ItemType valueIn ) {
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
Pos DOList<ItemType>::indexOf( ItemType value ) {
	Pos tr = -1 ;
	if( !isEmpty() ) tr = _indexOf_( value ) ;
	return tr ;
}
template <class ItemType>
bool DOList<ItemType>::contained( ItemType value ) {
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


template <class ItemType>
IList<ItemType>* factoryList( void ){
	IList<ItemType>* toReturn = new DOList<ItemType> ;
	toReturn->allocPtr() ;
	return toReturn ;
}
#endif
