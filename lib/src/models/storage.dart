import 'dart:convert';

import 'package:crypt_signature/src/crypt_signature_api.dart';
import 'package:crypt_signature/src/utils/extensions.dart';
import 'package:shared_preferences/shared_preferences.dart';

/// Локальное хранилище для моделей
class Storage<T> {
  String key;
  late SharedPreferences sharedPreferences;
  T Function(Map<String, dynamic> map) parser;

  Storage({required this.parser, String? key}) : key = key ?? T.toString() {
    sharedPreferences = CryptSignature.sharedPreferences!;
  }

  List<T> get() {
    String? data = sharedPreferences.getString(key);

    if (data == null) return <T>[];

    List<dynamic>? list = json.decode(data) as List?;

    if (list == null || list.isEmpty) return <T>[];

    List<T> objects = [];

    for (final object in list) {
      objects.addNonNull(parser(object as Map<String, dynamic>));
    }

    return objects;
  }

  void save(List<T> objects) {
    sharedPreferences.setString(key, json.encode(objects));
  }

  bool add(T object) {
    List<T> objects = get();

    if (objects.contains(object)) return false;

    objects.addNonNull(object);

    save(objects);

    return true;
  }

  bool remove(T object) {
    List<T> objects = get();

    if (!objects.contains(object)) return false;

    objects.remove(object);

    save(objects);

    return true;
  }

  void setDefaultKey() {
    key = T.toString();
  }
}
