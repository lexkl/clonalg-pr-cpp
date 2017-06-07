#include "Antibody.h"
#include <time.h>
#include <stdlib.h>

/*****************************************************************************/

Antibody::Antibody( int _array[Row_Number][Column_Number] )
	: Base(_array)
{
}


/*****************************************************************************/


Antibody::Antibody( const Antibody & _antibody )
{
	for (int i = 0; i < Row_Number; i++)
		for (int j = 0; j < Column_Number; j++)
			m_aMatrix[i][j] = _antibody(i, j);

	m_nAffinity = 13;
	m_pTargetAntigen = _antibody.getTargetAntigen();
	m_pParentAntibody = _antibody.getParentAntibody();
}


/*****************************************************************************/


Antibody::Antibody()
	: Base()
{
	m_nAffinity = 13;
	m_pTargetAntigen = nullptr;
	m_pParentAntibody = nullptr;
	
	for (int i = 0; i < Row_Number; i++)
	{
		for (int j = 0; j < Column_Number; j++)
		{
			m_aMatrix[i][j] = rand() % 2;
		}
	}
}


/*****************************************************************************/


Antibody::~Antibody()
{
}


/*****************************************************************************/


void Antibody::countAffinity( Antigen * _pAntigen )
{
	int affinity = 0;
	for (int i = 0; i < Row_Number; i++)
	{
		for (int j = 0; j < Column_Number; j++)
		{
			if ((*this)(i, j) != (*_pAntigen)(i, j))
				affinity++;
		}
	}

	if (affinity < m_nAffinity)
	{
		m_nAffinity = affinity;
		m_pTargetAntigen = _pAntigen;
	}
}


/*****************************************************************************/


void Antibody::mutate()
{
	for (int i = 0; i < Row_Number; i++)
	{
		for (int j = 0; j < Column_Number; j++)
		{
			if (rand() % 10 < 3)
				m_aMatrix[i][j] ^= 1;
		}
	}
}


/*****************************************************************************/
