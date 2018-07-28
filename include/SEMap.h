#ifndef _SE_MAP_H_
#define _SE_MAP_H_

template <class T, class U>
class SEMap
{
public:
	bool Find(T pNeedle)
	{
		return map_.find(pNeedle) != map_.end();
	}

	void Erase(T pNeedle)
	{
		if (Find(pNeedle))
			map_.erase(pNeedle);
	}
	bool Insert(T pKey, U pValue)
	{
		if (!Find(pKey))
		{
			map_.insert(std::pair<T, U>(pKey, pValue));
			return true;
		}
		return false;
	}

	U operator[](T pNeedle)
	{
		if (Find(pNeedle))
			return map_.at(pNeedle);
		return nullptr;
	}

	typedef typename std::map<T, U> map_type;
	typedef typename map_type::iterator iterator;
	typedef typename map_type::const_iterator const_iterator;
	iterator begin() noexcept { return map_.begin(); }
	iterator end() noexcept { return map_.end(); }
	const_iterator cbegin() noexcept { return map_.cbegin(); }
	const_iterator cend() noexcept { return map_.cend(); }
private:
	map_type map_ = map_type();
};

#endif _SE_MAP_H_