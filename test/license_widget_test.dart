import 'package:crypt_signature/src/core/interface/smooth_button.dart';
import 'package:crypt_signature/src/models/license.dart';
import 'package:crypt_signature/src/services/license_service.dart';
import 'package:crypt_signature/src/services/lock_service.dart';
import 'package:crypt_signature/src/ui/license_widget.dart';
import 'package:flutter/material.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:provider/provider.dart';

void main() {
  group("Тестирование виджета License.", () {
    late LicenseService service;

    Future<void> pumpWidget(WidgetTester tester, {License? license}) => tester.pumpWidget(
          MaterialApp(
            home: Scaffold(
              body: MultiProvider(
                providers: [
                  ChangeNotifierProvider<LockService>(create: (context) => LockService()),
                  ChangeNotifierProvider<LicenseService>(create: (context) => service = LicenseService(context.read<LockService>(), license: license)),
                ],
                builder: (context, _) => const LicenseWidget(),
              ),
            ),
          ),
        );

    testWidgets("Лицензия активна", (tester) async {
      License license = License(status: true, message: "Message", expiredThroughDays: 5, serialNumber: "123");
      await pumpWidget(tester, license: license);

      final licenseNumber = find.text("123");
      final expireText = find.text("Лицензия активна и истекает через 5 дней");
      final changeButton = find.byType(SmoothButton);
      expect(licenseNumber, findsOneWidget);
      expect(expireText, findsOneWidget);
      expect(changeButton, findsOneWidget);
    });

    testWidgets("Лицензия просрочена", (tester) async {
      License license = License(status: false, message: "Срок действия лицензии истек", expiredThroughDays: 5, serialNumber: "123");
      await pumpWidget(tester, license: license);

      final expireText = find.text("Срок действия лицензии истек");
      final changeButton = find.byType(SmoothButton);
      expect(expireText, findsOneWidget);
      expect(changeButton, findsOneWidget);
    });

    testWidgets("Виджет реагирует на изменение лицензии", (tester) async {
      License firstLicense = License(status: true, message: "Message", expiredThroughDays: 5, serialNumber: "1");
      await pumpWidget(tester, license: firstLicense);

      final firstLicenseNumber = find.text("1");
      expect(firstLicenseNumber, findsOneWidget);

      License secondLicense = License(status: true, message: "Message", expiredThroughDays: 5, serialNumber: "2");
      service.license = secondLicense;

      await tester.pumpAndSettle();

      final secondLicenseNumber = find.text("2");
      expect(secondLicenseNumber, findsOneWidget);

      License thirdLicense = License(status: false, message: "Error", expiredThroughDays: 5, serialNumber: "3");
      service.license = thirdLicense;

      await tester.pumpAndSettle();

      final thirdLicenseMessage = find.text("Error");
      expect(thirdLicenseMessage, findsOneWidget);
    });
  });
}
