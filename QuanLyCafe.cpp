#include <stdio.h>
#include <string.h>
#define MAX_DOUONG 100

struct Mon {
    char maDoUong[16];
    char DoUong[51];
    char size;
    int giaTien;
    int trangThai; /* 1 = ConHang, 0 = HetHang */
};

/* KHAI BAO NGUYEN MAU HAM (PROTOTYPE) */
void xoaDongNhap(void);
int kiemTraMa(char ma[], struct Mon ds[], int n);
int kiemTraSize(char size[]);
int kiemTraGia(int gia);
int kiemTraTrangThai(int trangThai);
int nhapMa(struct Mon ds[], int n);
int nhapTen(struct Mon ds[], int n);
int nhapSize(struct Mon ds[], int n);
int nhapGia(struct Mon ds[], int n);
int nhapTrangThai(struct Mon ds[], int n);
int themMon(struct Mon ds[], int n);
void hienThiDanhSach(struct Mon ds[], int n);
void timMon(struct Mon ds[], int n);
int capNhatMon(struct Mon ds[], int n);
int xoaMon(struct Mon ds[], int n);
void hienThiMenu(void);

/* HAM MAIN */
int main(void) {
    /* Mang du lieu Mockdata */
    struct Mon danhSach[MAX_DOUONG] = {
        {"CF01", "Ca phe den", 'S', 20000, 1},
        {"CF02", "Ca phe sua", 'M', 30000, 1},
        {"TS01", "Tra sua tran chau", 'L', 40000, 1},
        {"TE01", "Tra dao", 'M', 35000, 0},
        {"NC01", "Nuoc cam", 'L', 45000, 1}
    };
    int soLuong = 5;

    int luaChon = 0;
    int ketQua = 0;
    while (1) {
        hienThiMenu();
        ketQua = scanf("%d", &luaChon);
        if (ketQua == EOF) return 0;
        xoaDongNhap();
        if (ketQua != 1) {
            printf("Hay nhap so tu 0 den 5.\n");
            continue;
        }
        switch (luaChon) {
            case 1: hienThiDanhSach(danhSach, soLuong); break;
            case 2: soLuong = themMon(danhSach, soLuong); break;
            case 3: timMon(danhSach, soLuong); break;
            case 4: soLuong = capNhatMon(danhSach, soLuong); break;
            case 5: soLuong = xoaMon(danhSach, soLuong); break;
            case 0: printf("Tam biet!\n"); return 0;
            default: printf("Lua chon khong hop le.\n");
        }
    }
}

