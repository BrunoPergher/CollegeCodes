# -*- coding: utf-8 -*-
# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: memoria.proto
# Protobuf Python Version: 5.26.1
"""Generated protocol buffer code."""
from google.protobuf import descriptor as _descriptor
from google.protobuf import descriptor_pool as _descriptor_pool
from google.protobuf import symbol_database as _symbol_database
from google.protobuf.internal import builder as _builder
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()


from google.protobuf import wrappers_pb2 as google_dot_protobuf_dot_wrappers__pb2


DESCRIPTOR = _descriptor_pool.Default().AddSerializedFile(b'\n\rmemoria.proto\x12\x06\x61genda\x1a\x1egoogle/protobuf/wrappers.proto\"H\n\x07Jogador\x12\n\n\x02id\x18\x01 \x01(\x05\x12\x0c\n\x04nome\x18\x02 \x01(\t\x12\x11\n\tpontuacao\x18\x03 \x01(\x05\x12\x10\n\x08\x65ndereco\x18\x04 \x01(\t\"F\n\x05\x43\x61rta\x12\n\n\x02id\x18\x01 \x01(\x05\x12\r\n\x05valor\x18\x02 \x01(\t\x12\r\n\x05\x61tivo\x18\x03 \x01(\x08\x12\x13\n\x0bselecionada\x18\x04 \x01(\x08\"\xa9\x01\n\x04Jogo\x12\x11\n\tnumCartas\x18\x01 \x01(\x05\x12\x1a\n\x12numCartasRestantes\x18\x02 \x01(\x05\x12\x1d\n\x06\x63\x61rtas\x18\x03 \x03(\x0b\x32\r.agenda.Carta\x12\"\n\tjogadores\x18\x07 \x03(\x0b\x32\x0f.agenda.Jogador\x12\x17\n\x0fidUltimoJogador\x18\x08 \x01(\x05\x12\x16\n\x0eidJogadorAtual\x18\t \x01(\x05\";\n\x06Jogada\x12\x0e\n\x06\x63\x61rta1\x18\x01 \x01(\x05\x12\x0e\n\x06\x63\x61rta2\x18\x02 \x01(\x05\x12\x11\n\tidJogador\x18\x03 \x01(\x05\x32L\n\x0fMemoriaServidor\x12\x39\n\x08\x63onectar\x12\x0f.agenda.Jogador\x1a\x1a.google.protobuf.BoolValue\"\x00\x32\xbf\x01\n\x0eMemoriaCliente\x12\x31\n\x0finformarJogador\x12\x0c.agenda.Jogo\x1a\x0e.agenda.Jogada\"\x00\x12;\n\rreceberJogada\x12\x0c.agenda.Jogo\x1a\x1a.google.protobuf.BoolValue\"\x00\x12=\n\x0finformarFimJogo\x12\x0c.agenda.Jogo\x1a\x1a.google.protobuf.BoolValue\"\x00\x62\x06proto3')

_globals = globals()
_builder.BuildMessageAndEnumDescriptors(DESCRIPTOR, _globals)
_builder.BuildTopDescriptorsAndMessages(DESCRIPTOR, 'memoria_pb2', _globals)
if not _descriptor._USE_C_DESCRIPTORS:
  DESCRIPTOR._loaded_options = None
  _globals['_JOGADOR']._serialized_start=57
  _globals['_JOGADOR']._serialized_end=129
  _globals['_CARTA']._serialized_start=131
  _globals['_CARTA']._serialized_end=201
  _globals['_JOGO']._serialized_start=204
  _globals['_JOGO']._serialized_end=373
  _globals['_JOGADA']._serialized_start=375
  _globals['_JOGADA']._serialized_end=434
  _globals['_MEMORIASERVIDOR']._serialized_start=436
  _globals['_MEMORIASERVIDOR']._serialized_end=512
  _globals['_MEMORIACLIENTE']._serialized_start=515
  _globals['_MEMORIACLIENTE']._serialized_end=706
# @@protoc_insertion_point(module_scope)
