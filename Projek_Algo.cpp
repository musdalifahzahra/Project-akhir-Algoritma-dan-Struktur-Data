#include <iostream>
#include <iomanip>
using namespace std;

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

    peminjamanBuku *next;
    peminjamanBuku *prev;
};

peminjamanBuku peminjaman[100];

struct pengembalianBuku
{
    char id_buku[10];
    char id_peminjam[10];
    char nama_peminjam[20];
};
pengembalianBuku pengembalian;

void simpan_data(dataBuku *ptr, int &jumlah);
void menambahkan_data_buku(dataBuku *ptr, int &jumlah);
void melihat_daftar_buku(dataBuku *ptr, int &jumlah);
void cari_buku();
void peminjaman_buku();
void pengembalian_buku();
void riwayat_peminjaman();
void membaca_data_buku_txt();

dataBuku *ptr = buku;
int jumlahData = 0;
char pilihan;
int n; // n = jumlah data yang tersimpan di buku[]

int main()
{
    do
    {
        cout << setw(30) << setfill('=') << "" << endl; // mau pake setfill
        cout << "       Lentera Digital\n";
        cout << setw(30) << setfill('=') << "" << endl;
        cout << "1. Tambah data buku\n";
        cout << "2. Lihat daftar buku\n";
        cout << "3. Cari buku\n";
        cout << "4. Peminjaman buku\n";
        cout << "5. Pengembalian buku\n";
        cout << "6. Riwayat Peminjaman\n";
        cout << "7. Keluar\n";
        cout << setw(30) << setfill('=') << "" << endl;
        cout << "Pilih menu (1-7): ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan)
        {
        case '1':
        {
            menambahkan_data_buku(ptr, jumlahData);
            break;
        }
        case '2':
        {
            melihat_daftar_buku(ptr, jumlahData);
            break;
        }
        case '3':
        {
            cari_buku();
            break;
        }
        case '4':
        {
            peminjaman_buku();
            break;
        }
        case '5':
        {
            pengembalian_buku();
            break;
        }
        case '6':
        {
            riwayat_peminjaman();
            break;
        }
        case '7':
        {
            cout << "Terima Kasih Telah menggunakan program ini!:>\n";
            break;
        }
        default:
        {
            cout << "Pilihan tidak ada!\n\n";
        }
        }
    } while (pilihan != '7');
}

void simpan_data(dataBuku *ptr, int &jumlah)
{
    FILE *fptr = fopen("data_buku.txt", "a");
    if (fptr == NULL)
    {
        cout << "Gagal membuka file!\n";
        return;
    }
    else
    {
        fprintf(fptr, "%s| %s| %d| %d| %d| %d\n",
                (ptr + jumlah - 1)->id_buku, (ptr + jumlah - 1)->judul_buku,
                (ptr + jumlah - 1)->stok_buku, (ptr + jumlah - 1)->total_peminjaman,
                (ptr + jumlah - 1)->tersedia, (ptr + jumlah - 1)->terpinjam);
        fclose(fptr);
    }
}

void menambahkan_data_buku(dataBuku *ptr, int &jumlah)
{
    cout << "ID Buku             : ";
    cin.getline((ptr + jumlah)->id_buku, 10);

    cout << "Judul Buku maks(100): ";
    cin.getline((ptr + jumlah)->judul_buku, 100);

    cout << "Stok buku           : ";
    cin >> ((ptr + jumlah)->stok_buku);
    cin.ignore();

    (ptr + jumlah)->total_peminjaman = 0;
    (ptr + jumlah)->tersedia = (ptr + jumlah)->stok_buku;
    (ptr + jumlah)->terpinjam = 0;

    jumlah++;
    simpan_data(ptr, jumlah);
    cout << "Data berhasil ditambahkan!\n";
    system("pause");
    system("cls");
}

