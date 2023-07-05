import 'package:crypt_signature/src/core/interface/smooth_card.dart';
import 'package:crypt_signature/src/services/lock_service.dart';
import 'package:flutter/material.dart';
import 'package:provider/provider.dart';

class LockerWidget extends StatelessWidget {
  const LockerWidget({super.key});

  @override
  Widget build(BuildContext context) => Provider.of<LockService>(context).lock
      ? Container(
          width: double.infinity,
          height: double.infinity,
          color: Colors.black.withOpacity(0.5),
          child: Center(
            child: SmoothCard(
              padding: EdgeInsets.zero,
              child: Container(
                width: 50,
                height: 50,
                padding: const EdgeInsets.all(20),
                child: CircularProgressIndicator(
                  valueColor: AlwaysStoppedAnimation<Color>(Theme.of(context).colorScheme.primary),
                  strokeWidth: 1,
                ),
              ),
            ),
          ),
        )
      : const SizedBox.shrink();
}