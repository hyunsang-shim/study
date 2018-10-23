#include "stdafx.h"
#include "cRawLoader.h"


cRawLoader::cRawLoader()
{
}


cRawLoader::~cRawLoader()
{
}

vector<int> cRawLoader::RawLoad(string filepath, int &filesize)
{
	vector<int> heights;

	ifstream file;
	file.open(filepath, ios::in | ios::binary);

	int nFSize;
	file.seekg(0, ios::end);
	filesize = (int)file.tellg();
	printf("File Size in %d Bytes.\n", filesize);
	file.seekg(0, ios::beg);
	char tmp;
	unsigned int cnt = 0;

	while (cnt++ < filesize)
	{		
		file.read(&tmp, 1);
		heights.push_back((int)tmp + 128);
		/*printf("#%06d = [ %4d ]  ", cnt, tmp);
		if (cnt % 5 == 0)
			printf("\n");*/
	}

	printf("%d Byte(s) loaded.\n", heights.size());

	file.close();

	return heights;
}
