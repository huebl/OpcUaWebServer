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
c.checkEqual(res['Header']['StatusCode'], "Success")
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
# send call request to the opc ua server
#
req = {
    "Header" : {
        "MessageType" : "GW_CallRequest",
        "ClientHandle" : "client-handle",
        "SessionId" : sessionId
    },
    "Body" : {
        "MethodsToCall" : [
            {
	        "ObjectId" : {
                    "Namespace" : "6",
                    "IdType" : "1",
		    "Id" : "Function"
	        },
                "MethodId" : {
                    "Namespace" : "6",
                    "IdType" : "1",
                    "Id" : "funcMult"
                },
		"InputArguments" : [
                    {
                        "Type" : "7",
                        "Body" : "5"
                    },
           	    {
                        "Type" : "7",
                        "Body" : "6"
                    }
		]
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
c.checkEqual(res['Header']['MessageType'], "GW_CallResponse")
c.checkEqual(res['Header']['ClientHandle'], "client-handle")
c.checkEqual(res['Header']['SessionId'], sessionId)
c.checkEqual(res['Header']['StatusCode'], "Success")
c.checkEqual(len(res['Body']['Results']), 1)
c.checkEqual(res['Body']['Results'][0]['Status'], "Success")
c.checkEqual(len(res['Body']['Results'][0]['OutputArguments']), 1)
c.checkEqual(res['Body']['Results'][0]['OutputArguments'][0]['Type'], "7")
c.checkEqual(res['Body']['Results'][0]['OutputArguments'][0]['Body'], "30")


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
c.checkEqual(res['Header']['StatusCode'], "Success")


#
# close web socket connection
#
ws.close()