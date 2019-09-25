#include "TestAVerMedia.h"
#include <iostream>
#include <Windows.h>
#include <AVerCapAPI_Pro.h>

void testGetDeviceNum()
{
	// Always init before using API
	AVerInitialize();

	// Number of cards
	DWORD dwDeviceNumber = 0;

	// Return code of the method
	LONG lCode = AVerGetDeviceNum(&dwDeviceNumber);

	// Printing results
	if (lCode == CAP_EC_SUCCESS)
		std::cout << "Worked ! Number of cards : " << dwDeviceNumber << std::endl;
	else if (lCode == CAP_EC_INVALID_PARAM)
		std::cout << "Invalid parameter..." << std::endl << std::endl;

	// Always uninit to free stuff
	AVerUninitialize();
}

void testGetDeviceName()
{
	// Always init before using API
	AVerInitialize();

	// Number of cards
	DWORD dwDeviceNumber = 0;
	AVerGetDeviceNum(&dwDeviceNumber);

	for (int iDeviceIndex = 0; iDeviceIndex < dwDeviceNumber; iDeviceIndex++)
	{
		// Device's name
		WCHAR wszName[260] = { L'\0' };
		char szName[260] = { '\0' };
		char* pszName = szName;

		// Calling the method
		AVerGetDeviceName(iDeviceIndex, wszName);

		// Printing the results
		WideCharToMultiByte(CP_ACP, 0, wszName, -1, pszName, 260, NULL, NULL);
		printf(pszName);
		std::cout << std::endl;
	}

	// Always uninit to free stuff
	AVerUninitialize();
}

void testGetDeviceSerialNum()
{
	// Always init before using API
	AVerInitialize();

	// Number of cards
	DWORD dwDeviceNumber = 0;
	AVerGetDeviceNum(&dwDeviceNumber);

	for (int iDeviceIndex = 0; iDeviceIndex < dwDeviceNumber; iDeviceIndex++)
	{
		// Device's serial number
		BYTE pbySerialNum[12] = { 0 };
		char cSerialNum[12] = { '\0' };
		/*char* pcSerialNum = cSerialNum;*/
		
		// Calling the method
		AVerGetDeviceSerialNum(iDeviceIndex, pbySerialNum);

		// Printing results
		for (int i = 0; i < 12; i++)
		{
			cSerialNum[i] = (char)pbySerialNum[i];
		}

		std::string s(cSerialNum, sizeof(cSerialNum));

		std::cout << s << std::endl;
	}

	// Always uninit to free stuff
	AVerUninitialize();
}

int main(int argc, char** argv)
{
	testGetDeviceNum();
	std::cout << std::endl;
	testGetDeviceName();
	std::cout << std::endl;
	testGetDeviceSerialNum();

	return 0;
}