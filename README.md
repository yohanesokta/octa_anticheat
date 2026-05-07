## OCTA_ANTICHEAT

Proyek ini dikembangkan secara langsung dan biasanya aku live [instagram](https://instagram.com/yohanesoktanio) untuk coding ini, sehingga mencerminkan proses eksplorasi dan implementasi secara real-time. Pendekatan yang digunakan menyesuaikan dengan sistem display server yang berjalan. Untuk lingkungan berbasis X11, interaksi terhadap window dilakukan menggunakan `xdotool`, sedangkan pada Wayland khususnya di KDE Plasma (KWin), digunakan `kdotool` sebagai alternatif yang kompatibel.

Di sisi Windows, implementasi memanfaatkan Win32 API untuk mengakses dan memantau window secara langsung dengan kontrol yang lebih rendah terhadap sistem. Sementara itu, untuk macOS, pengujian belum dapat dilakukan karena keterbatasan perangkat, sehingga belum ada implementasi spesifik yang divalidasi pada platform tersebut.

Selain pendekatan berbasis tools tersebut, telah dikembangkan juga versi utama menggunakan bahasa Go yang langsung berinteraksi dengan API bawaan sistem operasi. Pendekatan ini diharapkan memberikan performa yang lebih optimal dan stabil, sehingga evaluasi terhadap kinerjanya menjadi hal yang penting untuk pengembangan selanjutnya.


# DBUS Notification ( Linux )

Pada Linux, untuk mengirim notifikasi ke desktop, kita bisa menggunakan DBUS.

```c
// Using DBUS to send desktop notifications in Linux
// sudo apt install libdbus-1-dev ( Ubuntu/Debian )
// sudo dnf install dbus-devel ( Fedora )
// sudo pacman -S dbus ( Arch Linux )

#include <dbus/dbus.h>
#include <stdio.h>
#include <stdlib.h>
...


```
#### cara build:

```bash
gcc --static dbus-notify.c $(pkg-config --cflags --libs dbus-1) -lsystemd -o dbus-notify
```
