// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: adsb.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "adsb.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace {

const ::google::protobuf::Descriptor* AdsBReport_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  AdsBReport_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_adsb_2eproto() {
  protobuf_AddDesc_adsb_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "adsb.proto");
  GOOGLE_CHECK(file != NULL);
  AdsBReport_descriptor_ = file->message_type(0);
  static const int AdsBReport_offsets_[8] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AdsBReport, timestamp_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AdsBReport, latitude_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AdsBReport, longitude_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AdsBReport, altitude_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AdsBReport, tail_number_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AdsBReport, north_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AdsBReport, east_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AdsBReport, down_),
  };
  AdsBReport_reflection_ =
    ::google::protobuf::internal::GeneratedMessageReflection::NewGeneratedMessageReflection(
      AdsBReport_descriptor_,
      AdsBReport::default_instance_,
      AdsBReport_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AdsBReport, _has_bits_[0]),
      -1,
      -1,
      sizeof(AdsBReport),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(AdsBReport, _internal_metadata_),
      -1);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_adsb_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
      AdsBReport_descriptor_, &AdsBReport::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_adsb_2eproto() {
  delete AdsBReport::default_instance_;
  delete AdsBReport_reflection_;
}

void protobuf_AddDesc_adsb_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\nadsb.proto\"\226\001\n\nAdsBReport\022\021\n\ttimestamp"
    "\030\001 \002(\020\022\020\n\010latitude\030\002 \002(\017\022\021\n\tlongitude\030\003 "
    "\002(\017\022\020\n\010altitude\030\004 \002(\017\022\023\n\013tail_number\030\005 \002"
    "(\t\022\r\n\005north\030\006 \002(\002\022\014\n\004east\030\007 \002(\002\022\014\n\004down\030"
    "\010 \002(\002B#\n\033edu.calpoly.capstone.sensorB\004Ad"
    "sB", 202);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "adsb.proto", &protobuf_RegisterTypes);
  AdsBReport::default_instance_ = new AdsBReport();
  AdsBReport::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_adsb_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_adsb_2eproto {
  StaticDescriptorInitializer_adsb_2eproto() {
    protobuf_AddDesc_adsb_2eproto();
  }
} static_descriptor_initializer_adsb_2eproto_;

namespace {

static void MergeFromFail(int line) GOOGLE_ATTRIBUTE_COLD;
static void MergeFromFail(int line) {
  GOOGLE_CHECK(false) << __FILE__ << ":" << line;
}

}  // namespace


// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int AdsBReport::kTimestampFieldNumber;
const int AdsBReport::kLatitudeFieldNumber;
const int AdsBReport::kLongitudeFieldNumber;
const int AdsBReport::kAltitudeFieldNumber;
const int AdsBReport::kTailNumberFieldNumber;
const int AdsBReport::kNorthFieldNumber;
const int AdsBReport::kEastFieldNumber;
const int AdsBReport::kDownFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

AdsBReport::AdsBReport()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:AdsBReport)
}

void AdsBReport::InitAsDefaultInstance() {
}

AdsBReport::AdsBReport(const AdsBReport& from)
  : ::google::protobuf::Message(),
    _internal_metadata_(NULL) {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:AdsBReport)
}

void AdsBReport::SharedCtor() {
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  timestamp_ = GOOGLE_LONGLONG(0);
  latitude_ = 0;
  longitude_ = 0;
  altitude_ = 0;
  tail_number_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  north_ = 0;
  east_ = 0;
  down_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

AdsBReport::~AdsBReport() {
  // @@protoc_insertion_point(destructor:AdsBReport)
  SharedDtor();
}

void AdsBReport::SharedDtor() {
  tail_number_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (this != default_instance_) {
  }
}

void AdsBReport::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* AdsBReport::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return AdsBReport_descriptor_;
}

const AdsBReport& AdsBReport::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_adsb_2eproto();
  return *default_instance_;
}

AdsBReport* AdsBReport::default_instance_ = NULL;

