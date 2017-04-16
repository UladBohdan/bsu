// Dubkou p.25 #8

// ! of long number

#include "stdafx.h"
#include <iostream>
#include <string>
#include <stack>

using namespace std;

int main()
{
	int ans[20000]={}, tmpans[20000]={}, glbans[20000]={};
	int a[31]={}, cur[31]={}, curlen=1, reached=0, temp_chck, rest;
	int degten, digit, posmin, posmin2, posminfin=0;
	string t;
	cout << "your long number: ";
	cin >> t;
	for (int i=0; i<t.length(); i++)
		a[i]=t[t.length()-1-i]-48;
	__asm
	{
		// Initialization
		mov ebx, 0
		mov cur[ebx*4], 0
		mov ans[ebx*4], 1
		inc ebx
		mov ans[ebx*4], -1
main1: // GLOBAL
		jmp inccur
	cont1:
		jmp multiply1
	cont2:	
		jmp checkingfinish
	cont3:
		cmp reached, 1
		je end1
		jmp main1
			
	// LIKE FUNCTIONS:

	// inc current number: ~ go to next number
	// works!
inccur:
		mov ebx, 0
		mov ecx, curlen
		inc cur[ebx*4]
	inside1:
		mov eax, cur[ebx*4]
		cmp eax, 10
		je throwone
	inside2:
		inc ebx
		loop inside1
		cmp cur[ebx*4], 0
		je cont1 // exit 1 from inccur
		inc curlen
		jmp cont1 // exit 2 from inccur
	throwone:
		mov cur[ebx*4], 0
		inc ebx
		add cur[ebx*4], 1
		dec ebx
		jmp inside2


		// Multiplies ans and cur
multiply1: 
		// FOR DEBUG:
		mov eax, curlen
		cmp eax, 4
		jne nottodebug
		inc eax
	nottodebug:

		//Copying ans to glbans
		mov ebx, 0
		mov ecx, 0
	copy_glb:
		mov eax, ans[ebx*4]
		mov glbans[ebx*4], eax
		inc ebx
		inc ecx
		cmp eax, -1
		jne copy_glb
		//copied.
		//We need to clear ANS
		mov ebx, 0
	clearANS:
		mov ans[ebx*4], 0
		inc ebx
		loop clearANS
		mov ans[4], -1
		//is it fine clearing? NO. maybe YES
		//Preparing to multiply all digits
		mov degten, -1
		mov ecx, curlen
		mov rest, ecx
// !!!!!
	digitcycle: // go through all digits of cur-number
		//init:
		inc degten
		dec rest
		mov ebx, degten
		mov eax, cur[ebx*4]
		mov digit, eax
		
		//Multiplying glbans on DIGIT to tmpans using DEGTEN

		//problems with 100!
		// lets try to clear TMPANS
		mov ecx, posminfin
		mov ebx, 0
		inc ecx
		inc ecx
		inc ecx
		inc ecx // why inc x4 ? to be sure
	clearTmpans:
		mov tmpans[ebx*4], 0
		inc ebx
		loop clearTmpans
		mov tmpans[4], -1

		

		mov ebx, degten
		mov ecx, 0
		mov eax, digit
		cmp eax, 0
		je multonzero
	multondig1: // mult all digits of glbans on DIGIT
		mov eax, glbans[ecx*4]
		imul digit
		mov tmpans[ebx*4], eax
		inc ebx
		inc ecx
		cmp eax, 0
		jge multondig1
		dec ebx
		mov tmpans[ebx*4], -1
		// kastyl. ???
		cmp degten, 2
		jl multdone
		mov tmpans[4], 0
		// ???
		jmp multdone
	multonzero:
		mov tmpans[0], 0
		mov tmpans[4], -1
		jmp multdone
	multdone:	
		// done.
		//Looking for numbers >=10
		   // looking for posmin for TMPANS
		mov ebx, 0
	findminus:
		mov eax, tmpans[ebx*4]
		inc ebx
		inc eax
		mov ecx, 0
		cmp eax, ecx
		jne findminus
		dec ebx
		mov posmin, ebx
		 // minus position is in posmin now
			// looking for posmin2 for ANS
		mov ebx, 0
		dec ebx
	inside9:
		inc ebx
		mov eax, ans[ebx*4]
		inc eax
		mov ecx, 0
		cmp eax, ecx
		jne inside9
		mov posmin2, ebx
		jmp inside11
	inside11:
		// -1 -> 0
		// as we know - positions (posmin, posmin2)
		mov ebx, posmin2
		mov ans[ebx*4], 0
		mov ebx, posmin
		mov tmpans[ebx*4], 0
		// now they are ready for copying
		// >=10 ?
		mov ebx, 0 // check for it - ok.
		dec ebx
	inside5:
		inc ebx
		cmp tmpans[ebx*4], 9
		jg throwsmth
	inside6:
		cmp ebx, posmin
		jne inside5
		jmp inside7
	throwsmth:
		mov eax, tmpans[ebx*4]
		cdq
		mov ecx, 10
		idiv ecx
		mov tmpans[ebx*4], edx
		inc ebx
		add tmpans[ebx*4], eax
		dec ebx
		jmp inside6
	inside7:
		cmp tmpans[ebx*4], 0
		je inside8
		inc ebx
		mov tmpans[ebx*4], -1
		inc posmin
		jmp inside8x
		// Now we should have a fine number in tempans, which we should add to ans
	inside8:

	inside8x:
		//Now will add TEMPANS to ANS
		//choosing max minus position
		mov eax, posmin
		cmp eax, posmin2
		jg inside10
		//posmin2 grower
		mov eax, posmin2
		mov posminfin, eax
		jmp inside10x
	inside10: // posmin grower
		mov eax, posmin
		mov posminfin, eax
		// max in posminusfin
		//Now can sum them!
	inside10x:
		mov ecx, posminfin
		mov ebx, 0
	inside12:
		mov eax, tmpans[ebx*4]
		add ans[ebx*4], eax
		cmp ans[ebx*4], 10
		jl inside13
		mov edx, 10
		sub ans[ebx*4], edx
		mov edx, 1
		inc ebx
		add ans[ebx*4], edx
		dec ebx
	inside13:
		inc ebx
		loop inside12
		//whats with the oldest place
		cmp ans[ebx*4], 0
		je inside14
		inc ebx
		mov ans[ebx*4], -1
		dec ebx
		jmp inside15
	inside14:
		mov ans[ebx*4], -1
		jmp inside15
	inside15:
		// is that all? we got ans!
		// now repeat for other digits
		// or finish
		cmp rest, 0
		je cont2 // exit!
		jmp digitcycle




		//Maybe it`s enough to multiply?!
		//WORKS i guess - no, it does not!
checkingfinish:
		mov temp_chck, 1
		mov ecx, 31
		mov ebx, 0
	inside20:
		// Comparing a, cur
		mov eax, a[ebx*4]
		cmp eax, cur[ebx*4]
		jne inside23
	inside21:
		inc ebx
		loop inside20
		jmp inside24
	inside23:
		mov temp_chck, 0
		jmp inside24
	inside24:
		mov eax, temp_chck
		mov reached, eax
		jmp cont3

end1: // answer is already in ANS. Finish it!

	}
	stack <int> rev;
	int poss=0;
	while (true)
	{
		rev.push(ans[poss]);
		poss++;
		if (ans[poss]==-1)
			break;
	}
	cout << "our long answer: " << t << "!=";
	while (!rev.empty())
	{
		cout << rev.top();
		rev.pop();
	}
	cout << endl;
	return 0;
}