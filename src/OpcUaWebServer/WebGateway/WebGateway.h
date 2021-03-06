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

#ifndef __OpcUaWebServer_WebGateway_h__
#define __OpcUaWebServer_WebGateway_h__

#include "ClientManager.h"
#include "OpcUaStackCore/Base/Config.h"
#include "OpcUaStackCore/Utility/IOThread.h"
#include "OpcUaStackCore/Certificate/CryptoManager.h"
#include "OpcUaWebServer/WebSocket/WebSocketServer.h"
#include "OpcUaWebServer/WebGateway/ClientManager.h"
#include "OpcUaWebServer/WebGateway/WebGatewayConfig.h"

using namespace OpcUaStackCore;

namespace OpcUaWebServer
{

	class WebGateway
	{
	  public:
		typedef std::function<void (bool error)> StartupCompleteCallback;
		typedef std::function<void (bool error)> ShutdownCompleteCallback;

		WebGateway(void);
		virtual ~WebGateway(void);

		void startup(
			Config* config,
			IOThread::SPtr ioThread,
			CryptoManager::SPtr cryptoManager,
			const StartupCompleteCallback& startupCompleteCallback
		);
		void shutdown(
			const ShutdownCompleteCallback& shutdownCompleteCallback
		);

		bool getWebGatewayConfig(Config* config);

	  private:
		void startupStrand(
			Config* config,
			IOThread::SPtr ioThread,
			CryptoManager::SPtr cryptoManager,
			const StartupCompleteCallback& startupCompleteCallback
		);
		void shutdownStrand(
			const ShutdownCompleteCallback& shutdownCompleteCallback
		);

		WebGatewayConfig webGatewayConfig_;

		WebSocketConfig webSocketConfig_;
		WebSocketServer::SPtr webSocketServer_;

		boost::shared_ptr<boost::asio::io_service::strand> strand_ = nullptr;

		ClientManager clientManager_;

	};

}

#endif
