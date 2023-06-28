import 'dart:async';

import 'package:crypt_signature/src/core/interface/error.dart';
import 'package:crypt_signature/src/core/interface/loading.dart';
import 'package:crypt_signature/src/core/interface/refresher.dart';
import 'package:crypt_signature/src/providers/crypt_signature_provider.dart';
import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import 'package:pull_to_refresh/pull_to_refresh.dart';

class AsyncFutureBuilder<T> extends StatefulWidget {
  final bool refreshIndicator;
  final bool scrollbar;
  final bool wrapWithList;
  final bool alwaysScrollableScrollPhysics;
  final Widget loading;
  final List<Widget> Function(BuildContext context, T entity) builder;

  final T? data;
  final Widget Function(BuildContext context, void Function(Future<T>? future) update)? init;
  final Future<T> Function()? getObject;

  AsyncFutureBuilder({
    required this.builder,
    this.data,
    this.init,
    this.getObject,
    this.wrapWithList = true,
    this.refreshIndicator = true,
    this.scrollbar = true,
    this.alwaysScrollableScrollPhysics = true,
    this.loading = const LoadingWidget(),
    super.key,
  }) : assert(getObject != null || init != null);

  @override
  State<AsyncFutureBuilder<T>> createState() => _AsyncFutureBuilderState<T>();
}

class _AsyncFutureBuilderState<T> extends State<AsyncFutureBuilder<T>> {
  late final RefreshController controller;
  Future<T>? _future;

  bool get hasInitState => widget.init != null;
  bool get hasData => widget.data != null;

  @override
  void initState() {
    controller = RefreshController();
    super.initState();
  }

  @override
  void didChangeDependencies() {
    _future = widget.getObject!.call();
    super.didChangeDependencies();
  }

  @override
  void didUpdateWidget(covariant AsyncFutureBuilder<T> oldWidget) {
    if (widget.data == null && oldWidget.data != null) repeat();
    super.didUpdateWidget(oldWidget);
  }

  void update(Future<T>? future) {
    if (future != _future) {
      setState(() {
        _future = future;
      });
    }
  }

  void repeat() => update(widget.getObject!());

  Widget _wrapWithRefresher(Widget child, ScrollPhysics scrollPhysics) => SmartRefresher(
        controller: controller,
        header: const RefresherHeader(),
        onRefresh: () async {
          controller.refreshToIdle();
          repeat();
        },
        physics: scrollPhysics,
        child: child,
      );

  Widget _wrapWithList(List<Widget> children, ScrollPhysics scrollPhysics) => ListView(
        key: PageStorageKey("AsyncFutureBuilder$T"),
        physics: widget.alwaysScrollableScrollPhysics ? AlwaysScrollableScrollPhysics(parent: scrollPhysics) : scrollPhysics,
        padding: const EdgeInsets.only(left: 15, right: 15, bottom: 20),
        children: children,
      );

  Widget _wrapWithScrollbar(Widget child) => CupertinoScrollbar(thumbVisibility: true, child: child);

  Widget buildEntity(T data) {
    ScrollPhysics scrollPhysics = context.read<CryptSignatureProvider>().theme.scrollPhysics;
    List<Widget> dataWidgets = widget.builder(context, data);
    assert(dataWidgets.isNotEmpty);

    Widget child = widget.wrapWithList ? _wrapWithList(dataWidgets, scrollPhysics) : dataWidgets.first;
    if (widget.refreshIndicator) child = _wrapWithRefresher(child, scrollPhysics);
    if (widget.scrollbar) child = _wrapWithScrollbar(child);

    return child;
  }

  Widget resolveFutureBuilder() => FutureBuilder<T>(
        future: _future,
        builder: (context, snapshot) {
          switch (snapshot.connectionState) {
            case ConnectionState.none:
              if (hasInitState) return widget.init!.call(context, update);
              return widget.loading;
            case ConnectionState.waiting:
            case ConnectionState.active:
              return widget.loading;
            case ConnectionState.done:
              if (snapshot.hasError) {
                if (hasInitState) return widget.init!.call(context, update);
                return ErrorViewWidget(snapshot.error ?? "Неизвестная ошибка", stackTrace: snapshot.stackTrace ?? StackTrace.current, repeatTry: repeat);
              }
              if (snapshot.hasData) return buildEntity(snapshot.data as T);
              return widget.loading;
          }
        },
      );

  @override
  Widget build(BuildContext context) => resolveFutureBuilder();
}

