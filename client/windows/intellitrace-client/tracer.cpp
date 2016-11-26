#include "tracer.h"
#include <Olectl.h>
#include "HelperUtils.h"
#include <sstream>
#include <iomanip>

Tracer* Tracer::instance = NULL;

Tracer::Tracer() {
	setSampleFrequency(30000);

	if (setupConfigDirectory() == FALSE)
		exit(1);
}

Tracer* Tracer::getInstance() {
	if (instance == NULL) {
		instance = new Tracer();
	}
	return instance;
}

BOOL CALLBACK Tracer::EnumWindowsProc(HWND hWnd, LPARAM lParam)
{
	Tracer* tracer = getInstance();

	DWORD processId;
	TCHAR szCaption[256];
	TCHAR szProcessName[256];
	std::wstring appName;

	GetWindowThreadProcessId(hWnd, &processId);

	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processId);

	if (NULL == hProcess)
		return TRUE;

	GetModuleFileNameEx(hProcess, NULL, szProcessName, sizeof(szProcessName) / sizeof(TCHAR));
	appName = HelperUtils::appName(HelperUtils::baseName(szProcessName));

	GetWindowText(hWnd, szCaption, sizeof(szCaption) / sizeof(TCHAR));

	if (IsWindowVisible(hWnd) && wcslen(szCaption) != 0 && !(GetWindowLong(hWnd, GWL_STYLE) & WS_POPUP)) {

		time_t now = time(NULL);

		std::wstring processName = szProcessName;
		std::map<std::wstring, interval>::iterator iter = tracer->current.find(processName);
		if (iter == tracer->current.end()) {
			interval span;
			span.start = now;
			span.end = now;
			tracer->current.insert(std::map<std::wstring, interval>::value_type(processName, span));
		}
		else {
			iter->second.end = now;
		}

		std::wstring iconFilePath;
		iconFilePath = tracer->getConfigDirectory() + TEXT("\\icons");

		if (!PathIsDirectoryW(iconFilePath.c_str())) {
			CreateDirectoryW(iconFilePath.c_str(), NULL);
		}

		std::wstring iconFileName = appName + TEXT(".ico");

		HICON hIcon = (HICON)SendMessage(hWnd, WM_GETICON, ICON_BIG, 0);
		if (hIcon == NULL) {
			hIcon = (HICON)GetClassLongPtr(hWnd, GCL_HICON);
		}
		tracer->saveIcon(hIcon, (iconFilePath + TEXT("\\") + iconFileName).c_str());
	}

	CloseHandle(hProcess);
	return TRUE;
}

void Tracer::saveIcon(HICON hIcon, LPCTSTR szIconFileName)
{
	if (hIcon == NULL || szIconFileName == NULL)
		return;

	PICTDESC picdesc;
	picdesc.cbSizeofstruct = sizeof(PICTDESC);
	picdesc.picType = PICTYPE_ICON;
	picdesc.icon.hicon = hIcon;

	IPicture* pPicture = NULL;
	OleCreatePictureIndirect(&picdesc, IID_IPicture, TRUE, (VOID**)&pPicture);
	LPSTREAM pStream;
	CreateStreamOnHGlobal(NULL, TRUE, &pStream);

	LONG size;
	HRESULT hr = pPicture->SaveAsFile(pStream, TRUE, &size);

	TCHAR pathbuf[1024];
	wcscpy(pathbuf, szIconFileName);

	HANDLE hIconFile = CreateFile(szIconFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);

	LARGE_INTEGER li;
	li.HighPart = 0;
	li.LowPart = 0;

	ULARGE_INTEGER ulnewpos;
	pStream->Seek(li, STREAM_SEEK_SET, &ulnewpos);

	ULONG uReadCount = 1;
	while (uReadCount > 0)
	{
		pStream->Read(pathbuf, sizeof(pathbuf), &uReadCount);
		if (uReadCount > 0)
			WriteFile(hIconFile, pathbuf, uReadCount, NULL, NULL);
	}

	pStream->Release();
	CloseHandle(hIconFile);
}

