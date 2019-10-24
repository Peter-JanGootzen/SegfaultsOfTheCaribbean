#ifndef FILE_HARBOR_DISTANCE_HPP
#define FILE_HARBOR_DISTANCE_HPP
#include "models/harbor.hpp"

// WHooh no rule of five here!
// This class is not the owner of it's heap data, so no destructor needed
class HarborDistance {
public:
	HarborDistance(Harbor* from, Harbor* to, int distance) noexcept;
	// This is a pointer because it will get used in the player, which needs a ptr
	Harbor* getFrom() const noexcept;
	// This is a pointer because it will get used in the player, which needs a ptr
	Harbor* getTo() const noexcept;
	int getDistance() const noexcept;
private:
	Harbor* from;
	Harbor* to;
	int distance;
};

#endif