void melihat_daftar_buku(dataBuku *ptr, int &jumlah)
{
    cout << setfill(' ');
    FILE *fptr;
    fptr = fopen("data_buku.txt", "r");
    if (fptr == NULL)
    {
        cout << "Data masih kosong!\n";
        system("pause");
        system("cls");
        return;
    }
    jumlahData = 0;
    while (fscanf(fptr, " %[^|]| %[^|]| %d| %d| %d| %d\n",
                  buku[jumlahData].id_buku, buku[jumlahData].judul_buku,
                  &buku[jumlahData].stok_buku, &buku[jumlahData].total_peminjaman,
                  &buku[jumlahData].tersedia, &buku[jumlahData].terpinjam) == 6)
    {
        jumlahData++;
    }
    fclose(fptr);

    if (jumlahData == 0)
    {
        cout << "Data tidak dapat dibaca\n";
        system("pause");
        system("cls");
        return;
    }

    int metode;
    cout << "====== TAMPILKAN DATA ======\n";
    cout << "1. Stok terbanyak\n";  // DESC
    cout << "2. Stok tersedikit\n"; // ASC
    cout << "Pilih: ";
    cin >> metode;
    if (metode == 1 || metode == 2)
    {
        for (int i = 0; i < jumlahData - 1; i++)
        {
            for (int j = i + 1; j < jumlahData; j++)
            {
                bool tukar = false;
                if (metode == 1)
                {
                    if (buku[i].stok_buku < buku[j].stok_buku)
                    {
                        tukar = true;
                    }
                }
                else if (metode == 2)
                {
                    if (buku[i].stok_buku > buku[j].stok_buku)
                    {
                        tukar = true;
                    }
                }
                if (tukar)
                {
                    dataBuku temp = buku[i];
                    buku[i] = buku[j];
                    buku[j] = temp;
                }
            }
        }
    }
    else if (metode < 1 || metode > 2)
    {
        cout << "Pilihan tidak valid\n";
        system("pause");
        system("cls");
    }
    cout << "========= DATA BUKU ========\n"; 
    cout << left << setfill(' ') << setw(3) << "No." << " "
         << left << setfill(' ') << setw(10) << "ID_buku" << " "
         << left << setfill(' ') << setw(20) << "judul" << " "
         << left << setfill(' ') << setw(6) << "stok" << " "
         << left << setfill(' ') << setw(17) << "Total_Peminjaman" << " "
         << left << setfill(' ') << setw(8) << "Tersedia" << " "
         << left << setfill(' ') << setw(3) << "Sedang_dipinjam" << " "
         << endl;
    for (int i = 0; i < jumlahData; i++)
    {
        cout << left << setfill(' ') << setw(3) << i + 1 << " "
             << left << setfill(' ') << setw(10) << buku[i].id_buku << " "
             << left << setfill(' ') << setw(20) << buku[i].judul_buku << " "
             << left << setfill(' ') << setw(12) << buku[i].stok_buku << " "
             << left << setfill(' ') << setw(15) << buku[i].total_peminjaman << " "
             << left << setfill(' ') << setw(10) << buku[i].tersedia << " "
             << left << setfill(' ') << setw(3) << buku[i].terpinjam << " "
             << endl;

       
    }
    system("pause");
    system("cls");
}

void cari_buku()
{
    membaca_data_buku_txt();
    if (n == 0)
    {
        cout << "\nBelum ada data buku yang tersimpan\n\n";
    }
    else
    {
        string cari;
        cout << "======= CARI DATA BUKU =======" << endl
             << "Masukkan Judul dengan huruf kapital di awal setiap kata" << endl
             << "Cari Buku: ";
        getline(cin, cari);

        // Proses searching (sequential search tanpa sentinel)
        bool found = false;
        int s = 0;
        string temp_benar;
        while (s < n and found == false)
        {
            temp_benar = buku[s].judul_buku;
            if (temp_benar == cari)
            {
                found = true;
            }
            else
            {
                s++; // s = index yg isinya adalah data Buku yg di cari
            }
        }

        if (found == false)
        {
            cout << endl
                 << "Judul Buku tidak ditemukan!" << endl;
        }
        else
        {
            cout << endl
                 << "----------------------------------------------------------------------------" << endl
                 << left << setfill(' ') << setw(10) << "ID buku" << " "
                 << left << setfill(' ') << setw(15) << "judul" << " "
                 << left << setfill(' ') << setw(6) << "stok" << " "
                 << left << setfill(' ') << setw(17) << "Total_Peminjaman" << " "
                 << left << setfill(' ') << setw(8) << "Tersedia" << " "
                 << left << setfill(' ') << setw(3) << "Sedang_dipinjam" << " "
                 << endl
                 << "----------------------------------------------------------------------------" << endl

                 << left << setfill(' ') << setw(10) << buku[s].id_buku << " "
                 << left << setfill(' ') << setw(15) << buku[s].judul_buku << " "
                 << left << setfill(' ') << setw(6) << buku[s].stok_buku << " "
                 << left << setfill(' ') << setw(17) << buku[s].total_peminjaman << " "
                 << left << setfill(' ') << setw(8) << buku[s].tersedia << " "
                 << left << setfill(' ') << setw(3) << buku[s].terpinjam << " "
                 << endl;

            cout << "============================================================================" << endl
                 << endl;
        }
    }
}

