import 'dart:async';

/// Базовый репозиторий для получения:
/// 1. Сущности
/// 2. Списка сущностей
abstract class BaseRepository<T> {
  FutureOr<List<T>> getEntities();
  FutureOr<T> getEntity(int id);
}
