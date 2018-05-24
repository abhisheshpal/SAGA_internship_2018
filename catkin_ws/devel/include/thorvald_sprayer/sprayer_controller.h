// Generated by gencpp from file thorvald_sprayer/sprayer_controller.msg
// DO NOT EDIT!


#ifndef THORVALD_SPRAYER_MESSAGE_SPRAYER_CONTROLLER_H
#define THORVALD_SPRAYER_MESSAGE_SPRAYER_CONTROLLER_H

#include <ros/service_traits.h>


#include <thorvald_sprayer/sprayer_controllerRequest.h>
#include <thorvald_sprayer/sprayer_controllerResponse.h>


namespace thorvald_sprayer
{

struct sprayer_controller
{

typedef sprayer_controllerRequest Request;
typedef sprayer_controllerResponse Response;
Request request;
Response response;

typedef Request RequestType;
typedef Response ResponseType;

}; // struct sprayer_controller
} // namespace thorvald_sprayer


namespace ros
{
namespace service_traits
{


template<>
struct MD5Sum< ::thorvald_sprayer::sprayer_controller > {
  static const char* value()
  {
    return "d219122364590b6594a5c4f91ba561ca";
  }

  static const char* value(const ::thorvald_sprayer::sprayer_controller&) { return value(); }
};

template<>
struct DataType< ::thorvald_sprayer::sprayer_controller > {
  static const char* value()
  {
    return "thorvald_sprayer/sprayer_controller";
  }

  static const char* value(const ::thorvald_sprayer::sprayer_controller&) { return value(); }
};


// service_traits::MD5Sum< ::thorvald_sprayer::sprayer_controllerRequest> should match 
// service_traits::MD5Sum< ::thorvald_sprayer::sprayer_controller > 
template<>
struct MD5Sum< ::thorvald_sprayer::sprayer_controllerRequest>
{
  static const char* value()
  {
    return MD5Sum< ::thorvald_sprayer::sprayer_controller >::value();
  }
  static const char* value(const ::thorvald_sprayer::sprayer_controllerRequest&)
  {
    return value();
  }
};

// service_traits::DataType< ::thorvald_sprayer::sprayer_controllerRequest> should match 
// service_traits::DataType< ::thorvald_sprayer::sprayer_controller > 
template<>
struct DataType< ::thorvald_sprayer::sprayer_controllerRequest>
{
  static const char* value()
  {
    return DataType< ::thorvald_sprayer::sprayer_controller >::value();
  }
  static const char* value(const ::thorvald_sprayer::sprayer_controllerRequest&)
  {
    return value();
  }
};

// service_traits::MD5Sum< ::thorvald_sprayer::sprayer_controllerResponse> should match 
// service_traits::MD5Sum< ::thorvald_sprayer::sprayer_controller > 
template<>
struct MD5Sum< ::thorvald_sprayer::sprayer_controllerResponse>
{
  static const char* value()
  {
    return MD5Sum< ::thorvald_sprayer::sprayer_controller >::value();
  }
  static const char* value(const ::thorvald_sprayer::sprayer_controllerResponse&)
  {
    return value();
  }
};

// service_traits::DataType< ::thorvald_sprayer::sprayer_controllerResponse> should match 
// service_traits::DataType< ::thorvald_sprayer::sprayer_controller > 
template<>
struct DataType< ::thorvald_sprayer::sprayer_controllerResponse>
{
  static const char* value()
  {
    return DataType< ::thorvald_sprayer::sprayer_controller >::value();
  }
  static const char* value(const ::thorvald_sprayer::sprayer_controllerResponse&)
  {
    return value();
  }
};

} // namespace service_traits
} // namespace ros

#endif // THORVALD_SPRAYER_MESSAGE_SPRAYER_CONTROLLER_H
