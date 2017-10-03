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
		virtual ItemType extractByValue( const ItemType value ) ;
		virtual ItemType extractByIndex( const Pos position ) ;
		virtual ItemType extractFirst( void ) ;
		virtual ItemType extractLast( void ) ;
		virtual bool replace( const ItemType valueOut, ItemType valueIn ) ;
		// capacity and info functions
		virtual bool isEmpty( void ) ;
		virtual size listSize( void ) ;
		virtual Pos indexOf( const ItemType value ) ;
		virtual bool contained( const ItemType value ) ;
		// manage functions
		virtual void emptyList( void ) ;
		virtual void cleanRepeated( void ) ;
        virtual void allocPtr( void ) ;
};

template <class ItemType>
IList<ItemType>* factoryList( void ){
	IList<ItemType>* toReturn = new DOList<ItemType> ;
    toReturn->allocPtr() ;
	return toReturn ;
}

#endif
