import 'package:crypt_signature/src/core/repositories/base_repository.dart';

/// Репозиторий для хранения [T]
/// Если понадобится хранить [T] для разных классов, то можно добавить [Q] как идентификатор
abstract class StorageRepository<T> extends BaseRepository<T> {
  Future<bool> add(T entity);
  Future<bool> remove(T entity);
  Future<void> save(List<T> entities);
  Future<void> clear();
}
