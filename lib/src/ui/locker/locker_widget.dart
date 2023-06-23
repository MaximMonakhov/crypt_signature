import 'package:crypt_signature/src/ui/locker/inherited_locker.dart';
import 'package:flutter/material.dart';

class LockerWidget extends StatelessWidget {
  const LockerWidget({super.key});

  @override
  Widget build(BuildContext context) {
    if (InheritedLocker.of(context).lock) {
      return Container(
        width: double.infinity,
        height: double.infinity,
        color: Colors.black.withOpacity(0.5),
        child: Center(
          child: Container(
            width: 50,
            height: 50,
            padding: const EdgeInsets.all(20),
            decoration: BoxDecoration(
              color: const Color.fromRGBO(106, 147, 245, 1),
              borderRadius: BorderRadius.circular(10),
            ),
            child: const CircularProgressIndicator(
              valueColor: AlwaysStoppedAnimation<Color>(Colors.white),
              strokeWidth: 1,
            ),
          ),
        ),
      );
    }

    return const SizedBox.shrink();
  }
}
