import 'dart:async';

import 'package:crypt_signature/src/models/certificate.dart';
import 'package:crypt_signature/src/repositories/certificate_repository.dart';

class MemoryCertificateRepository implements CertificateRepository {
  List<Certificate> list = [];

  @override
  FutureOr<bool> add(Certificate certificate) {
    if (list.contains(certificate)) return false;
    list.add(certificate);
    return true;
  }

  @override
  FutureOr<void> clear() {
    list.clear();
  }

  @override
  FutureOr<List<Certificate>> getEntities() => list;

  @override
  FutureOr<bool> remove(Certificate certificate) {
    if (!list.contains(certificate)) return false;
    list.remove(certificate);
    return true;
  }

  @override
  FutureOr<Certificate> getEntity(int id) {
    throw UnimplementedError();
  }
}
