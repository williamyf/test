// GetBmpInfo.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <windows.h>

int main(int argc, char** argv)
{
	int pos = 0x0012;
	std::ifstream ifs("snapshot.bmp", std::ios_base::binary);
	std::ofstream ofs("bmp.header", std::ios_base::binary);
	ifs.seekg(0, std::ios_base::end);
	int totalbytes = ifs.tellg();
	std::cout << "total bytes : " << totalbytes << std::endl;
	ifs.seekg(pos, std::ios_base::beg);
	int width(0), height(0);
	ifs.read((char*)&width, 4);
	ifs.read((char*)&height, 4);
	std::cout << "width: " << width << std::endl;
	std::cout << "height: " << height << std::endl;
	// save the bmp header content to bmp.header file
	char bmp_header[54];
	ifs.seekg(0, std::ios_base::beg);
	ifs.read(bmp_header, 54);
	ofs.write(bmp_header, 54);
	ofs.close();
	// read the first pixcel
	ifs.seekg(54, std::ios_base::beg);	
	int rgba = 0;
	ifs.read((char*)&rgba, 4);
	std::cout << "rgba :" << rgba << std::endl;
	printf_s("r,g,b = (%d,%d,%d)\n", GetBValue(rgba), GetGValue(rgba), GetRValue(rgba));
	
	ifs.close();
	std::cout << (int)('A') << std::endl;
	std::cout << 0x41 << std::endl;
	system("pause");
    return 0;
}

