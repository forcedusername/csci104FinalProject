#ifndef  _Set
#define _Set

#include <iostream>
#include <cstdlib>
#include <set>

using namespace std;

//Set <WebPage*, Set_compare>

template <class T, class K>
class Set: public set<T, K> {
	public:
	
		Set () { };   	// constructor for an empty set
		/*
		Set (const Set<T> & other) {
			walker_index= 0;
			internalStorage = other.internalStorage;
		}// copy constructor, making a deep copy
		*/
		~Set () { };                    // destructor
	
		using set<T, K>::insert;
		using set<T, K>::erase;
		using set<T, K>::empty;
		using set<T, K>::size;
		using set<T, K>::begin;
		using set<T, K>::end;
		
    bool contains (const T & item) const;
		Set<T, K> setIntersection (const Set<T, K> & other) const;
		/* Returns the intersection of the current set with other.
         That is, returns the set of all items that are both in this
         and in other. */

		Set<T, K> setUnion (const Set<T, K> & other) const;
		/* Returns the union of the current set with other.
         That is, returns the set of all items that are in this set
         or in other (or both).
         The resulting set should not contain duplicates. */
      
	/*private
		using set<T>::begin;
		using set<T>::end;
	*/
};
template <class T, class K>
bool Set<T,K>:: contains (const T& item) const{
  typename set<T, K>::iterator thing; //the object
  
	//use iterator thru set here
	for (thing=this->begin(); thing!=this->end(); ++thing)
  {
    if (*thing == item)
    {
      return true;
    }
  }
	return false;
}

template <class T, class K>
Set<T, K> Set<T, K>:: setIntersection (const Set<T, K> & other) const{
	//for set intersection, you have to find common elements and put them in an array? return the array
	//loop through the sets and then pull out the items
	
	//int list_size = internalStorage.size();
	//int list_other_size=other.size();
	Set<T, K>inter;
	if (this->size()==0||other.size()==0){
		return inter;
	}
	
	typename set<T, K>::iterator thing; //the object

	//use iterator thru set here
	for (thing=this->begin(); thing!=this->end(); ++thing){//CHANGED HERE
		typename set<T, K>::iterator thing2=other.begin();
		while (thing2!=other.end()){
			if (*thing==*thing2){
				inter.insert (*thing);
			}
			thing2++;
		}
	}
	
	return inter;
}

template<class T, class K>
Set<T, K> Set<T, K>::setUnion (const Set<T, K> & other) const {
	
	//int list_size = internalStorage.size();
	//int list_other_size=other.size();
	
	//if (list_size<list_other_size){
	
	Set<T, K> combinate;
	
	//you go through the list of both internal and other
	//check if the combination already has element from internal storage
	// if it doesnt, add it. 
	//now check if the other has the element at index i
	//after you loop through the smaller list, add the rest of the larger list

    /*
	if (this->size()==0&&other.size()==0){
		return combinate;
	}

    */

    //use iterator thru set here
	typename set<T,K>::iterator other_thing= other.begin();
	//for (typename set<T,K>::iterator other_thing=other.begin( ); other_thing!=other.end(); other_thing++){
	for (;other_thing!=other.end();++other_thing){		//HERE
		combinate.insert (*other_thing);
	}

	
	typename set<T, K>::iterator thing=this->begin();
	
  // IMPORTANT: insert already skips the duplicates.
  
	for (; thing!=this->end(); ++thing)
	{
		combinate.insert(*thing);
	}
	//use iterator thru set here
  /*
	for (thing=this->begin ( ); thing!=this->end(); thing++){
		typename set<T, K>::iterator thing2 = combinate.begin();
		while (thing2!=combinate.end()){
			if (*thing==*thing2){
				continue;
			}
			else {
				combinate.insert (*thing);
			}
			thing2++;
		}
	}
	*/
	
	return combinate;

}
//you're returning the 0th element of the List, and that's the head of the List ergo
//the set.
//so the function doesnt yell at you, you just set index to zero. 
//this will work because you wont call first after next. 

#endif
