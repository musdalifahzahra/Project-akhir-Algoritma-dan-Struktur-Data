#include <iostream>
#include <iomanip>
using namespace std;
/// perubahanpunyaku musdal duluuu
/////////// comeeennn

struct dataBuku
{
    char id_buku[10];
    char judul_buku[100];
    int stok_buku;
    int total_peminjaman;
    int tersedia;
    int terpinjam;
};
dataBuku buku[100];

struct peminjamanBuku
{
    char id_buku[10];
    char id_peminjam[10];
    char nama_peminjam[20];
};

peminjamanBuku peminjaman[100];

void simpan_data();
void menambahkan_data_buku();
void melihat_daftar_buku();
void peminjaman_buku();
void pengembalian_buku();

int main()
{
    cout << "==========================\n"; // mau pake setfill
    cout << "    Lentera Digital\n";
    cout << "==========================\n";
    cout << "1. Menambah data buku\n";
    cout << "2. Melihat daftar buku\n";
    cout << "3. Peminjaman buku\n";
    cout << "4. Pengembalian buku\n";
    cout << "5. Keluar\n";
    cout << "============================\n";
    cout << "Pilih menu (1-5): ";
    switch (pilihan)
    {
    case 1:
    {
        menambahkan_data_buku();
        break;
    }
    case 2:
    {
        melihat_daftar_buku();
        break;
    }
    case 3:
    {
        peminjaman_buku();
        break;
    }
    case 4:
    {
        pengembalian_buku();
        break;
    }
    case 5:
    {
        cout << "Terima Kasih Telah menggunakan program ini!:>\n";
    }
    }
}

FILE *fptr = fopen("data_buku.txt", "a");
dataBuku *ptr = buku;
int pilihan, jumlahData = 0;

////////simpan data
void simpan_data(dataBuku *ptr, int &jumlah)
{
    if (fptr == NULL)
    {
        cout << "Gagal membuka file!\n";
        return;
    }
    else
    {
        fprintf(fptr, "%s, %s, %d, %d, %d, %d\n",
                (ptr + jumlah - 1)->id_buku, (ptr + jumlah - 1)->judul_buku,
                (ptr + jumlah - 1)->stok_buku, (ptr + jumlah - 1)->tersedia,
                (ptr + jumlah - 1)->terpinjam, (ptr + jumlah - 1)->total_peminjaman);
        fclose(fptr);
    }
}

//////tambah data buku leeeeeeee
void menambahkan_data_buku(dataBuku *ptr, int &jumlah)
{
    cout << "=== TAMBAH DATA LUKISAN ===\n";
    cout << left << setw(15) << "ID Buku " << ": ";
    cin.getline((ptr + jumlah)->id_buku, 10);
    cout << left << setw(15) << "Judul Buku" << ": ";
    cin.getline((ptr + jumlah)->judul_buku, 100);
    cout << left << setw(15) << "Stok Buku" << ": ";
    cin >> ((ptr + jumlah)->stok_buku);
    cout << left << setw(15) << "Total yang tersedia" << ": ";
    cin >> ((ptr + jumlah)->tersedia);
    cout << left << setw(15) << "Total yang terpinjam" << ": ";
    cin >> ((ptr + jumlah)->terpinjam);
    jumlah++;
    simpan_data(ptr, jumlah);
    cout << "Data berhasil ditambahkan!\n";
    system("pause");
    system("cls");
}

void melihat_daftar_buku(dataBuku *ptr, int &jumlah)
{
    fptr = fopen("data_buku.txt", "r");
    if (fptr == NULL)
    {
        cout << "Gagal membuka file!\n";
        system("pause");
        system("cls");
        return;
    }
    jumlahData = 0;
    while (fscanf(fptr, "%s, %s, %d, %d, %d, %d\n",
                  buku[jumlahData].id_buku, buku[jumlahData].judul_buku,
                  buku[jumlahData].stok_buku, buku[jumlahData].total_peminjaman, buku[jumlahData].tersedia,
                  buku[jumlahData].terpinjam) != EOF)
    {
        jumlahData++;
    }
    fclose(fptr);
    int metode;
    cout << "=== TAMPILKAN DATA ===\n";
}

