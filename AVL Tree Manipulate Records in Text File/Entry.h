#pragma once
#ifndef ENTRY_H
#define ENTRY_H

#include <string>

template <typename C, typename P, typename N>
class Entry {					
public:						
	typedef C CountyCode;
	typedef P CountyPopulation;
	typedef N CountyName;

	Entry(const C& c = C(), const P& p = P(), const N& n = N())
		: _countyCode(c), _countyPopulation(p), _countyName(n) { }

	const C& countyCode() const
	{ 
		return _countyCode;
	}		
	const P& countyPopulation() const 
	{ 
		return _countyPopulation; 
	}	
	const N& countyName() const 
	{ 
		return _countyName; 
	}	

	void setCountyCode(const C& c) 
	{ 
		_countyCode = c; 
	}		
	
	void setCountyPopulation(const P& p) 
	{ 
		_countyPopulation = p; 
	}	
	void setCountyName(const N& n) 
	{ 
		_countyName = n; 
	}	


private:						
	C _countyCode;
	P _countyPopulation; 
	N _countyName;						

	friend class AVLTree;
};
#endif
