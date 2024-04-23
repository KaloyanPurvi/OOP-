#pragma once
#include "MultiSet.h"
#include <assert.h>

static unsigned getMin(unsigned ls, unsigned rs) {
	return (ls > rs ? rs : ls);
}
static unsigned getMax(unsigned ls, unsigned rs) {
	return (ls > rs ? ls : rs);
}

static unsigned getMaskOfOnes(unsigned numberOfOnes) {
	return (1 << numberOfOnes) - 1;
}
static unsigned getKbitsFrom(unsigned n, unsigned k, unsigned leftSpacing) {
	unsigned digitsToKeepMask = getMaskOfOnes(k);
	return digitsToKeepMask & (n >> leftSpacing);
}

static unsigned maskToRemoveKbits(unsigned k, unsigned leftSpacing) {
	unsigned mask = getMaskOfOnes(k);
	mask <<= leftSpacing;
	return ~mask;
}
static void printBinaryUint8_t(uint8_t num) {
	const unsigned elements = sizeof(uint8_t) * 8;
	for (uint8_t maskStep = elements - 1; maskStep > 0; maskStep--) {
		std::cout << (bool)(num & (1 << (maskStep)));
	}
	//and since its unsigned and we will fall in an infinite loop if condition is maskStep>=0, therefore:
	//we take care of the last bit:
	std::cout << (bool)(num & 1);
}

MultiSet::MultiSet(unsigned newN, unsigned newK) {
	assert(newK >= 1 && newK <= 8); //or throw ex, im not sure, we havent studies `em yet
	k = newK;
	N = newN;
	bucketsCount = getBucket(newN) + 1; //it would be convinient to cast to double here and use ceiling instead of +1 but im not sure im allowed to
	//and we are thought to do it this way, so...
	buckets = new uint8_t[bucketsCount]{ 0 };
}
void MultiSet::free()
{
	delete[] buckets;
	uint8_t* buckets = nullptr;
	unsigned bucketsCount = 0;
	unsigned N = 0;
	unsigned k = 0;
}

void MultiSet::copyFrom(const MultiSet& other) {
	buckets = new uint8_t[other.bucketsCount];
	bucketsCount = other.bucketsCount;
	for (unsigned i = 0; i < bucketsCount; i++) {
		buckets[i] = other.buckets[i];
	}
	N = other.N;
	k = other.k;
}

MultiSet::MultiSet(const MultiSet& other) {
	copyFrom(other);
}

MultiSet& MultiSet::operator=(const MultiSet& other) {
	if (&other != this) {
		free();
		copyFrom(other);
	}
	return *this;
}

MultiSet::~MultiSet() {
	free();
}

unsigned MultiSet::getBucket(unsigned num) const {
	return (((num * k) + k) / elementsInBucket);
}

unsigned MultiSet::getBucketIndex(unsigned num) const {
	return (((num * k) + k) % elementsInBucket);
	//from right to left if k is 3 we add 0 3  and '2' 3 times bucket is presented as:  [011,000,01][1,000,000,0]...
	//if we search for '2' it will return 1
}


void MultiSet::printBinary() const {
	for (int i = 0; i < bucketsCount; i++) {
		printBinaryUint8_t(buckets[i]);
		std::cout << ' ';
	}
}

void MultiSet::printNumbers() const { // !!!! its stated to print All number, but it isnt stated directly whether we should print for all of the occurences or not
	// I will print it for each occurence :) 
	std::cout << '{';
	for (int i = 0; i <= N; i++) {
		unsigned count = contains(i);
		if (count) {
			std::cout << "{ ";
			while (count) {
				std::cout << i << ' ';
				count--;

			}
			std::cout << '}';
		}

	}
	std::cout << '}';
}

void MultiSet::changeOccurancies(unsigned num, unsigned newOccurrence) {
	unsigned currentIndex = getBucketIndex(num);
	unsigned currentBucket = getBucket(num);
	unsigned digitsMissing = getDigitsMissing(currentIndex, k);
	unsigned rightSideNonNeededBits = (elementsInBucket - currentIndex) - 1;

	unsigned digitsToRemove = maskToRemoveKbits(k, rightSideNonNeededBits);
	buckets[currentBucket] &= digitsToRemove;
	buckets[currentBucket] |= (newOccurrence << (rightSideNonNeededBits + 1));
	if (digitsMissing) {
		currentBucket--;
		buckets[currentBucket] &= ~getMaskOfOnes(digitsMissing);//((1 << digitsMissing) - 1); //return (1 << digitsMissing) - 1;
		buckets[currentBucket] |= (newOccurrence >> (k - digitsMissing));
	}

}

bool MultiSet::add(unsigned num) {
	if (num > N) {
		std::cout << num << " cant be added to Set. Input is bigger then expected \0";
		return 0;
	}
	unsigned occurrences = contains(num);
	if (occurrences == ((1 << k) - 1)) {
		std::cout << num << " cant be added to Set. Capacity is full. \0";
		return 0;
	}

	occurrences++;
	//we must turn the existing occurrences to 0 and then add our accourancies
	changeOccurancies(num, occurrences);

	return 1;
}

bool MultiSet::remove(unsigned num) { //remove one occurrence
	unsigned occurrences = contains(num);
	if (occurrences == 0) {
		return 1; //lets make it do nothing
	}

	occurrences--;
	//we must turn the existing occurrences to 0 and then add our accourancies
	changeOccurancies(num, occurrences);

	return 1;

}

