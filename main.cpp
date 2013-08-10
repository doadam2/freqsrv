/*
 * main.cpp
 *
 *  Created on: Aug 8, 2013
 *      Author: adam
 */


#include <iostream>
#include <algorithm>
#include "FrequencyReceiver.h"
#include <Poco/Net/ServerSocket.h>
#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Util/ServerApplication.h>

using namespace Poco::Net;
using namespace Poco::Util;
using namespace std;

void replaceAll(std::string& str, const std::string& from, const std::string& to) {
    if(from.empty())
        return;
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
}

FrequencyReceiver* freqReceiver;
class MyRequestHandler : public HTTPRequestHandler
{
public:
  virtual void handleRequest(HTTPServerRequest &req, HTTPServerResponse &resp)
  {
    resp.setStatus(HTTPResponse::HTTP_OK);
    resp.setContentType("text/html");


    std::string url = req.getURI();
    url = url.substr(1, url.length());
    std::string space = "%20";
    std::string spacereal = "	";
    replaceAll(url, space, spacereal);
    cout << "receiving request for phrase " << url.c_str() << endl;


    ostream& out = resp.send();/*
    out << "<h1>Hello world!</h1>"
        << "<p>Count: "  << ++count         << "</p>"
        << "<p>Host: "   << req.getHost()   << "</p>"
        << "<p>Method: " << req.getMethod() << "</p>"
        << "<p>URI: "    << req.getURI()    << "</p>";
        */
    out << freqReceiver->getFrequency(url.c_str());
    out.flush();
/*
    cout << endl
         << "Response sent for count=" << count
         << " and URI=" << req.getURI() << endl;*/
  }
/*
private:
  static int count;*/
};

//int MyRequestHandler::count = 0;

class MyRequestHandlerFactory : public HTTPRequestHandlerFactory
{
public:
  virtual HTTPRequestHandler* createRequestHandler(const HTTPServerRequest &)
  {
    return new MyRequestHandler;
  }
};

class MyServerApp : public ServerApplication
{
protected:
  int main(const vector<string> &)
  {
    HTTPServer s(new MyRequestHandlerFactory, ServerSocket(9090), new HTTPServerParams);

    s.start();
    cout << endl << "Server started" << endl;

    waitForTerminationRequest();  // wait for CTRL-C or kill

    cout << endl << "Shutting down..." << endl;
    s.stop();

    return Application::EXIT_OK;
  }
};

int main(int argc, char** argv)
{
	cout << "freqserv - Frequency Web Sevice, written by Adam." << endl;
	system("sleep 2");
	freqReceiver = new FrequencyReceiver();
	MyServerApp app;
	return app.run(argc, argv);
}

