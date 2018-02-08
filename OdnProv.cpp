/* This will not compile, its just for understanding purpose*/
#include <iostream>

class OdnProvSvrSession : public AService
{
private:
	typedef map<string, bool (OdnProvSvrSession::*)(VzxmlSerializable *)> FUNCT_PTR_MAP;
	VzxmlSerializable *getMessageObject(const string &rootTag);
	FUNCT_PTR_MAP messageHandlingMap;
	VziumXmlUtil vziumXmlUtil;
	AppMQMsg *message;
public:
	OdnProvSvrSession(const char* pServiceName, int argc, char *argv[]);
	OdnProvSvrSession() {}
	int OdnProvSvrSession::ProcessIncoming(AppMQMsg& in_message);
	bool OdnProvSvrSession::handleXmlCemMessage(AppMQMsg *msg);
	VzxmlSerializable *OdnProvSvrSession::getMessageObject(const string &rootTag);
};

OdnProvSvrSession::OdnProvSvrSession(const char* pServiceName, int argc, char *argv[])
{
	//initialize XML Util
	//Open database connection
	//Assign function pointer map using the root tag string
	messageHandlingMap[dictName + messageSeperator + (string)"SpecialsPlanningMsg"] = &OdnProvSvrSession::handleStartSplsOdnProvisioning;

	//This uses the concept of Singleton 
	//string sToggleRcvDesignOltSwcOff = CommonParamsUtility::instance().getParamValue("RCV_LOOKUP_SQE");
	readConfigParameters();

}

int OdnProvSvrSession::ProcessIncoming(AppMQMsg& in_message)
{
	message = &in_message;
	handleXmlCemMessage(&in_message);

	//reconnect database if connection lost
	return 0;
}

bool OdnProvSvrSession::handleXmlCemMessage(AppMQMsg *msg)
{
	//Get the Xml Message
	string xmlMessage = msg->GetBody();
	string rootElement;
	void *tempPtr = vziumXmlUtil.LoadXmlString(xmlMessage, rootElement);
	VzxmlSerializable *xmlMessagePtr = getMessageObject(rootElement);

	if (!vziumXmlUtil.PopulateObject(tempPtr, *xmlMessagePtr))
	{
		logMsg(DEBUG, 2, "Could not load xml into the object");
		delete xmlMessagePtr;
		return false;
	}

	//Search for root element and call the respective handler
	FUNCT_PTR_MAP::iterator itFind = messageHandlingMap.find(dictName + messageSeperator + rootElement);
	bool result = (this->*(itFind->second)) (xmlMessagePtr);
	delete xmlMessagePtr;
	return result;
}

VzxmlSerializable *OdnProvSvrSession::getMessageObject(const string &rootTag)
{
	logMsg(DEBUG, 2, "*OdnProvSvrSession::getMessageObject");
	VzxmlSerializable *xmlMessagePtr = 0;

	if (rootTag == "SpecialsPlanningMsg")
		xmlMessagePtr = new SpecialsPlanningMsg();
	else
		xmlMessagePtr = 0;

	return xmlMessagePtr;
}
/*
int main(int argc, char *argv[], char *[])
{
	//  Initialize the Parser
	XMLPlatformUtils::Initialize();

	OdnProvSvrSession odnServer(argv[1], argc, argv);
	odnServer.Init(); //This is responsible for bringing up the server

	//This takes care of incoming message ProcessIncoming
	odnServer.Go();

	//      Since the ClockManager will call the shutdown during the destruction
	//      no need to call the shutdown, which will make a infinite wait (deadlock) to get the thread back
	//      to SHUTDOWN state.

	//      lock_manager.Shutdown();
}
*/
