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

#include "OpcUaStackCore/Base/Log.h"
#include "OpcUaWebServer/WebServer/HttpServer.h"

namespace OpcUaWebServer
{

	HttpServer::HttpServer(HttpConfig* httpConfig)
	: HttpServerBase(httpConfig)
	, httpConfig_(httpConfig)
	, ipLogger_()
	{
		ipLogger_.logFileName(httpConfig->logFileName());
		ipLogger_.maxLogFileNumber(httpConfig->maxLogFileNumber());
		ipLogger_.maxLogFileSize(httpConfig->maxLogFileSize());
		ipLogger_.maxIPAge(httpConfig->maxIPAge());
	}

	HttpServer::~HttpServer(void)
	{
	}

	void
	HttpServer::startup(
		const StartupCompleteCallback& startupCompleteCallback
	)
	{
		httpConfig_->strand()->dispatch(
			[this, startupCompleteCallback](){
			    startupStrand(startupCompleteCallback);
		    }
		);
	}

	void
	HttpServer::startupStrand(
		const StartupCompleteCallback& startupCompleteCallback
	)
	{
		Log(Info, "open http listener socket")
			.parameter("Address", httpConfig_->address())
			.parameter("Port", httpConfig_->port());

		tcpAcceptor_.listen(128);
		accept();

		return startupCompleteCallback(true);
	}

	void
	HttpServer::shutdown(
		const ShutdownCompleteCallback& shutdownCompleteCallback
	)
	{
		httpConfig_->strand()->dispatch(
			[this, shutdownCompleteCallback](){
			    shutdownStrand(shutdownCompleteCallback);
		    }
		);
	}

	void
	HttpServer::shutdownStrand(
		const ShutdownCompleteCallback& shutdownCompleteCallback
	)
	{
		tcpAcceptor_.close();
		shutdownCompleteCallback(true);
	}

	void
	HttpServer::accept(void)
	{
		auto httpChannel = new HttpChannel(httpConfig_->ioThread()->ioService()->io_service());

#if 0
		httpChannel->socket().async_accept(
			httpConfig_->strand(),
			&tcpAcceptor_,
			[this, httpChannel](const boost::system::error_code& error) {
				handleAccept(error, httpChannel);
			}
		);
#endif

		tcpAcceptor_.async_accept(
			httpChannel->socket(),
			httpConfig_->strand(),
			boost::bind(&HttpServer::handleAccept, this, boost::asio::placeholders::error, httpChannel)
		);
		Log(Debug, "HttpServer is waiting for new connection");
	}

	void
	HttpServer::handleAccept(const boost::system::error_code& error, HttpChannel* httpChannel)
	{
		if (error) {
			Log(Error, "HttpServer error");
			delete httpChannel;
			return;
		}

		httpChannel->partner_ = httpChannel->socket().remote_endpoint();
		Log(Debug, "HttpServer accept connection from client")
			.parameter("Address", httpChannel->partner_.address().to_string())
			.parameter("Port", httpChannel->partner_.port())
			.parameter("ChannelId", httpChannel->channelId_);

		ipLogger_.logout(httpChannel->partner_.address().to_string());

		receiveRequest(httpChannel);

		accept();
	}

}
