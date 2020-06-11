#include <stdio.h>
#include <string.h>

//tipedata bungkusan untuk data calon penerima sembako
struct Data {
    char namaKepKel[100];   //nama kepala keluarga
    int RT;                 //nomor RT
    int jmlAnggotaKel;      //jumlah anggota keluarga
    int penghasilanKepKel;  //penghasilan
    float ongkosHidupMin;   //ongkos hidup yang merupakan hasil perhitungan dari penghasilan/anggota keluarga
};


//fungsi pengurutan 
void DACQuickSort(int n, struct Data * calonPenerima, int fr, int bk) { 
    //temp var
    int c, d, pivot;
    struct Data e;

    //pengecekan batas
    if (fr < bk) {
        pivot = fr;
        c = fr;
        d = bk;

        //proses pengurutan berdasarkan ongkos hidup
        while (c < d) {
            while ((calonPenerima[c].ongkosHidupMin <= calonPenerima[pivot].ongkosHidupMin) && (c < bk)) {
                ++c;
            }

            while (calonPenerima[d].ongkosHidupMin > calonPenerima[pivot].ongkosHidupMin) {
                --d;
            }

            //pertukaran data
            if (c < d) {
                e = calonPenerima[c];
                calonPenerima[c] = calonPenerima[d];
                calonPenerima[d] = e;
            }
        }

        //pertukaran data
        e = calonPenerima[pivot];
        calonPenerima[pivot] = calonPenerima[d];
        calonPenerima[d] = e;

        //rekursif
        DACQuickSort(n, calonPenerima, fr, d - 1);
        DACQuickSort(n, calonPenerima, d + 1, bk);
    }
}


//fungsi menghitung ongkos hidup minimal (penghasilan/jumlah anggota keluarga)
void hitungOngkosHidupMinimal(struct Data * calonPenerima, int n) {
    int i;

    for (i = 0; i < n; i++) {
        calonPenerima[i].ongkosHidupMin = calonPenerima[i].penghasilanKepKel / calonPenerima[i].jmlAnggotaKel;
    }
}

int main(){
    int i;
    int n = 0;
    int jSembako;

    //array data penerima
    struct Data calonPenerima[200];

    //buka berkas data (.txt)
    FILE *fCalon;
    fCalon = fopen("Data_Calon_Penerima_Sembako.txt", "r");

    //proses membaca data
    fscanf(fCalon, "%s %d %d %d", calonPenerima[n].namaKepKel, &calonPenerima[n].RT,
        &calonPenerima[n].jmlAnggotaKel, &calonPenerima[n].penghasilanKepKel);

    //baca keseluruhan data hingga selesai
    while (strcmp(calonPenerima[n].namaKepKel, "##########") != 0) {
        ++n;
        fscanf(fCalon, "%s %d %d %d", calonPenerima[n].namaKepKel, &calonPenerima[n].RT,
               &calonPenerima[n].jmlAnggotaKel, &calonPenerima[n].penghasilanKepKel);
    }

    //tutup koneksi
    fclose(fCalon);

    if (n == 0) { //jika data kosong
        printf("Tidak ada data!\n");
    } else {
        //buka berkas untuk menyimpan data penerima sembako
        FILE *fhasil;
        fhasil = fopen("Hasil_Penerima_Sembako.txt", "w");

        //menampilkan data calon penerima sembako ke layar
        printf("==================================================================================\n");
        printf("  Data calon penerima sembako:\n");
        printf(" [Nama Kepala Keluarga, RT, Jumlah Anggota Keluarga, Penghasilan Kepala Keluarga]\n");
        printf("==================================================================================\n");

        for (i = 0; i < n; ++i) {
            printf("%s %d %d %d\n", calonPenerima[i].namaKepKel, calonPenerima[i].RT,
                   calonPenerima[i].jmlAnggotaKel, calonPenerima[i].penghasilanKepKel);
        }

        printf("==================================================================================\n\n");

        //meminta masukan sembako yang tersedia
        printf("Jumlah sembako yang tersedia: ");
        scanf("%d", &jSembako);
        printf("\n");

        //proses penghitungan ongkos hidup dan pengurutan data calon penerima
        hitungOngkosHidupMinimal(calonPenerima, n);
        DACQuickSort(n, calonPenerima, 0, n-1);

        //konfirmasi data telah berhasil dibuat
        printf("Hasil berhasil dibuat.\n");

        //proses menuliskan data hasil ke berkas
        fprintf(fhasil,"==================================================================================\n");
        fprintf(fhasil,"  Data penerima sembako tetap:\n");
        fprintf(fhasil," [Nama Kepala Keluarga, RT, Jumlah Anggota Keluarga, Penghasilan Kepala Keluarga]\n");
        fprintf(fhasil,"==================================================================================\n");

        for (i = 0; i < jSembako; ++i)
        {
            fprintf(fhasil,"%s %d %d %d\n", calonPenerima[i].namaKepKel, calonPenerima[i].RT,
                   calonPenerima[i].jmlAnggotaKel, calonPenerima[i].penghasilanKepKel);
        }

        fprintf(fhasil,"==================================================================================\n");
    }

    return 0;
}