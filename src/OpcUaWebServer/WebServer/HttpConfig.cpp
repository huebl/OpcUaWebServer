/*
   Copyright 2015 Kai Huebl (kai@huebl-sgh.de)

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

#include "OpcUaWebServer/WebServer/HttpConfig.h"

namespace OpcUaWebServer
{

	HttpConfig::HttpConfig(void)
	: address_("0.0.0.0")
	, port_(8080)
	, ioThread_()
	, webDirectory_("")
	, requestTimeout_(5000)
	{
	}

	HttpConfig::~HttpConfig(void)
	{
	}

	void
	HttpConfig::address(const std::string& address)
	{
		address_ = address;
	}

	std::string&
	HttpConfig::address(void)
	{
		return address_;
	}

	void
	HttpConfig::port(uint32_t port)
	{
		port_ = port;
	}

	uint32_t
	HttpConfig::port(void)
	{
		return port_;
	}

	void
	HttpConfig::ioThread(const IOThread::SPtr& ioThread)
	{
		ioThread_ = ioThread;
	}

	IOThread::SPtr&
	HttpConfig::ioThread(void)
	{
		return ioThread_;
	}

	void
	HttpConfig::webDirectory(const std::string& webDirectory)
	{
		webDirectory_ = webDirectory;
	}

	std::string
	HttpConfig::webDirectory(void)
	{
		return webDirectory_;
	}

	void
	HttpConfig::requestTimeout(uint32_t requestTimeout)
	{
		requestTimeout_ = requestTimeout;
	}

	uint32_t
	HttpConfig::requestTimeout(void)
	{
		return requestTimeout_;
	}

	void
	HttpConfig::logFileName(const std::string& logFileName)
	{
		logFileName_ = logFileName;
	}

	std::string
	HttpConfig::logFileName(void)
	{
		return logFileName_;
	}

	void
	HttpConfig::maxLogFileNumber(uint32_t maxLogFileNumber)
	{
		maxLogFileNumber_ = maxLogFileNumber;
	}

	uint32_t
	HttpConfig::maxLogFileNumber(void)
	{
		return maxLogFileNumber_;
	}

	void
	HttpConfig::maxLogFileSize(uint32_t maxLogFileSize)
	{
		maxLogFileSize_ = maxLogFileSize;
	}

	uint32_t
	HttpConfig::maxLogFileSize(void)
	{
		return maxLogFileSize_;
	}

	void
	HttpConfig::maxIPAge(uint32_t maxIPAge)
	{
		maxIPAge_ = maxIPAge;
	}

	uint32_t
	HttpConfig::maxIPAge(void)
	{
		return maxIPAge_;
	}

}