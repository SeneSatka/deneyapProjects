// File generated by FlutterFire CLI.
// ignore_for_file: lines_longer_than_80_chars, avoid_classes_with_only_static_members
import 'package:firebase_core/firebase_core.dart' show FirebaseOptions;
import 'package:flutter/foundation.dart'
    show defaultTargetPlatform, kIsWeb, TargetPlatform;

/// Default [FirebaseOptions] for use with your Firebase apps.
///
/// Example:
/// ```dart
/// import 'firebase_options.dart';
/// // ...
/// await Firebase.initializeApp(
///   options: DefaultFirebaseOptions.currentPlatform,
/// );
/// ```
class DefaultFirebaseOptions {
  static FirebaseOptions get currentPlatform {
    if (kIsWeb) {
      return web;
    }
    switch (defaultTargetPlatform) {
      case TargetPlatform.android:
        return android;
      case TargetPlatform.iOS:
        return ios;
      case TargetPlatform.macOS:
        return macos;
      case TargetPlatform.windows:
        throw UnsupportedError(
          'DefaultFirebaseOptions have not been configured for windows - '
          'you can reconfigure this by running the FlutterFire CLI again.',
        );
      case TargetPlatform.linux:
        throw UnsupportedError(
          'DefaultFirebaseOptions have not been configured for linux - '
          'you can reconfigure this by running the FlutterFire CLI again.',
        );
      default:
        throw UnsupportedError(
          'DefaultFirebaseOptions are not supported for this platform.',
        );
    }
  }

  static const FirebaseOptions web = FirebaseOptions(
    apiKey: 'AIzaSyB1jC8q58q79of6n8TYvkhmpUWE_zyxLgo',
    appId: '1:708103188138:web:e40d541ced3b949ea02ad3',
    messagingSenderId: '708103188138',
    projectId: 'deneyap-smart-house',
    authDomain: 'deneyap-smart-house.firebaseapp.com',
    storageBucket: 'deneyap-smart-house.appspot.com',
    measurementId: 'G-VNCFJD4R72',
  );

  static const FirebaseOptions android = FirebaseOptions(
    apiKey: 'AIzaSyCXyUnSDk9GaiVV_4xjIJGfxHYZAfz_R2g',
    appId: '1:708103188138:android:6e742e3b9655d3b1a02ad3',
    messagingSenderId: '708103188138',
    projectId: 'deneyap-smart-house',
    storageBucket: 'deneyap-smart-house.appspot.com',
  );

  static const FirebaseOptions ios = FirebaseOptions(
    apiKey: 'AIzaSyDZE3shgIQuodQLWc5R0vnpfXQg9wMlyH0',
    appId: '1:708103188138:ios:f8aab02af0d0adc3a02ad3',
    messagingSenderId: '708103188138',
    projectId: 'deneyap-smart-house',
    storageBucket: 'deneyap-smart-house.appspot.com',
    iosBundleId: 'com.example.deneyapSmartHouse',
  );

  static const FirebaseOptions macos = FirebaseOptions(
    apiKey: 'AIzaSyDZE3shgIQuodQLWc5R0vnpfXQg9wMlyH0',
    appId: '1:708103188138:ios:d2b6ae2b091df729a02ad3',
    messagingSenderId: '708103188138',
    projectId: 'deneyap-smart-house',
    storageBucket: 'deneyap-smart-house.appspot.com',
    iosBundleId: 'com.example.deneyapSmartHouse.RunnerTests',
  );
}