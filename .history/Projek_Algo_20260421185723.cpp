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

    peminjamanBuku *next;
};

// ++++ mau pake linked list ++++
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

FILE *fptr = fopen("data_buku.txt", "a");
dataBuku *ptr = buku;
int pilihan, jumlahData = 0;

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
        cout << "6. Keluar\n";
        cout << setw(30) << setfill('=') << "" << endl;
        cout << "Pilih menu (1-6): ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan)
        {
        case 1:
        {
            menambahkan_data_buku(ptr, jumlahData);
            break;
        }
        case 2:
        {
            melihat_daftar_buku(ptr, jumlahData);
            break;
        }
        case 3:
        {
            cari_buku();
            break;
        }
        case 4:
        {
            peminjaman_buku();
            break;
        }
        case 5:
        {
            pengembalian_buku();
            break;
        }
        case 6:
        {
            cout << "Terima Kasih Telah menggunakan program ini!:>\n";
            break;
        }
        default:
        {
            cout << "Pilihan tidak ada!\n";
        }
        }
    } while (pilihan != 6);
}

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
        fprintf(fptr, "%s| %s| %d| %d| %d| %d\n",
                (ptr + jumlah - 1)->id_buku, (ptr + jumlah - 1)->judul_buku,
                (ptr + jumlah - 1)->stok_buku, (ptr + jumlah - 1)->total_peminjaman,
                (ptr + jumlah - 1)->tersedia, (ptr + jumlah - 1)->terpinjam);
        fclose(fptr);
    }
}

//////tambah data buku leeeeeeee
void menambahkan_data_buku(dataBuku *ptr, int &jumlah)
{
    cout << "ID Buku            : ";
    // cin.ignore();
    cin.getline((ptr + jumlah)->id_buku, 10);

    cout << "Judul Buku         : ";
    cin.getline((ptr + jumlah)->judul_buku, 100);

    cout << "Stok buku          : ";
    cin >> ((ptr + jumlah)->stok_buku);

    (ptr + jumlah)->total_peminjaman = 0;
    (ptr + jumlah)->tersedia = (ptr + jumlah)->stok_buku;
    (ptr + jumlah)->terpinjam = 0;

    // cout << "Total peminjaman   : ";
    // cin >> ((ptr + jumlah)->total_peminjaman);

    // cout << "Total yang tersedia: ";
    // cin >> ((ptr + jumlah)->tersedia);

    // cout << "Total yang terpinjam: ";
    // cin >> ((ptr + jumlah)->terpinjam);

    // dreeyyyyy maaapp, mau cek bentarrrrr,
    // ini yg bawah punya km gk ak apa apa iiiinnn, cuma komenin doanggggg

    // cout << setfill(' ');
    // cout << "=== TAMBAH DATA LUKISAN ===\n";
    // cout << left << setw(15) << "ID Buku " << ": "; cin.ignore();
    // cin.getline((ptr + jumlah)->id_buku, 10);
    // cout << left << setw(15) << "Judul Buku" << ": ";
    // cin.getline((ptr + jumlah)->judul_buku, 100);
    // cout << left << setw(15) << "Stok Buku" << ": ";
    // cin >> ((ptr + jumlah)->stok_buku);
    // cout << left << setw(15) << "Total yang tersedia" << ": ";
    // cin >> ((ptr + jumlah)->tersedia);
    // cout << left << setw(15) << "Total yang terpinjam" << ": ";
    // cin >> ((ptr + jumlah)->terpinjam);
    // cout << endl;
    jumlah++;
    simpan_data(ptr, jumlah);
    cout << "Data berhasil ditambahkan!\n";
    system("pause");
    system("cls");
}

