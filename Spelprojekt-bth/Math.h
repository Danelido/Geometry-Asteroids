#ifndef MATH_H
#define MATH_H
#include <SFML/System/Vector2.hpp>
#include <cstdlib>

namespace CustomMath
{
	const float PI = 3.1415926535f;

	template<typename T>
	inline T getDistance(const sf::Vector2<T>& vec1, const sf::Vector2<T>& vec2)
	{
		sf::Vector2<T> diffVec = getDifference(vec1, vec2);
		T distance = sqrt(pow(diffVec.x, 2) + pow(diffVec.y, 2));
		
		return distance;
	}

	template<typename T>
	inline sf::Vector2<T> getDifference(const sf::Vector2<T>& vec1, const sf::Vector2<T>& vec2)
	{
		sf::Vector2<T> diffVec = vec2 - vec1;

		return diffVec;
	}

	template<typename T>
	inline sf::Vector2<T> getDifferenceNormalized(const sf::Vector2<T>& vec1, const sf::Vector2<T>& vec2)
	{
		T totLength = getDistance(vec1, vec2);
		sf::Vector2<T> normVec = getDifference(vec1, vec2) / totLength;

		return normVec;
	}

	///< Returns a angle in degrees
	template<typename T>
	inline T getAngle(const sf::Vector2<T>& vec1, const sf::Vector2<T>& vec2)
	{
		sf::Vector2<T> diffVec = getDifference(vec1, vec2);

		T angle = (atan2(diffVec.y, diffVec.x) * 180) / PI;

		return angle;
	}

	// intersection
	template<typename T>
	inline bool intersection(const sf::Vector2<T>& posOfElement1,T sizeOfElement1, const sf::Vector2<T>& posOfElement2, T sizeOfElement2)
	{	
		T distance = getDistance(posOfElement1,posOfElement2);

		if (distance < ((sizeOfElement1 / 2) + (sizeOfElement2 / 2)))
		{
			return true;
		}
		return false;
	}

}

#endif
