import 'package:flutter/material.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:flutter_timezone_plus_example/main.dart';

void main() {
  testWidgets('Get time zone', (WidgetTester tester) async {
    // Build our app and trigger a frame.
    await tester.pumpWidget(const MyApp());
    expect(
      find.byWidgetPredicate(
        (Widget widget) =>
            widget is Text &&
            widget.data?.startsWith('Local timezone:') == true,
      ),
      findsOneWidget,
    );
  });
}
