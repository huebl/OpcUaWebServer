/*
   Copyright 2015-2019 Kai Huebl (kai@huebl-sgh.de)

   Lizenziert gemäß Apache Licence Version 2.0 (die „Lizenz“); Nutzung dieser
   Datei nur in Übereinstimmung mit der Lizenz erlaubt.
   Eine Kopie der Lizenz erhalten Sie auf http://www.apache.org/licenses/LICENSE-2.0.

   Sofern nicht gemäß geltendem Recht vorgeschrieben oder schriftlich vereinbart,
   erfolgt die Bereitstellung der im Rahmen der Lizenz verbreiteten Software OHNE
   GEWÄHR ODER VORBEHALTE – ganz gleich, ob ausdrücklich oder stillschweigend.

   Informationen über die jeweiligen Bedingungen für Genehmigungen und Einschränkungen
   im Rahmen der Lizenz finden Sie in der Lizenz.

   Autor: Kai Huebl (kai@huebl-sgh.de)

 */

#ifndef __OpcUaWebServer_HttpServer_h__
#define __OpcUaWebServer_HttpServer_h__

#include <boost/asio/ssl.hpp>
#include "OpcUaWebServer/WebServer/HttpServerBase.h"
#include "OpcUaWebServer/WebServer/IPLogger.h"

using namespace OpcUaStackCore;

namespace OpcUaWebServer
{

	class HttpServer
	: public HttpServerBase
	{
	  public:
		typedef std::function<void (bool error)> StartupCompleteCallback;
		typedef std::function<void (bool error)> ShutdownCompleteCallback;
		typedef boost::shared_ptr<HttpServer> SPtr;

		HttpServer(HttpConfig* httpConfig);
		virtual ~HttpServer(void);

		void startup(
		    const StartupCompleteCallback& startupCompleteCallback
		);
		void shutdown(
			const ShutdownCompleteCallback& shutdownCompleteCallback
		);

	  private:
		void startupStrand(
			const StartupCompleteCallback& startupCompleteCallback
		);
		void shutdownStrand(
			const ShutdownCompleteCallback& shutdownCompleteCallback
		);
		std::string getPassword() const;
		HttpChannel* createHttpChannel(void);

		void accept(void);
		void handleAccept(const boost::system::error_code& error, HttpChannel* httpChannel);
		void handleAccept1(const boost::system::error_code& error){}

		bool ssl_ = false;
		HttpConfig* httpConfig_;
		boost::asio::ssl::context* context_ = nullptr;
		IPLogger ipLogger_;
	};

}

#endif
