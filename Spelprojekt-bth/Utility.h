#ifndef UTILITY_H
#define UTILITY_H
#include <cstdlib>
#include <SFML/System/Vector2.hpp>
namespace Utility
{
	template<typename T>
	inline T getRandomNumber(const T& lowerBound, const T& upperBound)
	{
		if (lowerBound == upperBound)
		{
			return upperBound;
		}

		//T magicNumber = (rand()) % (int)(upperBound - lowerBound) + (lowerBound + 1);
		T magicNumber = (rand()) % (int)(upperBound - lowerBound + 1) + lowerBound;
		return magicNumber;
	}
	

	template<typename T>
	inline sf::Vector2<T> getRandomVector(const T& lowerBound, const T& upperBound)
	{
		sf::Vector2<T> magicVector = sf::Vector2<T>(getRandomNumber(lowerBound, upperBound), getRandomNumber(lowerBound, upperBound));

		return magicVector;
	}

	template<typename T>
	inline sf::Vector2<T> getRandomVector(const T& minX, const T& maxX, const T& minY, const T& maxY)
	{
		sf::Vector2<T> magicVector = sf::Vector2<T>(getRandomNumber(minX, maxX), getRandomNumber(minY, maxY));

		return magicVector;
	}

}


#endif
