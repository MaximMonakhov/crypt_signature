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

    List<dynamic> list = json.decode(data);

    if (list == null || list.isEmpty) return [];

    List<T> objects = [];

    /// TODO: переделать парсер в compute
    for (Map object in list) objects.add(parser(object));

    return objects;
  }

  void save(List<T> objects) {
    sharedPreferences.setString(T.toString(), json.encode(objects));
  }

  bool add(T object) {
    List<T> objects = this.get();

    if (objects.contains(object)) return false;

    objects.add(object);

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
}
