#pragma once
#include <string>
#include <boost/functional/hash.hpp>

namespace model
{
	class Coordinater
	{
	public:
		Coordinater(int x, int y);
		Coordinater(std::string coord);
		~Coordinater();

		int getX();
		int getY();

		inline bool operator==(const Coordinater &other) const
		{
			return x_ == other.x_ && y_ == other.y_;
		}

	private:
		int x_;
		int y_;
	};

	struct KeyHasher
	{
		std::size_t operator()(Coordinater& key) const
		{
			using boost::hash_value;
			using boost::hash_combine;

			std::size_t seed = 0;

			hash_combine(seed, hash_value(key.getX()));
			hash_combine(seed, hash_value(key.getY()));

			return seed;
		}
	};
}

