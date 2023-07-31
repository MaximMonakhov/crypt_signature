import 'package:crypt_signature/crypt_signature.dart';
import 'package:crypt_signature/src/core/interface/loading.dart';
import 'package:crypt_signature/src/core/interface/smooth_button.dart';
import 'package:crypt_signature/src/providers/crypt_signature_provider.dart';
import 'package:crypt_signature/src/repositories/certificate_repository.dart';
import 'package:crypt_signature/src/services/certificate_service.dart';
import 'package:crypt_signature/src/services/license_service.dart';
import 'package:crypt_signature/src/services/lock_service.dart';
import 'package:crypt_signature/src/ui/certificate_widget.dart';
import 'package:crypt_signature/src/ui/certificates_view.dart';
import 'package:flutter/material.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:provider/provider.dart';
import 'package:shared_preferences/shared_preferences.dart';

void main() {
  group("Тестирование виджета CertificatesView.", () {
    late SPCertificateRepository certificateRepository;

    setUp(() async {
      SharedPreferences.setMockInitialValues({});
      SharedPreferences sharedPreferences = await SharedPreferences.getInstance();
      certificateRepository = SPCertificateRepository(sharedPreferences, (data) => Certificate.fromJson(data));
    });

    Future<void> pumpWidget(WidgetTester tester) => tester.pumpWidget(
          MaterialApp(
            home: Scaffold(
              body: MultiProvider(
                providers: [
                  Provider<CertificateRepository>(create: (context) => certificateRepository),
                  Provider<CryptSignatureProvider>(
                    create: (context) => CryptSignatureProvider(context, CryptSignatureTheme(hint: "HINT"), MessageSignRequest("")),
                  ),
                  ChangeNotifierProvider<LockService>(create: (context) => LockService()),
                  ChangeNotifierProvider<LicenseService>(create: (context) => LicenseService(context.read<LockService>())),
                ],
                builder: (context, _) => const CertificatesView(),
              ),
            ),
          ),
        );

    testWidgets("View должен содержать кнопку для добавления сертификатов и текст с подсказкой", (tester) async {
      await pumpWidget(tester);

      final hintText = find.text("HINT");
      final addCertificateButton = find.byType(SmoothButton);
      final addCertificateText = find.text("Добавить сертификат (.pfx)");
      final loadingWidget = find.byType(LoadingWidget);
      expect(hintText, findsOneWidget);
      expect(addCertificateButton, findsOneWidget);
      expect(addCertificateText, findsOneWidget);
      expect(loadingWidget, findsOneWidget);

      await tester.pumpAndSettle();
    });

    testWidgets('При добавлении/удалении сертификатов из хранилища, список должен обновляться', (tester) async {
      await pumpWidget(tester);

      final loadingWidget = find.byType(LoadingWidget);
      expect(loadingWidget, findsOneWidget);

      await tester.pumpAndSettle();

      final emptyListCaption = find.text("Список сертификатов пуст");
      expect(emptyListCaption, findsOneWidget);
      expect(find.byType(CertificateWidget), findsNothing);

      final BuildContext context = tester.element(find.byType(Column));
      CertificateService service = context.read<CertificateService>();
      final firstCertificate = Certificate(
        algorithm: Algorithm.algorithms.first,
        alias: "ALIASS",
        certificate: "1",
        certificateDescription: "",
        notAfterDate: "DATE",
        serialNumber: "1",
        subjectDN: "SUBJECT_DN",
        parameterMap: {},
        uuid: "1",
      );
      final secondCertificate = Certificate(
        algorithm: Algorithm.algorithms.first,
        alias: "ALIASS",
        certificate: "2",
        certificateDescription: "",
        notAfterDate: "DATE",
        serialNumber: "2",
        subjectDN: "SUBJECT_DN",
        parameterMap: {},
        uuid: "2",
      );

      await certificateRepository.add(firstCertificate);
      service.resetEntities();
      await tester.pumpAndSettle();
      final firstCertificateWidget = find.byType(CertificateWidget);
      expect(firstCertificateWidget, findsOneWidget);

      await certificateRepository.add(secondCertificate);
      service.resetEntities();
      await tester.pumpAndSettle();
      final certificateWidgets = find.byType(CertificateWidget);
      expect(certificateWidgets, findsNWidgets(2));

      await certificateRepository.remove(firstCertificate);
      service.resetEntities();
      await tester.pumpAndSettle();
      final secondCertificateWidget = find.byType(CertificateWidget);
      expect(secondCertificateWidget, findsOneWidget);

      await certificateRepository.remove(secondCertificate);
      service.resetEntities();
      await tester.pumpAndSettle();
      expect(find.byType(CertificateWidget), findsNothing);
    });

    testWidgets("При наличии сертификатов в репозитории, они должны быть отображены", (tester) async {
      certificateRepository.sharedPreferences.setString(
        "Certificate",
        '[{"uui1d":"1","certificate":"1","alias":"ALIASS","subjectDN":"SUBJECT_DN","notAfterDate":"DATE","serialNumber":"1","algorithm":{"name":"ГОСТ Р 34.10-2001","hashOID":"1.2.643.2.2.9","publicKeyOID":"1.2.643.2.2.19","signatureOID":"1.2.643.2.2.3"},"parameterMap":{},"certificateDescription":""}]',
      );

      await pumpWidget(tester);

      final loadingWidget = find.byType(LoadingWidget);
      expect(loadingWidget, findsOneWidget);

      await tester.pumpAndSettle();

      final certificateWidget = find.byType(CertificateWidget);
      expect(certificateWidget, findsOneWidget);
    });

    testWidgets("При отсутствии сертификатов в репозитории должен отображаться пустой список", (tester) async {
      await pumpWidget(tester);

      final loadingWidget = find.byType(LoadingWidget);
      expect(loadingWidget, findsOneWidget);

      await tester.pumpAndSettle();

      final emptyListCaption = find.text("Список сертификатов пуст");
      expect(emptyListCaption, findsOneWidget);
      expect(find.byType(CertificateWidget), findsNothing);
    });

    testWidgets("View вызывает методы сервиса при взаимодействии", (tester) async {
      // TODO: Доделать тест
      // Нужно сделать verify(service.getEntities/service.addCertificate).called(1), но на текущий момент не замокать сервис, т.к. он создается внутри View
    });
  });
}
