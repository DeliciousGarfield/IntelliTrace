#pragma once

#include <QApplication>

#include <windows.h>
#include <Shlwapi.h>
#include <stdio.h>
#include <tchar.h>
#include <psapi.h>
#include <time.h>
#include <iostream>

#include <map>
#include <vector>
#include <string>

#include "tinyxml2.h"
#include "tracerui.h"

#pragma comment(lib,"shlwapi.lib")

class Tracer : QObject
{
	Q_OBJECT
public:
	struct interval
	{
		time_t start;
		time_t end;
	};
private:
	std::map<std::wstring, interval> current;
	std::map<std::wstring, std::vector<interval> > history;

	static Tracer* instance;
	BOOL running;
	HANDLE hTracerThread;
	HANDLE hLogThread;
	std::wstring configDirectory;
	int sampleFrequency;

	TracerUI *ui;

public:
	static Tracer* getInstance();
	void startUp();
	void shutDown();
	BOOL isRunning();
	BOOL setupConfigDirectory();
	std::wstring getConfigDirectory();
	std::map<std::wstring, interval> getCurrentRecord();
	std::map<std::wstring, std::vector<interval> > getHistoryRecord();
	std::string stringOfRecordTime();
	std::wstring stringOfCurrentRecord();
	std::wstring stringOfHistoryRecord();
	void printRecordTime();
	void printCurrentRecord();
	void printHistoryRecord();
	void enableLog();
	void disableLog();
	int getSampleFrequency();
	void setSampleFrequency(int rate);

	void createUI();
private:
	Tracer();
	static BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam);
	static DWORD WINAPI run(LPVOID lpParam);
	BOOL saveToXML(std::map<std::wstring, std::vector<interval> > history);
	void saveIcon(HICON hIcon, LPCTSTR szIconFileName);
	static DWORD WINAPI log(LPVOID lpParam);
signals:
	void log(QString info);
};

