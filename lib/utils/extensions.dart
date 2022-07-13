extension ListExtension<E> on List<E> {
  void addNonNull(E item) {
    if (item != null) add(item);
  }
}
