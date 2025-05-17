#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <ctype.h>

typedef struct SinhVien {
  char mssv[40];
  char hoten[50];
  char CHUcaiDAU;
  char Danh_Gia[100];
  float diem;
    struct SinhVien* next;
} SinhVien;


//Ham lay chu cai dau trong ten sinh vien:
char chuCaiDau(char *tenRieng) {
    int len = strlen(tenRieng);
    
    //Duyet tu cuoi ve dau de tim dau cach cuoi cung
    for (int i = len - 1; i >= 0; i--) {
        if (tenRieng[i] == ' ') {
            return tenRieng[i + 1];    //Tra ve chu cai dau trong ten
        }
    }

    //Neu khong co dau cach coi toan bo la ten
    return tenRieng[0];
}


//Ham tao 1 sinh vien:
SinhVien* taoSV(char mssv[], char hoten[], float diem) {
    SinhVien* sv = (SinhVien*)malloc(sizeof(SinhVien));     //Cap phat dong 
    strcpy(sv->mssv, mssv);      //
    strcpy(sv->hoten, hoten);    // Chep cac thong tin can thiet khi da nhap thong tin sinh vien
    strcpy(sv->Danh_Gia, "");    //
    sv->CHUcaiDAU = toupper(chuCaiDau(hoten));           //Chuyen chu cai dau trong ten thanh chu in hoa
    sv->diem = diem;
    sv->next = NULL;
    return sv;        // Tra ve ham con tro kieu struct sv
}


//Ham them sinh vien vao cuoi DSLK:
void Them(SinhVien **a,char mssv[],char hoten[],float diem){
	SinhVien* newSV= taoSV(mssv,hoten,diem);       //Cap phat dong va cho newSV quan li con tro duoc luu trong taoSV()
	if (*a == NULL) {
        *a = newSV;     //Neu danh sach trong thi cho con tro a quan li newSV
    } else {
        SinhVien* tmp = *a;
        while (tmp->next != NULL) {
            tmp = tmp->next;
        }
        tmp->next = newSV;
    }
}


//Ham nhap thong tin sinh vien vao DSLK:
void NhapSV(SinhVien **a,int n){
	for (int i=0; i<n; i++){                  // Lap lai "n" lan khi co "n" sinh vien can nhap thong tin
		char mssv[40];
		char hoten[50];
		float diem;
		
		 printf("\nNhap MSSV: ");
        fgets(mssv, sizeof(mssv), stdin);
        mssv[strcspn(mssv, "\n")] = '\0';        //Xoa ki tu xuong dong trong chuoi

        printf("Nhap ho ten: ");
        fgets(hoten, sizeof(hoten), stdin);
        hoten[strcspn(hoten, "\n")] = '\0';

        printf("Nhap diem tong ket: ");
        scanf("%f", &diem);
        getchar();         //Xoa ki tu xuong dong trong bo nho dem
        
		Them(a,mssv,hoten,diem);        //Them sinh vien vao danh sach
	}
	
}


//Ham in thong tin 1 sinh vien:
void in1SinhVien(SinhVien* sv) {
	//In ra man hinh cac thong tin can thiet cua 1 sinh vien
    printf("\nMSSV: %s\n", sv->mssv);
    printf("Ho ten: %s\n", sv->hoten);
    printf("Diem: %.2f\n", sv->diem);
    if (sv->Danh_Gia[0] == '\0')
     printf("Danh_gia_sinh_vien: Trong!!\n");
	else 
     printf("Danh_gia_sinh_vien: %s\n",sv->Danh_Gia);
}

//Ham in DSLK: 
void inDanhSachSinhVien(SinhVien* head) {
    if (head == NULL) {
        printf("\nDANH SACH CHUA CO SINH VIEN NAO.\n");
        return;
    }
    printf("\n=== DANH SACH SINH VIEN ===\n");
    SinhVien* tmp = head;
    while (tmp != NULL) {      //Lap cho den sinh vien cuoi cung trong danh sach
        in1SinhVien(tmp);      //Goi ham in 1 sinh vien
        tmp = tmp->next;       //Di chuyen tmp den quan li node ke tiep trong danh sach  
    }
}


//Ham them sinh vien vao DSLK:
void ThemSV(SinhVien **a){
		char mssv[40];
		char hoten[50];
		float diem;
		 printf("\nNhap MSSV: ");
        fgets(mssv, sizeof(mssv), stdin);
        mssv[strcspn(mssv, "\n")] = '\0';

        printf("Nhap ho ten: ");
        fgets(hoten, sizeof(hoten), stdin);
        hoten[strcspn(hoten, "\n")] = '\0';

        printf("Nhap diem tong ket: ");
        scanf("%f", &diem);
        getchar();
        
        Them(a,mssv,hoten,diem);
}