// void peminjaman_buku(){
// }

// musdal
int n; // jumlah data yang tersimpan di buku[]
void membaca_data_buku_txt()
{
    FILE *fp_data_buku = fopen("data_buku.txt", "r");
    if (!fp_data_buku)
    {
        cout << "Belum ada data buku";
        return;
    }

    // n = jumlah data yang tersimpan di buku[]
    n = 0;
    while (fscanf(fp_data_buku,
                  "%[^|]| %[^|]| %d %d %d %d\n",
                  buku[n].id_buku, buku[n].judul_buku,
                  &buku[n].stok_buku, &buku[n].tersedia,
                  &buku[n].terpinjam, &buku[n].total_peminjaman) != EOF)
    {
        n++;
    };
    fclose(fp_data_buku);
}

void input_peminjaman_pengembalian()
{
    cout << "ID Anggota  : ";
    cin >> peminjaman[0].id_peminjam;
    cout << endl
         << "Nama Anggota:";
    cin.ignore();
    cin.getline(peminjaman[0].nama_peminjam, 20);
    cout << endl
         << "ID Buku     : ";
    cin >> peminjaman[0].id_buku;
    cout << endl;
}

void peminjaman_buku()
{
    // membaca data buku dari data_buku.txt
    membaca_data_buku_txt();

    // input data peminjaman
    FILE *fp_data_peminjaman = fopen("data_peminjaman.txt", "a");
    if (!fp_data_peminjaman)
    {
        cout << "Belum ada data peminjaman buku";
        return;
    }

    cout << "===== PEMINJAMAN BUKU =====" << endl;
    input_peminjaman_pengembalian();

    // cari id_buku yang ingin dipinjam tersimpan di index mana
    bool found = false;
    int s = 0;
    string temp_id_buku = peminjaman[0].id_buku;
    string temp_benar;
    while (s < n && found == false)
    {
        temp_benar = buku[s].id_buku;
        if (temp_benar == temp_id_buku)
        {
            found = true;
        }
        else
        {
            s++; // s = index yg isinya adalah id_buku yg akan dimpinjam
        }
    }
    // end cari id_buku yang ingin dipinjam tersimpan di index mana

    if (!found)
    {
        cout << endl
             << "Buku yang anda cari tidak tersedia" << endl;
        fclose(fp_data_peminjaman);
        return;
    }
    else if (buku[s].tersedia == 0)
    {
        cout << "Maaf, stok buku yang anda cari lagi dipinjam smua" << endl; // bikinin kat kata yg indah
        fclose(fp_data_peminjaman);
    }
    else
    {
        // menulis data peminjam ke file data_peminjaman.txt
        fprintf(fp_data_peminjaman,
                "%s| %s| %s|\n",
                peminjaman[0].id_peminjam,
                peminjaman[0].nama_peminjam,
                peminjaman[0].id_buku);

        cout << "Data peminjaman berhasil disimpan!" << endl;
        fclose(fp_data_peminjaman);
        // end menulis data peminjam ke file data_peminjaman.txt

        buku[s].tersedia--;
        buku[s].terpinjam++;
        buku[s].total_peminjaman++;

        // memperbarui data stok buku di data_buku.txt
        FILE *fp_data_buku = fopen("data_buku.txt", "w");
        if (!fp_data_buku)
        {
            cout << "Belum ada data buku yang tersimpan";
            return;
        }

        for (int i = 0; i < n; i++)
        {
            fprintf(fp_data_buku,
                    "%s| %s| %d %d %d %d\n",
                    buku[i].id_buku, buku[i].judul_buku,
                    buku[i].stok_buku, buku[i].tersedia,
                    buku[i].terpinjam, buku[i].total_peminjaman);
        }
        fclose(fp_data_buku);
        // end memperbarui data stok buku di data_buku.txt
    }
}
// end void peminjaman buku

