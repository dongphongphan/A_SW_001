/* All bit operation
*/
#include <iostream>
#include <vector>
#include <set>
#include <bitset>

using namespace std;
#define BYTE_TO_BINARY_PATTERN "%c %c %c %c %c %c %c %c "

#define BYTE_TO_BINARY(byte) \
	byte & 0x80 ? '1' : '0', byte & 0x40 ? '1' : '0', byte & 0x20 ? '1' : '0', byte & 0x10 ? '1' : '0',\
	byte & 0x08 ? '1' : '0', byte & 0x04 ? '1' : '0', byte & 0x02 ? '1' : '0', byte & 0x01 ? '1' : '0'

void setBit(int data, bool val, unsigned char idx)
{
	printf("setBit(data = %d, val = %d, idx = %d)\n",data,val,idx);
	printf(BYTE_TO_BINARY_PATTERN,BYTE_TO_BINARY(data>>24));
	printf(BYTE_TO_BINARY_PATTERN,BYTE_TO_BINARY(data>>16));
	printf(BYTE_TO_BINARY_PATTERN,BYTE_TO_BINARY(data>>8));
	printf(BYTE_TO_BINARY_PATTERN,BYTE_TO_BINARY(data));
	
	data = (~(1 << idx) & data) | (val << idx);
	
	printf("\n");
	printf(BYTE_TO_BINARY_PATTERN,BYTE_TO_BINARY(data>>24));
	printf(BYTE_TO_BINARY_PATTERN,BYTE_TO_BINARY(data>>16));
	printf(BYTE_TO_BINARY_PATTERN,BYTE_TO_BINARY(data>>8));
	printf(BYTE_TO_BINARY_PATTERN,BYTE_TO_BINARY(data));
	printf("\n");
}
void reverseBit(int data, unsigned char idx)
{
	printf("reverseBit(data = %d, idx = %d)\n",data,idx);
	printf(BYTE_TO_BINARY_PATTERN,BYTE_TO_BINARY(data>>24));
	printf(BYTE_TO_BINARY_PATTERN,BYTE_TO_BINARY(data>>16));
	printf(BYTE_TO_BINARY_PATTERN,BYTE_TO_BINARY(data>>8));
	printf(BYTE_TO_BINARY_PATTERN,BYTE_TO_BINARY(data));
	
	data ^= (1<<idx);
	//data ^= (1UL << idx);
	
	printf("\n");
	printf(BYTE_TO_BINARY_PATTERN,BYTE_TO_BINARY(data>>24));
	printf(BYTE_TO_BINARY_PATTERN,BYTE_TO_BINARY(data>>16));
	printf(BYTE_TO_BINARY_PATTERN,BYTE_TO_BINARY(data>>8));
	printf(BYTE_TO_BINARY_PATTERN,BYTE_TO_BINARY(data));
	printf("\n");
}
bool checkbit(int data, unsigned char idx)
{
	printf("checkbit(data = %d, idx = %d)\n",data,idx);
	printf(BYTE_TO_BINARY_PATTERN,BYTE_TO_BINARY(data>>24));
	printf(BYTE_TO_BINARY_PATTERN,BYTE_TO_BINARY(data>>16));
	printf(BYTE_TO_BINARY_PATTERN,BYTE_TO_BINARY(data>>8));
	printf(BYTE_TO_BINARY_PATTERN,BYTE_TO_BINARY(data));
	printf("\n");
	bool ret = (data >> idx & 1UL);
	printf("ret = %d\n",ret);
	return ret;
}
void clearBit(int data, unsigned char idx)
{
	printf("clearBit(data = %d, idx = %d)\n",data,idx);
	printf(BYTE_TO_BINARY_PATTERN,BYTE_TO_BINARY(data>>24));
	printf(BYTE_TO_BINARY_PATTERN,BYTE_TO_BINARY(data>>16));
	printf(BYTE_TO_BINARY_PATTERN,BYTE_TO_BINARY(data>>8));
	printf(BYTE_TO_BINARY_PATTERN,BYTE_TO_BINARY(data));
	printf("\n");
	
	data &= ~(1UL << idx);
	
	printf(BYTE_TO_BINARY_PATTERN,BYTE_TO_BINARY(data>>24));
	printf(BYTE_TO_BINARY_PATTERN,BYTE_TO_BINARY(data>>16));
	printf(BYTE_TO_BINARY_PATTERN,BYTE_TO_BINARY(data>>8));
	printf(BYTE_TO_BINARY_PATTERN,BYTE_TO_BINARY(data));
}
// Why need suffix ULL;
void foo()
{
	printf("sizeof long long %d\n",sizeof(long long));
	
	long long a = 1LL << 36;
	long long b = 1    << 36;
	printf("a %lld\n",a);
	printf("b %lld\n",b);
}
int main(int argc, char** argv) {
	
	unsigned int a = 0xFF11EEAA;
	//reverseBit(a,31);
	foo();
}