//Ham tim sinh vien theo ma sinh vien:
void TimSV(SinhVien *a){
	char tim[50];
	printf("Nhap mssv can tim: ");
    getchar();            // loai bo ki tu thua
     fgets(tim, sizeof(tim), stdin);
     tim[strcspn(tim, "\n")] = '\0';           // loai bo '\n'
	SinhVien* tmp = a;
	
    while (tmp != NULL) {
        if (strcmp(tim,tmp->mssv)==0) {
        	in1SinhVien(tmp);
        	return;
		}
        tmp = tmp->next;
    }
    printf("Khong co sinh vien nay.\n");
}


//Ham xoa sinh vien theo ma sinh vien: 
void xoaSinhVienTheoMSSV(SinhVien** a) {
	
	if (*a  == NULL) {
        printf("Danh sach rong. Khong co gi de xoa.\n");
        return;
    }
    
	char xoa[50];
	printf("Nhap mssv can xoa : ");
	getchar();
	fgets(xoa, sizeof(xoa), stdin);
     xoa[strcspn(xoa, "\n")] = '\0';

    SinhVien* tmp = *a;
    SinhVien* truoc = NULL;

    if (strcmp(tmp->mssv, xoa) == 0) {
        *a = tmp->next;
        printf("Da xoa sinh vien co MSSV %s\n", xoa);
        free(tmp);
        return;
    }

    while (tmp != NULL && strcmp(tmp->mssv, xoa) != 0) {
        truoc = tmp;
        tmp = tmp->next;
    }

    if (tmp == NULL) {
        printf("Khong tim thay sinh vien co MSSV %s de xoa.\n", xoa);
        return;
    }
    
    truoc->next = tmp->next;
    free(tmp); 
    
    printf("Da xoa sinh vien co MSSV %s\n", xoa);
}


//Ham tim sinh vien co diem cao nhat: 
void timSinhVienDiemCaoNhat(SinhVien* a) {
    if (a == NULL) {
        printf("Danh sach rong. Khong co sinh vien de tim.\n");
        return;
    }

    float maxDiem = a->diem;
    SinhVien* svMax = a;

    for (SinhVien* p = a->next; p != NULL; p = p->next) {
        if (p->diem > maxDiem) {
            maxDiem = p->diem;
            svMax = p;
        }
    }

    printf("\nSinh vien co diem cao nhat:\n");
    in1SinhVien(svMax);
}


//Ham tach sinh vien ra hai DS dat va  khong dat: 
void tachDanhSach(SinhVien* head, SinhVien** dat, SinhVien** khongdat) {
    while (head != NULL) {
        SinhVien* sv = (SinhVien*)malloc(sizeof(SinhVien));
        *sv = *head;
        sv->next = NULL;

        if (sv->diem >= 5) {
            if (*dat == NULL) *dat = sv;
            else {
                SinhVien* tmp = *dat;
                while (tmp->next) tmp = tmp->next;
                tmp->next = sv;
            }
        } else {
            if (*khongdat == NULL) *khongdat = sv;
            else {
                SinhVien* tmp = *khongdat;
                while (tmp->next) tmp = tmp->next;
                tmp->next = sv;
            }
        }
        head = head->next;
    }
}


//Ham ghi vao file: 
void ghifile_txt(SinhVien* head, char* filename) {
    FILE* f = fopen(filename, "w");
    if (f == NULL) {
        printf("Khong the mo file %s de ghi.\n", filename);
        return;
    }

    while (head != NULL) {
        fprintf(f, "%s\t%s\t%.2f\n", head->mssv, head->hoten, head->diem);
        head = head->next;
    }

    fclose(f);
    printf("Da ghi danh sach vao file %s\n", filename);
}


//Ham dem so sinh vien trong DSLK:
int demSinhVien(SinhVien* head) {
    int count = 0;
    SinhVien* temp = head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}


//Ham tim min diem sinh vien:
float minDiem(SinhVien* head){
	float min = head->diem;
	SinhVien* temp = head;
	while (temp != NULL){
		if (temp->diem < min){
			min = temp->diem;
		}
		temp = temp->next;
	}
	 return min;
}


//Ham tim max diem sinh vien:
float maxDiem(SinhVien* head){
	float max = head->diem;
	SinhVien* temp = head;
	while (temp != NULL){
		if (temp->diem > max){
			max = temp->diem;
		}
		temp = temp->next;
	}
	 return max;
}

//Ham tim min max giua hai so:
float minMax(float a,float b,int x){
	
	//Tim min...
	if (x == 0){
		if (a<b)
		return a; 
		else return b;
	}
	
	//Tim max... 
	if (x == 1){
		if (a>b) 
		return a; 
		else return b;
	}
}

