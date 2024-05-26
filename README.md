# Sistem Pemantauan Suhu, Kelambaban, dan Jarak dengan ESP32

Proyek ini menggunakan mikrokontroler ESP32 untuk memantau kondisi lingkungan seperti suhu, kelembaban, dan tinggi tanaman. Data yang dikumpulkan dari sensor dikirim ke database Supabase melalui permintaan HTTPS. Sensor yang digunakan adalah:
- DHT11 untuk suhu dan kelembaban
- Sensor ultrasonik untuk mengukur tinggi tanaman

## Komponen
- Mikrokontroler ESP32
- Sensor suhu dan kelembaban DHT11
- Sensor ultrasonik (HC-SR04)
- Kabel jumper
- Breadboard (opsional)

## Pustaka
Proyek ini memerlukan pustaka Arduino berikut:
- `DHT`: Untuk interfacing dengan sensor DHT11.
- `WiFi`: Untuk koneksi ke jaringan WiFi.
- `WiFiClientSecure`: Untuk membuat permintaan HTTPS yang aman.
- `HTTPClient`: Untuk menangani permintaan HTTP.
- `NewPing`: Untuk interfacing dengan sensor ultrasonik.

## Diagram Sirkuit
1. **Sensor DHT11**:
   - VCC ke 3.3V
   - GND ke GND
   - Data ke GPIO 18

2. **Sensor Ultrasonik**:
   - VCC ke 5V
   - GND ke GND
   - TRIG ke GPIO 26
   - ECHO ke GPIO 25

## Instruksi Setup

1. **Install Pustaka Arduino**:
   - Buka Arduino IDE.
   - Pergi ke `Sketch` -> `Include Library` -> `Manage Libraries`.
   - Install pustaka berikut:
     - `DHT sensor library`
     - `WiFi`
     - `WiFiClientSecure`
     - `HTTPClient`
     - `NewPing`

2. **Konfigurasi WiFi**:
   Ganti variabel `ssid` dan `password` dengan kredensial jaringan WiFi Anda.

   ```cpp
   const char* ssid = "your_SSID";
   const char* password = "your_PASSWORD";

3. **Konfigurasi Supabase**:
    Ganti API_URL dan API_KEY dengan URL proyek Supabase dan    kunci API Anda.

   ```cpp
    String API_URL = "https://your_supabase_project_url";
    String API_KEY = "your_supabase_api_key";
    String TableName = "datasensor";


4. **Unggah Kode**:
    Sambungkan ESP32 ke komputer Anda, pilih board dan port yang sesuai di Arduino IDE, lalu unggah kode.

4. **Monitor Output Serial**:
    Buka Serial Monitor di Arduino IDE untuk memeriksa status koneksi WiFi dan data yang dikirim ke Supabase.


## Permintaan HTTP POST

Data sensor dikirim sebagai objek JSON dalam body permintaan POST.

```cpp
int httpCode = https.POST("{\"temperature\":" + String(temperature)+ ",\"humidity\":"+ String(humidity) + ",\"distance\":"+ String(distance) + ",\"plantHeight\":"+ String(plantHeight) +  "}" );
