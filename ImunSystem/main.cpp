#include <iostream>
#include <vector>
#include "Antigen.h"
#include "Antibody.h"
#include "ImunSystem.h"
#include <time.h>

int main() {
	srand(time(NULL));

	int ag1[4][3] = {
		{ 0, 1, 0 },
		{ 0, 1, 0 },
		{ 0, 1, 0 },
		{ 0, 1, 0 }
	};
	int ag2[4][3] = {
		{ 1, 0, 1 },
		{ 1, 0, 1 },
		{ 1, 1, 1 },
		{ 0, 0, 1 }
	};
	int ag3[4][3] = {
		{ 1, 1, 1 },
		{ 0, 0, 1 },
		{ 0, 0, 1 },
		{ 0, 0, 1 }
	};

	std::vector<Antigen*> antigens;
	Antigen* ag = new Antigen(ag1);
	antigens.push_back(ag);
	ag = new Antigen(ag2);
	antigens.push_back(ag);
	ag = new Antigen(ag3);
	antigens.push_back(ag);

	ImunSystem* imunSystem = new ImunSystem(antigens);
	imunSystem->start();

	return 0;
}