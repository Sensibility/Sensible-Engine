#ifndef _BASE_PROVIDER_H_
#define _BASE_PROVIDER_H_
#include <string>


class BaseProvider
{
public:
	BaseProvider() = default;
	virtual ~BaseProvider() = default;
	virtual std::string* Diagnostics() { return nullptr; };

	virtual bool IsInit() { return true; };

	virtual std::string GetKey() = 0;
	static std::string GetKeyStatic() { return ""; }
private:
};

std::vector<BaseProvider*> providers = std::vector<BaseProvider*>();
template<class T>
BaseProvider* GetProvider()
{
	for(auto& prov: providers)
	{
		if (prov->GetKey() == T::GetKeyStatic())
			return prov;
	}
	BaseProvider* prov = new T();
	providers.push_back(prov);
	return prov;
}

#endif _BASE_PROVIDER_H_