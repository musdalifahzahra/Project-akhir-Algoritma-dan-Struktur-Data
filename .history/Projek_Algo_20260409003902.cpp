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

peminjamanBuku peminjaman[100];

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
    // baca data buku dari data_buku.txt
    FILE *fp_data_buku = fopen("data_buku.txt", "r");
    if (!fp_data_buku)
    {
        cout << "Belum ada buku yang dapat dipinjam!";
        return;
    }

    // n = jumlah data yang tersimpan di buku[]
    int n = 0;
    while (fscanf(fp_data_buku,
                  "%[^|]| %[^|]| %d %d %d %d\n",
                  buku[n].id_buku, buku[n].judul_buku,
                  &buku[n].stok_buku, &buku[n].tersedia,
                  &buku[n].terpinjam, &buku[n].total_peminjaman) != EOF)
    {
        n++;
    };
    fclose(fp_data_buku);
    // end baca data buku dari data_buku.txt

    // input data peminjaman
    FILE *fp_data_peminjaman = fopen("data_peminjaman.txt", "a");
    if (!fp_data_peminjaman)
    {
        cout << "Belum ada data peminjaman buku";
        return;
    }

    cout << "===== PEMINJAMAN BUKU =====" << endl;
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

    // menulis data peminjam ke file data_peminjaman.txt
    fprintf(fp_data_peminjaman,
            "%s| %s| %s|\n",
            peminjaman[0].id_peminjam,
            peminjaman[0].nama_peminjam,
            peminjaman[0].id_buku);

    cout << "Data peminjaman berhasil disimpan!" << endl;
    fclose(fp_data_peminjaman);
    // end input data peminjaman

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
        return;
    }
    else if (buku[s].tersedia == 0)
    {
        cout << "Maaf, stok buku yang anda cari lagi dipinjam smua" << endl; // bikinin kat kata yg indah
    }
    else
    {
        buku[s].tersedia--;
        buku[s].terpinjam++;
        buku[s].total_peminjaman++;

        // memperbarui data stok buku di data_buku.txt
        fp_data_buku = fopen("data_buku.txt", "w");
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