void pengembalian_buku()
{
    // membaca + menyimpan data buku dari file data_buku.txt
    membaca_data_buku_txt();

    // input data pengembalian buku
    cout << "===== PENGEMBALIAN BUKU =====" << endl;
    input_peminjaman_pengembalian();

    //cari id_buku && id_peminjam berada di indeks mana 
    //apakah ada di 


}

// backup void pengembalian_buku()
//  void pengembalian_buku()
//  {
//      // membaca data buku dari data_buku.txt
//      membaca_data_buku_txt();

//     // input data peminjaman
//     FILE *fp_data_peminjaman = fopen("data_peminjaman.txt", "a");
//     if (!fp_data_peminjaman)
//     {
//         cout << "Belum ada data peminjaman buku";
//         return;
//     }

//     cout << "===== PENGEMBALIAN BUKU =====" << endl;
//     input_peminjaman_pengembalian();

//     // cari id_buku yang ingin dikembalikan tersimpan di index mana
//     bool found = false;
//     int s = 0;
//     string temp_id_buku = peminjaman[0].id_buku;
//     string temp_id_peminjam = peminjaman[0].id_peminjam;
//     string temp_benar_id_buku;
//     string temp_benar_id_peminjam;
//     while (s < n && !found)
//     {
//         temp_benar_id_buku = peminjaman[s].id_buku;
//         temp_benar_id_peminjam = peminjaman[s].id_peminjam;
//         if (temp_benar_id_buku == temp_id_buku && temp_benar_id_peminjam == temp_benar_id_peminjam)
//         {
//             found = true;
//         }
//         else
//         {
//             s++; // s = index yg isinya adalah id_buku yg akan dikembalikan
//         }
//     }
//     // end cari id_buku yang ingin dikembalikan tersimpan di index mana

//     if (!found)
//     {
//         cout << endl
//              << "Tidak ada data peminjaman tersebut" << endl;
//         fclose(fp_data_peminjaman);
//         return;
//     }
//     else
//     {
//         //////// GESER DULU DATA PEMINJAMAN YG MAU DI HAPUUUSSS// NGANTUK MW TDR DULU
//         // Geser index setelah index yang mau dihapus datanya
//         for (int i = s; i < n ; i++)
//         {
//             peminjaman[i] = peminjaman[i + 1];
//         }
//         n--; // karena menghapus 1 data, maka jumlah data yang tersimpan akan berkurag

//         // menulis ULANG  data peminjam ke file data_peminjaman.txt
//         fprintf(fp_data_peminjaman,
//                 "%s| %s| %s|\n",
//                 peminjaman[0].id_peminjam,
//                 peminjaman[0].nama_peminjam,
//                 peminjaman[0].id_buku);

//         cout << "Data peminjaman berhasil disimpan!" << endl;
//         fclose(fp_data_peminjaman);
//         // end menulis data peminjam ke file data_peminjaman.txt

//         buku[s].tersedia--;
//         buku[s].terpinjam++;
//         buku[s].total_peminjaman++;

//         // memperbarui data stok buku di data_buku.txt
//         FILE *fp_data_buku = fopen("data_buku.txt", "w");
//         if (!fp_data_buku)
//         {
//             cout << "Belum ada data buku yang tersimpan";
//             return;
//         }

//         for (int i = 0; i < n; i++)
//         {
//             fprintf(fp_data_buku,
//                     "%s| %s| %d %d %d %d\n",
//                     buku[i].id_buku, buku[i].judul_buku,
//                     buku[i].stok_buku, buku[i].tersedia,
//                     buku[i].terpinjam, buku[i].total_peminjaman);
//         }
//         fclose(fp_data_buku);
//         // end memperbarui data stok buku di data_buku.txt
//     }
// }