// Generated by gencpp from file thorvald_sprayer/CANopen_srvResponse.msg
// DO NOT EDIT!


#ifndef THORVALD_SPRAYER_MESSAGE_CANOPEN_SRVRESPONSE_H
#define THORVALD_SPRAYER_MESSAGE_CANOPEN_SRVRESPONSE_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace thorvald_sprayer
{
template <class ContainerAllocator>
struct CANopen_srvResponse_
{
  typedef CANopen_srvResponse_<ContainerAllocator> Type;

  CANopen_srvResponse_()
    : message()
    , success(false)  {
    }
  CANopen_srvResponse_(const ContainerAllocator& _alloc)
    : message(_alloc)
    , success(false)  {
  (void)_alloc;
    }



   typedef std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  _message_type;
  _message_type message;

   typedef uint8_t _success_type;
  _success_type success;





  typedef boost::shared_ptr< ::thorvald_sprayer::CANopen_srvResponse_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::thorvald_sprayer::CANopen_srvResponse_<ContainerAllocator> const> ConstPtr;

}; // struct CANopen_srvResponse_

typedef ::thorvald_sprayer::CANopen_srvResponse_<std::allocator<void> > CANopen_srvResponse;

typedef boost::shared_ptr< ::thorvald_sprayer::CANopen_srvResponse > CANopen_srvResponsePtr;
typedef boost::shared_ptr< ::thorvald_sprayer::CANopen_srvResponse const> CANopen_srvResponseConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::thorvald_sprayer::CANopen_srvResponse_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::thorvald_sprayer::CANopen_srvResponse_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace thorvald_sprayer

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': False}
// {'thorvald_sprayer': ['/home/thomasdegallaix-ubuntu/catkin_ws/src/thorvald_sprayer/msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::thorvald_sprayer::CANopen_srvResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::thorvald_sprayer::CANopen_srvResponse_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::thorvald_sprayer::CANopen_srvResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::thorvald_sprayer::CANopen_srvResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::thorvald_sprayer::CANopen_srvResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::thorvald_sprayer::CANopen_srvResponse_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::thorvald_sprayer::CANopen_srvResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "9bf829f07d795d3f9e541a07897da2c4";
  }

  static const char* value(const ::thorvald_sprayer::CANopen_srvResponse_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x9bf829f07d795d3fULL;
  static const uint64_t static_value2 = 0x9e541a07897da2c4ULL;
};

template<class ContainerAllocator>
struct DataType< ::thorvald_sprayer::CANopen_srvResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "thorvald_sprayer/CANopen_srvResponse";
  }

  static const char* value(const ::thorvald_sprayer::CANopen_srvResponse_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::thorvald_sprayer::CANopen_srvResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "string message\n\
bool success\n\
\n\
";
  }

  static const char* value(const ::thorvald_sprayer::CANopen_srvResponse_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::thorvald_sprayer::CANopen_srvResponse_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.message);
      stream.next(m.success);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct CANopen_srvResponse_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::thorvald_sprayer::CANopen_srvResponse_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::thorvald_sprayer::CANopen_srvResponse_<ContainerAllocator>& v)
  {
    s << indent << "message: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.message);
    s << indent << "success: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.success);
  }
};

} // namespace message_operations
} // namespace ros

#endif // THORVALD_SPRAYER_MESSAGE_CANOPEN_SRVRESPONSE_H
