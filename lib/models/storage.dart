import 'dart:convert';

import 'package:shared_preferences/shared_preferences.dart';

import '../crypt_signature.dart';

class Storage<T> {
  SharedPreferences sharedPreferences;
  T Function(Map<String, dynamic>) parser;

  Storage(this.parser) {
    sharedPreferences = CryptSignature.sharedPreferences;
  }

  List<T> get() {
    String data = sharedPreferences.getString(T.toString());

    if (data == null) return [];

    List<dynamic> list = json.decode(data) as List;

    if (list == null || list.isEmpty) return [];

    List<T> objects = [];

    /// TODO: переделать парсер в compute
    for (final Map<String, dynamic> object in list as List<Map<String, dynamic>>) {
      objects.add(parser(object));
    }

    return objects;
  }

  void save(List<T> objects) {
    sharedPreferences.setString(T.toString(), json.encode(objects));
  }

  bool add(T object) {
    List<T> objects = get();

    if (objects.contains(object)) return false;

    objects.add(object);

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
}
