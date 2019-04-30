/*
   Copyright 2019 Kai Huebl (kai@huebl-sgh.de)

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

#include "OpcUaWebServer/WebGateway/WebGatewayConfig.h"

namespace OpcUaWebServer
{

	WebGatewayConfig::WebGatewayConfig(void)
	: address_("0.0.0.0")
	, port_(8082)
	, active_(false)
	{
	}

	WebGatewayConfig::~WebGatewayConfig(void)
	{
	}

	void
	WebGatewayConfig::active(bool active)
	{
		active_ = active;
	}

	bool
	WebGatewayConfig::active(void)
	{
		return active_;
	}

	void
	WebGatewayConfig::address(const std::string& address)
	{
		address_ = address;
	}

	std::string&
	WebGatewayConfig::address(void)
	{
		return address_;
	}

	void
	WebGatewayConfig::port(uint32_t port)
	{
		port_ = port;
	}

	uint32_t
	WebGatewayConfig::port(void)
	{
		return port_;
	}

}