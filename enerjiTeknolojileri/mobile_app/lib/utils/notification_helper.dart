import 'package:flutter_local_notifications/flutter_local_notifications.dart';

class NotificationHelper {
  static final _notifications = FlutterLocalNotificationsPlugin();
  static Future initialize() async {
    const androidInitialize =
        AndroidInitializationSettings("mipmap/smart_home");
    const initializationsSettings =
        InitializationSettings(android: androidInitialize);
    await _notifications.initialize(initializationsSettings);
  }

  static Future _notificationDetails() async => const NotificationDetails(
      android: AndroidNotificationDetails("Senka Akıllı Ev", "Senka Akıllı Ev",
          importance: Importance.max));
  static Future showNotification(
          {int id = 0,
          required String title,
          required String body,
          required String payload}) async =>
      _notifications.show(id, title, body, await _notificationDetails(),
          payload: payload);
}
