import 'package:flutter/material.dart';
import 'package:get/get.dart';
import 'package:mobile_app/screens/bluetooth_connection_screen.dart';
import 'package:mobile_app/screens/home.dart';
import 'package:mobile_app/screens/wifi_control_screen.dart';
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
          colorScheme: const ColorScheme.dark(
        background: Colors.black,
        primary: Colors.white,
        surface: Colors.green,
        error: Colors.red,
      )),
      home: const Home(),
      getPages: [
        GetPage(name: "/connection", page: () => const Home()),
        GetPage(
          name: "/bluetoothConnection",
          page: () => const SelectBluettothDevice(),
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
