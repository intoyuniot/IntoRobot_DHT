#include <IntoRobot_DHT.h>

//传感器通讯引脚
#define DHTPIN D2

//选择传感器类型
//#define DHTTYPE DHT11		// DHT 11
#define DHTTYPE DHT22		// DHT 22 (AM2302)
//#define DHTTYPE DHT21		// DHT 21 (AM2301)

#define HUMITURE_DATA_TEMPERATURE    "channel/humiture_0/data/temperature"   //空气温度
#define HUMITURE_DATA_HUMIDITY       "channel/humiture_0/data/humidity"      //空气湿度

IntoRobot_DHT dht(DHTPIN, DHTTYPE);

void setup()
{
    Serial.begin(115200);
    Serial.println("DHTxx test!");
    dht.begin();
}

void loop()
{
    float h = dht.getHumidity();     //获取湿度
    float t = dht.getTempCelcius();  //获取摄氏温度
    float f = dht.getTempFarenheit();//获取华氏温度

    // 将温湿度数据上送到云平台
    IntoRobot.publish(HUMITURE_DATA_TEMPERATURE,t);
    IntoRobot.publish(HUMITURE_DATA_HUMIDITY,h);

    //检查是否获取数据失败(失败重新开始)
    if (isnan(h) || isnan(t) || isnan(f))
    {
        Serial.println("Failed to read from DHT sensor!");
    }

    float hi = dht.getHeatIndex();  //获取热指数
    float dp = dht.getDewPoint();   //获取露点
    float k = dht.getTempKelvin();  //获取绝对温度

    Serial.print("Humid: ");
    Serial.print(h);
    Serial.print("% - ");
    Serial.print("Temp: ");
    Serial.print(t);
    Serial.print("*C ");
    Serial.print(f);
    Serial.print("*F ");
    Serial.print(k);
    Serial.print("*K - ");
    Serial.print("DewP: ");
    Serial.print(dp);
    Serial.print("*C - ");
    Serial.print("HeatI: ");
    Serial.print(hi);
    Serial.println("*C");
    Serial.println(Time.timeStr());

    delay(1000);
}
