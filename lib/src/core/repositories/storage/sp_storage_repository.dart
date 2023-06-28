import 'package:crypt_signature/src/core/repositories/storage/storage_repository.dart';
import 'package:shared_preferences/shared_preferences.dart';

/// Хранилище для [T] на основе SharedPreferences
abstract class SPStorageRepository<T> implements StorageRepository<T> {
  final String key;
  final SharedPreferences sharedPreferences;

  SPStorageRepository(this.sharedPreferences, {String? key}) : key = key ?? "$T";

  List<T>? cache;

  @override
  Future<bool> add(T entity) async {
    List<T> entities = await getEntities();
    if (entities.contains(entity)) return false;
    entities.add(entity);
    await save(entities);
    return true;
  }

  @override
  Future<bool> remove(T entity) async {
    List<T> entities = await getEntities();
    if (!entities.contains(entity)) return false;
    entities.remove(entity);
    await save(entities);
    return true;
  }

  @override
  Future<void> clear() async {
    cache = null;
    await sharedPreferences.remove(key);
  }
}
