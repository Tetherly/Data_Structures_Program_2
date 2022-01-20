// Created by Tyler Starling on 6/2/2021.
// COP 4530
// Assignment 2
// Many of these functions were written using the assistance of the ch3_list powerpoint provided by Bob Myers.

#include <iostream>
#include <initializer_list>
#include "List.h"

using namespace std;
using namespace cop4530;

/*
 *  List Class Function Definitions
 */

//  Default List Constructor
template <typename T>
List< T >::List(){
    init();
}

//  Copy Constructor
template <typename T>
List< T >::List(const List &rhs){
    init();
    for(auto & x : rhs){
        push_back(x);
    }
}

//  Move Constructor
template <typename T>
List< T >::List(List && rhs){
    theSize = rhs.theSize;
    head = rhs.head;
    tail = rhs.tail;

    rhs.theSize = 0;
    rhs.head = nullptr;
    rhs.tail = nullptr;
}

//  List Constructor that creates a number of nodes based on num param with data based on val param
template <typename T>
List< T >::List(int num, const T& val){
    init();
    for(int i = 0; i < num; i++){
        push_back(val);
    }
}

//  List Constructor that uses iterators for construction
template <typename T>
List< T >::List(const_iterator start, const_iterator end){
    init();
    while(start != end){
        push_back(start++.retrieve());
    }
}

//  Constructs with a copy of each of the elements in initializer list
template <typename T>
List< T >::List(initializer_list<T> iList){
    init();
    for(auto & x : iList){
        push_back(x);
    }
}

//  Destructor
template <typename T>
List< T >::~List(){
    clear();
    delete head;
    delete tail;
}

//  Copy Assignment Operator
template <typename T>
const List< T >& List< T >::operator=(const List &rhs){
    List newList = rhs;
    swap(*this, newList);
    return *this;
}

//  Move Assignment Operator
template <typename T>
List< T >& List< T >::operator=(List && rhs){
    swap(theSize, rhs.theSize);
    swap(head, rhs.head);
    swap(tail, rhs.tail);

    return *this;
}

//  Sets list to the elements of the initializer list
template <typename T>
List< T >& List< T >::operator=(initializer_list< T > iList){
    clear();
    for(auto & x : iList){
        push_back(x);
    }
    return *this;
}

//  Getter function for the size of the list
template <typename T>
int List< T >::size() const{
    return theSize;
}

//  Function to check if the list is empty
template <typename T>
bool List< T >::empty() const{
    return size() == 0;
}

//  Deletes all elements of the list
template <typename T>
void List< T >::clear(){
    while(!empty()){
        pop_front();
    }
}

//  Reverses the order of the elements in the list
template <typename T>
void List< T >::reverse(){
    //  Needs to switch prev nodes with next nodes and vice versa
    /*
    iterator itr = begin();
    while(itr != end()){
        Node * temp = itr.current->prev;
        itr.current->prev = itr.current->next;
        itr.current->next = temp;
        itr++;
    }
     */
}

//  Reference to the first element
template <typename T>
T& List< T >::front(){
    return *begin();
}

//  Const Reference to the first element
template <typename T>
const T& List< T >::front() const{
    return *begin();
}

//  Reference to the last element
template <typename T>
T& List< T >::back(){
    return *--end();
}

//  Const Reference to the last element
template <typename T>
const T& List< T >::back() const{
    return *--end();
}

//  Inserts at the beginning of the list
template <typename T>
void List< T >::push_front(const T & val){
    insert(begin(), val);
}

//  Move version of inserting at beginning of the list
template <typename T>
void List< T >::push_front(T && val){
    insert(begin(), move(val));
}

//  Inserts at the back of the list
template <typename T>
void List< T >::push_back(const T & val){
    insert(end(), val);
}

//  Move version of inserting at the back of the list
template <typename T>
void List< T >::push_back(T && val){
    insert(end(), move(val));
}

//  Deletes the first element in the list
template <typename T>
void List< T >::pop_front(){
    erase(begin());
}

//  Deletes the last element in the list
template <typename T>
void List< T >::pop_back(){
    erase(--end());
}

//  Removes all elements with the value given as parameter
template <typename T>
void List< T >::remove(const T &val){
    iterator itr = begin();
    while(itr != end()){
        if(itr.retrieve() == val){
            itr = erase(itr);
            itr--;
        }
        itr++;
    }
}

//  Removes all elements based on a specified predicate
template <typename T>
template <typename PREDICATE>
void List< T >::remove_if(PREDICATE pred){
    iterator itr = begin();
    while(itr != end()){
        if(pred(itr.retrieve())){
            itr = erase(itr);
            itr--;
        }
        itr++;
    }
}

//  Prints out all of the elements with a delimiter given as parameter
template <typename T>
void List< T >::print(ostream& os, char ofc) const{
    for(auto & x : *this){
        os << x << ofc;
    }
}

//  Returns an iterator to the first element in the list
template <typename T>
typename List< T >::iterator List< T >::begin(){
    return iterator(head->next);
}

//  Returns a const_iterator to the first element in the list
template <typename T>
typename List< T >::const_iterator List< T >::begin() const{
    return const_iterator(head->next);
}

//  Returns an iterator the last element in the list
template <typename T>
typename List< T >::iterator List< T >::end(){
    return iterator(tail);
}

