#include <iostream>
#include <stdlib.h>
#include <fstream>

// Need algorithm to convert string to lowercase
#include <algorithm>

#include <string>
#include <vector>

// Structure which holds the advertiserBid and its components
struct advertiserBid {
	std::string _company;
	std::string _bidKeyword;
	float _price;
};

inline bool operator< ( const advertiserBid & lhs, const advertiserBid & rhs ) {
	return lhs._bidKeyword < rhs._bidKeyword;
}

std::vector< advertiserBid > * setBids( char* inputFile );

int main( int argc, char* argv[] )
{

	// Test if there are enough arguments for the filestream
	if ( argc < 3 ) {
		// Must provide input and output file
		std::cout << "Must provide input and output files" << std::endl;
		return 0;
	}
	
	// Have a vector of all advertiserBid's
	std::vector< advertiserBid > * allBids;
	
	// Use setBids function to set all bids for all advertisers from inputstream
	allBids = setBids( argv[1] );
	
	// Test to see if it worked
	std::cout << std::endl << "BidKeyword\t\t\t\tPrice\t\t\t\tCompany" << std::endl;
	for ( std::vector< advertiserBid >::iterator it = allBids->begin(); it != allBids->end(); ++it ) {
		std::cout << it->_bidKeyword << "\t\t\t\t" << it->_price << "\t\t\t\t" << it->_company << std::endl;
	}
	
	// Delete allBids
	delete allBids;
	
	return 0;
	
}

std::vector< advertiserBid > * setBids( char* inputFile ) {
	
	std::cout << "Opening Input File: " << inputFile << std::endl;
	
	// Open dataStream to take companies, bids, and the price in dollars for their bids
	std::ifstream inputStream;
	inputStream.open( inputFile );
	
	// Take in company names as case sensitive
	// Keyword bids are case insensitive
	// Price in dollars for bid are accumulated
	
	// First take in the number of bids
	int numBids;
	inputStream >> numBids;
	
	// Have a vector of all advertiserBid's
	std::vector< advertiserBid > * allBids = new std::vector< advertiserBid >;
	
	// Use a loop to fill set one by one
	for ( int i = 0; i < numBids; ++i ) {
		std::string company;
		std::string bidKeyword;
		float price;
		
		// Variable to hold the advertiser bid pairing
		advertiserBid tempBid;
		
		// Get the bid, convert to lowercase
		inputStream >> bidKeyword;
		std::transform( bidKeyword.begin(), bidKeyword.end(), bidKeyword.begin(), ::tolower );
		
		// Get bid value
		inputStream >> price;
		
		// Get company name
		// Get first word, then add temp line to rest
		inputStream >> tempBid._company;
		std::string tempRestLine;
		std::getline( inputStream, tempRestLine );
		tempBid._company += tempRestLine;
		
		// Fill advertiserBid values
		tempBid._bidKeyword = bidKeyword;
		tempBid._price = price;
		
		allBids->push_back( tempBid );
	}
	
	// Close inputstream
	inputStream.close();
	
	// Return a pointer to the set
	return allBids;

}
