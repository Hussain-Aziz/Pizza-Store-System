#ifndef UTILS
#define UTILS
#include <string>
#include <vector>
#include <string.h>
using namespace std;
class Utils
{
public:
	template<class T>
	static int searchVector(vector<T> t, string id)
	{
		for (size_t i = 0; i < t.size(); i++)
		{
			if (t[i] == id) return i;
		}
		return -1;
	}
	template<class T>
	static int searchVector(vector<T*> t, string id)
	{
		for (size_t i = 0; i < t.size(); i++)
		{
			if (t[i] == id) return i;
		}
		return -1;
	}
	template<class T>
	static int searchVector(vector<T> t, int id)
	{
		for (size_t i = 0; i < t.size(); i++)
		{
			if (t[i] == id) return i;
		}
		return -1;
	}
	template<class T>
	static int searchVector(vector<T*> t, int id)
	{
		for (size_t i = 0; i < t.size(); i++)
		{
			if (t[i] == id) return i;
		}
		return -1;
	}
	template<class T>
	static string getNewId(vector<T> t, string prefix)
	{
		bool foundId = false;
		string id;
		while (!foundId)
		{
			id = prefix + to_string(getRandomNumber());
			int index = Utils::searchVector(t, id);
			if (index == -1)
			{
				foundId = true;
			}
		}
		return id;
	}

	static int getRandomNumber()
	{
		return (rand() % 9000 + 1000);
	}
};
#endif