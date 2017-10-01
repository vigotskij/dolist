#ifndef DOLIST_H
	#include "dolist.h"
#endif
//PRIVATE:
template <class ItemType>
Pos DOList<ItemType>::_indexOf_( const ItemType value ) {
	Pos pos = -1 ;
	if( !isEmpty() ) {
		Node *actual = first ;
		if( contained( value ) ) {
			for( ;
				actual != nullptr && actual->value != value ;
				actual = actual->next ){
				pos++ ;
			}
			if( actual->value == value ) pos++ ;
		}
	}
	return  pos ;
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
void DOList<ItemType>::insert( const ItemType value ){
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
bool DOList<ItemType>::replace( const ItemType valueOut, const ItemType valueIn ) {
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
	return _indexOf_( value ) ;
}
template <class ItemType>
bool DOList<ItemType>::contained( const ItemType value ) {
	Node *actual = first ;
	for( ;
		actual != nullptr && actual->value != value ;
		actual = actual->next ) ;
	ItemType toCompare ;
	if( actual == nullptr ) toCompare = NULL ;
	if ( actual!= nullptr ) toCompare = actual->value ;
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

template class DOList<int> ;
template class DOList<char*>;