AdsBReport* AdsBReport::New(::google::protobuf::Arena* arena) const {
  AdsBReport* n = new AdsBReport;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void AdsBReport::Clear() {
#define ZR_HELPER_(f) reinterpret_cast<char*>(\
  &reinterpret_cast<AdsBReport*>(16)->f)

#define ZR_(first, last) do {\
  ::memset(&first, 0,\
           ZR_HELPER_(last) - ZR_HELPER_(first) + sizeof(last));\
} while (0)

  if (_has_bits_[0 / 32] & 255u) {
    ZR_(timestamp_, longitude_);
    ZR_(altitude_, down_);
    if (has_tail_number()) {
      tail_number_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    }
  }

#undef ZR_HELPER_
#undef ZR_

  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  if (_internal_metadata_.have_unknown_fields()) {
    mutable_unknown_fields()->Clear();
  }
}

bool AdsBReport::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:AdsBReport)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required sfixed64 timestamp = 1;
      case 1: {
        if (tag == 9) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int64, ::google::protobuf::internal::WireFormatLite::TYPE_SFIXED64>(
                 input, &timestamp_)));
          set_has_timestamp();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(21)) goto parse_latitude;
        break;
      }

      // required sfixed32 latitude = 2;
      case 2: {
        if (tag == 21) {
         parse_latitude:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_SFIXED32>(
                 input, &latitude_)));
          set_has_latitude();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(29)) goto parse_longitude;
        break;
      }

      // required sfixed32 longitude = 3;
      case 3: {
        if (tag == 29) {
         parse_longitude:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_SFIXED32>(
                 input, &longitude_)));
          set_has_longitude();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(37)) goto parse_altitude;
        break;
      }

      // required sfixed32 altitude = 4;
      case 4: {
        if (tag == 37) {
         parse_altitude:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_SFIXED32>(
                 input, &altitude_)));
          set_has_altitude();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(42)) goto parse_tail_number;
        break;
      }

      // required string tail_number = 5;
      case 5: {
        if (tag == 42) {
         parse_tail_number:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_tail_number()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->tail_number().data(), this->tail_number().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "AdsBReport.tail_number");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(53)) goto parse_north;
        break;
      }

      // required float north = 6;
      case 6: {
        if (tag == 53) {
         parse_north:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   float, ::google::protobuf::internal::WireFormatLite::TYPE_FLOAT>(
                 input, &north_)));
          set_has_north();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(61)) goto parse_east;
        break;
      }

      // required float east = 7;
      case 7: {
        if (tag == 61) {
         parse_east:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   float, ::google::protobuf::internal::WireFormatLite::TYPE_FLOAT>(
                 input, &east_)));
          set_has_east();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(69)) goto parse_down;
        break;
      }

      // required float down = 8;
      case 8: {
        if (tag == 69) {
         parse_down:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   float, ::google::protobuf::internal::WireFormatLite::TYPE_FLOAT>(
                 input, &down_)));
          set_has_down();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:AdsBReport)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:AdsBReport)
  return false;
#undef DO_
}

void AdsBReport::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:AdsBReport)
  // required sfixed64 timestamp = 1;
  if (has_timestamp()) {
    ::google::protobuf::internal::WireFormatLite::WriteSFixed64(1, this->timestamp(), output);
  }

  // required sfixed32 latitude = 2;
  if (has_latitude()) {
    ::google::protobuf::internal::WireFormatLite::WriteSFixed32(2, this->latitude(), output);
  }

  // required sfixed32 longitude = 3;
  if (has_longitude()) {
    ::google::protobuf::internal::WireFormatLite::WriteSFixed32(3, this->longitude(), output);
  }

  // required sfixed32 altitude = 4;
  if (has_altitude()) {
    ::google::protobuf::internal::WireFormatLite::WriteSFixed32(4, this->altitude(), output);
  }

  // required string tail_number = 5;
  if (has_tail_number()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->tail_number().data(), this->tail_number().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "AdsBReport.tail_number");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      5, this->tail_number(), output);
  }

  // required float north = 6;
  if (has_north()) {
    ::google::protobuf::internal::WireFormatLite::WriteFloat(6, this->north(), output);
  }

  // required float east = 7;
  if (has_east()) {
    ::google::protobuf::internal::WireFormatLite::WriteFloat(7, this->east(), output);
  }

  // required float down = 8;
  if (has_down()) {
    ::google::protobuf::internal::WireFormatLite::WriteFloat(8, this->down(), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:AdsBReport)
}

