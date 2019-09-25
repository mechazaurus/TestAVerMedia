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

	for (unsigned int iDeviceIndex = 0; iDeviceIndex < dwDeviceNumber; iDeviceIndex++)
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

	for (unsigned int iDeviceIndex = 0; iDeviceIndex < dwDeviceNumber; iDeviceIndex++)
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

void testCaputreObject()
{
	// Always init before using API
	AVerInitialize();

	// Card index
	DWORD dwDeviceIndex = 4;

	// Handle to the capture object
	HANDLE* phCaptureObject = new HANDLE();

	// Get the capture object and give it to the handle
	LONG lCode = AVerCreateCaptureObject(dwDeviceIndex, NULL, phCaptureObject);

	// Use the returned code from the method
	if (lCode == CAP_EC_DEVICE_IN_USE)
		std::cout << "Capture card already in use." << std::endl;
	else if (lCode == CAP_EC_SUCCESS)
	{
		// Video infos
		INPUT_VIDEO_INFO inputVideoInfo = { 0 };
		inputVideoInfo.dwVersion = 2;

		// Calling methods
		AVerGetVideoInfo(*phCaptureObject, &inputVideoInfo);

		// Printing infos
		std::cout << "===== Video infos =====" << std::endl;
		std::cout << "Version : " << inputVideoInfo.dwVersion << std::endl;
		std::cout << "Width : " << inputVideoInfo.dwWidth << std::endl;
		std::cout << "Height : " << inputVideoInfo.dwHeight << std::endl;
		std::cout << "Frame rate : " << inputVideoInfo.dwFramerate << std::endl;
		std::cout << "=======================" << std::endl;
	}
	
	// Always uninit to free stuff
	AVerDeleteCaptureObject(phCaptureObject);
	AVerUninitialize();
}


/* CHECK SAMPLE : AVerCapSDKDemo_VC_Main
   PropRecordCommon.cpp
 */
void testRecordFile()
{
	// Always init before using API
	AVerInitialize();

	// Card index
	DWORD dwDeviceIndex = 4;

	// Handle to the capture object
	HANDLE* phCaptureObject = new HANDLE();

	// Get the capture object and give it to the handle
	LONG lCode = AVerCreateCaptureObject(dwDeviceIndex, NULL, phCaptureObject);

	if (lCode == CAP_EC_DEVICE_IN_USE)
		std::cout << "Device already in use..." << std::endl;


	// Always uninit to free stuff
	AVerDeleteCaptureObject(phCaptureObject);
	AVerUninitialize();
}

int main(int argc, char** argv)
{
	/*testGetDeviceNum();
	std::cout << std::endl;
	testGetDeviceName();
	std::cout << std::endl;
	testGetDeviceSerialNum();*/

	testCaputreObject();

	return 0;
}