// membaca file data_buku.txt
void membaca_data_buku_txt()
{
    FILE *fp_data_buku = fopen("data_buku.txt", "r");
    if (!fp_data_buku)
    {
        cout << "File data_buku.txt Gagal Dibuka!!!";
        return;
    }

    // n = jumlah data yang tersimpan di buku[]
    n = 0;
    while (fscanf(fp_data_buku,
                  "%[^|]| %[^|]| %d| %d| %d| %d\n",
                  buku[n].id_buku, buku[n].judul_buku,
                  &buku[n].stok_buku, &buku[n].total_peminjaman,
                  &buku[n].tersedia, &buku[n].terpinjam) != EOF)
    {
        n++;
    };
    fclose(fp_data_buku);
}

// membaca file data_peminjaman.txt
int m; // jumlah data yamg tersimpan di peminjaman[]
void membaca_data_peminjaman_txt(peminjamanBuku *&head, peminjamanBuku *&tail)
{
    FILE *fp_data_peminjaman = fopen("data_peminjaman.txt", "r");
    if (!fp_data_peminjaman)
    {
        cout << "File data_peminjaman.txt Gagal Dibuka!!!";
        return;
    }

    peminjamanBuku *new_node;
    new_node = new peminjamanBuku();

    while (fscanf(fp_data_peminjaman,
                  "%[^|]| %[^|]| %[^|]|\n",
                  new_node->id_peminjam,
                  new_node->nama_peminjam,
                  new_node->id_buku) != EOF)
    {
        new_node->next = NULL;
        // data dimasukkan ke linked list
        if (head == NULL)
        {
            head = new_node;
            tail = head;
        }
        else
        {
            tail->next = new_node;
            tail = new_node;
        }
        // node baru u/ list slanjutnya
        new_node = new peminjamanBuku();
    };
    // hapus node terakhir setelah loop selsai
    delete new_node;

    fclose(fp_data_peminjaman);
}

void peminjaman_buku()
{
    // 1. membaca file data_buku.txt dan simpan data ke buku[]
    membaca_data_buku_txt();
    if (n == 0)
    {
        cout << "\nBelum ada data buku yang tersimpan\n\n";
    }
    else
    {

        // 2. input data peminjaman
        FILE *fp_data_peminjaman = fopen("data_peminjaman.txt", "a");
        if (!fp_data_peminjaman)
        {
            cout << "File data_peminjaman.txt Gagal Dibuka!!!";
            return;
        }

        cout << "\n===== PEMINJAMAN BUKU =====" << endl;
        cout << "ID Anggota  : ";
        cin >> peminjaman[0].id_peminjam;
        cout << "Nama Anggota: ";
        cin.ignore();
        cin.getline(peminjaman[0].nama_peminjam, 20);
        cout << "ID Buku     : ";
        cin >> peminjaman[0].id_buku;
        cout << endl;

        // 3. mencari index buku[] mana yang menyimpan data buku yang ingin dipinjam
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

        if (!found)
        {
            cout << "Buku yang anda cari tidak tersedia\n\n";
            fclose(fp_data_peminjaman);
            return;
        }
        else if (buku[s].tersedia <= 0)
        {
            cout << "Maaf, buku yang anda cari sedang dipinjam semua\n\n";
            fclose(fp_data_peminjaman);
        }

        // 4. apabila di buku[] terdapat data yang ingin dipinjam dan stok buku tersedia
        // 4.1 data peminjaman di tulis ke dalam data_peminjaman.txt
        else
        {
            fprintf(fp_data_peminjaman,
                    "%s| %s| %s|\n",
                    peminjaman[0].id_peminjam,
                    peminjaman[0].nama_peminjam,
                    peminjaman[0].id_buku);

            cout << "Data peminjaman berhasil disimpan!\n\n";
            fclose(fp_data_peminjaman);

            // masukkan data peminjaman ke file riwayat_peminjaman.txt
            FILE *fp_riwayat_peminjaman = fopen("riwayat_peminjaman.txt", "a");
            if (!fp_riwayat_peminjaman)
            {
                cout << "File Riwayat_peminjaman.txt Gagal Dibuka!!!";
                return;
            }
            fprintf(fp_riwayat_peminjaman,
                    "%s| %s| %s|\n",
                    peminjaman[0].id_peminjam,
                    peminjaman[0].nama_peminjam,
                    peminjaman[0].id_buku);

            fclose(fp_riwayat_peminjaman);

            // 4.2 melakukan update mengenai informasi stok buku di data_buku.txt
            buku[s].tersedia--;
            buku[s].terpinjam++;
            buku[s].total_peminjaman++;

            FILE *fp_data_buku = fopen("data_buku.txt", "w");
            if (!fp_data_buku)
            {
                cout << "Belum ada data buku yang tersimpan";
                return;
            }

            for (int i = 0; i < n; i++)
            {
                fprintf(fp_data_buku,
                        "%s| %s| %d| %d| %d| %d\n",
                        buku[i].id_buku, buku[i].judul_buku,
                        buku[i].stok_buku, buku[i].total_peminjaman,
                        buku[i].tersedia, buku[i].terpinjam);
            }
            fclose(fp_data_buku);
        }
    }
}

