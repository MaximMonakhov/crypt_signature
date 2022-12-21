extension ListExtension<E> on List<E> {
  void addNonNull(E item) {
    if (item != null) add(item);
  }
}

extension StringExtension on String {
  String truncate({int length = 10, String omission = '...'}) {
    if (length >= this.length) return this;

    return replaceRange(length, this.length, omission);
  }
}
