#ifndef EntityManager_hpp
#define EntityManager_hpp

#include <queue>
#include <functional>

namespace Engine
{
	namespace EntityManager
	{
		static unsigned _uniqueID = 0;
		std::priority_queue< unsigned, std::vector<unsigned>, std::greater<unsigned> > freeIDs;

		unsigned GetID() {
			if (freeIDs.empty()) {
				return ++_uniqueID;
			}
			unsigned ret = freeIDs.top();
			freeIDs.pop();
			return ret;
		}
	} /*END ENTITY MANAGER*/
} /*END ENGINE*/
#endif /*END INCLUDE GUARD*/