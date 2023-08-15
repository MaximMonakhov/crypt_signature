class ApiResponseException implements Exception {
  final String? message;
  final String? details;

  ApiResponseException(this.message, this.details);

  @override
  String toString() => "ApiResponseException. $message $details";
}