BOOL Tracer::setupConfigDirectory()
{
	BOOL success = FALSE;

	TCHAR home[1024];
	GetEnvironmentVariable(TEXT("HOMEPATH"), home, sizeof(home) / sizeof(TCHAR));

	configDirectory = std::wstring(home) + TEXT("\\.intellitrace");

	if (!PathIsDirectoryW(configDirectory.c_str())) {
		success = CreateDirectoryW(configDirectory.c_str(), NULL);
	}
	else {
		success = TRUE;
	}

	return success;
}

std::wstring Tracer::getConfigDirectory() {
	return configDirectory;
}

std::map<std::wstring, Tracer::interval> Tracer::getCurrentRecord()
{
	return current;
}

std::map<std::wstring, std::vector<Tracer::interval> > Tracer::getHistoryRecord()
{
	return history;
}

std::string Tracer::stringOfRecordTime()
{
	std::ostringstream ss;

	time_t now = time(NULL);
	struct tm localtime;
	localtime_s(&localtime, &now);

	CHAR format[256];
	strftime(format, sizeof(format) / sizeof(CHAR), "%Y-%m-%d %H:%M:%S", &localtime);
	ss << "============================= " << format << " =============================" << std::endl;

	return ss.str();
}

std::wstring Tracer::stringOfCurrentRecord()
{
	std::wostringstream ss;
	ss.setf(std::ios::left);
	ss << std::setw(30) << "Active" << std::setw(30) << "Stat Start" << std::setw(30) << "Stat End" << std::endl;
	for (std::map<std::wstring, interval>::iterator iter = current.begin(); iter != current.end(); ++iter) {
		ss << std::setw(30) << HelperUtils::baseName(iter->first) << std::setw(30) << HelperUtils::localTime(iter->second.start) << std::setw(30) << HelperUtils::localTime(iter->second.end) << std::endl;
	}

	return ss.str();
}

std::wstring Tracer::stringOfHistoryRecord()
{
	std::wostringstream ss;
	ss.setf(std::ios::left);
	ss << std::setw(30) << "History" << std::setw(30) << "Start At" << std::setw(30) << "End At" << std::endl;
	for (std::map<std::wstring, std::vector<interval> >::iterator iter = history.begin(); iter != history.end(); ++iter) {
		ss << HelperUtils::baseName(iter->first) << std::endl;
		for (size_t i = 0; i < iter->second.size(); ++i) {
			ss << std::setw(30) << ' ' << std::setw(30) << HelperUtils::localTime(iter->second[i].start) << std::setw(30) << HelperUtils::localTime(iter->second[i].end) << std::endl;
		}
	}

	return ss.str();
}

void Tracer::printRecordTime()
{
	time_t now = time(NULL);

	struct tm localtime;
	localtime_s(&localtime, &now);

	CHAR format[256];
	strftime(format, sizeof(format) / sizeof(CHAR), "%Y-%m-%d %H:%M:%S", &localtime);
	printf("========== %s ==========\n", format);
}

void Tracer::printCurrentRecord()
{
	std::cout << std::endl << "Map<ProcessName, Interval>:" << std::endl;
	for (std::map<std::wstring, interval>::iterator iter = current.begin(); iter != current.end(); ++iter) {
		std::wcout << iter->first << "\t" << iter->second.start << "\t" << iter->second.end << std::endl;
	}
}
void Tracer::printHistoryRecord()
{
	std::cout << std::endl << "Map<ProcessName, Vector<Interval>>:" << std::endl;
	for (std::map<std::wstring, std::vector<interval> >::iterator iter = history.begin(); iter != history.end(); ++iter) {
		std::wcout << iter->first << std::endl;
		for (size_t i = 0; i < iter->second.size(); ++i) {
			std::cout << iter->second[i].start << "\t" << iter->second[i].end << std::endl;
		}
	}
}