/// melihat daftar buku
void melihat_daftar_buku(dataBuku *ptr, int &jumlah)
{
    cout << setfill(' ');
    fptr = fopen("data_buku.txt", "r");
    if (fptr == NULL)
    {
        cout << "Data masih kosong!\n";
        system("pause");
        system("cls");
        return;
    }
    jumlahData = 0;
    while (fscanf(fptr, "%[^|]| %[^|]| %d| %d| %d| %d\n",
                  buku[jumlahData].id_buku, buku[jumlahData].judul_buku,
                  &buku[jumlahData].stok_buku, &buku[jumlahData].total_peminjaman,
                  &buku[jumlahData].tersedia, &buku[jumlahData].terpinjam) != EOF)
    {
        jumlahData++;
    }
    fclose(fptr);
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
    cout << "========= DATA BUKU ========\n"; // 30
    // DREEEYY MAAAPPPP, CEK BENTARR
    //  cout << left << setw(5) << "No" << setw(15) << "ID Buku " << setw(35) << "Nama Buku" << setw(25) << "Stok Buku\n";
    cout << left << setfill(' ') << setw(3) << "No." << " "
         << left << setfill(' ') << setw(10) << "ID buku" << " "
         << left << setfill(' ') << setw(15) << "judul" << " "
         << left << setfill(' ') << setw(6) << "stok" << " "
         << left << setfill(' ') << setw(17) << "Total Peminjaman" << " "
         << left << setfill(' ') << setw(8) << "Tersedia" << " "
         << left << setfill(' ') << setw(3) << "Sedang dipinjam" << " "
         << endl;
    for (int i = 0; i < jumlahData; i++)
    {
        cout << left << setfill(' ') << setw(3) << i + 1 << " "
             << left << setfill(' ') << setw(10) << buku[i].id_buku << " "
             << left << setfill(' ') << setw(15) << buku[i].judul_buku << " "
             << left << setfill(' ') << setw(6) << buku[i].stok_buku << " "
             << left << setfill(' ') << setw(17) << buku[i].total_peminjaman << " "
             << left << setfill(' ') << setw(8) << buku[i].tersedia << " "
             << left << setfill(' ') << setw(3) << buku[i].terpinjam << " "
             << endl;

        // DREEEYY MAAAPPPP, CEK BENTARR
        //  cout << left << setw(5) << i + 1 << setw(15) << buku[i].id_buku << setw(35) << buku[i].judul_buku << setw(25) << buku[i].stok_buku << endl;
    }
    system("pause");
    system("cls");
}

// DREEEY AK G NGERTI POINTER KMU, JADI AK G PAKE POOINTER DULU YY, NTR AKHIR AK UBAH
//  void cari_buku(dataBuku *ptr, int &jumlah)
//  {
//  }

