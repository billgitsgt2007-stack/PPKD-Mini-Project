#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <thread>
#include <chrono>

using namespace std;

const int JumlahMenu = 6;
const int TambahIce = 3000;

struct Menu {
    string nama[JumlahMenu] = {
        "Americano",
        "Arabika",
        "Cafe Latte",
        "Matcha latte",
        "Butterscotch",
        "Kopi Susu Gula Aren"
    };

    const int harga[JumlahMenu] = {
        17000, 20000, 25000, 30000, 28000, 26000
    };

    bool ketersediaan[JumlahMenu] = {
        true, true, true, false, true, true
    };
} menu;

struct Pilihan {
    string namaItem;
    int namaID;
    int jumlah;
    int jumlahDenganEs;
    int totalHarga() const {
        int hargaDasar = menu.harga[namaID - 1];
        return (jumlah * hargaDasar) + (jumlahDenganEs * TambahIce);
    }
};

vector<Pilihan> daftarPesanan;

void tampilMenu(Menu menu) {
    cout << "========================================================================\n";
    cout << left  << setw(26) << "Menu Minuman"
         << right << setw(12) << "Hot"
         << right << setw(14) << "Ice"
         << right << setw(18) << "Ketersediaan" << endl;
    cout << "========================================================================\n";

    for (int i = 0; i < JumlahMenu; i++) {
        string status = menu.ketersediaan[i] ? "Tersedia" : "Tidak Tersedia";

        cout << left  << setw(3)  << to_string(i + 1) + "."
             << left  << setw(23) << menu.nama[i]
             << right << setw(7)  << "Rp." << setw(7) << menu.harga[i]
             << right << setw(6)  << "Rp." << setw(7) << menu.harga[i] + TambahIce
             << "   " << left  << setw(18) << status
             << endl;
    }
}

void pilihanMenu(Menu menu, int nomorMenu, vector<Pilihan>& daftarPesanan) {
    int jumlah;
    int jumlahDenganEs;

    cout << "Masukkan jumlah pesanan: ";
    cin >> jumlah;

    while (true) {
        cout << "Berapa jumlah yang ingin ditambahkan es (0 jika tidak): ";
        cin >> jumlahDenganEs;
        if (jumlahDenganEs >= 0 && jumlahDenganEs <= jumlah) {
            break;
        }
        cout << "Jumlah es tidak boleh melebihi total pesanan (" << jumlah << "). Silakan coba lagi.\n";
    }

    Pilihan pesananBaru;
    pesananBaru.namaItem = menu.nama[nomorMenu - 1];
    pesananBaru.namaID = nomorMenu;
    pesananBaru.jumlah = jumlah;
    pesananBaru.jumlahDenganEs = jumlahDenganEs;

    daftarPesanan.push_back(pesananBaru);
}
void Pembayaran(int totalbayar){
    string qr[] = {
       "11111110101111111",
        "10000010001000001",
        "10111010101011101",
        "10111010001011101",
        "10111010001011101",
        "10000010001000001",
        "11111110101111111",
        "00000000000000000",
        "00011000100001000",
        "00000000011001000",
        "11111110100001111",
        "10000010111000011",
        "10111010111001010",
        "10111010110011111",
        "10111010001100111",
        "10000010110110010",
        "11111110010011100"
    };
     cout << "\n===================================" << endl;
    cout << "          PEMBAYARAN QR" << endl;
    cout << "===================================" << endl;
    cout << "Total Bayar : Rp. " << totalbayar << endl << endl;

    for (string baris : qr) {
        cout << baris << endl;
    }

    cout << "\nSilakan lakukan pembayaran..." << endl;
    for (int i = 10; i >= 1; i--) {
        cout << "\rPembayaran sedang diproses... "
             << i << " detik   ";
        cout.flush();

        this_thread::sleep_for(chrono::seconds(1));
    }
    cout << "\n\n===================================" << endl;
    cout << "       PEMBAYARAN BERHASIL!" << endl;
    cout << "===================================" << endl;
    cout << "Total Pembayaran : Rp. " << totalbayar << endl;
    cout << "Status           : LUNAS" << endl;
    cout << "===================================" << endl;
    cout << "Terima kasih telah beli di L7 Coffee, Stand by untuk pesanan kamu yaa"<<endl;
    cout << "Kami bakal panggil kamu sesuai nomor antrian yang kamu dapatkan saat ini, jangan kemana-mana yaa :)"<<endl;
}

int main() {
    string namaPemesan;

    cout << "===================================" << endl;
    cout << "Hallo Selamat Datang di L7 Coffee" << endl;
    cout << "Masukkan Nama Kamu: ";
    cin >> namaPemesan;

    cout << "===================================" << endl;

    tampilMenu(menu);

    while (true) {
        cout << "\nMasukkan nomor menu yang ingin dipesan (0 untuk selesai): ";
        int nomorMenu;
        cin >> nomorMenu;

        if (nomorMenu == 0) {
            break;
        } 
        else if (nomorMenu < 1 || nomorMenu > JumlahMenu) {
            cout << "Menu tidak valid. Silakan pilih nomor menu antara 1 hingga " << JumlahMenu << endl;
        } 
        else if (!menu.ketersediaan[nomorMenu - 1]) {
            cout << "Maaf, menu " << menu.nama[nomorMenu - 1] << " tidak tersedia." << endl;
        } 
        else {
            pilihanMenu(menu, nomorMenu, daftarPesanan);
            cout << "Berhasil menambahkan pesanan!\n";
        }
    }

    int grandTotal = 0;
    cout << "\n===================================" << endl;
    cout << "Ringkasan Pesanan " << namaPemesan << ":" << endl;
    for (size_t i = 0; i < daftarPesanan.size(); i++) {
        int subtotal = daftarPesanan[i].totalHarga();
        grandTotal += subtotal;
        
        cout << i + 1 << ". " << daftarPesanan[i].namaItem 
             << " | Qty: " << daftarPesanan[i].jumlah 
             << " (Es: " << daftarPesanan[i].jumlahDenganEs << ") | Total Harga: Rp. " 
             << subtotal << endl;
    }
    cout << "===================================" << endl;
    cout << "TOTAL BAYAR: Rp. " << grandTotal << endl;

    Pembayaran(grandTotal);

    return 0;
}