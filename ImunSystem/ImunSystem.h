
#pragma once

/*****************************************************************************/

#include "Antigen.h"
#include "Antibody.h"
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>

/*****************************************************************************/

class ImunSystem
{

/*-----------------------------------------------------------------*/

public:

/*-----------------------------------------------------------------*/

	ImunSystem (const std::vector<Antigen*> & _antigens );

	~ ImunSystem ();

	void start();

/*-----------------------------------------------------------------*/

private:

/*-----------------------------------------------------------------*/

	int m_nGeneration;


	std::vector<Antibody*> generateAb( int _nAmount = Population_Size );

	std::vector<Antibody*> selectBestAb( const std::vector<Antibody*> & _antibodies );

	std::vector<Antibody*> clone( const std::vector<Antibody*> & _antibodies, int _nCloneNum );

	void checkAffinity( const std::vector<Antibody*> & _antibodies);

	void mutate (const std::vector<Antibody*> & _antibodies );

	void cloneSelection( const std::vector<Antibody*> & _clones );

	void addToMemory( Antigen* _antigen, Antibody* _antibody );

	void sortByAffinity( std::vector<Antibody*> & _antibodies );

	void printResult();

/*-----------------------------------------------------------------*/

	std::vector<Antigen*> m_antigens;

	std::vector<Antibody*> m_antibodies;

	std::map<Antigen*, Antibody*> m_memoryAb;

};


/*****************************************************************************/

