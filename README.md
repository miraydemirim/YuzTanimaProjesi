# 💻 Yüz Tanıma ve Arduino Kontrollü Uyarı Sistemi

## 📌 Proje Hakkında
Bu projede, bir kişinin yüzü tanındığında sistem sessiz kalır.
Tanınmayan biri algılandığında, Arduino üzerinden sesli (buzzer) ve görsel (röle-LED) uyarı verilir.
Kamera görüntüsü üzerinde tanınan yüzler **yeşil**, tanınmayanlar **kırmızı çerçeve** ile gösterilir.

## ⚙️ Kullanılan Teknolojiler
- Python 3.10.11
- OpenCV
- face_recognition
- PySerial
- Arduino (C++)
- Seri port haberleşmesi

## 📁 Klasör Yapısı
YuzTanimaProjesi/
├── kamera.py  
├── main.py  
├── referans_yuz/              ← Kullanıcının kendi yüz fotoğrafını ekleyeceği klasör  
│   └── referans.jpg           ← Tanınacak kişi bu dosyayla eşleştirilir  
├── yuztanima_ino/             ← Arduino kodları burada  
├── yuz_ortami/                ← Sanal ortam (ignore ediliyor)  
├── README.md  
└── .gitignore  

## ⚙️ Kurulum
1. Sanal ortam oluştur:  
    python -m venv yuz_ortami

2. Sanal ortamı aktif et (Windows):  
    .\yuz_ortami\Scripts\activate

3. Gerekli kütüphaneleri kur:  
    pip install -r requirements.txt

Eğer requirements.txt yoksa elle yükleyebilirsin:  
    pip install face_recognition opencv-python pyserial

## ▶️ Kullanım
1. `referans_yuz/referans.jpg` dosyasına tanınacak kişinin yüz fotoğrafını yerleştir.
2. Ardından terminalde çalıştır:  
    python kamera.py

- Kamera açılır.  
- Tanınan kişi → Yeşil çerçeve  
- Tanınmayan kişi → Kırmızı çerçeve + Arduino uyarısı (buzzer, röle)  

## 💡 Notlar
- Arduino COM13 portuna bağlı (gerekirse güncelleyin).
- Yüz tanıma için kullanılacak referans fotoğrafı `referans_yuz/referans.jpg` dosyası olmalıdır.
- Arduino kodu `yuztanima_ino` klasöründe bulunur.
