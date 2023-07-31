import 'dart:async';

import 'package:crypt_signature/crypt_signature.dart';
import 'package:crypt_signature/src/core/repositories/base_repository.dart';
import 'package:crypt_signature/src/core/repositories/storage/object_sp_storage_repository.dart';

abstract class CertificateRepository extends BaseRepository<Certificate> {
  FutureOr<bool> add(Certificate certificate);
  FutureOr<bool> remove(Certificate certificate);
  FutureOr<void> clear();
}

class SPCertificateRepository extends ObjectSPStorageRepository<Certificate> implements CertificateRepository {
  SPCertificateRepository(super.sharedPreferences, super.parser);
}
