import 'package:api_event/models/event.dart';

class UI {
  static Event<bool> lockScreenEvent = new Event<bool>(initValue: false);

  static void lockScreen() => lockScreenEvent.publish(true);
  static void unlockScreen() => lockScreenEvent.publish(false);
}