//Ham tim sinh vien trong khoang diem tu c den d:
void timTheoDiemSV(SinhVien *a){
	int dem = 1;
	float d,c;
	printf("Nhap khoang diem muon tim: \n");
	 printf("Tu: ");scanf("%f",&c);
     printf("den: ");scanf("%f",&d);
	if (a == NULL) {
        printf("Danh sach rong. Khong tim thay SV.\n");
        return;
    }
    
    if ( minMax(c,d,1) < minDiem(a) || minMax(c,d,0) > maxDiem(a) )
	    dem = 0;
	    
	        if (dem){
	        	printf("\n---------- CO CAC SINH VIEN LA -----------\n");
	    	while (a != NULL){
    	         if (a->diem >= minMax(c,d,0) && a->diem <= minMax(c,d,1))
    	         in1SinhVien(a);
    	         a = a->next;
	            }
		    } else printf("KHONG CO SINH VIEN NAO CA");
}


//Ham cap nhat sinh vien theo MSSV:
void capNhatSinhVien(SinhVien* head) {
    char mssvCanTim[sizeof(head->mssv)];
    printf("\nNhap MSSV can cap nhat: ");
    scanf("%s", mssvCanTim);

    SinhVien* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->mssv, mssvCanTim) == 0) {
            printf("Nhap ho ten moi: ");
            getchar();              //Xoa ki tu \n trong bo dem
            fgets(temp->hoten, sizeof(temp->hoten), stdin);
            temp->hoten[strcspn(temp->hoten, "\n")] = '\0';

            printf("Nhap diem moi: ");
            scanf("%f", &temp->diem);

            //Cap nhat CHUcaiDAU sau khi doi ten
            temp->CHUcaiDAU = toupper(chuCaiDau(temp->hoten));

            printf("Da cap nhat sinh vien co MSSV: %s\n", mssvCanTim);
            return;
        }
        temp = temp->next;
    }
    printf("Khong tim thay sinh vien co MSSV %s.\n", mssvCanTim);
}

//void swapSinhVien(SinhVien* a, SinhVien* b) {
//    SinhVien temp = *a;  // Luu cac truong trong a v o struct temp
//    *a = *b;             // Gan b cho a
//    *b = temp;           // G n temp (la a cu) cho b
//}
void swapSinhVien(SinhVien* a, SinhVien* b) {
    // Chi hoan doi du lieu, khong hoan doi "next"
    char tempMaSV[40], tempHoTen[50];
    float tempDiem;
    char CHUcaiDAU;
  char Danh_Gia[100];

    strcpy(tempMaSV, a->mssv);
    strcpy(tempHoTen, a->hoten);
    CHUcaiDAU=a->CHUcaiDAU;
    strcpy(Danh_Gia, a->Danh_Gia);
    tempDiem = a->diem;

    strcpy(a->mssv, b->mssv);
    strcpy(a->hoten, b->hoten);
    a->CHUcaiDAU= b->CHUcaiDAU;
    strcpy(a->Danh_Gia, b->Danh_Gia);
    a->diem = b->diem;

    strcpy(b->mssv, tempMaSV);
    strcpy(b->hoten, tempHoTen);
    b->CHUcaiDAU= CHUcaiDAU;
    strcpy(b->Danh_Gia, Danh_Gia);
    b->diem = tempDiem;
}

//Ham sap xep theo diem giam dan:
void sapXepTheoDiemGiamDan(SinhVien* head) {
    if (head == NULL) return;

    SinhVien* i, *j;
    for (i = head; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (i->diem < j->diem) {
                swapSinhVien(i,j);
            }
        }
    }
    inDanhSachSinhVien(head);
}

//Ham sap xep sinh vien theo Alphabet:
void sapXepAlphabet(SinhVien** head){
	int x = demSinhVien(*head);
	char tempName[50];
    char tempKey;

	SinhVien *i,*j;
	for (i = *head; i != NULL;i = i->next){
		for (j = i->next;j != NULL;j = j->next){
			if (i->CHUcaiDAU > j->CHUcaiDAU)
			{
				swapSinhVien(i,j);            //Hoan doi thong tin
			}
		}
	}
}