void hapus_data_peminjaman(peminjamanBuku *&head, char *id_peminjam, char *id_buku, bool &respon_pengembalian)
{
    if (head == NULL)
    {
        respon_pengembalian = false;
        return;
    }

    string kembali_idBuku = id_buku;
    string kembali_idPeminjam = id_peminjam;

    string pinjam_idBuku = head->id_buku;
    string pinjam_idPeminjam = head->id_peminjam;
    // a. cek apakah data tersebut ada di head atau tidak
    if (pinjam_idBuku == kembali_idBuku and pinjam_idPeminjam == kembali_idPeminjam)
    {
        peminjamanBuku *hapus = head;
        head = head->next;
        delete hapus;
        respon_pengembalian = true;
        return;
    }
    // b. jika bukan di head, cari ke node selanjutnya
    peminjamanBuku *temp = head;
    while (temp->next != NULL)
    {
        pinjam_idBuku = temp->next->id_buku;
        pinjam_idPeminjam = temp->next->id_peminjam;

        if (pinjam_idBuku == kembali_idBuku &&
            pinjam_idPeminjam == kembali_idPeminjam)
        {
            respon_pengembalian = true;
            break;
        }
        temp = temp->next;
    }

    // c. data yg di cari tidak ada
    if (temp->next == NULL)
    {
        respon_pengembalian = false;
        return;
    }

    // d. melakukan hapus
    peminjamanBuku *hapus = temp->next;
    temp->next = temp->next->next;
    delete hapus;
}

void pengembalian_buku()
{
    peminjamanBuku *head = NULL;
    peminjamanBuku *tail = NULL;
    bool respon_pengembalian = false;

    // 1. membaca file data_buku.txt dan simpan data di buku[]
    membaca_data_buku_txt();

    // 2. membaca file data_peminjaman.txt dan simpan data di linked list peminjamanBuku
    membaca_data_peminjaman_txt(head, tail);
    if (head == NULL)
    {
        cout << "\nBelum ada peminjaman yang dilakukan\n\n";
    }
    else
    {
        // 3. input data pengembalian buku
        cout << "\n===== PENGEMBALIAN BUKU =====\n";
        cout << "ID Anggota  : ";
        cin >> pengembalian.id_peminjam;
        cout << "ID Buku     : ";
        cin >> pengembalian.id_buku;
        cout << endl;

        // 4. Hapus node yg berisi data pengembalian pada linked list peminjamanBuku
        hapus_data_peminjaman(head, pengembalian.id_peminjam, pengembalian.id_buku, respon_pengembalian);

        // 5. apabila sebelumnya dia tidak melakukan peminjaman
        if (!respon_pengembalian)
        {
            cout << "Tidak ada peminjaman buku tersebutn\n\n";
        }
        // 6. Apabila sebelumnya dia melakukan peminjaman
        else
        {
            // 6.1 Memperbarui informasi stok buku di data_buku.txt
            bool found_2 = false;
            int s2 = 0;
            string temp_benar_id_buku_2;
            while (s2 < n && found_2 == false)
            {
                temp_benar_id_buku_2 = buku[s2].id_buku;

                if (temp_benar_id_buku_2 == pengembalian.id_buku)
                {
                    found_2 = true;
                }
                else
                {
                    s2++; // s = index buku[] yg isinya adalah id_buku yg akan dikembalikan
                }
            }
            if (found_2 == false)
            {
                cout << "Data  buku tidak ditemukan!\n";
                return;
            }

            buku[s2].tersedia++;
            buku[s2].terpinjam--;

            FILE *fp_data_buku = fopen("data_buku.txt", "w");

            if (!fp_data_buku)
            {
                cout << "File data_buku.txt Gagal Dibuka!!!";
                return;
            }

            for (int i = 0; i < n; i++)
            {
                fprintf(fp_data_buku,
                        "%s| %s| %d| %d| %d| %d\n",
                        buku[i].id_buku, buku[i].judul_buku,
                        buku[i].stok_buku, buku[i].total_peminjaman,
                        buku[i].tersedia, buku[i].terpinjam);
            }

            fclose(fp_data_buku);

            // 6.2 Memperbarui data peminjaman di data_peminjaman.txt
            FILE *fp_data_peminjaman = fopen("data_peminjaman.txt", "w");
            if (!fp_data_peminjaman)
            {
                cout << "File data_peminjaman.txt Gagal Dibuka!!!";
                return;
            }

            peminjamanBuku *temp = head;

            while (temp != NULL)
            {
                fprintf(fp_data_peminjaman,
                        "%s| %s| %s|\n",
                        temp->id_peminjam,
                        temp->nama_peminjam,
                        temp->id_buku);
                temp = temp->next;
            }

            cout << "Buku berhasil dikembalikan dan\nData peminjaman berhasil diupdate!\n\n";

            fclose(fp_data_peminjaman);
        }
    }
}

