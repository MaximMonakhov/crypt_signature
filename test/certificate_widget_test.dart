import 'dart:async';

import 'package:crypt_signature/crypt_signature.dart';
import 'package:crypt_signature/src/ui/certificate_widget.dart';
import 'package:flutter/material.dart';
import 'package:flutter_test/flutter_test.dart';

void main() {
  testWidgets('Тестирование виджета Certificate', (tester) async {
    Certificate certificate = Certificate(
      algorithm: Algorithm.algorithms.first,
      alias: "ALIASS",
      certificate: "",
      certificateDescription: "",
      notAfterDate: "DATE",
      serialNumber: "123",
      subjectDN: "SUBJECT_DN",
      parameterMap: {},
      uuid: "",
    );
    final onTapCompleter = Completer<void>();
    final removeCompleter = Completer<void>();

    await tester.pumpWidget(MaterialApp(home: Scaffold(body: CertificateWidget(certificate, onTapCompleter.complete, removeCompleter.complete))));

    final serialNumber = find.textContaining("123");
    final alias = find.text("ALIASS");
    final date = find.text("DATE");
    final algorithm = find.text(Algorithm.algorithms.first.name);
    expect(serialNumber, findsOneWidget);
    expect(alias, findsOneWidget);
    expect(date, findsOneWidget);
    expect(algorithm, findsOneWidget);

    await tester.tap(find.byType(CertificateWidget));
    expect(onTapCompleter.isCompleted, true);

    await tester.tap(find.byIcon(Icons.clear));
    expect(removeCompleter.isCompleted, true);

    await tester.tap(find.text("Просмотреть идентифицирующие сведения"));
    await tester.pumpAndSettle();
    final dn = find.text("SUBJECT_DN");
    expect(dn, findsOneWidget);
  });
}
