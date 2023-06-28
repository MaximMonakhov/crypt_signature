// ignore_for_file: avoid_catches_without_on_clauses

import 'dart:async';
import 'dart:convert';

import 'package:crypt_signature/src/core/repositories/storage/sp_storage_repository.dart';

/// Реализация хранилища для [T] на основе SharedPreferences
class ObjectSPStorageRepository<T> extends SPStorageRepository<T> {
  final T Function(Map<String, dynamic> data) parser;

  ObjectSPStorageRepository(super.sharedPreferences, this.parser);

  @override
  List<T> getEntities() {
    if (cache != null) return cache!;

    String? data = sharedPreferences.getString(key);
    if (data == null) return cache = [];

    List<dynamic>? list;
    try {
      list = json.decode(data) as List<dynamic>;
    } catch (_) {
      clear();
      return cache = [];
    }

    List<T>? objects;
    try {
      objects = list.map((e) => parser(e as Map<String, dynamic>)).toList();
    } catch (_) {
      clear();
      return cache = [];
    }

    return objects;
  }

  @override
  FutureOr<T> getEntity(int id) {
    throw UnimplementedError();
  }

  @override
  Future<void> save(List<T> entities) async {
    cache = entities;
    await sharedPreferences.setString(key, json.encode(entities));
  }
}
