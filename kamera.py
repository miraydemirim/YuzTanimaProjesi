import face_recognition
import cv2
import sys
import serial
import time

# Arduino bağlantısını başlat
try:
    arduino = serial.Serial('COM13', 9600)  # Arduino portunu buraya yaz
    time.sleep(2)
    print("🔌 Arduino bağlantısı kuruldu.")
except Exception as e:
    print("❌ Arduino bağlantı hatası:", e)
    sys.exit()

# Görseli oku
image_path = r"images/referans.jpg"
bgr_image = cv2.imread(image_path)

if bgr_image is None:
    print("❌ Görsel bulunamadı.")
    sys.exit()

rgb_image = cv2.cvtColor(bgr_image, cv2.COLOR_BGR2RGB)
face_locations = face_recognition.face_locations(rgb_image)

if len(face_locations) == 0:
    print("❌ Görselde yüz bulunamadı.")
    sys.exit()

known_encoding = face_recognition.face_encodings(rgb_image, face_locations)[0]

# Kamera başlat
video_capture = cv2.VideoCapture(0)
if not video_capture.isOpened():
    print("❌ Kamera açılamadı.")
    sys.exit()

print("🎥 Kamera açık. Tanıma için bakın.")

while True:
    ret, frame = video_capture.read()
    if not ret:
        print("❌ Görüntü alınamadı.")
        break

    rgb_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
    face_locations = face_recognition.face_locations(rgb_frame)
    face_encodings = face_recognition.face_encodings(rgb_frame, face_locations)

    for (top, right, bottom, left), face_encoding in zip(face_locations, face_encodings):
        matches = face_recognition.compare_faces([known_encoding], face_encoding)

        if matches[0]:
            label = "TANINDI"
            color = (0, 255, 0)
        else:
            label = "TANINMADI"
            color = (0, 0, 255)
            arduino.write(b'H')  # ❗ Sadece tanınmayan kişi için Arduino'ya sinyal gönder

        # Dikdörtgen ve etiket
        cv2.rectangle(frame, (left, top), (right, bottom), color, 2)
        cv2.putText(frame, label, (left, top - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.8, color, 2)

    cv2.imshow('Kamera', frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

video_capture.release()
cv2.destroyAllWindows()
arduino.close()
