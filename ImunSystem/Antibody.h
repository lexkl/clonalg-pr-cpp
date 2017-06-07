#pragma once

/*****************************************************************************/

#include "Base.h"
#include "Antigen.h"
#include "constants.h"

/*****************************************************************************/

class Antibody
	: public Base
{

/*-----------------------------------------------------------------*/

public:

/*-----------------------------------------------------------------*/

	Antibody();

	Antibody( int _array[Row_Number][Column_Number] );

	Antibody( const Antibody & _antibody );

	~Antibody();

	void countAffinity( Antigen * _pAntigen );

	void mutate();

	int getAffinity() const;

	Antigen* getTargetAntigen() const;

	Antibody* getParentAntibody() const;

	void setParentAntibody(Antibody* _pAntibody);

/*-----------------------------------------------------------------*/

private:

/*-----------------------------------------------------------------*/

	int m_nAffinity;

	Antigen* m_pTargetAntigen;

	Antibody* m_pParentAntibody;

};


/*****************************************************************************/


inline
int Antibody::getAffinity() const
{
	return m_nAffinity;
}


/*****************************************************************************/


inline
Antigen* Antibody::getTargetAntigen() const
{
	return m_pTargetAntigen;
}


/*****************************************************************************/


inline
Antibody* Antibody::getParentAntibody() const
{
	return m_pParentAntibody;
}


/*****************************************************************************/


inline
void Antibody::setParentAntibody(Antibody* _pAntibody)
{
	m_pParentAntibody = _pAntibody;
}


/*****************************************************************************/

