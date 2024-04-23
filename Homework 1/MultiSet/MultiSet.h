#pragma once
#include <iostream>
#include <fstream>

class MultiSet {

	uint8_t* buckets = nullptr;
	unsigned bucketsCount = 0;
	unsigned N = 0;
	unsigned k = 0;
	static const unsigned elementsInBucket = sizeof(uint8_t) * 8; //its static because for every MultiSet it would be the same

	void free();
	void copyFrom(const MultiSet& other);
	void changeOccurancies(unsigned num, unsigned newOccurrence);
	unsigned getBucketIndex(unsigned num) const;
	unsigned getBucket(unsigned num) const;
	unsigned getDigitsMissing(uint8_t currentIndex, uint8_t k) const;

public:
	MultiSet() = default;
	MultiSet(unsigned newN, unsigned newK);

	MultiSet(const MultiSet& other);
	MultiSet& operator=(const MultiSet& other);
	~MultiSet();

	bool add(unsigned num);
	bool remove(unsigned num);
	unsigned contains(unsigned num) const;
	void printBinary() const;
	void printNumbers() const;
	void writeToFile(std::ofstream& file) const;
	void writeToFile(const char* fileName) const;
	void readFromFile(std::ifstream& file);
	void readFromFile(const char* fileName);
	friend MultiSet DifferenceOfSets(const MultiSet& lhs, const MultiSet& rhs);
	friend MultiSet IntersectionOfSets(const MultiSet& lhs, const MultiSet& rhs);
	friend MultiSet compliment(const MultiSet& original);
	friend std::ofstream& operator<<(std::ofstream& out, const MultiSet& set);
	friend std::ifstream& operator>>(std::ifstream& ifs, MultiSet& set);
};