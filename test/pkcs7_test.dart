import 'dart:typed_data';

import 'package:flutter_test/flutter_test.dart';

void main() {
  group("Тестирование класса PKCS7", () {
    List<int> list = [1, 2, 3];
    List<Uint8List> list2 = [Uint8List.fromList(list)];
    var result = list2.expand((x) => [1]).toList();
    print(result);
  });
}

const int CONTEXT_SPECIFIC_TYPE = 0xA0;
