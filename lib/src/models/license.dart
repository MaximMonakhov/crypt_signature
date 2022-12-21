class License {
  final bool status;
  final String serialNumber;
  final String message;
  final int expiredThroughDays;

  License({required this.status, required this.message, required this.expiredThroughDays, required this.serialNumber});

  factory License.fromMap(Map<String, dynamic> map) => License(
        status: map["success"] as bool,
        message: map["message"] as String,
        expiredThroughDays: map["expiredThroughDays"] as int,
        serialNumber: map["serialNumber"] as String,
      );
}
