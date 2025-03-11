#include "FunctionReader.h"


int32_t FunctionReader::operator()(int32_t x) const {
    return ptr->operator()(x);
}


void FunctionReader::read(std::ifstream& ifs) {
    uint16_t N, T;
    ifs.read((char*)&N, sizeof(N));
    ifs.read((char*)&T, sizeof(T));
    int32_t* N1 = new int32_t[N];
    int32_t* N2;
    switch (T) {
    case 0:
        N2 = new int32_t[N];
        ifs.read((char*)&N1, sizeof(N1) * N);
        ifs.read((char*)&N2, sizeof(N2) * N);
        ptr = new FunctionType0(N1, N2, N);
    case 1:
        ifs.read((char*)&N1, sizeof(N1) * N);
        ptr = new FunctionType1(N1, N);
    case 2:
        ifs.read((char*)&N1, sizeof(N1) * N);
        ptr = new FunctionType2(N1, N);
    default:
        ptr = nullptr;
    }
}
FunctionReader::FunctionReader(std::ifstream& ifs) {  //we did an overloading function just in case
    read(ifs);
}

bool FunctionReader::isDefinedAt(int32_t x) const
{
    return ptr->isDefinedAt(x);
}

FunctionReader::FunctionReader(const char* file) {
    std::ifstream ifs(file, std::ios::binary);
    read(ifs);
};