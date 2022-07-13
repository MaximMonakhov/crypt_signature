class License {
  final bool status;
  final String serialNumber;
  final String message;
  final int expiredThroughDays;

  License({this.status, this.message, this.expiredThroughDays, this.serialNumber});

  static License fromMap(Map map) => License(
        status: map["success"] as bool,
        message: map["message"] as String,
        expiredThroughDays: map["expiredThroughDays"] as int,
        serialNumber: map["serialNumber"] as String,
      );
}
