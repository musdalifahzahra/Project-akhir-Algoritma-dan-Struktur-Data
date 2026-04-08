#include <iostream>
#include <iomanip>
using namespace std;

struct mus{
    ////musdal
    ////
    ////
    ////
    ///
};

struct dataBuku{
    char id_buku[10];
    char judul_buku[100];
    int stok_buku;
    int total_peminjaman;
    int tersedia;
    int terpinjam;
    
}; dataBuku buku[100];

struct peminjamanBuku{
    char id_buku[10];
    char id_peminjam[10];
    char nama_peminjam[20];
};

void menambahkan_data_buku();
void melihat_daftar_buku();
void peminjaman_buku();
void pengembalian_buku();

int main (){
    int pilihan;
    cout<<"=========================\n";
    cout<<"    Lentera Digital\n";
    cout<<"==========================\n";
    
}
    
void peminjaman_buku(){
    
}