/*------------ DINH NGHIA CAC HAM ------------*/
/* Bo cac ky tu con lai cua dong vua nhap. */
void xoaDongNhap(void) {
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

/* Moi ham kiem tra tra ve 1 neu hop le, 0 neu khong hop le. */
int kiemTraMa(char ma[], struct Mon ds[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        if (strcmp(ds[i].maDoUong, ma) == 0) {
            return 0;
        }
    }
    return 1;
}

int kiemTraSize(char size[]) {
    if (size[1] == '\0' &&
        (size[0] == 'S' || size[0] == 'M' || size[0] == 'L')) {
        return 1;
    }
    return 0;
}

int kiemTraGia(int gia) {
    if (gia >= 0) {
        return 1;
    }
    return 0;
}

int kiemTraTrangThai(int trangThai) {
    if (trangThai == 0 || trangThai == 1) {
        return 1;
    }
    return 0;
}

/* Cac ham nhap tra ve 0 neu dau vao da ket thuc, 1 neu thanh cong. */
int nhapMa(struct Mon ds[], int n) {
    int hopLe;
    do {
        printf("Ma do uong: ");
        if (scanf("%15s", ds[n].maDoUong) != 1) {
            return 0;
        }
        xoaDongNhap();
        hopLe = kiemTraMa(ds[n].maDoUong, ds, n);
        if (hopLe == 0) {
            printf("Ma da ton tai. Hay nhap ma khac.\n");
        }
    } while (hopLe == 0);
    return 1;
}

int nhapTen(struct Mon ds[], int n) {
    printf("Ten do uong: ");
    /* Doc toi da 50 ky tu, cho phep ten co khoang trang. */
    if (scanf(" %50[^\n]", ds[n].DoUong) != 1) {
        return 0;
    }
    xoaDongNhap();
    return 1;
}

int nhapSize(struct Mon ds[], int n) {
    char sizeNhap[10];
    while (1) {
        printf("Size (S/M/L): ");
        if (scanf("%9s", sizeNhap) != 1) {
            return 0;
        }
        xoaDongNhap();
        if (kiemTraSize(sizeNhap) == 1) {
            ds[n].size = sizeNhap[0];
            return 1;
        }
        printf("Size chi duoc la S, M hoac L.\n");
    }
}

int nhapGia(struct Mon ds[], int n) {
    int gia;
    int ketQua;
    while (1) {
        printf("Gia tien (VND): ");
        ketQua = scanf("%d", &gia);
        if (ketQua == EOF) {
            return 0;
        }
        xoaDongNhap();
        if (ketQua == 1 && kiemTraGia(gia) == 1) {
            ds[n].giaTien = gia;
            return 1;
        }
        printf("Hay nhap so nguyen khong am.\n");
    }
}

int nhapTrangThai(struct Mon ds[], int n) {
    int trangThai;
    int ketQua;
    while (1) {
        printf("Trang thai (1 = ConHang, 0 = HetHang): ");
        ketQua = scanf("%d", &trangThai);
        if (ketQua == EOF) {
            return 0;
        }
        xoaDongNhap();
        if (ketQua == 1 && kiemTraTrangThai(trangThai) == 1) {
            ds[n].trangThai = trangThai;
            return 1;
        }
        printf("Trang thai chi duoc la 0 hoac 1.\n");
    }
}

/* Tra ve so luong moi de main tu cap nhat bien soLuong. */
int themMon(struct Mon ds[], int n) {
    if (n >= MAX_DOUONG) {
        printf("Danh sach da day.\n");
        return n;
    }
    if (nhapMa(ds, n) == 0) return n;
    if (nhapTen(ds, n) == 0) return n;
    if (nhapSize(ds, n) == 0) return n;
    if (nhapGia(ds, n) == 0) return n;
    if (nhapTrangThai(ds, n) == 0) return n;

    printf("Them mon thanh cong!\n");
    return n + 1;
}

void hienThiDanhSach(struct Mon ds[], int n) {
    int i;
    printf("\n%-15s | %-50s | %-4s | %10s | %-10s\n",
           "Ma mon", "Ten mon", "Size", "Gia (VND)", "Trang thai");
    for (i = 0; i < 104; i++) {
        printf("-");
    }
    printf("\n");

    for (i = 0; i < n; i++) {
        printf("%-15s | %-50s | %-4c | %10d | ",
               ds[i].maDoUong, ds[i].DoUong,
               ds[i].size, ds[i].giaTien);
        if (ds[i].trangThai == 1) {
            printf("ConHang\n");
        } else {
            printf("HetHang\n");
        }
    }
    printf("Tong so mon: %d\n", n);
}

void timMon(struct Mon ds[], int n) {
    char tuKhoa[51];
    int i, timThay = 0;
    printf("Nhap ma hoac mot phan ten do uong: ");
    if (scanf(" %50[^\n]", tuKhoa) != 1) return;
    xoaDongNhap();
    for (i = 0; i < n; i++) {
        if (strcmp(ds[i].maDoUong, tuKhoa) == 0 ||
            strstr(ds[i].DoUong, tuKhoa) != NULL) {
            if (!timThay)
                printf("\n%-15s | %-50s | %-4s | %10s | %-10s\n",
                       "Ma mon", "Ten mon", "Size", "Gia (VND)", "Trang thai");
            printf("%-15s | %-50s | %-4c | %10d | %s\n",
                   ds[i].maDoUong, ds[i].DoUong, ds[i].size, ds[i].giaTien,
                   ds[i].trangThai == 1 ? "ConHang" : "HetHang");
            timThay = 1;
        }
    }
    if (!timThay) printf("Khong tim thay do uong.\n");
}

int capNhatMon(struct Mon ds[], int n) {
    char ma[16], tenMoi[51], sizeNhap[10];
    int i, viTri = -1, gia, trangThai, ketQua;
    printf("Nhap ma do uong can cap nhat: ");
    if (scanf("%15s", ma) != 1) return n;
    xoaDongNhap();
    for (i = 0; i < n; i++)
        if (strcmp(ds[i].maDoUong, ma) == 0) { viTri = i; break; }
    if (viTri == -1) {
        printf("Khong tim thay ma do uong nay.\n");
        return n;
    }
    
      printf("Ten moi: ");
    if (scanf(" %50[^\n]", tenMoi) != 1) return n;
    xoaDongNhap();
    do {
        printf("Size moi (S/M/L): ");
        if (scanf("%9s", sizeNhap) != 1) return n;
        xoaDongNhap();
        if (!kiemTraSize(sizeNhap)) printf("Size chi duoc la S, M hoac L.\n");
    } while (!kiemTraSize(sizeNhap));
    
    while (1) {
        printf("Gia tien moi (VND): ");
        ketQua = scanf("%d", &gia);
        if (ketQua == EOF) return n;
        xoaDongNhap();
        if (ketQua == 1 && kiemTraGia(gia)) break;
        printf("Hay nhap so nguyen khong am.\n");
    }
    while (1) {
        printf("Trang thai moi (1 = ConHang, 0 = HetHang): ");
        ketQua = scanf("%d", &trangThai);
        if (ketQua == EOF) return n;
        xoaDongNhap();
        if (ketQua == 1 && kiemTraTrangThai(trangThai)) break;
        printf("Trang thai chi duoc la 0 hoac 1.\n");
    }
    strcpy(ds[viTri].DoUong, tenMoi);
    ds[viTri].size = sizeNhap[0];
    ds[viTri].giaTien = gia;
    ds[viTri].trangThai = trangThai;
    printf("Cap nhat do uong thanh cong!\n");
    return n;
}

int xoaMon(struct Mon ds[], int n) {
    char ma[16];
    int i, viTri = -1;
    printf("Nhap ma do uong can xoa: ");
    if (scanf("%15s", ma) != 1) return n;
    xoaDongNhap();
    for (i = 0; i < n; i++)
        if (strcmp(ds[i].maDoUong, ma) == 0) { viTri = i; break; }
    if (viTri == -1) {
        printf("Khong tim thay ma do uong nay.\n");
        return n;
    }
    for (i = viTri; i < n - 1; i++) ds[i] = ds[i + 1];
    printf("Xoa san pham thanh cong!\n");
    return n - 1;
}

void hienThiMenu(void) {
    printf("\n===== QUAN LY QUAN CAFE =====\n");
    printf("1. Hien thi danh sach\n");
    printf("2. Them mon\n");
    printf("3. Tim do uong\n");
    printf("4. Cap nhat do uong\n");
    printf("5. Xoa san pham\n");
    printf("0. Thoat\n");
    printf("Lua chon: ");
}