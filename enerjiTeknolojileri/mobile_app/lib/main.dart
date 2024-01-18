import 'package:flutter/material.dart';
import 'package:get/get.dart';
import 'package:mobile_app/screens/blueToothConnection.dart';
import 'package:mobile_app/screens/home.dart';
import 'package:mobile_app/screens/wifiControlScreen.dart';
import 'package:mobile_app/utils/notification_helper.dart';

void main() async {
  WidgetsFlutterBinding.ensureInitialized();
  await NotificationHelper.initialize();
  runApp(const App());
}

class App extends StatelessWidget {
  const App({super.key});
  @override
  Widget build(BuildContext context) {
    return GetMaterialApp(
      debugShowCheckedModeBanner: false,
      title: 'SeneSatka(Enes AKTAS)',
      theme: ThemeData(
        brightness: Brightness.light,
        colorScheme: ColorScheme.fromSeed(seedColor: Colors.blueAccent),
        useMaterial3: true,
      ),
      home: const Home(),
      getPages: [
        GetPage(name: "/connection", page: () => const Home()),
        GetPage(
          name: "/blueToothConnection",
          page: () => const BlueToothConnection(),
          transition: Transition.fadeIn,
        ),
        GetPage(
          name: "/wiFiControlScreen",
          page: () => const WiFiControlScreen(),
          transition: Transition.fadeIn,
        )
      ],
    );
  }
}