//Ham danh gia sinh vien:
void DGsinhvien(SinhVien** head) {
    if (*head == NULL) {
        printf("Khong co sinh vien nao de danh gia!!\n");
        return;
    }

    int d;
    int x = demSinhVien(*head);
    
    do {
      printf("Moi nhap so sinh vien can danh gia:\n");
      scanf("%d", &d);
    getchar(); // Xoa ki tu "\n" con lai sau scanf
      if (d > x){
      	printf("Vuot qua so sinh vien trong danh sach. Vui long nhap lai!!\n");
	  }
	} while (d > x);

    while (d--) {
        char mssvCanDanhGia[sizeof((*head)->mssv)];
        SinhVien* temp = NULL;

        // Vong lap nhap den khi tim thay MSSV dung
        while (1) {
            printf("Moi nhap MSSV cua sinh vien can danh gia:\n");
            fgets(mssvCanDanhGia, sizeof(mssvCanDanhGia), stdin);
            mssvCanDanhGia[strcspn(mssvCanDanhGia, "\n")] = '\0'; // X a \n

            // T m sinh vi n
            temp = *head;
            while (temp != NULL) {
                if (strcmp(temp->mssv, mssvCanDanhGia) == 0) {
                    break;
                }
                temp = temp->next;
            }

            if (temp != NULL) break; // Tim thay thi thoat khoi vong lap
            printf("Khong co MSSV nay. Vui long nhap lai!\n");
        }
        
        // Neu tim duoc thi nhap danh gia
        printf("Nhap danh gia: ");
        fgets(temp->Danh_Gia, sizeof(temp->Danh_Gia), stdin);
        temp->Danh_Gia[strcspn(temp->Danh_Gia, "\n")] = '\0'; // Xoa "\n"
    }
}

void GiaiPhongDSLK(SinhVien* a) {
    SinhVien* tmp;
    while (a != NULL) {
        tmp = a;
        a = a->next;
        free(tmp);
    }
}

// MENU 
int Menu(){
	printf("\n================-----MENU-----===================\n");
	printf("| 1.Them sinh vien.                             |\n");
	printf("| 2.Hien thi toan bo sinh vien.                 |\n");
	printf("| 3.Tim kiem sinh vien theo Ma so sinh vien.    |\n");
	printf("| 4.Xoa sinh vien theo Ma so sinh vien.         |\n");
	printf("| 5.Tim sinh vien co diem trung binh cao nhat.  |\n");
	printf("| 6.Tach DS sinh vien dat va khong dat.         |\n");
	printf("| 7.Tim theo khoang diem SV.                    |\n");
	printf("| 8.Cap Nhat Sinh Vien theo ma so sinh vien.    |\n");
	printf("| 9.Sap xep SV theo diem GIAM DAN.              |\n");
	printf("| 10.Sap xep sinh vien theo Alphabet.           |\n");
	printf("| 11.Danh gia sinh vien.                        |\n");
	printf("| 12.Thoat chuong trinh.                        |\n");
	printf("==================================================\n");
	
	int n;
	printf("Moi lua chon: ");
	scanf("%d",&n);
	return n;
}
int main(){
	SinhVien *a = NULL, *dat = NULL, *khongdat = NULL;
	int n;
	float ty_le;
	int choice;
		do{
		choice = Menu();
		switch (choice){
			case 1: 
					printf("Ban muon them bao nhieu sinh vien: ");
					scanf("%d",&n);
					getchar();
					NhapSV(&a,n);
					break;
			case 2:inDanhSachSinhVien(a);
					break;
			case 3:TimSV(a);
					break;
			case 4: xoaSinhVienTheoMSSV(&a);
			        break;
			case 5: timSinhVienDiemCaoNhat(a);
			        break;
			case 6: {
			      tachDanhSach(a,&dat,&khongdat);
			       printf("\n****************** DAT *******************\n");
					inDanhSachSinhVien(dat);
					printf("\n************* KHONG DAT *************\n");
					inDanhSachSinhVien(khongdat);
					int G = demSinhVien(a);
                    if (G != 0) {
                     float ty_le = (float)demSinhVien(dat) / G * 100.0;
                     printf("Ti le dat la: %.2f%%\n", ty_le);
                      printf("Ti le khong dat la: %.2f%%\n", 100.0 - ty_le);
                    } else {
                      printf("Khong co sinh vien nao trong danh sach.\n");
                      }
					dat=NULL;
					khongdat=NULL;
					break;
				}
			case 7: timTheoDiemSV(a);
					break;
			case 8: capNhatSinhVien(a);
					break;
			case 9: {
				    sapXepTheoDiemGiamDan(a);
					
				    break;
			}
			case 10: sapXepAlphabet(&a);
			        break;
			case 11: DGsinhvien(&a);
					break;
			case 12: printf("Da thoat chuong trinh.");
					break;
			default:
                printf("Lua chon khong hop le! Vui long chon lai.\n");
		}
	} while (choice!=12);
	
	GiaiPhongDSLK(a);
	GiaiPhongDSLK(dat);
	GiaiPhongDSLK(khongdat);
	
	return 0;
}