BOOL Tracer::saveToXML(std::map<std::wstring, std::vector<interval> > history)
{
	using tinyxml2::XMLDocument;
	using tinyxml2::XMLDeclaration;
	using tinyxml2::XMLElement;

	std::wstring filePath;

	filePath = configDirectory + TEXT("\\intellitrace.xml");

	XMLDocument *pDoc = new XMLDocument();
	XMLDeclaration *pDecl = pDoc->NewDeclaration();

	if (NULL == pDecl) {
		return FALSE;
	}

	pDoc->LinkEndChild(pDecl);

	XMLElement *pRoot = pDoc->NewElement("Applications");

	pDoc->LinkEndChild(pRoot);

	for (std::map<std::wstring, std::vector<interval> >::iterator iter = history.begin(); iter != history.end(); ++iter) {
		XMLElement *pApplicationElement = pDoc->NewElement("Application");
		pApplicationElement->SetAttribute("name", HelperUtils::UnicodeToAnsi(iter->first.c_str()));
		pRoot->LinkEndChild(pApplicationElement);

		for (size_t i = 0; i < iter->second.size(); ++i) {
			struct tm localtime;
			CHAR time[256];

			XMLElement *pIntervalElement = pDoc->NewElement("Interval");
			pApplicationElement->LinkEndChild(pIntervalElement);

			localtime_s(&localtime, &iter->second[i].start);
			strftime(time, sizeof(time) / sizeof(CHAR), "%Y-%m-%d %H:%M:%S", &localtime);

			XMLElement *pStartElement = pDoc->NewElement("Start");
			pStartElement->LinkEndChild(pDoc->NewText(time));
			pIntervalElement->LinkEndChild(pStartElement);

			localtime_s(&localtime, &iter->second[i].end);
			strftime(time, sizeof(time) / sizeof(CHAR), "%Y-%m-%d %H:%M:%S", &localtime);

			XMLElement *pEndElement = pDoc->NewElement("End");
			pEndElement->LinkEndChild(pDoc->NewText(time));
			pIntervalElement->LinkEndChild(pEndElement);
		}
	}
	pDoc->SaveFile(HelperUtils::UnicodeToAnsi(filePath.c_str()));

	delete pDoc;

	return TRUE;
}

DWORD WINAPI Tracer::run(LPVOID lpParam) {
	Tracer* tracer = getInstance();

	while (true) {
		time_t now = time(NULL);

		EnumDesktopWindows(NULL, EnumWindowsProc, NULL);

		for (std::map<std::wstring, interval>::iterator iter = tracer->current.begin(); iter != tracer->current.end(); ++iter) {
			std::wstring processName = iter->first;
			interval span = iter->second;

			std::map<std::wstring, std::vector<interval> >::iterator iterator = tracer->history.find(processName);
			if (iterator == tracer->history.end()) {
				std::vector<interval> intervals;
				intervals.push_back(span);
				tracer->history.insert(std::map<std::wstring, std::vector<interval> >::value_type(processName, intervals));
			}
			else {
				interval &recent = iterator->second.back();
				if (recent.start == span.start) {
					recent.end = span.end;
				}
				else {
					iterator->second.push_back(span);
				}
			}

			if (span.end < now) {
				iter = tracer->current.erase(iter);
			}
		}

		tracer->saveToXML(tracer->history);
		Sleep(tracer->getSampleFrequency());
	}
}

void Tracer::startUp() {
	running = true;

	hTracerThread = CreateThread(NULL, 0, run, NULL, 0, NULL);
}

void Tracer::shutDown()
{
	running = false;
	WaitForSingleObject(hTracerThread, 3000);
	CloseHandle(hTracerThread);
}

BOOL Tracer::isRunning()
{
	return running;
}

void Tracer::enableLog()
{
	hLogThread = CreateThread(NULL, 0, log, NULL, 0, NULL);
}

void Tracer::disableLog()
{
	WaitForSingleObject(hLogThread, 3000);
	CloseHandle(hLogThread);
}

int Tracer::getSampleFrequency()
{
	return sampleFrequency;
}

void Tracer::setSampleFrequency(int freq)
{
	sampleFrequency = freq;
}

DWORD WINAPI Tracer::log(LPVOID lpParam)
{
	Tracer* tracer = getInstance();

	Sleep(3000);

	while (true) {
		tracer->printRecordTime();
		tracer->printCurrentRecord();
		tracer->printHistoryRecord();

		emit tracer->log(QString::fromStdString(tracer->stringOfRecordTime()));
		emit tracer->log(QString::fromStdWString(tracer->stringOfCurrentRecord()));
		emit tracer->log(QString::fromStdWString(tracer->stringOfHistoryRecord()));

		Sleep(tracer->getSampleFrequency());
	}
}

void Tracer::createUI()
{
	ui = new TracerUI();
	ui->setupUI();

	connect(this, SIGNAL(log(QString)), ui, SLOT(log(QString)));
}