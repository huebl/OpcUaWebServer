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

#ifndef __OpcUaWebServer_ReadResponseData_h__
#define __OpcUaWebServer_ReadResponseData_h__

#include <boost/property_tree/ptree.hpp>
#include <string>
#include "OpcUaStackCore/BuildInTypes/OpcUaDataValue.h"
#include "OpcUaWebServer/OpcUaClient/ValueInfo.h"

using namespace OpcUaStackCore;

namespace OpcUaWebServer
{

	class ReadResponseData
	{
	  public:
		ReadResponseData(void);
		~ReadResponseData(void);

		void statusCode(const std::string& statusCode);
		std::string& statusCode(void);
		void dataValue(OpcUaDataValue& dataValue);
		void dataValue(OpcUaDataValue::SPtr dataValue);
		OpcUaDataValue::SPtr dataValue(void);
		void valueInfoEntry(const ValueInfoEntry::SPtr& valueInfoEntry);
		ValueInfoEntry::SPtr& valueInfoEntry(void);

		bool jsonDecode(boost::property_tree::ptree& pt);
		bool jsonEncode(boost::property_tree::ptree& pt);

	  private:
		std::string statusCode_;
		OpcUaDataValue::SPtr dataValue_;
		ValueInfoEntry::SPtr valueInfoEntry_;
	};

}

#endif
