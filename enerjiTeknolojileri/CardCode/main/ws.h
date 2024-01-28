
using namespace websockets;

void onEventsCallback(WebsocketsEvent event, String data);
void onMessageCallback(WebsocketsMessage message);
// WebsocketsClient wsc;

class WSCC
{
public:
    WebsocketsClient wsc;
    WSCC(WebsocketsClient &ws)
    {
        wsc = ws;
    }
    void start(const char *url, PartialMessageCallback onMessageCallback)
    {
        wsc.onMessage(onMessageCallback);
        wsc.onEvent(onEventsCallback);
        wsc.connect(url);
    };
    void send(String data)
    {
        wsc.send(data);
    };
};
void onEventsCallback(WebsocketsEvent event, String data)
{
    if (event == WebsocketsEvent::ConnectionOpened)
    {
        Serial.println("Bağlantı Açıldı");
    }
    else if (event == WebsocketsEvent::ConnectionClosed)
    {
        Serial.println("Bağlantı Kapandı");
        esp_restart();
    }
    else if (event == WebsocketsEvent::GotPing)
    {
        Serial.println("Ping alındı");
    }
    else if (event == WebsocketsEvent::GotPong)
    {
        Serial.println("Pong alındı");
    }
}