// MENAMPILKAN RIWAYAT PEMINJAMAN
peminjamanBuku *head = NULL;
peminjamanBuku *tail = NULL;

void baca_file_ke_linkedlist();
void tampil_awal_akhir();
void tampil_akhir_awal();
int cek_riwayat_kosong();

void riwayat_peminjaman()
{
    baca_file_ke_linkedlist();
    if (cek_riwayat_kosong() != 0)
    {
        int pilihan;
        cout << "\n1. peminjaman terlama -> terbaru\n";
        cout << "2. peminjaman terbaru -> terlama\n";
        cout << "Pilih: ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 1 || pilihan == 2)
        {
            cout << endl
                 << "==========================================" << endl
                 << "             RIWAYAT TERBARU " << endl
                 << "------------------------------------------" << endl
                 << left << setfill(' ') << setw(15) << "ID_Peminjam" << " "
                 << left << setfill(' ') << setw(15) << "Nama_Peminjam" << " "
                 << left << setfill(' ') << setw(6) << "ID_Buku" << " "
                 << endl
                 << "------------------------------------------" << endl;

            switch (pilihan)
            {
            case 1:
                tampil_awal_akhir();
                break;
            case 2:
                tampil_akhir_awal();
                break;
            }

            cout << "==========================================" << endl
                 << endl;
        }
        else
        {
            cout << "Pilihan tidak valid\n";
            system("pause");
            system("cls");
        }
    }
}

void baca_file_ke_linkedlist()
{
    FILE *fp = fopen("riwayat_peminjaman.txt", "r");
    if (!fp)
    {
        cout << "File riwayat_peminjaman.txt Gagal Dibuka!!!\n";
        return;
    }
    // RESET LINKED LIST
    head = NULL;
    tail = NULL;

    while (true)
    {
        peminjamanBuku *NB = new peminjamanBuku;
        int hasil = fscanf(fp,
                           "%[^|]| %[^|]| %[^|]|\n",
                           NB->id_peminjam,
                           NB->nama_peminjam,
                           NB->id_buku);
        if (hasil != 3)
        {
            delete NB;
            break;
        }

        NB->prev = NULL;
        NB->next = NULL;

        // LINKED LIST KOSONG
        if (head == NULL)
        {
            head = NB;
            tail = NB;
        }
        else
        {
            tail->next = NB;
            NB->prev = tail;
            tail = NB;
        }
    }
    fclose(fp);
}

int cek_riwayat_kosong()
{
    if (head == NULL)
    {
        cout << "\nData kosong! \nBelum ada peminjaman yang dilakukan\n\n";
        return 0;
    }
}

void tampil_awal_akhir()
{
    peminjamanBuku *bantu = head;
    while (bantu != NULL)
    {
        cout << left << setfill(' ') << setw(15) << bantu->id_peminjam << " "
             << left << setfill(' ') << setw(15) << bantu->nama_peminjam << " "
             << left << setfill(' ') << setw(6) << bantu->id_buku << " "
             << endl;
        bantu = bantu->next;
    }
}

void tampil_akhir_awal()
{
    peminjamanBuku *bantu = tail;
    while (bantu != NULL)
    {
        cout << left << setfill(' ') << setw(15) << bantu->id_peminjam << " "
             << left << setfill(' ') << setw(15) << bantu->nama_peminjam << " "
             << left << setfill(' ') << setw(6) << bantu->id_buku << " "
             << endl;
        bantu = bantu->prev;
    }
}