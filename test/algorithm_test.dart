import 'package:crypt_signature/models/algorithm.dart';
import 'package:flutter_test/flutter_test.dart';

void main() {
  group('Тестирование класса Algorithm', () {
    test(
        'Поиск алгоритма ГОСТ Р 34.10-2012 по алгоритму публичного ключа 1.2.643.7.1.1.1.1',
        () {
      String publicKeyOID = "1.2.643.7.1.1.1.1";
      Algorithm algorithm = Algorithm.findAlgorithmByPublicKeyOID(publicKeyOID);

      expect(algorithm.name, "ГОСТ Р 34.10-2012");
    });

    test('Поиск алгоритма по неизвестному OID', () {
      String publicKeyOID = "1.2.643.2.2.21";
      Algorithm algorithm = Algorithm.findAlgorithmByPublicKeyOID(publicKeyOID);

      expect(algorithm.name, "Неизвестен");
    });

    test('Поиск алгоритма по null OID', () {
      String publicKeyOID;
      Algorithm algorithm = Algorithm.findAlgorithmByPublicKeyOID(publicKeyOID);

      expect(algorithm.name, "Неизвестен");
    });

    test('Форматирование OID', () {
      String rawOID = "[1, 2, 643, 2, 2, 21]";
      String oid = Algorithm.formatOID(rawOID);

      expect(oid, "1.2.643.2.2.21");
    });

    test('Сериализация и десериализация', () {
      Algorithm algorithm = Algorithm.algorithms[0];
      Map json = algorithm.toJson();
      Algorithm parsedAlgorithm = Algorithm.fromJson(json);

      expect(algorithm.name, parsedAlgorithm.name);
      expect(algorithm.hashOID, parsedAlgorithm.hashOID);
      expect(algorithm.publicKeyOID, parsedAlgorithm.publicKeyOID);
      expect(algorithm.signatureOID, parsedAlgorithm.signatureOID);
    });
  });
}
