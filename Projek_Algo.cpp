#include <iostream>
#include <iomanip>
using namespace std;

struct mus
{
    ////musdal
    ////
    ////
    ////
    /// hhhhhbsaahhhhhh
};

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

peminjamanBuku v_peminjamanBuku[100];

void menambahkan_data_buku();
void melihat_daftar_buku();
void peminjaman_buku();
void pengembalian_buku();

int main()
{
    int pilihan;
    cout << "=========================\n";
    cout << "    Lentera Digital\n";
    cout << "==========================\n";
}

void peminjaman_buku()
{
    // buka file
    FILE *fp_data_peminjaman = fopen("data_peminjaman.txt", "a");
    if (!fp_data_peminjaman)
    {
        cout << "Belum ada data peminjaman buku";
        return;
    }

    cout << "===== PEMINJAMAN BUKU =====" << endl;
    cout << "ID Anggota  : ";
    cin >> v_peminjamanBuku[0].id_peminjam;
    cout << endl
         << "Nama Anggota:";
    cin.ignore();
    cin.getline(v_peminjamanBuku[0].nama_peminjam, 20);
    cout << endl
         << "ID Buku     : ";
    cin >> v_peminjamanBuku[0].id_buku;
    cout << endl;

    // menulis data peminjam ke file data_peminjaman.txt
    fprintf(fp_data_peminjaman,
            "%s| %s| %s|",
            v_peminjamanBuku[0].id_peminjam,
            v_peminjamanBuku[0].nama_peminjam,
            v_peminjamanBuku[0].id_buku);

    cout << "Data peminjaman berhasil disimpan!" << endl;
    fclose(fp_data_peminjaman);
}