import 'dart:async';

import 'package:flutter/foundation.dart';
import 'package:flutter/material.dart';
import 'package:flutter_timezone_plus/flutter_timezone_plus.dart';

void main() => runApp(const MyApp());

class MyApp extends StatelessWidget {
  const MyApp({Key? key}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    return const MaterialApp(
      home: HomePage(),
    );
  }
}

class HomePage extends StatefulWidget {
  const HomePage({Key? key}) : super(key: key);

  @override
  State<HomePage> createState() => _HomePageState();
}

class _HomePageState extends State<HomePage> {
  String? _timezone;
  List<String> _availableTimezones = <String>[];

  @override
  void initState() {
    _initData();
    super.initState();
  }

  Future<void> _initData() async {
    try {
      _timezone = await FlutterTimezone.getLocalTimezone();
      _timezone ??= 'Unknown';
    } catch (e) {
      if (kDebugMode) {
        print(e);
        print('Could not get the local timezone');
      }
    }
    try {
      _availableTimezones = await FlutterTimezone.getAvailableTimezones();
      _availableTimezones.sort();
    } catch (e) {
      if (kDebugMode) {
        print(e);
        print('Could not get available timezones');
      }
    }
    if (mounted) {
      setState(() {});
    }
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Local timezone app'),
      ),
      body: Column(
        children: <Widget>[
          Text('Local timezone: $_timezone\n'),
          const Text('Available timezones:'),
          Expanded(
            child: ListView.builder(
              itemCount: _availableTimezones.length,
              itemBuilder: (_, index) => Text(_availableTimezones[index]),
            ),
          )
        ],
      ),
    );
  }
}
