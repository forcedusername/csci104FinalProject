#ifndef SET_H_
#define SET_H_

// necessary includes can go here
#include <iostream>
#include <stdexcept>
#include <exception>
#include <set>
using namespace std;

template<class T>
class Set : public set<T> {
public:
	Set<T> setIntersection(const Set<T> & other) const;
	/* Returns the intersection of the current set with other.
	 That is, returns the set of all items that are both in this
	 and in other. */

	Set<T> setUnion(const Set<T> & other) const;
	/* Returns the union of the current set with other.
	 That is, returns the set of all items that are in this set
	 or in other (or both).
	 The resulting set should not contain duplicates. */

};

template<class T>
Set<T> Set<T>::setIntersection(const Set<T> & other) const {
	Set<T> i_set;
	typename set<T>::iterator it;
	for (it = this->begin(); it != this->end(); ++it)//iterate through all items in this
	{
		if (other.find(*it) != other.end())//add item if it's in other set
		{
			i_set.insert(*it);
		}
	}
	return i_set;
}
template<class T>
Set<T> Set<T>::setUnion(const Set<T> & other) const {
	Set<T> u_set;
	typename set<T>::iterator it;
	for (it = this->begin(); it != this->end(); ++it) {
		u_set.insert(*it);
	}
	for (it = other.begin(); it != other.end(); ++it) {
		//it = set<T>::u_set.find(item);
		if (u_set.find(*it) == u_set.end())//add if it's not already in the u_set
		{
			u_set.insert(*it);
		}
	}

	return u_set;
}

#endif /* SET_H_ */