::google::protobuf::uint8* AdsBReport::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:AdsBReport)
  // required sfixed64 timestamp = 1;
  if (has_timestamp()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteSFixed64ToArray(1, this->timestamp(), target);
  }

  // required sfixed32 latitude = 2;
  if (has_latitude()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteSFixed32ToArray(2, this->latitude(), target);
  }

  // required sfixed32 longitude = 3;
  if (has_longitude()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteSFixed32ToArray(3, this->longitude(), target);
  }

  // required sfixed32 altitude = 4;
  if (has_altitude()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteSFixed32ToArray(4, this->altitude(), target);
  }

  // required string tail_number = 5;
  if (has_tail_number()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->tail_number().data(), this->tail_number().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "AdsBReport.tail_number");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        5, this->tail_number(), target);
  }

  // required float north = 6;
  if (has_north()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteFloatToArray(6, this->north(), target);
  }

  // required float east = 7;
  if (has_east()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteFloatToArray(7, this->east(), target);
  }

  // required float down = 8;
  if (has_down()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteFloatToArray(8, this->down(), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:AdsBReport)
  return target;
}

int AdsBReport::RequiredFieldsByteSizeFallback() const {
  int total_size = 0;

  if (has_timestamp()) {
    // required sfixed64 timestamp = 1;
    total_size += 1 + 8;
  }

  if (has_latitude()) {
    // required sfixed32 latitude = 2;
    total_size += 1 + 4;
  }

  if (has_longitude()) {
    // required sfixed32 longitude = 3;
    total_size += 1 + 4;
  }

  if (has_altitude()) {
    // required sfixed32 altitude = 4;
    total_size += 1 + 4;
  }

  if (has_tail_number()) {
    // required string tail_number = 5;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->tail_number());
  }

  if (has_north()) {
    // required float north = 6;
    total_size += 1 + 4;
  }

  if (has_east()) {
    // required float east = 7;
    total_size += 1 + 4;
  }

  if (has_down()) {
    // required float down = 8;
    total_size += 1 + 4;
  }

  return total_size;
}
int AdsBReport::ByteSize() const {
  int total_size = 0;

  if (((_has_bits_[0] & 0x000000ff) ^ 0x000000ff) == 0) {  // All required fields are present.
    // required sfixed64 timestamp = 1;
    total_size += 1 + 8;

    // required sfixed32 latitude = 2;
    total_size += 1 + 4;

    // required sfixed32 longitude = 3;
    total_size += 1 + 4;

    // required sfixed32 altitude = 4;
    total_size += 1 + 4;

    // required string tail_number = 5;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->tail_number());

    // required float north = 6;
    total_size += 1 + 4;

    // required float east = 7;
    total_size += 1 + 4;

    // required float down = 8;
    total_size += 1 + 4;

  } else {
    total_size += RequiredFieldsByteSizeFallback();
  }
  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void AdsBReport::MergeFrom(const ::google::protobuf::Message& from) {
  if (GOOGLE_PREDICT_FALSE(&from == this)) MergeFromFail(__LINE__);
  const AdsBReport* source = 
      ::google::protobuf::internal::DynamicCastToGenerated<const AdsBReport>(
          &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void AdsBReport::MergeFrom(const AdsBReport& from) {
  if (GOOGLE_PREDICT_FALSE(&from == this)) MergeFromFail(__LINE__);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_timestamp()) {
      set_timestamp(from.timestamp());
    }
    if (from.has_latitude()) {
      set_latitude(from.latitude());
    }
    if (from.has_longitude()) {
      set_longitude(from.longitude());
    }
    if (from.has_altitude()) {
      set_altitude(from.altitude());
    }
    if (from.has_tail_number()) {
      set_has_tail_number();
      tail_number_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.tail_number_);
    }
    if (from.has_north()) {
      set_north(from.north());
    }
    if (from.has_east()) {
      set_east(from.east());
    }
    if (from.has_down()) {
      set_down(from.down());
    }
  }
  if (from._internal_metadata_.have_unknown_fields()) {
    mutable_unknown_fields()->MergeFrom(from.unknown_fields());
  }
}

