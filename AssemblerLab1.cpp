//ГОСТ 7.32-2017
#include <iostream>
using namespace std;

int factorial(int a) {
	int fact;
	__asm
	{
		mov eax, 1
		mov ecx, a
		mov ebx, 1
		start :
		imul eax, ebx
			add ebx, 1
			loop start

			mov fact, eax

	}
	return fact;
}
//только для n>0, k<=n
int compare(int n, int k) {
	int result = 1;
	_asm {

		mov eax, n
		cmp eax, k
		JE A1	

		mov eax, 0
		mov result, eax
		A1:
	}
	return result;
}

int dec(short int a) {
	short int result = 0;
	_asm {
		mov ax, a
		dec ax
		mov result, ax
	}
	return result;
}

int Stirling(int n, int k) {
	int result = 0;

	if (compare(n, k)) return 1;
	if (compare(0, k)) return 0;

	//первая часть
	short int stirlingN = n, stirlingK = k;
	_asm {
		mov ax, stirlingN
		dec ax
		mov stirlingN, ax

		mov ax, stirlingK
		dec ax
		mov stirlingK, ax
	}
	int stirling1 = Stirling(stirlingN, stirlingK);

	//часть с умножением
	int stirling2 = Stirling(stirlingN, k);
	_asm {
		mov eax, stirling2
		mov ebx, k
		mul ebx
		mov stirling2, eax

		mov eax, stirling1
		add eax, stirling2

		mov result, eax
	}

	return result;
}

void main() {

	/*N = 5;
	_asm {
		ADD N, 22
		SUB N, 1
	};
	cout << N;*/
	
	/*short int c = 3; int res = 7;
	_asm {
		MOV CX, c
		A: INC res
		LOOP A
	}
	cout << endl << res;*/

	int n = 9; int k = 7;
	cout << Stirling(n, k);
}