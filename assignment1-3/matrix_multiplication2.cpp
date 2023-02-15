#include<iostream>
#include<fstream>
using namespace std;

const int MAXN=300;

typedef struct Matrix_s
{
	size_t R,C;
	int **index;
} Matrix;

void read_matrix(ifstream & in,Matrix & M)
{
	in>>M.R>>M.C;				/**< 需增加矩阵超出规模判断 */
	M.index=new int*[M.R];
	for(int i=0;i<M.R;i++)
		M.index[i]=new int[M.C];
	for(int j=0;j<M.R;j++)
		for(int k=0;k<M.C;k++)
			in>>M.index[j][k];
}

void print_matrix(ofstream & out,Matrix & M)
{
	out<<endl<<M.R<<" "<<M.C<<endl;
	for(int j=0;j<M.R;j++)
	{
		for(int k=0;k<M.C;k++)
			out<<M.index[j][k]<<" ";
		out<<endl;
	}
}

void matrix_mult(Matrix & _A,Matrix & _B,Matrix & _C)
{
	if(_A.C!=_B.R)
		_C.R=_C.C=0;
	else
	{
		_C.R=_A.R;
		_C.C=_B.C;
		_C.index=new int*[_C.R];
		for(int i=0;i<_C.R;i++)
			_C.index[i]=new int[_C.C];
		int result;
		for(int j=0;j<_A.R;j++)
			for(int k=0;k<_B.C;k++)
			{
				result=0;
				for(int l=0;l<_A.C;l++)
					result+=_A.index[j][l]*_B.index[l][k];
				_C.index[j][k]=result;
			}
	}
}

void free_matrix(Matrix & M)
{
	for(int i=0;i<M.R;i++)
		delete [] M.index[i];
	delete M.index;
}

int main(int argc,char** argv)
{
	int count=1;
	for(int i=1;i<=argc/2;++i)
	{
		ifstream fin(argv[count++]);
		ofstream fout(argv[count++],ios_base::out | ios_base::app);			/**< 需增加文件正常打开判断 */

		Matrix A,B,C;
		read_matrix(fin,A);
		read_matrix(fin,B);
		matrix_mult(A,B,C);
		print_matrix(fout,C);

		free_matrix(A);
		free_matrix(B);
		free_matrix(C);
	}
	return 0;
}
