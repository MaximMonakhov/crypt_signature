import 'package:crypt_signature/src/core/repositories/base_repository.dart';
import 'package:flutter/foundation.dart';

/// Базовый ChangeNotifier для получения и хранения:
/// 1. Сущности
/// 2. Списка сущностей
abstract class BaseChangeNotifier<T> extends ChangeNotifier {
  final BaseRepository<T> repository;

  List<T>? _entities;
  T? _entity;

  BaseChangeNotifier(this.repository);

  List<T>? get entities => _entities;
  T? get entity => _entity;

  set entities(List<T>? entities) {
    _entities = entities;
    notifyListeners();
  }

  set entity(T? entity) {
    _entity = entity;
    notifyListeners();
  }

  Future<List<T>> getEntities({Map<String, String>? queryParams}) async {
    await Future.delayed(const Duration(milliseconds: 50));
    entities = await repository.getEntities();
    return entities!;
  }

  Future<T> getEntity(int id) async {
    entity = await repository.getEntity(id);
    return entity!;
  }

  void reset() {
    _entities = null;
    _entity = null;
    notifyListeners();
  }

  void resetEntity() {
    _entity = null;
    notifyListeners();
  }

  void resetEntities() {
    _entities = null;
    notifyListeners();
  }
}
