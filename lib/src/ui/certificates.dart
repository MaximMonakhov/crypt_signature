import 'package:crypt_signature/src/core/builder/async_builder.dart';
import 'package:crypt_signature/src/models/certificate.dart';
import 'package:crypt_signature/src/providers/crypt_signature_provider.dart';
import 'package:crypt_signature/src/repositories/certificate_repository.dart';
import 'package:crypt_signature/src/services/certificate_service.dart';
import 'package:crypt_signature/src/services/license_service.dart';
import 'package:crypt_signature/src/services/lock_service.dart';
import 'package:crypt_signature/src/ui/certificate.dart';
import 'package:flutter/material.dart';
import 'package:provider/provider.dart';

class CertificatesView extends StatelessWidget {
  const CertificatesView({super.key});

  @override
  Widget build(BuildContext context) => ChangeNotifierProvider<CertificateService>(
        create: (context) => CertificateService(
          context.read<CertificateRepository>(),
          context.read<CryptSignatureProvider>(),
          context.read<LockService>(),
          context.read<LicenseService>(),
        ),
        builder: (context, _) => Column(
          children: [
            GestureDetector(
              onTap: () {
                context.read<CertificateService>().addCertificate(context);
              },
              child: Container(
                margin: const EdgeInsets.only(bottom: 10.0, top: 10.0),
                padding: const EdgeInsets.symmetric(horizontal: 40.0, vertical: 10.0),
                decoration: BoxDecoration(
                  color: const Color.fromRGBO(106, 147, 245, 1),
                  borderRadius: BorderRadius.circular(10.0),
                ),
                child: const Text(
                  "Добавить сертификат (.pfx)",
                  textAlign: TextAlign.center,
                  style: TextStyle(color: Colors.white),
                ),
              ),
            ),
            Expanded(
              child: Selector<CertificateService, List<Certificate>?>(
                selector: (context, service) => service.entities,
                builder: (context, data, _) => AsyncFutureBuilderList<Certificate>(
                  data: data,
                  getObjects: () => context.read<CertificateService>().getEntities(),
                  emptyListCaption: "Список сертификатов пуст",
                  builder: (context, entity) => CertificateWidget(
                    entity,
                    (certificate) => context.read<CertificateService>().removeCertificate(certificate),
                  ),
                ),
              ),
            ),
          ],
        ),
      );
}
