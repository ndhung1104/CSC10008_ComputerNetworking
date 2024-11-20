#ifndef UTILITY
#define UTILITY
#pragma once
#include <string>
#include <windows.h>
#include<iostream>
#include<fstream>
#include<vector>
#include<thread>
#include<chrono>
#include<atomic>
#include <shobjidl.h>
#include <shlguid.h>
#include <tlhelp32.h>
// #include "service.cpp"
//#include "WebcamRecorder.h"
#define BUFFER_SIZE 1024

class Computer //: public ServiceManager //public WebcamRecorder
{
public:
	// ServiceManager service;
	void shutdown(); // doc lap
	void reset(); // doc lap
	void keyLogger(SOCKET serverSocket); // viet ca 2 ben. Kenh giao tiep binh thuong la port 55555, bat them 1 kenh moi o port 55556 va tren port do thi client se nghe server cho toi khi client danh lenh dung len port 55555
	void listApp(); // viet ca 2 ben
	void startApp(std::string name); // doc lap (hoi tiep theo kieu start co thanh cong hay khong va gui nguoc lai cho client)
	void stopApp(std::string name); // doc lap ////////////
	void copyFile(SOCKET clientSocket, const std::string& filePath);
	// using ServiceManager::listServices(); // viet ca 2 ben
	// using ServiceManager::startService(std::string name); // doc lap
	// using ServiceManager::stopService(std::string name); // doc lap
	// void screenShot(); // viet ca 2 ben
	// void copyFile(std::string name); // viet ca 2 ben
	// void startWebcam(); // viet ca 2 ben, nghe lenh o port 55555 
	// void stopWebcam(); // luu file lai roi xai copyFile de gui qua server
	// Computer();
	// ~Computer();

private:
	
};

// Computer::Computer()
// {
// }

// Computer::~Computer()
// {
// }

#endif