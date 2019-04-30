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

#ifndef __OpcUaWebServer_WebGatewayConfig_h__
#define __OpcUaWebServer_WebGatewayConfig_h__

#include <string>

namespace OpcUaWebServer
{

	class WebGatewayConfig
	{
	  public:
		WebGatewayConfig(void);
		virtual ~WebGatewayConfig(void);

		void active(bool active);
		bool active(void);
		void address(const std::string& address);
		std::string& address(void);
		void port(uint32_t port);
		uint32_t port(void);

	  private:
		bool active_;
		std::string address_;
		uint32_t port_;
	};

}

#endif