unsigned MultiSet::getDigitsMissing(uint8_t currentIndex, uint8_t k) const {
	if (currentIndex < k)  return k - currentIndex;
	return 0;
};


// [0000,0000] [0000,0000]
unsigned MultiSet::contains(unsigned num) const {
	if (num > N) return 0;
	unsigned currentBucket = getBucket(num);
	unsigned currentIndex = getBucketIndex(num);
	unsigned digitsMissing = getDigitsMissing(currentIndex, k);
	unsigned howMuchToPushBack = (elementsInBucket - currentIndex) - 1;
	unsigned rs = getKbitsFrom(buckets[currentBucket], k, howMuchToPushBack + 1);


	unsigned ls = 0;
	if (digitsMissing/*!=0*/) {
		currentBucket--;
		ls = getKbitsFrom(buckets[currentBucket], digitsMissing, 0);
		ls <<= digitsMissing - 1;

	}
	if (digitsMissing == k) {
		return ls >>= k - 1;
	}
	return ls + rs;
}

//NOTE TO SELF:
//! TRANSFER TO HEADER FILES

void MultiSet::writeToFile(std::ofstream& file) const {
	/*
	uint8_t* buckets = nullptr;
	unsigned bucketsCount = 0;
	unsigned N = 0;
	unsigned k = 0;
	*/
	file.write((const char*)&bucketsCount, sizeof(bucketsCount)); //Firstly we write down the size so when we read we know how much memory to save
	file.write((const char*)buckets, sizeof(buckets) * bucketsCount);
	file.write((const char*)&N, sizeof(N));
	file.write((const char*)&k, sizeof(k));
	//when we read we can get the bucketsCount just by getting n and k - therefore we may not need to write down bucketsCount. Yet i will do it - to avoid any mistakes.
}
void MultiSet::writeToFile(const char* fileName) const {
	std::ofstream ofs(fileName, std::ios::binary);
	if (!ofs.is_open()) {
		std::cerr << "File wasnt opened correctly";
		return;
	}
	writeToFile(ofs);
}

void MultiSet::readFromFile(const char* fileName) {
	std::ifstream ifs(fileName, std::ios::binary);
	if (!ifs.is_open()) {
		std::cerr << "File wasnt opened correctly";
		return;
	}
	readFromFile(ifs);
}

void MultiSet::readFromFile(std::ifstream& ifs) {
	int keepStart = ifs.tellg();
	free();
	ifs.read((char*)&bucketsCount, sizeof(bucketsCount));
	buckets = new uint8_t[bucketsCount];
	ifs.read((char*)buckets, sizeof(buckets) * bucketsCount);
	ifs.read((char*)&N, sizeof(N));
	ifs.read((char*)&k, sizeof(k));

	ifs.seekg(keepStart);
	ifs.clear();
}
std::ofstream& operator<<(std::ofstream& ofs, const MultiSet& set) {
	ofs.write((const char*)&set.bucketsCount, sizeof(set.bucketsCount)); //Firstly we write down the size so when we read we know how much memory to save
	ofs.write((const char*)set.buckets, sizeof(set.buckets) * set.bucketsCount);
	ofs.write((const char*)&set.N, sizeof(set.N));
	ofs.write((const char*)&set.k, sizeof(set.k));
	return ofs;
}
std::ifstream& operator>>(std::ifstream& ifs, MultiSet& set) {
	//int keepStart = ifs.tellg();  note to self: not needed here
	set.free();
	ifs.read((char*)&set.bucketsCount, sizeof(set.bucketsCount));
	set.buckets = new uint8_t[set.bucketsCount];
	ifs.read((char*)set.buckets, sizeof(set.buckets) * set.bucketsCount);
	ifs.read((char*)&set.N, sizeof(set.N));
	ifs.read((char*)&set.k, sizeof(set.k));

	//ifs.seekg(keepStart); note to self: not needed here
	ifs.clear();
	return ifs;
}

MultiSet compliment(const MultiSet& original) {
	MultiSet result(original.N, original.k);
	for (int i = 0; i < result.bucketsCount; i++) {
		result.buckets[i] = ~original.buckets[i];
	}
	return result;
}

MultiSet IntersectionOfSets(const MultiSet& lhs, const MultiSet& rhs) {
	MultiSet result(getMin(lhs.N, rhs.N), getMin(lhs.k, rhs.k));
	for (int i = 0; i <= result.N; i++) { //i dont think there is a way to do it using bitwise since its a MULTI set and it cant be done with just bitwise OR
		//vse pak e sechenie a ne obedinenie
		unsigned countL = lhs.contains(i);
		unsigned countR = rhs.contains(i);
		for (int j = getMin(countL, countR); j > 0; j--)
			result.add(i);
	}
	return result;
}

MultiSet DifferenceOfSets(const MultiSet& lhs, const MultiSet& rhs) {
	MultiSet result(getMax(lhs.N, rhs.N), getMax(lhs.k, rhs.k));
	for (int i = 0; i <= result.N; i++) {
		unsigned countL = lhs.contains(i);
		unsigned countR = rhs.contains(i);

		for (int j = getMax(countL, countR) - getMin(countL, countR); j > 0; j--)
			result.add(i);
	}
	return result;
}
