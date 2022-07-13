import 'package:crypt_signature/ui/locker/inherited_locker.dart';
import 'package:flutter/material.dart';

class LockerWrapper extends StatefulWidget {
  final Widget child;
  const LockerWrapper({Key key, @required this.child}) : super(key: key);

  @override
  State<LockerWrapper> createState() => _LockerWrapperState();
}

class _LockerWrapperState extends State<LockerWrapper> {
  bool lock = false;

  void lockScreen() {
    setState(() {
      lock = true;
    });
  }

  void unlockScreen() {
    setState(() {
      lock = false;
    });
  }

  @override
  Widget build(BuildContext context) => InheritedLocker(
        lock: lock,
        lockScreen: lockScreen,
        unlockScreen: unlockScreen,
        child: widget.child,
      );
}
