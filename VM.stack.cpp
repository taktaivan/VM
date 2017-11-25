#include "iostream"

using namespace std;

int code[] = { 0x1003, 0x1020, 0x1100, 0x0000 };
int ip = 0;
int prs0;
int prs1;
int prs2;
int running = 1;

struct node_s {
	int data = 0;
	node_s *prev = nullptr;
};

node_s *top;

int pop(){
	int save_data = top->data;
	node_s *new_top = top->prev;
	top = new_top;
	return save_data;
}

void push(int new_data) {
	node_s* node = new node_s;
	node->data = new_data;
	node->prev = top;
	top = node;
}

int fetch() {
	return code[ip++];
}

void decode(int inst) {
	prs0 = (inst & 0xF000) >> 12;
	prs1 = (inst & 0xF00) >> 8;
	prs2 = (inst & 0xFF);
}

void eval() {
	int a, b;
	switch (prs0) {
	case 0:
		cout << "halt" << endl;
		running = 0;
		break;
	case 1:
		switch (prs1) {
		case 0:
			push(prs2);
			break;
		case 1:
			a = pop();
			b = pop();
			push(a + b);
			cout << a + b << endl;
			break;
		case 2:
			a = pop();
			b = pop();
			push(a*b);
			cout << a*b << endl;
			break;
		}
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

int main() {
	run();
	system("PAUSE");
	return 0;
}
