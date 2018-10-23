#pragma once
class cRawLoader
{
public:
	cRawLoader();
	~cRawLoader();

	static vector<int> RawLoad(string filepath, int& filesize);
};

