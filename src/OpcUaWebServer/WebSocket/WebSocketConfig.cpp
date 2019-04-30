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

#include "OpcUaWebServer/WebSocket/WebSocketConfig.h"

namespace OpcUaWebServer
{

	WebSocketConfig::WebSocketConfig(void)
	: address_("0.0.0.0")
	, port_(8081)
	, requestTimeout_(5000)
	, idleTimeout_(60*60*1000)
	, ioThread_()
	{
	}

	WebSocketConfig::~WebSocketConfig(void)
	{
	}

	void
	WebSocketConfig::address(const std::string& address)
	{
		address_ = address;
	}

	std::string&
	WebSocketConfig::address(void)
	{
		return address_;
	}

	void
	WebSocketConfig::port(uint32_t port)
	{
		port_ = port;
	}

	uint32_t
	WebSocketConfig::port(void)
	{
		return port_;
	}

	void
	WebSocketConfig::requestTimeout(uint32_t requestTimeout)
	{
		requestTimeout_ = requestTimeout;
	}

	uint32_t
	WebSocketConfig::requestTimeout(void)
	{
		return requestTimeout_;
	}

	void
	WebSocketConfig::idleTimeout(uint32_t idleTimeout)
	{
		idleTimeout_ = idleTimeout;
	}

	uint32_t
	WebSocketConfig::idleTimeout(void)
	{
		return idleTimeout_;
	}

	void
	WebSocketConfig::ioThread(const IOThread::SPtr& ioThread)
	{
		ioThread_ = ioThread;
	}

	IOThread::SPtr&
	WebSocketConfig::ioThread(void)
	{
		return ioThread_;
	}

}