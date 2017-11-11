#include "iostream"
using namespace std;

int regs[4];
int code[] = { 0x1108, 0x1206, 0x2312, 0x0000 };
int ip = 0;
int prs0;
int prs1;
int prs2;
int prs3;
int prs4;
int running = 1;

int fetch(){
	return code[ip++];
}

void decode(int inst){
	prs0 = (inst & 0xF000) >> 12;
	prs1 = (inst & 0xF00) >> 8;
	prs2 = (inst & 0xF0) >> 4;
	prs3 = (inst & 0xF);
	prs4 = (inst & 0xFF);
}

void eval(){
	switch (prs0){
	case 0:
		cout << "halt" << endl;
		running = 0;
		break;
	case 1:
		cout << "load " << prs1 << " " << prs4 << endl;
		regs[prs1] = prs4;
		break;
	case 2:
		cout << "add " << prs1 << " " << prs2 << " " << prs3 << endl;
		regs[prs1] = regs[prs2] + regs[prs3];
		cout << regs[prs1] << endl;
		break;
	}
}

void run()
{
	while (running)
	{
		int instr = fetch();
		decode(instr);
		eval();
	}
}

int main(){
	run();
	system("PAUSE");
	return 0;
}