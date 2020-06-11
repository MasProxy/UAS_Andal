#include <stdio.h>
#include <string.h>

struct Data {
    char namaKepKel[100];
    int RT;
    int jmlAnggotaKel;
    int penghasilanKepKel;
    float ongkosHidupMin;
};


void DACQuickSort(int n, struct Data * calonPenerima, int fr, int bk) {
    int c, d, pivot;
    struct Data e;

    if (fr < bk) {
        pivot = fr;
        c = fr;
        d = bk;

        while (c < d) {
            while ((calonPenerima[c].ongkosHidupMin <= calonPenerima[pivot].ongkosHidupMin) && (c < bk)) {
                ++c;
            }

            while (calonPenerima[d].ongkosHidupMin > calonPenerima[pivot].ongkosHidupMin) {
                --d;
            }

            if (c < d) {
                e = calonPenerima[c];
                calonPenerima[c] = calonPenerima[d];
                calonPenerima[d] = e;
            }
        }

        e = calonPenerima[pivot];
        calonPenerima[pivot] = calonPenerima[d];
        calonPenerima[d] = e;

        DACQuickSort(n, calonPenerima, fr, d - 1);
        DACQuickSort(n, calonPenerima, d + 1, bk);
    }
}

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

    struct Data calonPenerima[200];

    FILE *fCalon;
    fCalon = fopen("Data_Calon_Penerima_Sembako.txt", "r");

    fscanf(fCalon, "%s %d %d %d", calonPenerima[n].namaKepKel, &calonPenerima[n].RT,
        &calonPenerima[n].jmlAnggotaKel, &calonPenerima[n].penghasilanKepKel);

    while (strcmp(calonPenerima[n].namaKepKel, "##########") != 0) {
        ++n;
        fscanf(fCalon, "%s %d %d %d", calonPenerima[n].namaKepKel, &calonPenerima[n].RT,
               &calonPenerima[n].jmlAnggotaKel, &calonPenerima[n].penghasilanKepKel);
    }

    fclose(fCalon);

    if (n == 0) {
        printf("Tidak ada data!\n");
    } else {
        printf("==================================================================================\n");
        printf("  Data calon penerima sembako:\n");
        printf(" [Nama Kepala Keluarga, RT, Jumlah Anggota Keluarga, Penghasilan Kepala Keluarga]\n");
        printf("==================================================================================\n");

        for (i = 0; i < n; ++i) {
            printf("%s %d %d %d\n", calonPenerima[i].namaKepKel, calonPenerima[i].RT,
                   calonPenerima[i].jmlAnggotaKel, calonPenerima[i].penghasilanKepKel);
        }

        printf("==================================================================================\n\n");

        printf("Jumlah sembako yang tersedia: ");
        scanf("%d", &jSembako);
        printf("\n");

        hitungOngkosHidupMinimal(calonPenerima, n);
        DACQuickSort(n, calonPenerima, 0, n-1);

        printf("==================================================================================\n");
        printf("  Data penerima sembako tetap:\n");
        printf(" [Nama Kepala Keluarga, RT, Jumlah Anggota Keluarga, Penghasilan Kepala Keluarga]\n");
        printf("==================================================================================\n");

        for (i = 0; i < jSembako; ++i)
        {
            printf("%s %d %d %d\n", calonPenerima[i].namaKepKel, calonPenerima[i].RT,
                   calonPenerima[i].jmlAnggotaKel, calonPenerima[i].penghasilanKepKel);
        }

        printf("==================================================================================\n");
    }

    return 0;
}