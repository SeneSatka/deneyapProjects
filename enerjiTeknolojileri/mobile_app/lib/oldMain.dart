// import 'package:flutter/material.dart';
// import 'package:get/get.dart';
// import 'package:mobile_app/controllers/main_controller.dart';
// import 'package:mobile_app/screens/ikinci_ekran.dart';

// void main() {
//   runApp(const MyApp());
// }

// class MyApp extends StatelessWidget {
//   const MyApp({super.key});

//   @override
//   Widget build(BuildContext context) {
//     return GetMaterialApp(
//       title: 'Flutter Demo',
//       theme: ThemeData(
//         colorScheme: ColorScheme.fromSeed(seedColor: Colors.deepPurple),
//         useMaterial3: true,
//       ),
//       home: const MyHomePage(title: 'Flutter Demo Home Page'),
//     );
//   }
// }

// class MyHomePage extends StatefulWidget {
//   const MyHomePage({super.key, required this.title});
//   final String title;

//   @override
//   State<MyHomePage> createState() => _MyHomePageState();
// }

// class _MyHomePageState extends State<MyHomePage> {
//   final _mainController = Get.put(MainController());
//   @override
//   Widget build(BuildContext context) {
//     //

//     return Scaffold(
//       appBar: AppBar(
//         backgroundColor: Theme.of(context).colorScheme.inversePrimary,
//         title: Text(widget.title),
//       ),
//       body: Center(
//         child: Column(
//           //

//           //

//           mainAxisAlignment: MainAxisAlignment.center,
//           children: <Widget>[
//             const Text(
//               'You have pushed the button this many times:',
//             ),
//             Obx(
//               () => Text(
//                 _mainController.counter.value.toString(),
//                 style: Theme.of(context).textTheme.headlineMedium,
//               ),
//             ),
//             ElevatedButton(
//                 onPressed: () {
//                   Get.to(ikinciEkran(), transition: Transition.fadeIn);
//                   Get.snackbar("Title", "MEsajın varr",
//                       snackPosition: SnackPosition.BOTTOM);
//                 },
//                 child: Text("İkinci ekrana git"))
//           ],
//         ),
//       ),
//       floatingActionButton: FloatingActionButton(
//         onPressed: () => _mainController.incrementCounter(),
//         tooltip: 'Increment',
//         child: const Icon(Icons.add),
//       ),
//     );
//   }
// }