void membaca_data_buku_txt();
int n; // jumlah data yang tersimpan di buku[]
void cari_buku()
{
    membaca_data_buku_txt();

    // Input nama buku yang dicari
    string cari;
    cout << "======= CARI DATA BUKU =======" << endl
         << "Masukkan Judul dengan huruf kapital di awal setiap kata (contoh: Musdalifah Zah Yhahaha)" << endl
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
             << left << setfill(' ') << setw(17) << "Total Peminjaman" << " "
             << left << setfill(' ') << setw(8) << "Tersedia" << " "
             << left << setfill(' ') << setw(3) << "Sedang dipinjam" << " "
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

// musdal
// membaca file data_buku.txt
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
void membaca_data_peminjaman_txt(peminjamanBuku *head, peminjamanBuku *tail)
{
    FILE *fp_data_peminjaman = fopen("data_peminjaman.txt", "r");
    if (!fp_data_peminjaman)
    {
        cout << "Belum ada data peminjaman";
        return;
    }

    /*++++++++++++++ awal SEBELUM LINKED baca peminjaman++++++++++
    // m = jumlah data yang tersimpan di peminjaman[]
    m = 0;
    while (fscanf(fp_data_peminjaman,
                  "%[^|]| %[^|]| %[^|]|\n",
                  peminjaman[m].id_peminjam,
                  peminjaman[m].nama_peminjam,
                  peminjaman[m].id_buku) != EOF)
    {
        m++;
    };
    +++++++++++++++ akhir SEBELUM LINKED baca peminjaman +++++++++*/

    //++++++++++++++ awal SETELAH LINKED baca peminjaman++++++++++

    peminjamanBuku *new_node;
    new_node = new peminjamanBuku();

    while (fscanf(fp_data_peminjaman,
                  "%[^|]| %[^|]| %[^|]|\n",
                  new_node->id_peminjam,
                  new_node->nama_peminjam,
                  new_node->id_buku) != EOF)
    {
        new_node->next = NULL;
        // masukan ke  linked
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
    // hapus node trakir setelah loop selsai
    delete new_node;
    //+++++++++++++++ akhir SETELAH LINKED baca peminjaman +++++++++

    fclose(fp_data_peminjaman);
}

void peminjaman_buku()
{
    // 1. membaca file data_buku.txt dan simpan data ke buku[]
    membaca_data_buku_txt();

    // 2. input data peminjaman
    FILE *fp_data_peminjaman = fopen("data_peminjaman.txt", "a");
    if (!fp_data_peminjaman)
    {
        cout << "Belum ada data peminjaman buku";
        return;
    }

    // ++++++++++++++++++++++ SEBELUM LINKED LIST ++++++++++++++++++++++++++++++++++++++++++
    // cout << "===== PEMINJAMAN BUKU =====" << endl;
    // cout << "ID Anggota  : ";
    // cin >> peminjaman[0].id_peminjam;
    // cout << "Nama Anggota: ";
    // cin.ignore();
    // cin.getline(peminjaman[0].nama_peminjam, 20);
    // cout << "ID Buku     : ";
    // cin >> peminjaman[0].id_buku;
    // cout << endl;

    // ++++++++++++++++++++++ SETELAHH LINKED LIST ++++++++++++++++++++++++++++++++++++++++++
    peminjamanBuku *head = NULL;
    peminjamanBuku *new_node;        // dekla var pointer
    new_node = new peminjamanBuku(); // membuat object struct peminjamanBuku di memo, lalu alamatnya akan disimpan di pointer new_node

    // pengisian new_node

    cout << "===== PEMINJAMAN BUKU =====" << endl;
    cout << "ID Anggota  : ";
    cin >> new_node->id_peminjam;
    cout << "Nama Anggota: ";
    cin.ignore();
    cin.getline(new_node->nama_peminjam, 20);
    cout << "ID Buku     : ";
    cin >> new_node->id_buku;
    cout << endl;

    new_node->next = NULL;

    if (head == NULL)
    {
        head = new_node;
    }
    else
    {
        peminjamanBuku *temp = head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = new_node;
    }
    // ++++++++++++++++++++++ akhir SETELAHH LINKED LIST ++++++++++++++++++++++++++++++++++++++++++

    /* +++++++++++++++++++++  SEBELUM LINKED mencari index buku[] +++++++++++++++++++++++++++++++++
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

    +++++++++++++++++++++  akhir SEBELUM LINKED mencari index buku[] +++++++++++++++++++++++++++++++++*/

    // +++++++++++++++++++++  awal SETELAH LINKED mencari index buku[] +++++++++++++++++++++++++++++++++
    // 3. mencari index buku[] mana yang menyimpan data buku yang ingin dipinjam
    bool found = false;
    int s = 0;
    string temp_id_buku = new_node->id_buku;
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
        cout << endl
             << "Buku yang anda cari tidak tersedia" << endl;
        fclose(fp_data_peminjaman);
        return;
    }
    else if (buku[s].tersedia == 0)
    {
        cout << "Maaf, stok buku yang anda cari sedang dipinjam semua" << endl; // bikinin kat kata yg indah
        fclose(fp_data_peminjaman);
    }
    // +++++++++++++++++++++  akhir SETELAH LINKED mencari index buku[] +++++++++++++++++++++++++++++++++

    /*+++++++++++++++++++++  awal SEBELUM LINKED  data yang ingin dipinjam  tersedia +++++++++++++++++++++++++++++++++
        // 4. apabila di buku[] terdapat data yang ingin dipinjam dan stok buku tersedia
        // 4.1 data peminjaman di tulis ke dalam data_peminjaman.txt
        else
        {
            fprintf(fp_data_peminjaman,
                    "%s| %s| %s|\n",
                    peminjaman[0].id_peminjam,
                    peminjaman[0].nama_peminjam,
                    peminjaman[0].id_buku);

            cout << "Data peminjaman berhasil disimpan!" << endl;
            fclose(fp_data_peminjaman);

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
    +++++++++++++++++++++  akhir SEBELUM LINKED  data yang ingin dipinjam  tersedia +++++++++++++++++++++++++++++++++*/

    //+++++++++++++++++++++  awal SETELAH LINKED  data yang ingin dipinjam  tersedia +++++++++++++++++++++++++++++++++
    // 4. apabila di buku[] terdapat data yang ingin dipinjam dan stok buku tersedia
    // 4.1 data peminjaman di tulis ke dalam data_peminjaman.txt
    else
    {
        fprintf(fp_data_peminjaman,
                "%s| %s| %s|\n",
                new_node->id_peminjam,
                new_node->nama_peminjam,
                new_node->id_buku);

        cout << "Data peminjaman berhasil disimpan!" << endl;
        fclose(fp_data_peminjaman);

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
    //+++++++++++++++++++++  akhir SETELAH LINKED  data yang ingin dipinjam  tersedia +++++++++++++++++++++++++++++++++
}
// end void peminjaman buku

void hapus_data_peminjaman(peminjamanBuku *head, char *id_peminjam, char *id_buku)
{
    if (head == NULL)
        return;
    
    string pengembalian_idBuku = id_buku;
    string pengembalian_idPeminjam = id_peminjam;
    
    string peminjaman_idBuku = head->
    // a. cek apakah data tersebut ada di head atau tidak

    // b. jika bukan di head, cari ke node selanjutnya
    // c. data yg di cari tidak ada
}

void pengembalian_buku()
{

    peminjamanBuku *head = NULL;
    peminjamanBuku *tail = NULL;
    // 1. membaca file data_buku.txt dan simpan data di buku[]
    membaca_data_buku_txt();

    // 2. membaca file data_peminjaman.txt dan simpan data di peminjaman[]
    membaca_data_peminjaman_txt(head, tail);

    // 3. input data pengembalian buku
    cout << "===== PENGEMBALIAN BUKU =====" << endl;
    cout << "ID Anggota  : ";
    cin >> pengembalian.id_peminjam;
    cout << "ID Buku     : ";
    cin >> pengembalian.id_buku;
    cout << endl;

    hapus_data_peminjaman(head, pengembalian.id_peminjam, pengembalian.id_buku);

    /* ++++++++++++++ awal SEBELUM LINKED hapus data peminnjaman ++++++++++++++++++
    // 4. cari data pengembalian buku di file data_peninjaman.txt u/ cek apakah sebelumnya dia melakukan peminjaman atau tidak
    bool found = false;
    int s = 0;
    string temp_benar_id_buku;
    string temp_benar_id_peminjam;
    while (s < m && found == false)
    {
        temp_benar_id_buku = peminjaman[s].id_buku;
        temp_benar_id_peminjam = peminjaman[s].id_peminjam;

        if (temp_benar_id_buku == pengembalian.id_buku && temp_benar_id_peminjam == pengembalian.id_peminjam)
        {
            found = true;
        }
        else
        {
            s++; // s = index(peminjaman[]) yg isinya adalah id_buku yg akan dikembalikan
        }
    }

    if (!found)
    {
        cout << endl
             << "Tidak ada peminjaman buku yang dilakukan" << endl;
        return;
    }

    // 5. apabila sebelumnya dia melakukan peminjaman
    // 5.1 memperbarui informasi stok buku di data_buku.txt
    else
    {
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

     // JANGAN LUPA UPDATE DATA DI FILE data_buku.txt
        buku[s2].tersedia++;
        buku[s2].terpinjam--;

        FILE *fp_data_buku = fopen("data_buku.txt", "w");

        for (int i = 0; i < n; i++)
        {
            fprintf(fp_data_buku,
                    "%s| %s| %d| %d| %d| %d\n",
                    buku[i].id_buku, buku[i].judul_buku,
                    buku[i].stok_buku, buku[i].total_peminjaman,
                    buku[i].tersedia, buku[i].terpinjam);
        }

        fclose(fp_data_buku);

        // 5.2 memperbarui data peminjaman di data_peminjaman.txt
        for (int i = s2; i < m; i++)
        {
            peminjaman[i] = peminjaman[i + 1];
        }
        m--;

        FILE *fp_data_peminjaman = fopen("data_peminjaman.txt", "w");
        if (!fp_data_peminjaman)
        {
            cout << "Belum ada data peminjaman yang tersimpan";
            return;
        }

        for (int i = 0; i < m; i++)
        {
            fprintf(fp_data_peminjaman,
                    "%s| %s| %s|\n",
                    peminjaman[i].id_peminjam,
                    peminjaman[i].nama_peminjam,
                    peminjaman[i].id_buku);
        }

        cout << "Data peminjaman berhasil diupdate!" << endl;

        fclose(fp_data_peminjaman);
    }
       ++++++++++++++ akhir SEBELUM LINKED hapus data peminnjaman ++++++++++++++++++ */
}
