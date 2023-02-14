#include<iostream>
#include<fstream>
using namespace std;

const unsigned int exponent_bits=8;
const unsigned int mantissa_bits=23;
const unsigned int exponent_mask=0xffu;
const unsigned int mantissa_mask=0x007fffffu;
const unsigned int exponent_bias=127;

union float_bits
{
	float f;
	unsigned int bits;
};

// print hex( 5.Of ) outputs "The float looks like Ox4OaOOOOO in hex." 0100 0000 1010 0000 0000 0000 0000 0000
//分解 0--100 0000 1--010 0000 0000 0000 0000 0000 符号位--指数位+127--尾数，省略了1.，以此提高存储精度

void print_hex(ofstream & out,float f)
{
	union float_bits t;
	t.f=f;
	unsigned int mantissa=t.bits & mantissa_mask;
	int exponent=(t.bits >> mantissa_bits) & exponent_mask;

	if((t.bits >> (exponent_bits+mantissa_bits)) == 1)
		out<<"-";

/*	sample solution 多的判断
	if( exponent > 2 * EXPONENT_BIAS )
	{
		out<<"Inf\n"; // Infinity 
		return;
	}
	else if( exponent == 0 )
	{
		out<<"0.";  // Zero or Denormal
		exponent = ( mantissa != 0 ) ? exponent + 1 : exponent;
	}
	else 
		out<<"1.";
*/
	out<<"1.";
	for(int i=mantissa_bits-1;i>=0;--i)
		out<<((mantissa >> i) & 1);
	out<<" * 2 ^ "<<int(exponent-exponent_bias)<<endl;
}

int main(int argc,char **argv)
{
	int count=1;
	for(int i=1;i<=argc;++i)
	{
		ofstream fout(argv[count++],ios_base::out | ios_base::app);
		ifstream fin(argv[count++]);
		int n;
		fin>>n;
		float f;
		for(int j=0;j<n;j++)
		{
			fin>>f;
			print_hex(fout,f);
		}
	}
	
	return 0;
}