class AsyncFutureBuilderList<T> extends StatefulWidget {
  final bool refreshIndicator;
  final bool scrollbar;
  final bool alwaysScrollableScrollPhysics;
  final bool keepAlive;
  final EdgeInsets? padding;
  final Widget loading;
  final Widget Function(BuildContext context, T entity) builder;

  final String emptyListCaption;
  final List<T>? data;
  final Widget Function(BuildContext context, void Function(Future<List<T>>? future) update)? init;
  final Future<List<T>> Function()? getObjects;

  const AsyncFutureBuilderList({
    required this.builder,
    this.data,
    this.init,
    this.getObjects,
    this.padding,
    this.loading = const LoadingWidget(),
    this.keepAlive = false,
    this.refreshIndicator = true,
    this.scrollbar = true,
    this.alwaysScrollableScrollPhysics = true,
    this.emptyListCaption = "Список пуст",
    super.key,
  }) : assert(getObjects != null || init != null);

  @override
  State<AsyncFutureBuilderList<T>> createState() => _AsyncFutureBuilderListState<T>();
}

class _AsyncFutureBuilderListState<T> extends State<AsyncFutureBuilderList<T>> {
  late final RefreshController controller;
  late final ScrollController scrollController;

  Future<List<T>>? _future;

  bool get hasInitState => widget.init != null;
  bool get hasData => widget.data != null;
  bool get wantKeepAlive => widget.keepAlive && hasData;

  @override
  void initState() {
    scrollController = ScrollController();
    controller = RefreshController();
    super.initState();
  }

  @override
  void didChangeDependencies() {
    if (!wantKeepAlive && !hasInitState) _future = widget.getObjects!.call();
    super.didChangeDependencies();
  }

  @override
  void didUpdateWidget(covariant AsyncFutureBuilderList<T> oldWidget) {
    if (widget.data == null && oldWidget.data != null) repeat();
    super.didUpdateWidget(oldWidget);
  }

  void update(Future<List<T>>? future) {
    if (future != _future) {
      setState(() {
        _future = future;
      });
    }
  }

  void repeat() => update(widget.getObjects!());

  Widget _wrapWithRefresher(Widget child, ScrollPhysics scrollPhysics) => SmartRefresher(
        controller: controller,
        header: const RefresherHeader(),
        scrollController: scrollController,
        onRefresh: () async {
          controller.refreshToIdle();
          repeat();
        },
        physics: scrollPhysics,
        child: child,
      );

  Widget _wrapWithScrollbar(Widget child) => CupertinoScrollbar(thumbVisibility: true, controller: scrollController, child: child);

  Widget getEmptyListWidget() => Center(child: Text(widget.emptyListCaption, style: TextStyle(color: Theme.of(context).primaryColor)));

  Widget buildList(List<T> data) {
    ScrollPhysics scrollPhysics = context.read<CryptSignatureProvider>().theme.scrollPhysics;

    Widget list = data.isEmpty
        ? getEmptyListWidget()
        : ListView.builder(
            key: PageStorageKey("AsyncFutureBuilderList$T"),
            controller: scrollController,
            physics: widget.alwaysScrollableScrollPhysics ? AlwaysScrollableScrollPhysics(parent: scrollPhysics) : scrollPhysics,
            padding: widget.padding ?? const EdgeInsets.only(left: 15, right: 15, bottom: 20),
            itemCount: data.length,
            itemBuilder: (context, index) => widget.builder(context, data[index]),
          );

    Widget child = widget.refreshIndicator ? _wrapWithRefresher(list, scrollPhysics) : list;
    if (widget.scrollbar) child = _wrapWithScrollbar(child);

    return child;
  }

  Widget resolveFutureBuilder() => FutureBuilder<List<T>>(
        future: _future,
        builder: (context, snapshot) {
          switch (snapshot.connectionState) {
            case ConnectionState.none:
              if (hasInitState) return widget.init!.call(context, update);
              if (wantKeepAlive) return buildList(widget.data!);
              return widget.loading;
            case ConnectionState.waiting:
            case ConnectionState.active:
              return widget.loading;
            case ConnectionState.done:
              if (snapshot.hasError) {
                if (hasInitState) return widget.init!.call(context, update);
                return ErrorViewWidget(snapshot.error ?? "Неизвестная ошибка", stackTrace: snapshot.stackTrace ?? StackTrace.current, repeatTry: repeat);
              }
              if (snapshot.hasData) return buildList(snapshot.data!);
              return widget.loading;
          }
        },
      );

  @override
  Widget build(BuildContext context) => resolveFutureBuilder();
}
