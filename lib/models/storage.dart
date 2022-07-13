import 'dart:convert';

import 'package:crypt_signature/crypt_signature.dart';
import 'package:crypt_signature/utils/extensions.dart';
import 'package:shared_preferences/shared_preferences.dart';

/// Локальное хранилище для моделей
class Storage<T> {
  String key;
  SharedPreferences sharedPreferences;
  T Function(Map map) parser;

  Storage({this.parser, String key}) : this.key = key ?? T.toString() {
    sharedPreferences = CryptSignature.sharedPreferences;
  }

  List<T> get() {
    String data = sharedPreferences.getString(key);

    if (data == null) return <T>[];

    List list = json.decode(data) as List;

    if (list == null || list.isEmpty) return <T>[];

    List<T> objects = [];

    /// TODO: переделать парсер в compute
    for (final object in list) objects.addNonNull(parser != null ? parser(object as Map) : object as T);

    return objects;
  }

  void save(List<T> objects) {
    sharedPreferences.setString(key, json.encode(objects));
  }

  bool add(T object) {
    List<T> objects = this.get();

    if (objects.contains(object)) return false;

    objects.addNonNull(object);

    this.save(objects);

    return true;
  }

  bool remove(T object) {
    List<T> objects = this.get();

    if (!objects.contains(object)) return false;

    objects.remove(object);

    this.save(objects);

    return true;
  }

  void setDefaultKey() {
    key = T.toString();
  }
}
