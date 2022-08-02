
#include <iostream>
using namespace std;

int kmap[2][4] = { 0 };
int len = 0;
bool Octet_Check = true;
bool Quad_Check[6] = { false };
bool Pair_Check[12] = { false };
bool Single_Check[8] = { false };
void Input() {
	
	int val[8] = { NULL };
	do {
		cout<< "Enter the number of values you want to enter (They should be less than 9):";
		cin >> len;
	} while (len > 8 || len<0);

	for (int i = 0; i < len; ++i) {
		bool s_check = false;
		do {
			if (s_check == true) {
				cout << "The value already exists.\n";
				s_check = false;
			}
			cout << "Enter Value between 0 and 7:";
			cin >> val[i];
			for (int z = 0; z < i; ++z) {
				if (val[z] == val[i])
					s_check = true;
			}
		} while (val[i] > 7 || val[i] < 0 || s_check == true);
	}

	for (int x = 0, z = 0; x < len; ++x, z++) {
		if (val[z] < 4)
			kmap[0][val[z]] = 1;
		else if (val[z] > 3 && val[z] < 8)
			kmap[1][val[z] - 4] = 1;
	}
	
	for (int i = 0; i < len; ++i){
		int a = 0;
		for (int x = 0; x < i; ++x){
			if (val[x] > val[i]){
				a = val[x];
				val[x] = val[i];
				val[i] = a;
			}
		}
	}
	cout << "The Function you chose is :\nF (X ,Y ,Z) = { ";
	for (int i = 0; i < len; ++i)
		cout << val[i] << " ,";
	
	cout << "\b}" << endl;

}
void Display() {
	cout << "\n\n 		  Y*Z*  Y*Z   YZ    YZ*" << endl;
	cout << "		 _____,_____,_____,_____," << endl;
	cout << "	 X* 	|" << kmap[0][0] << "\t\b\b|" << kmap[0][1] << "    |"
		<< kmap[0][3] << "    |" << kmap[0][2] << "    |" << endl;
	cout << "	    	|_____|_____|_____|_____|" << endl;
	cout << "	 X  	|" << kmap[1][0] << "\t\b\b|" << kmap[1][1] << "    |"
		<< kmap[1][3] << "    |" << kmap[1][2] << "    |" << endl;
	cout << "		|_____|_____|_____|_____|" << endl;
}