void AdsBReport::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void AdsBReport::CopyFrom(const AdsBReport& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool AdsBReport::IsInitialized() const {
  if ((_has_bits_[0] & 0x000000ff) != 0x000000ff) return false;

  return true;
}

void AdsBReport::Swap(AdsBReport* other) {
  if (other == this) return;
  InternalSwap(other);
}
void AdsBReport::InternalSwap(AdsBReport* other) {
  std::swap(timestamp_, other->timestamp_);
  std::swap(latitude_, other->latitude_);
  std::swap(longitude_, other->longitude_);
  std::swap(altitude_, other->altitude_);
  tail_number_.Swap(&other->tail_number_);
  std::swap(north_, other->north_);
  std::swap(east_, other->east_);
  std::swap(down_, other->down_);
  std::swap(_has_bits_[0], other->_has_bits_[0]);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata AdsBReport::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = AdsBReport_descriptor_;
  metadata.reflection = AdsBReport_reflection_;
  return metadata;
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// AdsBReport

// required sfixed64 timestamp = 1;
bool AdsBReport::has_timestamp() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
void AdsBReport::set_has_timestamp() {
  _has_bits_[0] |= 0x00000001u;
}
void AdsBReport::clear_has_timestamp() {
  _has_bits_[0] &= ~0x00000001u;
}
void AdsBReport::clear_timestamp() {
  timestamp_ = GOOGLE_LONGLONG(0);
  clear_has_timestamp();
}
 ::google::protobuf::int64 AdsBReport::timestamp() const {
  // @@protoc_insertion_point(field_get:AdsBReport.timestamp)
  return timestamp_;
}
 void AdsBReport::set_timestamp(::google::protobuf::int64 value) {
  set_has_timestamp();
  timestamp_ = value;
  // @@protoc_insertion_point(field_set:AdsBReport.timestamp)
}

// required sfixed32 latitude = 2;
bool AdsBReport::has_latitude() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
void AdsBReport::set_has_latitude() {
  _has_bits_[0] |= 0x00000002u;
}
void AdsBReport::clear_has_latitude() {
  _has_bits_[0] &= ~0x00000002u;
}
void AdsBReport::clear_latitude() {
  latitude_ = 0;
  clear_has_latitude();
}
 ::google::protobuf::int32 AdsBReport::latitude() const {
  // @@protoc_insertion_point(field_get:AdsBReport.latitude)
  return latitude_;
}
 void AdsBReport::set_latitude(::google::protobuf::int32 value) {
  set_has_latitude();
  latitude_ = value;
  // @@protoc_insertion_point(field_set:AdsBReport.latitude)
}

// required sfixed32 longitude = 3;
bool AdsBReport::has_longitude() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
void AdsBReport::set_has_longitude() {
  _has_bits_[0] |= 0x00000004u;
}
void AdsBReport::clear_has_longitude() {
  _has_bits_[0] &= ~0x00000004u;
}
void AdsBReport::clear_longitude() {
  longitude_ = 0;
  clear_has_longitude();
}
 ::google::protobuf::int32 AdsBReport::longitude() const {
  // @@protoc_insertion_point(field_get:AdsBReport.longitude)
  return longitude_;
}
 void AdsBReport::set_longitude(::google::protobuf::int32 value) {
  set_has_longitude();
  longitude_ = value;
  // @@protoc_insertion_point(field_set:AdsBReport.longitude)
}

// required sfixed32 altitude = 4;
bool AdsBReport::has_altitude() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
void AdsBReport::set_has_altitude() {
  _has_bits_[0] |= 0x00000008u;
}
void AdsBReport::clear_has_altitude() {
  _has_bits_[0] &= ~0x00000008u;
}
void AdsBReport::clear_altitude() {
  altitude_ = 0;
  clear_has_altitude();
}
 ::google::protobuf::int32 AdsBReport::altitude() const {
  // @@protoc_insertion_point(field_get:AdsBReport.altitude)
  return altitude_;
}
 void AdsBReport::set_altitude(::google::protobuf::int32 value) {
  set_has_altitude();
  altitude_ = value;
  // @@protoc_insertion_point(field_set:AdsBReport.altitude)
}

// required string tail_number = 5;
bool AdsBReport::has_tail_number() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
void AdsBReport::set_has_tail_number() {
  _has_bits_[0] |= 0x00000010u;
}
void AdsBReport::clear_has_tail_number() {
  _has_bits_[0] &= ~0x00000010u;
}
void AdsBReport::clear_tail_number() {
  tail_number_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_tail_number();
}
 const ::std::string& AdsBReport::tail_number() const {
  // @@protoc_insertion_point(field_get:AdsBReport.tail_number)
  return tail_number_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void AdsBReport::set_tail_number(const ::std::string& value) {
  set_has_tail_number();
  tail_number_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:AdsBReport.tail_number)
}
 void AdsBReport::set_tail_number(const char* value) {
  set_has_tail_number();
  tail_number_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:AdsBReport.tail_number)
}
 void AdsBReport::set_tail_number(const char* value, size_t size) {
  set_has_tail_number();
  tail_number_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:AdsBReport.tail_number)
}
 ::std::string* AdsBReport::mutable_tail_number() {
  set_has_tail_number();
  // @@protoc_insertion_point(field_mutable:AdsBReport.tail_number)
  return tail_number_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 ::std::string* AdsBReport::release_tail_number() {
  clear_has_tail_number();
  return tail_number_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void AdsBReport::set_allocated_tail_number(::std::string* tail_number) {
  if (tail_number != NULL) {
    set_has_tail_number();
  } else {
    clear_has_tail_number();
  }
  tail_number_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), tail_number);
  // @@protoc_insertion_point(field_set_allocated:AdsBReport.tail_number)
}

