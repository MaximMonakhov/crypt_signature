import 'package:flutter/foundation.dart';

class LockService extends ChangeNotifier {
  bool _lock = false;

  bool get lock => _lock;

  set lock(bool value) {
    _lock = value;
    notifyListeners();
  }

  void lockScreen() => lock = true;
  void unlockScreen() => lock = false;
}
