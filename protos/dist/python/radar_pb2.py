# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: radar.proto

import sys
_b=sys.version_info[0]<3 and (lambda x:x) or (lambda x:x.encode('latin1'))
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor.FileDescriptor(
  name='radar.proto',
  package='',
  syntax='proto2',
  serialized_pb=_b('\n\x0bradar.proto\"\xc1\x01\n\x0bRadarReport\x12\x11\n\ttimestamp\x18\x01 \x02(\x10\x12\r\n\x05range\x18\x02 \x02(\x02\x12\x0f\n\x07\x61zimuth\x18\x03 \x02(\x02\x12\x11\n\televation\x18\x04 \x02(\x02\x12\n\n\x02id\x18\x05 \x02(\x0f\x12\r\n\x05north\x18\x06 \x02(\x02\x12\x0c\n\x04\x65\x61st\x18\x07 \x02(\x02\x12\x0c\n\x04\x64own\x18\x08 \x02(\x02\x12\x10\n\x08latitude\x18\t \x02(\x0f\x12\x11\n\tlongitude\x18\n \x02(\x0f\x12\x10\n\x08\x61ltitude\x18\x0b \x02(\x0f\x42$\n\x1b\x65\x64u.calpoly.capstone.sensorB\x05Radar')
)
_sym_db.RegisterFileDescriptor(DESCRIPTOR)




_RADARREPORT = _descriptor.Descriptor(
  name='RadarReport',
  full_name='RadarReport',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='timestamp', full_name='RadarReport.timestamp', index=0,
      number=1, type=16, cpp_type=2, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='range', full_name='RadarReport.range', index=1,
      number=2, type=2, cpp_type=6, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='azimuth', full_name='RadarReport.azimuth', index=2,
      number=3, type=2, cpp_type=6, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='elevation', full_name='RadarReport.elevation', index=3,
      number=4, type=2, cpp_type=6, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='id', full_name='RadarReport.id', index=4,
      number=5, type=15, cpp_type=1, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='north', full_name='RadarReport.north', index=5,
      number=6, type=2, cpp_type=6, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='east', full_name='RadarReport.east', index=6,
      number=7, type=2, cpp_type=6, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='down', full_name='RadarReport.down', index=7,
      number=8, type=2, cpp_type=6, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='latitude', full_name='RadarReport.latitude', index=8,
      number=9, type=15, cpp_type=1, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='longitude', full_name='RadarReport.longitude', index=9,
      number=10, type=15, cpp_type=1, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='altitude', full_name='RadarReport.altitude', index=10,
      number=11, type=15, cpp_type=1, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  syntax='proto2',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=16,
  serialized_end=209,
)

DESCRIPTOR.message_types_by_name['RadarReport'] = _RADARREPORT

RadarReport = _reflection.GeneratedProtocolMessageType('RadarReport', (_message.Message,), dict(
  DESCRIPTOR = _RADARREPORT,
  __module__ = 'radar_pb2'
  # @@protoc_insertion_point(class_scope:RadarReport)
  ))
_sym_db.RegisterMessage(RadarReport)


DESCRIPTOR.has_options = True
DESCRIPTOR._options = _descriptor._ParseOptions(descriptor_pb2.FileOptions(), _b('\n\033edu.calpoly.capstone.sensorB\005Radar'))
# @@protoc_insertion_point(module_scope)