//  Returns a const_iterator to the last element in the list
template <typename T>
typename List< T >::const_iterator List< T >::end() const{
    return const_iterator(tail);
}

//  Inserts the value ahead of the iterator
template <typename T>
typename List< T >::iterator List< T >::insert(iterator itr, const T& val){
    Node *p = itr.current;
    ++theSize;
    iterator retItr(p->prev = p->prev->next = new Node{val, p->prev, p});
    return retItr;
}

//  Move version of inserting the value ahead of the iterator
template <typename T>
typename List< T >::iterator List< T >::insert(iterator itr, T && val){
    Node *p = itr.current;
    ++theSize;
    return iterator(p->prev = p->prev->next = new Node{move(val), p->prev, p});
}

//  Deletes one element at the iterator
template <typename T>
typename List< T >::iterator List< T >::erase(iterator itr){
    Node *p = itr.current;
    iterator retVal(p->next);
    p->prev->next = p->next;
    p->next->prev = p->prev;
    delete p;
    --theSize;
    return retVal;
}

//  Deletes the elements specified in the iterator range
template <typename T>
typename List< T >::iterator List< T >::erase(iterator start, iterator end){
    for(iterator itr = start; itr != end;){
        itr = erase(itr);
    }
    return end;
}

template <typename T>
void List< T >::init(){
    theSize = 0;
    head = new Node;
    tail = new Node;
    head->next = tail;
    tail->prev = head;
}

/*
 *  Non-Class Overloads
 */

//  == Operator Overload for comparing two Lists
template <typename T>
bool operator==(const List< T > & lhs, const List< T > & rhs){

    List<T> dummyLHS = lhs;
    List<T> dummyRHS = rhs;

    if(dummyLHS.size() == dummyRHS.size()) {
        for(int i = 0; i < dummyLHS.size(); i++){
            if (dummyLHS.front() == dummyRHS.front()) {
                dummyLHS.pop_front();
                dummyRHS.pop_front();
            }else{
                return false;
            }
        }
        return true;
    }
    return false;
}

//  != Operator Overload for comparing two Lists
template <typename T>
bool operator!=(const List< T > & lhs, const List< T > & rhs){
    if(!(lhs == rhs)){
        return true;
    }
    return false;
}

//  << Operator Overload for outputting the contents of a list
template <typename T>
ostream & operator<<(ostream &os, const List< T > &l){
    l.print(os);
    return os;
}

/*
 *  Nested const_iterator Class Function Definitions
 */

//  Constructor for const_iterator
template <typename T>
List< T >::const_iterator::const_iterator(){
    current = nullptr;
}

//  Star overload for element return
template <typename T>
const T & List< T >::const_iterator::operator*() const{
    return retrieve();
}

//  Prefix increment operator
template <typename T>
typename List< T >::const_iterator& List< T >::const_iterator::operator++(){
    current = current->next;
    return *this;
}

//  Postfix increment operator
template <typename T>
typename List< T >::const_iterator List< T >::const_iterator::operator++(int){
    const_iterator temp = *this;
    ++(*this);
    return temp;
}

//  Prefix decrement operator
template <typename T>
typename List< T >::const_iterator& List< T >::const_iterator::operator--(){
    current = current-> prev;
    return *this;
}

//  Postfix decrement operator
template <typename T>
typename List< T >::const_iterator List< T >::const_iterator::operator--(int){
    const_iterator temp = *this;
    --(*this);
    return temp;
}

//  Operator == overload
template <typename T>
bool List< T >::const_iterator::operator==(const const_iterator &rhs) const{
    return current == rhs.current;
}

// Operator != overload
template <typename T>
bool List< T >::const_iterator::operator!=(const const_iterator &rhs) const{
    return !(*this == rhs);
}

//  Retrieves the current iterator node data
template <typename T>
T & List< T >::const_iterator::retrieve() const{
    return current->data;
}

//  Protected constructor
template <typename T>
List< T >::const_iterator::const_iterator(Node *p) {
    current = p;
}


/*
 *  Nested iterator Class Function Definitions
 */

//  Default constructor for Iterator
template <typename T>
List< T >::iterator::iterator(){
}

//  Star Operator Overload
template <typename T>
T & List< T >::iterator::operator*(){
    return const_iterator::retrieve();
}

//  Const Star Operator Overload
template <typename T>
const T & List< T >::iterator::operator*() const{
    return const_iterator::operator*();
}

//  Prefix Iterator Increment
template <typename T>
typename List< T >::iterator& List< T >::iterator::operator++(){
    this->current = this->current->next;
    return *this;
}

//  Postfix Iterator Increment
template <typename T>
typename List< T >::iterator List< T >::iterator::operator++(int){
    iterator temp = *this;
    ++(*this);
    return temp;
}

//  Prefix Iterator Decrement
template <typename T>
typename List< T >::iterator& List< T >::iterator::operator--(){
    this->current = this->current->prev;
    return *this;
}

//  Postfix Iterator Decrement
template <typename T>
typename List< T >::iterator List< T >::iterator::operator--(int){
    iterator temp = *this;
    --(*this);
    return temp;
}

//  Protected constructor
template <typename T>
List< T >::iterator::iterator(Node *p) {
    const_iterator retItr(p);
    this->current = p;
}



