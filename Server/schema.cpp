#include "pch.h"
#include "schema.h"
using namespace rapidjson;
std::string schema::throwError(std::string msg,int code=500){
	StringBuffer s;
	Writer<StringBuffer,Document::EncodingType,ASCII<>> response(s);
	response.StartObject();
	response.Key("code");
	response.Int(code);
	response.Key("msg");
	response.String(msg.c_str());
	response.EndObject();
	return s.GetString();
}