void Logic() {
	for (int i = 0; i < 2; ++i) {
		for (int x = 0; x < 4; ++x) {
			if (kmap[i][x] == 0)
				Octet_Check = false;
		}
	}

	/*
	0. First row
	1. Second Row.
	2. First 2
	3. 2-4
	4. Last 2
	5. 1-4
	*/
	//Quad Check Starts Here
	bool check = false;
	for (int i = 0; i < 4; ++i) {
		if (kmap[0][i] == 1)
			check = true;
		else {
			i = 4;
			check = false;
		}
	}
	if (check == true)
		Quad_Check[0] = true;
	check = false;
	for (int i = 0; i < 4; ++i) {
		if (kmap[1][i] == 1)
			check = true;
		else {
			i = 4;
			check = false;
		}
	}
	if (check == true)
		Quad_Check[1] = true;
	check = false;
	for (int i = 0; i < 2; ++i) {
		for (int x = 0; x < 2; ++x) {
			if (kmap[i][x] == 1)
				check = true;
			else {
				check = false;
				i = 2;
			}
		}
	}
	if (check == true)
		Quad_Check[2] = true;

	check = false;
	for (int i = 0; i < 2; ++i) {
		if (kmap[i][1] == 1 && kmap[i][3] == 1)
			check = true;
		else {
			check = false;
			i = 2;
		}
	}
	if (check == true) {
		Quad_Check[3] = true;
	}

	check = false;
	for (int i = 0; i < 2; ++i) {
		for (int x = 2; x < 4; ++x) {
			if (kmap[i][x] == 1)
				check = true;
			else {
				check = false;
				i = 2;
			}
		}
	}
	if (check == true) {
		Quad_Check[4] = true;
	}

	check = false;
	for (int i = 0; i < 2; ++i) {
		if (kmap[i][0] == 1 && kmap[i][2] == 1)
			check = true;
		else {
			check = false;
			i = 2;
		}
	}
	if (check == true) {
		Quad_Check[5] = true;
	}

	// Quad Check Ends Here

	/*
	0. kmap[0][0]-kmap[0][1]
	1. kmap[0][1]-kmap[0][3]
	2. kmap[0][3]-kmap[0][2]
	3. kmap[1][0]-kmap[1][1]
	4. kmap[1][1]-kmap[1][3]
	5. kmap[1][3]-kmap[1][2]
	6. kmap[0][0]-kmap[1][0]
	7. kmap[0][1]-kmap[1][1]
	8. kmap[0][3]-kmap[1][3]
	9. kmap[0][2]-kmap[1][2]
	10.kmap[0][0]-kmap[0][2]
	11.kamp[1][0]-kmap[1][2]
	*/

	check = false;
	// Pair Check Starts Here

	if ((kmap[0][0] == 1 && kmap[0][1] == 1)
		&& (Quad_Check[0] == false && Quad_Check[2] == false))
		Pair_Check[0] = true;
	if ((kmap[0][1] == 1 && kmap[0][3] == 1)
		&& (Quad_Check[0] == false && Quad_Check[3] == false))
		Pair_Check[1] = true;
	if ((kmap[0][3] == 1 && kmap[0][2] == 1)
		&& (Quad_Check[0] == false && Quad_Check[4] == false))
		Pair_Check[2] = true;
	if ((kmap[1][0] == 1 && kmap[1][1] == 1)
		&& (Quad_Check[1] == false && Quad_Check[2] == false))
		Pair_Check[3] = true;
	if ((kmap[1][1] == 1 && kmap[1][3] == 1)
		&& (Quad_Check[1] == false && Quad_Check[3] == false))
		Pair_Check[4] = true;
	if ((kmap[1][3] == 1 && kmap[1][2] == 1)
		&& (Quad_Check[1] == false && Quad_Check[4] == false))
		Pair_Check[5] = true;
	if ((kmap[0][0] == 1 && kmap[1][0] == 1)
		&& (Quad_Check[0] == false || Quad_Check[1] == false)
		&& (Quad_Check[2] == false && Quad_Check[5] == false))
		Pair_Check[6] = true;
	if ((kmap[0][1] == 1 && kmap[1][1] == 1)
		&& (Quad_Check[0] == false || Quad_Check[1] == false)
		&& (Quad_Check[2] == false && Quad_Check[3] == false))
		Pair_Check[7] = true;
	if ((kmap[0][3] == 1 && kmap[1][3] == 1)
		&& (Quad_Check[0] == false || Quad_Check[1] == false)
		&& (Quad_Check[3] == false && Quad_Check[4] == false))
		Pair_Check[8] = true;
	if ((kmap[0][2] == 1 && kmap[1][2] == 1)
		&& (Quad_Check[0] == false || Quad_Check[1] == false)
		&& (Quad_Check[4] == false && Quad_Check[5] == false))
		Pair_Check[9] = true;
	if ((kmap[0][0] == 1 && kmap[0][2] == 1)
		&& (Quad_Check[0] == false && Quad_Check[5] == false))
		Pair_Check[10] = true;
	if ((kmap[1][0] == 1 && kmap[1][2] == 1)
		&& (Quad_Check[1] == false && Quad_Check[5] == false))
		Pair_Check[11] = true;

	// Pair_Check Ends Here

	if ((kmap[0][0] == 1 && Pair_Check[0] == false && Pair_Check[6] == false
		&& Pair_Check[10] == false)
		&& (Quad_Check[0] == false && Quad_Check[2] == false
		&& Quad_Check[5] == false))
		Single_Check[0] = true;
	if ((kmap[0][1] == 1 && Pair_Check[0] == false && Pair_Check[1] == false
		&& Pair_Check[7] == false)
		&& (Quad_Check[0] == false && Quad_Check[2] == false
		&& Quad_Check[3] == false))
		Single_Check[1] = true;
	if ((kmap[0][3] == 1 && Pair_Check[1] == false && Pair_Check[2] == false
		&& Pair_Check[8] == false)
		&& (Quad_Check[0] == false && Quad_Check[3] == false
		&& Quad_Check[4] == false))
		Single_Check[2] = true;
	if ((kmap[0][2] == 1 && Pair_Check[2] == false && Pair_Check[9] == false
		&& Pair_Check[10] == false)
		&& (Quad_Check[0] == false && Quad_Check[4] == false
		&& Quad_Check[5] == false))
		Single_Check[3] = true;
	if ((kmap[1][0] == 1 && Pair_Check[3] == false && Pair_Check[6] == false
		&& Pair_Check[11] == false)
		&& (Quad_Check[1] == false && Quad_Check[2] == false
		&& Quad_Check[5] == false))
		Single_Check[4] = true;
	if ((kmap[1][1] == 1 && Pair_Check[3] == false && Pair_Check[4] == false
		&& Pair_Check[7] == false)
		&& (Quad_Check[1] == false && Quad_Check[2] == false
		&& Quad_Check[3] == false))
		Single_Check[5] = true;
	if ((kmap[1][3] == 1 && Pair_Check[4] == false && Pair_Check[5] == false
		&& Pair_Check[8] == false)
		&& (Quad_Check[1] == false && Quad_Check[3] == false
		&& Quad_Check[4] == false))
		Single_Check[6] = true;
	if ((kmap[1][2] == 1 && Pair_Check[5] == false && Pair_Check[9] == false
		&& Pair_Check[11] == false)
		&& (Quad_Check[1] == false && Quad_Check[4] == false
		&& Quad_Check[5] == false))
		Single_Check[7] = true;

	/*	for (int i=0;i<6;++i)
	cout<<Quad_Check[i]<<" ";
	cout<<endl;
	for(int i=0;i<12;++i)
	cout<<Pair_Check[i]<<" ";
	cout<<endl;
	for (int i=0;i<8;++i)
	cout<<Single_Check[i]<<" ";
	cout<<endl;*/
}
void LogicDisplay() {
	if (len == 0)
		return;
	cout << "\nThe Logic is ";
	if (Octet_Check == true) {
		cout << "1.\n";
		return;
	}
	if (Quad_Check[0] == true) {
		cout << "X'+";
	}
	if (Quad_Check[1] == true) {
		cout << "X+";
	}
	if (Quad_Check[2] == true) {
		cout << "Y'+";
	}
	if (Quad_Check[3] == true) {
		cout << "Z+";
	}
	if (Quad_Check[4] == true) {
		cout << "Y+";
	}
	if (Quad_Check[5] == true) {
		cout << "Z'+";
	}

	if (Pair_Check[0] == true) {
		cout << "X'Y'+";
	}
	if (Pair_Check[1] == true) {
		cout << "X'Z+";
	}
	if (Pair_Check[2] == true) {
		cout << "X'Y+";
	}
	if (Pair_Check[3] == true) {
		cout << "XY'+";

	}
	if (Pair_Check[4] == true) {
		cout << "XZ+";
	}
	if (Pair_Check[5] == true) {
		cout << "XY+";
	}
	if (Pair_Check[6] == true) {
		cout << "Y'Z'+";
	}
	if (Pair_Check[7] == true) {
		cout << "Y'Z+";
	}
	if (Pair_Check[8] == true) {
		cout << "YZ+";
	}
	if (Pair_Check[9] == true) {
		cout << "YZ'+";
	}
	if (Pair_Check[10] == true) {
		cout << "X'Z'+";

	}
	if (Pair_Check[11] == true) {
		cout << "XZ'+";
	}

	if (Single_Check[0] == true) {
		cout << "X'Y'Z'+";
	}
	if (Single_Check[1] == true) {
		cout << "X'Y'Z+";

	}
	if (Single_Check[2] == true) {
		cout << "X'YZ+";
	}
	if (Single_Check[3] == true) {
		cout << "X'YZ'+";
	}
	if (Single_Check[4] == true) {
		cout << "XY'Z'+";
	}
	if (Single_Check[5] == true) {
		cout << "XY'Z+";
	}
	if (Single_Check[6] == true) {
		cout << "XYZ+";
	}
	if (Single_Check[7] == true) {
		cout << "XYZ'+";
	}

	cout << "\b.\n";
}
int main() {
	cout << "\t<<<<<<<<<<	3 Variable K-Map	>>>>>>>>>>\t\n";
	cout << "\t\t<<<	ONLY FOR MIN-TERM's	>>>\t\n\n";

	Input();
	Display();
	Logic();
	LogicDisplay();
	system("PAUSE");
	return 0;
}


