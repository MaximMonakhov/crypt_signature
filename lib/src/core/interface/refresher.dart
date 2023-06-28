import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart' as material;
import 'package:pull_to_refresh/pull_to_refresh.dart';

class Refresher extends material.StatelessWidget {
  final Widget child;
  final VoidCallback? onRefresh;
  final VoidCallback? onLoadMore;
  final RefreshController controller;
  final bool scrollable;
  final bool showFooter;

  const Refresher({
    required this.child,
    required this.controller,
    super.key,
    this.onRefresh,
    this.onLoadMore,
    this.showFooter = false,
    this.scrollable = false,
  });

  @override
  material.Widget build(material.BuildContext context) {
    Widget widget = SmartRefresher(
      controller: controller,
      header: const RefresherHeader(),
      footer: const RefresherFooter(),
      enablePullUp: showFooter,
      onLoading: () {
        if (onLoadMore != null) {
          onLoadMore!();
          controller.loadComplete();
        }
      },
      onRefresh: () {
        if (onRefresh != null) {
          onRefresh!();
          controller.refreshToIdle();
        }
      },
      physics: const BouncingScrollPhysics(),
      child: !scrollable
          ? child
          : SingleChildScrollView(
              physics: const NeverScrollableScrollPhysics(),
              child: child,
            ),
    );

    return scrollable ? widget : widget;
  }
}

class RefresherHeader extends RefreshIndicator {
  const RefresherHeader({super.key});

  @override
  State createState() => _RefresherHeaderState();
}

class _RefresherHeaderState extends RefreshIndicatorState<RefresherHeader> {
  Widget _buildText(mode) => Text(
        mode == RefreshStatus.canRefresh
            ? "Отпустите, чтобы обновить"
            : mode == RefreshStatus.idle
                ? "Потяните вниз, чтобы обновить"
                : "",
        style: TextStyle(color: material.Theme.of(context).primaryColor),
      );

  Widget _buildIcon(mode) {
    Widget? icon = mode == RefreshStatus.canRefresh
        ? Icon(material.Icons.refresh_rounded, color: material.Theme.of(context).primaryColor, size: 20)
        : mode == RefreshStatus.idle
            ? Icon(material.Icons.arrow_downward_rounded, color: material.Theme.of(context).primaryColor, size: 20)
            : null;
    return icon ?? Container();
  }

  @override
  Widget buildContent(BuildContext context, RefreshStatus? mode) {
    Widget textWidget = _buildText(mode);
    Widget iconWidget = _buildIcon(mode);

    List<Widget> children = <Widget>[iconWidget, const Padding(padding: EdgeInsets.symmetric(horizontal: 5.0)), textWidget];

    final Widget container = Wrap(
      crossAxisAlignment: WrapCrossAlignment.center,
      alignment: WrapAlignment.center,
      children: children,
    );

    return SizedBox(
      height: 60,
      child: Center(child: container),
    );
  }
}

class RefresherFooter extends LoadIndicator {
  const RefresherFooter({super.key});

  @override
  double get height => 0;

  @override
  State createState() => _RefresherFooterState();
}

class _RefresherFooterState extends LoadIndicatorState<RefresherFooter> {
  Widget _buildText(mode) => Text(mode == LoadStatus.canLoading ? "Отпустите, чтобы показать ещё" : "");

  Widget _buildIcon(mode) {
    Widget? icon = mode == LoadStatus.canLoading
        ? Icon(material.Icons.arrow_downward_rounded, color: material.Theme.of(context).primaryColor.withOpacity(0.45))
        : mode == LoadStatus.idle
            ? Icon(material.Icons.refresh_rounded, color: material.Theme.of(context).primaryColor.withOpacity(0.45))
            : null;
    return icon ?? Container();
  }

  @override
  Widget buildContent(BuildContext context, LoadStatus? mode) {
    Widget textWidget = _buildText(mode);
    Widget iconWidget = _buildIcon(mode);

    List<Widget> children = <Widget>[iconWidget, const Padding(padding: EdgeInsets.symmetric(horizontal: 5.0)), textWidget];

    final Widget container = Wrap(
      crossAxisAlignment: WrapCrossAlignment.center,
      alignment: WrapAlignment.center,
      children: children,
    );

    return SizedBox(
      height: 60,
      child: Center(child: container),
    );
  }
}
