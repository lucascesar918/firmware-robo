protoc = find_program('protoc', required : true)
dep_protobuf = dependency('protobuf', required : true)

gen_proto = generator(protoc,
  output    : ['@BASENAME@.pb.cc', '@BASENAME@.pb.h'],
  arguments : ['--proto_path=@CURRENT_SOURCE_DIR@/protos', '--cpp_out=@BUILD_DIR@', '@INPUT@']
)

proto_srcs = gen_proto.process(
  'protos/grSim_Packet.proto',
  'protos/grSim_Commands.proto',
  'protos/grSim_Replacement.proto'
)

executable('vsss_sim',
  sources             : ['main_pc.cpp', 'hal_mock.cpp', proto_srcs],
  dependencies        : [common_dep, dep_protobuf],
  include_directories : include_directories('../hal')
)
