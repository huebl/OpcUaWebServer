#!/usr/bin/python3

from websocket import create_connection
import json
import Check as c

#
# open web socket connection
#
ws = create_connection("ws://127.0.0.1:8082")

#
# send login request to open opc ua session
#
req = {
    "Header" : {
        "MessageType" : "GW_LoginRequest",
        "ClientHandle" : "client-handle"
     },
     "Body" : {
         "DiscoveryUrl" : "opc.tcp://127.0.0.1:8889"
     }
}
print("SEND: ", json.dumps(req, indent = 4))
ws.send(json.dumps(req)) 

str = ws. recv()
print("RECV: ", str)
res = json.loads(str)
c.checkEqual(res['Header']['MessageType'], "GW_LoginResponse")
c.checkEqual(res['Header']['ClientHandle'], "client-handle")
c.checkEqual(res['Header']['StatusCode'], "0")
c.checkExists(res['Body']['SessionId'])
sessionId = res['Body']['SessionId']


#
# receive session status notify
#
str = ws. recv()
print("RECV: ", str)
res = json.loads(str)
c.checkEqual(res['Header']['MessageType'], "GW_SessionStatusNotify")
c.checkEqual(res['Header']['ClientHandle'], "client-handle")
c.checkEqual(res['Header']['SessionId'], sessionId)
c.checkEqual(res['Body']['SessionStatus'], "Connect")


#
# send history read event request to the opc ua server
#
req = {
    "Header" : {
        "MessageType" : "GW_HistoryReadRequest",
        "ClientHandle" : "client-handle",
        "SessionId" : sessionId
    },
    "Body" : {
        "HistoryReadDetails" : {
            "TypeId" : { "Id" : "15262"} ,
	    "Body" : {
               "StartTime" : "2019-05-04T14:33:04Z",
	       "EndTime" : "2050-05-04T14:33:04Z",
               "NumValuesPerNode" : "1000",
               "Filter" : {
                        "SelectClauses" : [
                            {
                                "TypeDefinitionId" : { "Id" : "2041" },
                                "AttributeId" : "13",
                                "IndexRange" : "",
                                "BrowsePath" : [ { "Name" : "EventId" } ]
                            },
                            {
                                "TypeDefinitionId" : { "Id" : "2041" },
                                "AttributeId" : "13",
                                "IndexRange" : "",
                                "BrowsePath" : [ { "Name" : "EventType" } ]
                            },
                            {
                                "TypeDefinitionId" : { "Id" : "2041" },
                                "AttributeId" : "13",
                                "IndexRange" : "",
                                "BrowsePath" : [ { "Name" : "SourceName" } ]
                            },
                            {
                                "TypeDefinitionId" : { "Id" : "2041" },
                                "AttributeId" : "13",
                                "IndexRange" : "",
                                "BrowsePath" : [ { "Name" : "Time" } ]
                            },
                            {
                                "TypeDefinitionId" : { "Id" : "2041" },
                                "AttributeId" : "13",
                                "IndexRange" : "",
                                "BrowsePath" : [ { "Name" : "Message" } ]
                            },
                            {
                                "TypeDefinitionId" : { "Id" : "2041" },
                                "AttributeId" : "13",
                                "IndexRange" : "",
                                "BrowsePath" : [ { "Name" : "Severity" } ]
                            },
                            {
                                "TypeDefinitionId" : { "Id" : "2041" },
                                "AttributeId" : "13",
                                "IndexRange" : "",
                                "BrowsePath" : [ { "Name" : "Prompt" } ]
                            },
                            {
                                "TypeDefinitionId" : { "Id" : "2041" },
                                "AttributeId" : "13",
                                "IndexRange" : "",
                                "BrowsePath" : [ { "Name" : "ResponseOptionSet" } ]
                            },
                            {
                                "TypeDefinitionId" : { "Id" : "2041" },
                                "AttributeId" : "13",
                                "IndexRange" : "",
                                "BrowsePath" : [ { "Name" : "Value" } ]
                            },
                            {
                                "TypeDefinitionId" : { "Id" : "2041" },
                                "AttributeId" : "13",
                                "IndexRange" : "",
                                "BrowsePath" : [ { "Name" : "Id" } ]
                            },
                            {
                                "TypeDefinitionId" : { "Id" : "2041" },
                                "AttributeId" : "13",
                                "IndexRange" : "",
                                "BrowsePath" : [ { "Name" : "AvtivateState" } ]
                            },
                            {
                                "TypeDefinitionId" : { "Id" : "2041" },
                                "AttributeId" : "13",
                                "IndexRange" : "",
                                "BrowsePath" : [ { "Name" : "ActivateState" }, { "Name" : "Id" } ]
                            }
                       ],
                       "WhereClause" : {
                           "Elements" : []
                       }
                }
       	    }
	},
	"NodesToRead" : [
            {
                "NodeId" : {
                    "Namespace" : "12",
                    "IdType" : "1",
		    "Id" : "EventObject"
                }
               
	    }
        ]
    }

}
print("SEND: ", json.dumps(req, indent = 4))
ws.send(json.dumps(req)) 


#
# receive history read response from the opc ua server
#
str = ws. recv()
print("RECV: ", str)
res = json.loads(str)
c.checkEqual(res['Header']['MessageType'], "GW_HistoryReadResponse")
c.checkEqual(res['Header']['ClientHandle'], "client-handle")
c.checkEqual(res['Header']['SessionId'], sessionId)
c.checkEqual(res['Header']['StatusCode'], "0")
c.checkEqual(len(res['Body']['Results']), 1)
c.checkEqual(len(res['Body']['Results'][0]['HistoryData']['Body']['Events']), 5)
c.checkEqual(res['Body']['Results'][0]['StatusCode'], "0")


#
# send logout request to close opc ua session
#
req = {
    "Header" : {
        "MessageType" : "GW_LogoutRequest",
        "ClientHandle" : "client-handle",
        "SessionId" : sessionId
    },
    "Body" : {
    }

}
print("SEND: ", json.dumps(req, indent = 4))
ws.send(json.dumps(req)) 

str = ws. recv()
print("RECV: ", str)
res = json.loads(str)
c.checkEqual(res['Header']['MessageType'], "GW_LogoutResponse")
c.checkEqual(res['Header']['ClientHandle'], "client-handle")
c.checkEqual(res['Header']['SessionId'], sessionId)
c.checkEqual(res['Header']['StatusCode'], "0")




#
# close web socket connection
#
ws.close()
