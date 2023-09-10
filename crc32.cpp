#include <iostream>
#include <bitset>
#include <iomanip>
#include <fstream>
using namespace std;

// CRC32 polynomial
// G(x) = x^32+x^26+x^23+x^22+x^16+x^12+x^11+x^10+x^8+x^7+x^5+x^4+x^2+x+1
// binary rep of G(x) in bitset order 100000100110000010001110110110111
int poly[] = {0,1,2,4,5,7,8,10,11,12,16,22,23,26,-1};

// bitset is oposite of a normal array. norm[0]=bitset[31], norm[31]=bitset[0]
const unsigned long n = 32;
bitset<n> result;

/* This method is using the linear feedback shift register. It is xoring each
 * bit in the result register, that corresponds to the location in the crc32
 * polynomial, with the least significant bit of the result register. The
 * message is fed in a byte at a time which is then subjected to the LFSR
 * circuit. Which is equivalent to R(x) = B(x) mod G(x). Where B(x) is the 
 * input data and a padding of 32 0's (multiplying the polynomial by x^32).
 */
bitset<n> 
crc32(bitset<8> data)
{
    bool bit;
    int xorpos, pos;

    for(int i = 0; i < 8; ++i){
        bit = result[31]; // bit at front of register to be xorred against
        result <<= 1;
        result.set(0,data[i]); // Setting LSB to the ith bit in the data
        xorpos = 0;
        while(poly[xorpos] != -1){ // looping threw poly
            pos = poly[xorpos]; // setting position in result
            result.set(pos,bit^result[pos]);
            ++xorpos;
        }
    }
    return result;
}

void
calc_crc(istream &in)
{
    unsigned char c;
    bitset<n> crc;
    result.reset(); // The padded 32 zeros
    while(!in.eof()){
        in.read((char*) &c, 1); // read one char at a time
        if(!in.eof()){
            bitset<8> data = c; // convert char to bitset<8>
            crc = crc32(data);  // calc the crc32 checksum
        }
    }
    cout << crc << "(" << setbase(16) << crc.to_ulong() << ")" << endl;
}

int
main(int argc, char* argv[])
{
    ifstream fin;
    if(argc > 1){
        for(int i = 1; i < argc; ++i){
            fin.open(argv[i], ios::in | ios::binary);
            cout << argv[i] << ":";
            calc_crc(fin);
            fin.close();
        }
    } else {
        calc_crc(cin);
    }
}
