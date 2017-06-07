#include "ImunSystem.h"

/*****************************************************************************/


ImunSystem::ImunSystem(const std::vector<Antigen*> & _antigens )
	:m_antigens(_antigens)
{
	m_antibodies = generateAb();
	m_nGeneration = Generation_Number;
}


/*****************************************************************************/


ImunSystem::~ImunSystem()
{
	for (int i = 0; i < m_antigens.size(); i++)
		delete m_antigens[i];
	for (int i = 0; i < m_antibodies.size(); i++)
		delete m_antibodies[i];
	for (auto it = m_memoryAb.begin(); it != m_memoryAb.end(); it++)
		delete it->second;
}


/*****************************************************************************/


void
ImunSystem::start()
{
	while (m_nGeneration >= 0)
	{
		// Вычисление аффинности антител к антигену
		// Affinity computation
		checkAffinity(m_antibodies);

		// Отбор антител для клонирования
		// Selection of antibodies for cloning
		std::vector<Antibody*> suitableAb;
		suitableAb = selectBestAb(m_antibodies);

		// Клонирование
		// Operator - CLONE
		std::vector<Antibody*> clonePopulation;
		clonePopulation = clone(suitableAb, Clone_Number);

		// Мутация клонов
		// Operator - MUTATE
		mutate(clonePopulation);

		// Вычисление аффинности клонов к антигену
		// Affinity computation
		checkAffinity(clonePopulation);

		// Отбор 1 клона и замена ним соответствующего антитела
		// If clone is better than parent => swap them
		sortByAffinity(clonePopulation);
		cloneSelection(clonePopulation);

		// Редактирование популяции
		// Remove the worst antibodies and add new ones
		sortByAffinity(m_antibodies);
		m_antibodies.erase(m_antibodies.end() - New_Ab_Number, m_antibodies.end());
		std::vector<Antibody*> freshBlood = generateAb(New_Ab_Number);
		m_antibodies.insert(m_antibodies.end(), freshBlood.begin(), freshBlood.end());

		--m_nGeneration;
	}

	printResult();

}


/*****************************************************************************/


std::vector<Antibody*>
ImunSystem::generateAb( int _amount )
{
	std::vector<Antibody*> antibodies;
	for (int i = 0; i < _amount; i++)
	{
		Antibody* ab = new Antibody();
		antibodies.push_back(ab);
	}
	return antibodies;
}


/*****************************************************************************/


void
ImunSystem::checkAffinity( const std::vector<Antibody*> & _antibodies )
{
	for (auto &ag : m_antigens)
		for (auto &ab : _antibodies)
			ab->countAffinity(ag);
}


/*****************************************************************************/


std::vector<Antibody*>
ImunSystem::selectBestAb( const std::vector<Antibody*> & _antibodies )
{
	std::vector<Antibody*> bestAb;
	for (int i = 0; i < m_antigens.size(); i++)
	{
		std::vector<Antibody*> suitableAb;
		for (int j = 0; j < _antibodies.size(); j++)
		{
			if (_antibodies[j]->getTargetAntigen() == m_antigens[i])
				suitableAb.push_back(_antibodies[j]);
		}
		sortByAffinity(suitableAb);
		suitableAb.erase(suitableAb.begin() + 4, suitableAb.end());
		bestAb.insert(bestAb.end(), suitableAb.begin(), suitableAb.end());
	}
	return bestAb;
}


/*****************************************************************************/


std::vector<Antibody*>
ImunSystem::clone( const std::vector<Antibody*> & _antibodies, int _cloneNum )
{
	std::vector<Antibody*> clones;
	for (size_t i = 0; i < _antibodies.size(); i++)
	{
		for (int j = 0; j < _cloneNum; j++)
		{
			Antibody* clone = new Antibody(*_antibodies[i]);
			clone->setParentAntibody(_antibodies[i]);
			clones.push_back(clone);
		}
	}

	return clones;
}


/*****************************************************************************/


void
ImunSystem::mutate( const std::vector<Antibody*> & _antibodies )
{
	for (auto clone : _antibodies)
		clone->mutate();
}


/*****************************************************************************/


void
ImunSystem::cloneSelection( const std::vector<Antibody*> & _clones )
{
	for (auto &ag : m_antigens)
	{
		for (auto &clone : _clones)
		{
			if (clone->getTargetAntigen() == ag)
			{
				if (clone->getAffinity() < clone->getParentAntibody()->getAffinity())
				{
					auto it = std::find(m_antibodies.begin(),
										m_antibodies.end(),
										clone->getParentAntibody());
					m_antibodies.erase(it);
					m_antibodies.push_back(clone);
					m_memoryAb[ag] = clone;
					break;
				}
				else
				{
					m_memoryAb[ag] = clone->getParentAntibody();
				}
			}
		}
	}
}


/*****************************************************************************/


void
ImunSystem::addToMemory( Antigen * _antigen, Antibody * _antibody )
{
	auto it = m_memoryAb.find(_antigen);
	if (it != m_memoryAb.end())
	{
		int affinity = m_memoryAb.at(_antigen)->getAffinity();
		if (affinity > _antibody->getAffinity())
			m_memoryAb.at(_antigen) = _antibody;
	}
	else m_memoryAb.at(_antigen) = _antibody;
		
}


/*****************************************************************************/


void
ImunSystem::sortByAffinity( std::vector<Antibody*> & _antibodies )
{
	std::sort(_antibodies.begin(), _antibodies.end(),
		[](const Antibody* _a, const Antibody* _b) -> bool
	{
		return (*_a).getAffinity() < (*_b).getAffinity();
	});
}


/*****************************************************************************/


void
ImunSystem::printResult()
{
	for (auto &ab : m_memoryAb)
	{
		std::cout 
			<< (*ab.first)(0, 0) << (*ab.first)(0, 1) << (*ab.first)(0, 2) << "\t"
			<< (*ab.second)(0, 0) << (*ab.second)(0, 1) << (*ab.second)(0, 2) << "\n"
			<< (*ab.first)(1, 0) << (*ab.first)(1, 1) << (*ab.first)(1, 2) << "\t"
			<< (*ab.second)(1, 0) << (*ab.second)(1, 1) << (*ab.second)(1, 2) << "\n"
			<< (*ab.first)(2, 0) << (*ab.first)(2, 1) << (*ab.first)(2, 2) << "\t"
			<< (*ab.second)(2, 0) << (*ab.second)(2, 1) << (*ab.second)(2, 2) << "\n"
			<< (*ab.first)(3, 0) << (*ab.first)(3, 1) << (*ab.first)(3, 2) << "\t"
			<< (*ab.second)(3, 0) << (*ab.second)(3, 1) << (*ab.second)(3, 2) << "\n"
			<< "Affinity = " << (ab.second->getAffinity()) << std::endl;
		std::cout << "--------------" << std::endl;
	}
}


/*****************************************************************************/