// required float north = 6;
bool AdsBReport::has_north() const {
  return (_has_bits_[0] & 0x00000020u) != 0;
}
void AdsBReport::set_has_north() {
  _has_bits_[0] |= 0x00000020u;
}
void AdsBReport::clear_has_north() {
  _has_bits_[0] &= ~0x00000020u;
}
void AdsBReport::clear_north() {
  north_ = 0;
  clear_has_north();
}
 float AdsBReport::north() const {
  // @@protoc_insertion_point(field_get:AdsBReport.north)
  return north_;
}
 void AdsBReport::set_north(float value) {
  set_has_north();
  north_ = value;
  // @@protoc_insertion_point(field_set:AdsBReport.north)
}

// required float east = 7;
bool AdsBReport::has_east() const {
  return (_has_bits_[0] & 0x00000040u) != 0;
}
void AdsBReport::set_has_east() {
  _has_bits_[0] |= 0x00000040u;
}
void AdsBReport::clear_has_east() {
  _has_bits_[0] &= ~0x00000040u;
}
void AdsBReport::clear_east() {
  east_ = 0;
  clear_has_east();
}
 float AdsBReport::east() const {
  // @@protoc_insertion_point(field_get:AdsBReport.east)
  return east_;
}
 void AdsBReport::set_east(float value) {
  set_has_east();
  east_ = value;
  // @@protoc_insertion_point(field_set:AdsBReport.east)
}

// required float down = 8;
bool AdsBReport::has_down() const {
  return (_has_bits_[0] & 0x00000080u) != 0;
}
void AdsBReport::set_has_down() {
  _has_bits_[0] |= 0x00000080u;
}
void AdsBReport::clear_has_down() {
  _has_bits_[0] &= ~0x00000080u;
}
void AdsBReport::clear_down() {
  down_ = 0;
  clear_has_down();
}
 float AdsBReport::down() const {
  // @@protoc_insertion_point(field_get:AdsBReport.down)
  return down_;
}
 void AdsBReport::set_down(float value) {
  set_has_down();
  down_ = value;
  // @@protoc_insertion_point(field_set:AdsBReport.down)
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)
