// Generated by gencpp from file thorvald_sprayer/CANFrame.msg
// DO NOT EDIT!


#ifndef THORVALD_SPRAYER_MESSAGE_CANFRAME_H
#define THORVALD_SPRAYER_MESSAGE_CANFRAME_H


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
struct CANFrame_
{
  typedef CANFrame_<ContainerAllocator> Type;

  CANFrame_()
    : can_id(0)
    , length(0)
    , data()  {
      data.assign(0);
  }
  CANFrame_(const ContainerAllocator& _alloc)
    : can_id(0)
    , length(0)
    , data()  {
  (void)_alloc;
      data.assign(0);
  }



   typedef uint32_t _can_id_type;
  _can_id_type can_id;

   typedef uint8_t _length_type;
  _length_type length;

   typedef boost::array<uint8_t, 8>  _data_type;
  _data_type data;





  typedef boost::shared_ptr< ::thorvald_sprayer::CANFrame_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::thorvald_sprayer::CANFrame_<ContainerAllocator> const> ConstPtr;

}; // struct CANFrame_

typedef ::thorvald_sprayer::CANFrame_<std::allocator<void> > CANFrame;

typedef boost::shared_ptr< ::thorvald_sprayer::CANFrame > CANFramePtr;
typedef boost::shared_ptr< ::thorvald_sprayer::CANFrame const> CANFrameConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::thorvald_sprayer::CANFrame_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::thorvald_sprayer::CANFrame_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace thorvald_sprayer

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'thorvald_sprayer': ['/home/thomasdegallaix-ubuntu/catkin_ws/src/thorvald_sprayer/msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::thorvald_sprayer::CANFrame_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::thorvald_sprayer::CANFrame_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::thorvald_sprayer::CANFrame_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::thorvald_sprayer::CANFrame_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::thorvald_sprayer::CANFrame_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::thorvald_sprayer::CANFrame_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::thorvald_sprayer::CANFrame_<ContainerAllocator> >
{
  static const char* value()
  {
    return "db6f3cdc168faf58b50386b02cdccc8f";
  }

  static const char* value(const ::thorvald_sprayer::CANFrame_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xdb6f3cdc168faf58ULL;
  static const uint64_t static_value2 = 0xb50386b02cdccc8fULL;
};

template<class ContainerAllocator>
struct DataType< ::thorvald_sprayer::CANFrame_<ContainerAllocator> >
{
  static const char* value()
  {
    return "thorvald_sprayer/CANFrame";
  }

  static const char* value(const ::thorvald_sprayer::CANFrame_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::thorvald_sprayer::CANFrame_<ContainerAllocator> >
{
  static const char* value()
  {
    return "uint32 can_id\n\
uint8 length\n\
uint8[8] data\n\
";
  }

  static const char* value(const ::thorvald_sprayer::CANFrame_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::thorvald_sprayer::CANFrame_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.can_id);
      stream.next(m.length);
      stream.next(m.data);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct CANFrame_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::thorvald_sprayer::CANFrame_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::thorvald_sprayer::CANFrame_<ContainerAllocator>& v)
  {
    s << indent << "can_id: ";
    Printer<uint32_t>::stream(s, indent + "  ", v.can_id);
    s << indent << "length: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.length);
    s << indent << "data[]" << std::endl;
    for (size_t i = 0; i < v.data.size(); ++i)
    {
      s << indent << "  data[" << i << "]: ";
      Printer<uint8_t>::stream(s, indent + "  ", v.data[i]);
    }
  }
};

} // namespace message_operations
} // namespace ros

#endif // THORVALD_SPRAYER_MESSAGE_CANFRAME_H
