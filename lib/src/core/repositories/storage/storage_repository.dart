import 'dart:async';

import 'package:crypt_signature/src/core/repositories/base_repository.dart';

/// Репозиторий для хранения [T]
/// Если понадобится хранить [T] для разных классов, то можно добавить [Q] как идентификатор
abstract class StorageRepository<T> extends BaseRepository<T> {
  FutureOr<bool> add(T entity);
  FutureOr<bool> remove(T entity);
  FutureOr<void> save(List<T> entities);
  FutureOr<void> clear();
}
