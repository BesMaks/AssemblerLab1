#include <iostream>
using namespace std;
//только для n>0, k<=n
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
//int compare(int n, int k) {
//int result = 1;
//_asm {
//
//mov eax, n
//cmp eax, k
//JE A1
//
//mov eax, 0
//mov result, eax
//A1 :
//}
//return result;
//}
//
//int dec(short int a) {
//short int result = 0;
//_asm {
//mov ax, a
//dec ax
//mov result, ax
//}
//return result;
//}
//
//int Stirling(int n, int k) {
//int result = 0;
//
//if (compare(n, k)) return 1;
//if (compare(0, k)) return 0;
//
////первая часть
//short int stirlingN = n, stirlingK = k;
//_asm {
//mov ax, stirlingN
//dec ax
//mov stirlingN, ax
//
//mov ax, stirlingK
//dec ax
//mov stirlingK, ax
//}
//int stirling1 = Stirling(stirlingN, stirlingK);
//
////часть с умножением
//int stirling2 = Stirling(stirlingN, k);
//_asm {
//mov eax, stirling2
//mov ebx, k
//mul ebx
//mov stirling2, eax
//
//mov eax, stirling1
//add eax, stirling2
//
//mov result, eax
//}
//
//return result;
//}
void main() {
	_asm {
		mov ax, 0
		sub ax, 2
		xor bx, bx
	}
	int n = 1; int k = 1;
	cout << "n = "; cin >> n;
	cout << "k = "; cin >> k;
	int factJ[10] = { 1 };
	int factKJ[10] = { 1 };
	int powJN[10] = { 0 };
	int negativeElements[10] = { 0 };

	int bigChislitel = 0;
	int smRes = 0;

	int resultat = 0;
	factKJ[0] = factorial(k);

	int j = 0;
	for (int i = 1; i <= k; i++) {
		factKJ[i] = factKJ[i - 1] / (k - j);
		j++;
	} cout << endl;

	_asm {
		mov ecx, 1

		; заполнение массива factJ
		CycleFactJ :
		mov edx, ecx
			dec edx
			mov ebx, factJ[4 * edx]
			imul ebx, ecx
			mov factJ[4 * ecx], ebx

			inc ecx
			cmp ecx, n
			jle CycleFactJ

			mov ecx, 1
			; заполнение массива powJN
			CyclePowJN :

		mov ebx, 1
			mov edx, 1
			InnerCycle :
			imul ebx, ecx

			inc edx
			cmp edx, n
			jle InnerCycle

			mov powJN[4 * ecx], ebx

			inc ecx
			cmp ecx, k
			jle CyclePowJN


		mov ecx, 0
		; итоговая сумма
		mov eax, 0
		; чередование знака в сумме
		mov ebx, k
		MainCycle :
		; слагаемое для конкретного j(ecx)
			mov edx, 1
			; умножение на j^ n
			imul edx, powJN[4 * ecx]

		; деление на j!
			mov bigChislitel, edx
			fld bigChislitel
			fdiv factJ[4 * ecx]
			fstp smRes
			mov edx, smRes

		; деление на(k - j)!
			mov bigChislitel, edx
			fld bigChislitel
			fdiv factKJ[4 * ecx]
			fstp smRes
			mov edx, smRes

		; проверим чётность k + j
			inc ebx
			bt ebx, 0
			jnc Summa

			mov negativeElements[4 * ecx], edx
			jmp EndOfMainCycle
		Summa :
			add eax, edx

		EndOfMainCycle:
			inc ecx
			cmp ecx, k
			jle MainCycle
	}

	cout << "filling powJN: ";
	for (int i = 0; i <= k; i++) cout << powJN[i] << '\t';
	cout << endl << "filling factKJ: {k!,(k-1)!,...,1,1}: ";
	for (int i = 0; i <= k; i++) cout << factKJ[i] << '\t';
	cout << endl << "filling factJ: ";
	for (int i = 0; i <= k; i++) cout << factJ[i] << '\t';
	for (int i = 0; i <= k; i++) {
		if ((k + i) % 2 == 0) resultat = resultat + (powJN[i] / factJ[i] / factKJ[i]);
		else resultat = resultat - (powJN[i] / factJ[i] / factKJ[i]);
	}

	cout << endl <<"S(n,k) = "<< resultat << endl;
}